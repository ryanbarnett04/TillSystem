# TillSystem

- This project is a simple POS / Till system made to emulate what you might find in a cafe / coffee shop
- This is a beginners project, i know the code sucks.
- Solution consists of two components, the 'Till System' and 'Till Shell'

## Till System
- The Till System project is the till itself
- Written in C++
- Uses WxWidgets for the UI
- Uses sqlite3 for the local database
 
## Till Shell
- The Till Shell is a shell that is used to interface with the Till's database freely
- The Till System has limited access to the database
- The Till System and Till Shell cannot be run at the same time
- Written in C
- Uses sqlite3 for the local database

## Other
- You will need to include the sqlite3 folder in the project some where
- Make sure that TillSystem/database.h & TillShell/main.c includes are pointing to the right location.
- For me, sqlite folder is in 'TillSystem' folder (Project folder, NOT solution folder),
  and 'TillShell' has 'TillSystem' as an additional include directory
   

  
