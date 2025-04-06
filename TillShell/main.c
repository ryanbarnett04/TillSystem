#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "sqlite3.h"
#include <Windows.h>
#include <tlhelp32.h>

// FUNCTION DEFINITIONS
void shell_loop(void);
char* shell_read_line(void);
char** shell_tokenize(char* line);
int shell_execute(char** args);
int shell_num_builtins(void);
int shell_help(char** args);
int shell_exit(char** args);
int shell_add_employee(char** args);
int shell_show_employees(char** args);
int shell_find_employee_by_name(char** args);
int shell_find_employee_by_number(char** args);
int shell_find_employee_by_role(char** args);
int shell_launch(char** args);
bool executeQuery(const char* query);
char* showEmployees(const char* query);


// BUILTIN COMMANDS
char* builtin_str[] = {
	"help",
	"exit",
	"addemp",
	"showemps",
	"findempna",
	"findempnu",
	"findempr"
};

// FUNCTION POINTERS
int (*builtin_func[]) (char**) = {
	&shell_help,
	&shell_exit,
	&shell_add_employee,
	&shell_show_employees,
	&shell_find_employee_by_name,
	&shell_find_employee_by_number,
	&shell_find_employee_by_role
};

// NUMBER OF BUILTIN COMMANDS
int shell_num_builtins(void) {
	return sizeof(builtin_str) / sizeof(char *);
}

// BUILTIN IMPLEMENTATIONS
int shell_help(char** args) {
	int i;
	printf("Shell for interfacing with the Till's database\n");
	printf("Type command name and arguments then press enter\n");
	printf("The following are built in:\n");

	for (i = 0; i < shell_num_builtins(); i++) {
		printf("  %s\n", builtin_str[i]);
	}

	printf("Follow a command with 'usage' for info on how to use the command\n");
	return 1;
}


int shell_exit(char** args) {
	return EXIT_SUCCESS;
}


int shell_add_employee(char** args) {
	int count = 0;
	while (args[count] != NULL) {
		count++;
	}

	if (count - 1 != 3) {
		printf("INCORRECT NUMBER OF ARGUMENTS, EXPECTS THREE ARGUMENTS [NAME] & [NUMBER] & [ROLE]\n");
		return 1;
	}
	else {

		char* name = args[1];
		char* num_str = args[2];
		int num = atoi(num_str);
		char* role = args[3];
		char sql[256];
		snprintf(sql, sizeof(sql), "INSERT INTO employees (NAME, NUMBER, ROLE) VALUES ('%s', %d, '%s')", name, num, role);
		bool result = executeQuery(sql);

		if (result == false) {
			printf("FAILED QUERY EXECUTION\n");
		}
		else {
			printf("SUCCESSFUL QUERY EXECUTION\n");
		}

		return 1;
	}
}


int shell_show_employees(char** args) {
	int count = 0;
	while (args[count] != NULL) {
		count++;
	}

	if (count != 1) {
		printf("COMMAND DOES NOT ACCEPT ARGUMENTS\n");
		return 1;
	}

	const char* sql = "SELECT * FROM employees;";
	char* result = showEmployees(sql);
	printf("%s\n", result);
	free(result);
	return 1;
}


int shell_find_employee_by_name(char** args) {
	int count = 0;
	while (args[count] != NULL) {
		count++;
	}

	if (count - 1 != 1) {
		printf("INCORRECT NUMBER OF ARGUMENTS, COMMAND EXPECTS ONE ARGUMENT [NAME]\n");
		return 1;
	}

	char sql[256];
	snprintf(sql, sizeof(sql), "SELECT * FROM employees WHERE NAME LIKE '%%%s%%';", args[1]);
	char* result = showEmployees(sql);
	printf("%s\n", result);
	free(result);
	return 1;
}


int shell_find_employee_by_number(char** args) {
	int count = 0;
	while (args[count] != NULL) {
		count++;
	}

	if (count - 1 != 1) {
		printf("COMMAND EXPECTS ONE ARGUMENT [NUMBER]\n");
		return 1;
	}

	char sql[256];
	int num = atoi(args[1]);
	snprintf(sql, sizeof(sql), "SELECT * FROM employees WHERE NUMBER = %d;", num);
	char* result = showEmployees(sql);
	printf("%s\n", result);
	free(result);
	return 1;
}


int shell_find_employee_by_role(char** args) {
	int count = 0;
	while (args[count] != NULL) {
		count++;
	}

	if (count - 1 != 1) {
		printf("COMMAND EXPECTS ONE ARGUMENT [ROLE]\n");
		return 1;
	}

	if (!strcmp(args[1], "Barista") == 0 && !strcmp(args[1], "Barista Maestro") == 0 && !strcmp(args[1], "Store Manager") == 0 && !strcmp(args[1], "Area Manager") == 0) {
		printf("Invalid role given, roles are 'Barista', 'Barista Maestro', 'Store Manager' or 'Area Manager'\n");
		return 1;
	}

	char sql[256];
	snprintf(sql, sizeof(sql), "SELECT * FROM employees WHERE ROLE = '%s';", args[1]);
	char* result = showEmployees(sql);
	printf("%s\n", result);
	free(result);
	return 1;
}


int shell_launch(char** args) {
	char app[256];  
	strncpy_s(app, sizeof(app), args[0], _TRUNCATE);

	if (strstr(app, ".exe") == NULL) {  
		strcat_s(app, sizeof(app), ".exe");
	}

	int wideSize = MultiByteToWideChar(CP_ACP, 0, app, -1, NULL, 0);
	wchar_t wideApp[256];
	MultiByteToWideChar(CP_ACP, 0, app, -1, wideApp, wideSize);

	HINSTANCE result = ShellExecute(NULL, L"open", wideApp, NULL, NULL, SW_SHOWNORMAL);
	if ((INT_PTR)result <= 32) {
		DWORD error = GetLastError();
		fprintf(stderr, "Application can't be found or doesn't exist\n");
	}

	return 1;
}

sqlite3* db;

// SHELL METHODS
int main(int argc, char** argv) {

	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	Process32First(snapshot, &pe32);

	do {
		if (wcscmp(pe32.szExeFile, L"TillSystem.exe") == 0) {
			MessageBoxW(NULL, L"Please ensure till is closed in order to run shell", L"Message", MB_OK);
			exit(EXIT_FAILURE);
		}
	} while (Process32Next(snapshot, &pe32));

	const char* db_path = "C:\\Users\\Ryan\\source\\repos\\TillSystem\\TillSystem\\database.db";

	if (sqlite3_open(db_path, &db) != SQLITE_OK) {
		fprintf(stderr, "ERROR OPENING DATABASE");
		return EXIT_FAILURE;
	}

	printf("DATABASE CONNECTED!\n");

	shell_loop();

	return EXIT_SUCCESS;
}


void shell_loop(void) {

	char* line;
	char** args;
	int status;

	do {
		printf("> ");
		line = shell_read_line();
		args = shell_tokenize(line);
		status = shell_execute(args);

		free(line);
		free(args);

	} while (status);

}


#define READLINE_BUFSIZE 1024
char* shell_read_line(void) {
	int bufsize = READLINE_BUFSIZE;
	int position = 0;
	char* buffer = malloc(sizeof(char) * bufsize);
	int c;

	if (!buffer) {
		fprintf(stderr, "MEMORY ALLOCATION ERROR");
		exit(EXIT_FAILURE);
	}

	while (1) {
		c = getchar();

		if (c == EOF || c == '\n') {
			buffer[position] = '\0';
			return buffer;
		}
		else {
			buffer[position] = c;
		}

		position++;

		if (position >= bufsize) {
			bufsize += READLINE_BUFSIZE;
			buffer = realloc(buffer, bufsize);
			if (!buffer) {
				fprintf(stderr, "MEMORY ALLOCATION ERROR");
				exit(EXIT_FAILURE);
			}
		}
	}
}


#define TOKENIZE_BUFSIZE 64
#define TOKENIZE_DELIMITERS " \t\r\n\a"
char** shell_tokenize(char* line) {
	int bufsize = TOKENIZE_BUFSIZE;															// Set initial buffer size
	int position = 0;																		// Position in Char** tokens
	char** tokens = malloc(bufsize * sizeof(char*));										// Allocate memory for the tokens
	if (!tokens) {																			// Exit if there was an error allocating memory
		fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
		exit(EXIT_FAILURE);
	}

	int i = 0;																				// Index of the input line, start at 0 to read first character in string
	while (line[i] != '\0') {																// While character 'i' is not a null terminator

		while (line[i] && strchr(TOKENIZE_DELIMITERS, line[i])) {							// Skip any leading whitespace using the delimiters
			i++;																			// Increment index to skip delimiter characters
		}

		if (line[i] == '\0')																// Once the first valid character is reached, check if it's a null terminator												
			break;																			// Exit loop

		char* token = NULL;																	// Initialise token
		int start = i;																		// Set the starting character of the token to 'i'


		if (line[i] == '\"' || line[i] == '\'') {											// Check if the character is a quote
			char quote = line[i];															// Set char quote to the quote so the type of quote is saved
			i++;																			// Increment to skip the opening quote as it should not be apart of the token
			start = i;																		// Mark the token start right after the quote


			while (line[i] && line[i] != quote) {											// Move 'i' through the string until the matching closing quote is found
				i++;																		// While 'i' is not the quote, increment
			}

			int length = i - start;															// Calculate the length of the token by subtracting the start index in the string from the current index

			token = malloc(length + 1);														// Allocate memory for the token equal to length + 1, the +1 is so a null terminator can be added at the end

			if (!token) {																	// If memory allocation failed, exit
				fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
				exit(EXIT_FAILURE);
			}

			if (strncpy_s(token, length + 1, &line[start], length) != 0) {					// Strncpy to copy a set amount of characters from the string into the token, exit if this fails
				fprintf(stderr, "String copy error\n");
				exit(EXIT_FAILURE);
			}

			token[length] = '\0';															// Strncpy should null terminate the string, but overwriting it here just to make sure

			if (line[i] == quote) {
				i++;																		// Skip the closing quote
			}

		} else {

			while (line[i] && !strchr(TOKENIZE_DELIMITERS, line[i])) {						// For unquoted tokens, copy while the character is not in the delimiter set
				i++;
			}

			int length = i - start;															// Same as before to determine token length

			token = malloc(length + 1);														// Allocate memory

			if (!token) {																	// Exit if memory allocation failed
				fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
				exit(EXIT_FAILURE);
			}

			if (strncpy_s(token, length + 1, &line[start], length) != 0) {					// Copy into token length amount of characters starting from line[start], exit if fails
				fprintf(stderr, "String copy error\n");
				exit(EXIT_FAILURE);
			}

			token[length] = '\0';															// Null terminate
		}

		tokens[position] = token;															// Add the token to the position in the tokens array
		position++;																			// Increment the position index, if there is still space in memory, at this point return to top while loop

		if (position >= bufsize) {															// Reallocate memory for the tokens array if it's reached it's limit
			bufsize += TOKENIZE_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char*));

			if (!tokens) {																	// Exit if memory allocation fails, else code returns to top level while loop
				fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
				exit(EXIT_FAILURE);
			}
		}
	}

	tokens[position] = NULL;																// Once line[i] does equal a null terminator, set the last element of the tokens array to null
	return tokens;																			// Return the tokens
}


int shell_execute(char **args) {
	int i;

	if (args[0] == NULL) {
		printf("Enter an command\n");
		return 1;
	}

	for (i = 0; i < shell_num_builtins(); i++) {
		if (strcmp(args[0], builtin_str[i]) == 0) {
			return (*builtin_func[i])(args);
		}
	}

	shell_launch(args);

	return 1;
}


// DATABASE METHODS
bool executeQuery(const char* query) {
	char* errorMessage;
	if (sqlite3_exec(db, query, NULL, NULL, &errorMessage) != SQLITE_OK) {
		printf(errorMessage + '\n');
		sqlite3_free(errorMessage);
		return false;
	}
	return true;
}


char* showEmployees(const char* query) {
	char* result = malloc(1024);
	if (!result) return "Memory allocation failed";

	strcpy_s(result, 1024, "NAME | NUMBER | ROLE\n");

	sqlite3_stmt* stmt;
	if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK) {
		free(result);
		return "QUERY FAILED";
	}

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		const char* name = (const char*)sqlite3_column_text(stmt, 1);
		int number = sqlite3_column_int(stmt, 2);
		const char* role = (const char*)sqlite3_column_text(stmt, 3);


		char row[256];
		snprintf(row, sizeof(row), "%s | %d | %s\n", name, number, role);

		size_t new_len = strlen(result) + strlen(row) + 1;
		result = realloc(result, new_len);
		if (!result) return "Memory allocation failed";

		strcat_s(result, new_len, row);
	}

	sqlite3_finalize(stmt);
	return result;
}