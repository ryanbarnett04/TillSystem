#include "MainFrame.h"
#include "Order.h"
#include "ProductMap.h"
#include "Database.h"
#include <iostream>
#include <unordered_map>
#include <tuple>
#include <optional>
#include <format>

Database db("database.db");

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {

	wxDisplay display;
	wxRect screenRect = display.GetGeometry();
	int screenWidth = screenRect.GetWidth();
	int screenHeight = screenRect.GetHeight();
	item_corrected = false;

	db.executeQuery("CREATE TABLE IF NOT EXISTS employees ("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"NAME TEXT NOT NULL, "
		"NUMBER INT NOT NULL, "
		"ROLE TEXT NOT NULL);");

	db.executeQuery("CREATE TABLE IF NOT EXISTS stock ("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"PRODUCT_KEY INT NOT NULL, "
		"NAME TEXT NOT NULL, "
		"QUANTITY DOUBLE NOT NULL, "
		"TYPE TEXT NOT NULL, "
		"SIZE TEXT);");

	// Main Panel
	wxPanel* mainPanel = new wxPanel(this);
	mainPanel->SetBackgroundColour(wxColour(60, 0, 8));

	// Simple Books for Frame
	order_top_band = new wxSimplebook(mainPanel, wxID_ANY, wxPoint(0, 0), wxSize(screenWidth, 100));
	order_side_tabs = new wxSimplebook(mainPanel, wxID_ANY, wxPoint(0, 100), wxSize(150, screenHeight - 100));
	primary_screen = new wxSimplebook(mainPanel, wxID_ANY, wxPoint(150, 100), wxSize( (screenWidth / 2) + 100, screenHeight - 300));
	righthand = new wxSimplebook(mainPanel, wxID_ANY, wxPoint(1210, 100), wxSize(710, screenHeight - 100));
	bottom_band = new wxSimplebook(mainPanel, wxID_ANY, wxPoint(150, screenHeight - 200), wxSize(screenWidth - 150, 200));

	/*
		PAGES FOR THE ORDER TOP BAND
	*/

	// Order Top Band / Page 1 - Empty
	wxPanel* order_top_band_page_empty = new wxPanel(order_top_band);

	// Order Top Band / Page 2 - Order Navigation Buttons
	wxPanel* order_top_band_page_navigation = new wxPanel(order_top_band);
	change_location = createButton(order_top_band_page_navigation, wxID_ANY, "", {15, 15}, {80, 80}, {0, 0, 0}, {255, 255, 255}, &MainFrame::ChangeLocation);
	change_location->SetFont(*new wxFont(9, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	drinks = createButton(order_top_band_page_navigation, wxID_ANY, "Drinks", {110, 15}, {80, 80}, {0, 0, 0}, {255, 255, 255}, &MainFrame::Drinks);
	food = createButton(order_top_band_page_navigation, wxID_ANY, "Food", {205, 15}, {80, 80}, {0, 0, 0}, {255, 255, 255}, &MainFrame::Food);
	merch = createButton(order_top_band_page_navigation, wxID_ANY, "Merch", {300, 15}, {80, 80}, {0, 0, 0}, {255, 255, 255}, &MainFrame::placeholder);
	functions = createButton(order_top_band_page_navigation, wxID_ANY, "Functions", {395, 15}, {80, 80}, {0, 0, 0}, {255, 255, 255}, &MainFrame::placeholder);

	// Order Top Band / Page 3 - Sign In
	wxPanel* order_top_band_sign_in = new wxPanel(order_top_band);
	signInToHomescreen = createButton(order_top_band_sign_in, wxID_ANY, "Home", {15, 15}, {80, 80}, {0, 0, 0}, {255, 255, 255}, &MainFrame::Homescreen);

	/*
		PAGES FOR THE ORDER SIDE TABS
	*/

	// Order Side Tabs / Page 1 - Empty
	wxPanel* order_side_tabs_page_empty = new wxPanel(order_side_tabs);

	// Order Side Tabs / Page 2 - Drink Tabs
	wxPanel* order_side_tabs_page_drinks = new wxPanel(order_side_tabs);
	hot_drinks = createButton(order_side_tabs_page_drinks, wxID_ANY, "Hot Drinks", {15, 40}, {120, 80}, {0, 0, 0}, {255, 255, 255}, &MainFrame::HotDrinks);
	iced_drinks = createButton(order_side_tabs_page_drinks, wxID_ANY, "Iced Drinks", {15, 140}, {120, 80}, {0, 0, 0}, {255, 255, 255}, &MainFrame::IcedDrinks);
	tea_hot_chocolate_drinks = createButton(order_side_tabs_page_drinks, wxID_ANY, "Tea / Hot Chocolate", {15, 240}, {120, 80}, {0, 0, 0}, {255, 255, 255}, &MainFrame::TeaHotChocolate);
	frappe_drinks = createButton(order_side_tabs_page_drinks, wxID_ANY, "Frappes", {15, 340}, {120, 80}, {0, 0, 0}, {255, 255, 255}, &MainFrame::Frappe);
	fruit_drinks = createButton(order_side_tabs_page_drinks, wxID_ANY, "Fruit Drinks", {15, 440}, {120, 80}, {0, 0, 0}, {255, 255, 255}, &MainFrame::Fruit);
	prepackaged_drinks = createButton(order_side_tabs_page_drinks, wxID_ANY, "Prepackaged", {15, 540}, {120, 80}, {0, 0, 0}, {255, 255, 255}, &MainFrame::PrepackagedDrinks);

	// Order Side Tabs / Page 3 - Food Tabs
	wxPanel* order_side_tabs_page_food = new wxPanel(order_side_tabs);
	breakfast_food = createButton(order_side_tabs_page_food, wxID_ANY, "Breakfast", {15, 40}, {120, 80}, {0, 0, 0}, {255, 255, 255}, &MainFrame::placeholder);
	cakes_food = createButton(order_side_tabs_page_food, wxID_ANY, "Cakes", {15, 140}, {120, 80}, {0, 0, 0}, {255, 255, 255}, &MainFrame::placeholder);
	impulse_food = createButton(order_side_tabs_page_food, wxID_ANY, "Impulse", {15, 240}, {120, 80}, {0, 0, 0}, {255, 255, 255}, &MainFrame::placeholder);
	prepackaged_food = createButton(order_side_tabs_page_food, wxID_ANY, "Prepackaged", {15, 340}, {120, 80}, {0, 0, 0}, {255, 255, 255}, &MainFrame::placeholder);

	wxPanel* order_side_tabs_page_homescreen = new wxPanel(order_side_tabs);
	sign_in = createButton(order_side_tabs_page_homescreen, wxID_ANY, "Sign In", {5, screenHeight - 135}, {70, 30}, {0, 0, 0}, {255, 255, 255}, &MainFrame::SignIn);
	sign_out = createButton(order_side_tabs_page_homescreen, wxID_ANY, "Sign Out", {80, screenHeight - 135}, {70, 30}, {0, 0, 0}, {255, 255, 255}, &MainFrame::signUserOut);

	/*
		PAGES FOR THE PRIMARY SCREEN
	*/

	// Primary Screen / Page 1 - Homescreen
	wxPanel* primary_screen_page_homescreen = new wxPanel(primary_screen);
	sit_in = createButton(primary_screen_page_homescreen, wxID_ANY, "Sit-In", {(screenWidth/2)-350, (screenHeight/2)-410}, {400, 200}, {0, 0, 0}, {255, 255, 255}, &MainFrame::SitIn);
	take_away = createButton(primary_screen_page_homescreen, wxID_ANY, "Take-Away", {(screenWidth/2)-350, (screenHeight/2)-200 }, {400, 200}, {0, 0, 0}, {255, 255, 255}, &MainFrame::TakeAway);
	receipts = createButton(primary_screen_page_homescreen, wxID_ANY, "Receipts", { (screenWidth/2)-350, (screenHeight/2)+10}, {400, 200}, {0, 0, 0}, {255, 255, 255}, &MainFrame::Receipts);

	// Primary Screen / Page 2 - Hot Drinks
	wxPanel* primary_screen_page_hot_drinks = new wxPanel(primary_screen);
	americano_blackSML = createButton(primary_screen_page_hot_drinks, 1000, "Americano SML", {75, 60}, {180, 40}, {255, 255, 255}, {0, 0, 0}, &MainFrame::addToOrder);
	americano_blackMED = createButton(primary_screen_page_hot_drinks, 1001, "Americano MED", {285, 60}, {180, 40}, {255, 255, 255}, {0, 0, 0}, &MainFrame::addToOrder);
	americano_blackLRG = createButton(primary_screen_page_hot_drinks, 1002, "Americano LRG", {495, 60}, {180, 40}, {255, 255, 255}, {0, 0, 0}, &MainFrame::addToOrder);
	americano_whiteSML = createButton(primary_screen_page_hot_drinks, 1003, "Americano w/ Milk SML", {75, 115}, {180, 40}, {0, 0, 0}, {255, 255, 255}, &MainFrame::addToOrder);
	americano_whiteMED = createButton(primary_screen_page_hot_drinks, 1004, "Americano w/ Milk MED", {285, 115}, {180, 40}, {0, 0, 0}, {255, 255, 255}, &MainFrame::addToOrder);
	americano_whiteLRG = createButton(primary_screen_page_hot_drinks, 1005, "Americano w/ Milk LRG", {495, 115}, {180, 40}, {0, 0, 0}, { 255, 255, 255 }, &MainFrame::addToOrder);
	latteSML = createButton(primary_screen_page_hot_drinks, 1006, "Latte SML", {75, 170}, {180, 40}, {0, 0, 0}, {196, 164, 132}, &MainFrame::addToOrder);
	latteMED = createButton(primary_screen_page_hot_drinks, 1007, "Latte MED", {285, 170}, {180, 40}, {0, 0, 0}, {196, 164, 132}, &MainFrame::addToOrder);
	latteLRG = createButton(primary_screen_page_hot_drinks, 1008, "Latte LRG", {495, 170}, {180, 40}, {0, 0, 0}, {196, 164, 132}, &MainFrame::addToOrder);
	cappuccinoSML = createButton(primary_screen_page_hot_drinks, 1009, "Cappuccino SML", {75, 225}, {180, 40}, {0, 0, 0}, {196, 164, 132}, &MainFrame::addToOrder);
	cappuccinoMED = createButton(primary_screen_page_hot_drinks, 1010, "Cappuccino MED", {285, 225}, {180, 40}, {0, 0, 0}, {196, 164, 132}, &MainFrame::addToOrder);
	cappuccinoLRG = createButton(primary_screen_page_hot_drinks, 1011, "Cappuccino LRG", {495, 225}, {180, 40}, {0, 0, 0}, {196, 164, 132}, &MainFrame::addToOrder);
	mochaSML = createButton(primary_screen_page_hot_drinks, 1012, "Mocha SML", {75, 280}, {180, 40}, {0, 0, 0}, {150, 121, 105}, &MainFrame::addToOrder);
	mochaMED = createButton(primary_screen_page_hot_drinks, 1013, "Mocha MED", {285, 280}, {180, 40}, {0, 0, 0}, {150, 121, 105}, &MainFrame::addToOrder);
	mochaLRG = createButton(primary_screen_page_hot_drinks, 1014, "Mocha LRG", {495, 280}, {180, 40}, {0, 0, 0}, {150, 121, 105}, &MainFrame::addToOrder);
	flatWhite = createButton(primary_screen_page_hot_drinks, 1015, "Flat White", {75, 335}, {285, 40}, {0, 0, 0}, {196, 164, 132}, &MainFrame::addToOrder);
	flatBlack = createButton(primary_screen_page_hot_drinks, 1016, "Flat Black", {390, 335}, {285, 40}, {255, 255, 255}, {0, 0, 0}, &MainFrame::addToOrder);

	// Primary Screen / Page 3 - Iced Drinks
	wxPanel* primary_screen_page_iced_drinks = new wxPanel(primary_screen);
	iced_americanoSML = createButton(primary_screen_page_iced_drinks, 1017, "Iced Americano SML", {75, 60}, {180, 40}, {255, 255, 255}, {0, 0, 0}, &MainFrame::addToOrder);
	iced_americanoMED = createButton(primary_screen_page_iced_drinks, 1018, "Iced Americano MED", {285, 60}, {180, 40}, {255, 255, 255}, {0, 0, 0}, &MainFrame::addToOrder);
	iced_americanoLRG = createButton(primary_screen_page_iced_drinks, 1019, "Iced Americano LRG", {495, 60}, {180, 40}, {255, 255, 255}, {0, 0, 0}, &MainFrame::addToOrder);
	icedLatteSML = createButton(primary_screen_page_iced_drinks, 1020, "Iced Latte SML", {75, 115}, {180, 40}, {0, 0, 0}, {255, 255, 255}, &MainFrame::addToOrder);
	icedLatteMED = createButton(primary_screen_page_iced_drinks, 1021, "Iced Latte MED", {285, 115}, {180, 40}, {0, 0, 0}, {255, 255, 255}, &MainFrame::addToOrder);
	icedLatteLRG = createButton(primary_screen_page_iced_drinks, 1022, "Iced Latte LRG", {495, 115}, {180, 40}, {0, 0, 0}, {255, 255, 255}, &MainFrame::addToOrder);
	icedCappuccinoSML = createButton(primary_screen_page_iced_drinks, 1023, "Iced Cappuccino SML", {75, 170}, {180, 40}, {0, 0, 0}, {255, 255, 255}, &MainFrame::addToOrder);
	icedCappuccinoMED = createButton(primary_screen_page_iced_drinks, 1024, "Iced Cappuccino MED", {285, 170}, {180, 40}, {0, 0, 0}, {255, 255, 255}, &MainFrame::addToOrder);
	icedCappuccinoLRG = createButton(primary_screen_page_iced_drinks, 1025, "Iced Cappuccino LRG", {495, 170}, {180, 40}, {0, 0, 0}, {255, 255, 255}, &MainFrame::addToOrder);
	icedMochaSML = createButton(primary_screen_page_iced_drinks, 1026, "Iced Mocha SML", {75, 225}, {180, 40}, {0, 0, 0}, {255, 255, 255}, &MainFrame::addToOrder);
	icedMochaMED = createButton(primary_screen_page_iced_drinks, 1027, "Iced Mocha MED", {285, 225}, {180, 40}, {0, 0, 0}, {255, 255, 255}, &MainFrame::addToOrder);
	icedMochaLRG = createButton(primary_screen_page_iced_drinks, 1028, "Iced Mocha LRG", {495, 225}, {180, 40}, {0, 0, 0}, {255, 255, 255}, &MainFrame::addToOrder);
	icedFlatWhite = createButton(primary_screen_page_iced_drinks, 1029, "Iced Flat White", {75, 280}, {285, 40}, {0, 0, 0}, {255, 255, 255}, &MainFrame::addToOrder);
	icedFlatBlack = createButton(primary_screen_page_iced_drinks, 1030, "Iced Flat Black", {390, 280}, {285, 40}, {0, 0, 0}, {255, 255, 255}, &MainFrame::addToOrder);


	// Primary Screen / Page 4 - Tea / Hot Chocolate
	wxPanel* primary_screen_page_tea_hot_chocolate_drinks = new wxPanel(primary_screen);
	breakfastTea = createButton(primary_screen_page_tea_hot_chocolate_drinks, 1031, "Breakfast Tea", {75, 60}, {180, 40}, {0, 0, 0}, {255, 255, 255}, &MainFrame::addToOrder);
	decafTea = createButton(primary_screen_page_tea_hot_chocolate_drinks, 1032, "Decaf Tea", {285, 60}, {180, 40}, {255, 255, 255}, {0, 0, 0}, &MainFrame::addToOrder);
	earlGreyTea = createButton(primary_screen_page_tea_hot_chocolate_drinks, 1033, "Earl Grey", {495, 60}, {180, 40}, {0, 0, 0}, {169, 169, 169}, &MainFrame::addToOrder);
	mintTea = createButton(primary_screen_page_tea_hot_chocolate_drinks, 1034, "Mint Tea", {75, 115}, {180, 40}, {0, 0, 0}, {152, 255, 152}, &MainFrame::addToOrder);
	greenTea = createButton(primary_screen_page_tea_hot_chocolate_drinks, 1035, "Green Tea", {285, 115}, {180, 40}, {0, 0, 0}, {0, 255, 0}, &MainFrame::addToOrder);
	berryTea = createButton(primary_screen_page_tea_hot_chocolate_drinks, 1036, "Berry Tea", {495, 115}, {180, 40}, {255, 255, 255}, {255, 77, 77}, &MainFrame::addToOrder);
	hotChocolateSML = createButton(primary_screen_page_tea_hot_chocolate_drinks, 1037, "Hot Chocolate SML", {75, 180}, {180, 40}, {0, 0, 0}, {172, 57, 57}, &MainFrame::addToOrder);
	hotChocolateMED = createButton(primary_screen_page_tea_hot_chocolate_drinks, 1038, "Hot Chocolate MED", {285, 180}, {180, 40}, {0, 0, 0}, {172, 57, 57}, &MainFrame::addToOrder);
	hotChocolateLRG = createButton(primary_screen_page_tea_hot_chocolate_drinks, 1039, "Hot Chocolate LRG", {495, 180}, {180, 40}, {0, 0, 0}, {172, 57, 57}, &MainFrame::addToOrder);
	whiteHotChocolateSML = createButton(primary_screen_page_tea_hot_chocolate_drinks, 1040, "White Hot Chocolate SML", {75, 235}, {180, 40}, {0, 0, 0}, {255, 253, 208}, &MainFrame::addToOrder);
	whiteHotChocolateMED = createButton(primary_screen_page_tea_hot_chocolate_drinks, 1041, "White Hot Chocolate MED", {285, 235}, {180, 40}, {0, 0, 0}, {255, 253, 208}, &MainFrame::addToOrder);
	whiteHotChocolateLRG = createButton(primary_screen_page_tea_hot_chocolate_drinks, 1042, "White Hot Chocolate LRG", {495, 235}, {180, 40}, {0, 0, 0}, {255, 253, 208}, &MainFrame::addToOrder);
	chaiLatteSML = createButton(primary_screen_page_tea_hot_chocolate_drinks, 1043, "Chai Latte SML", {75, 300}, {180, 40}, {0, 0, 0}, {255, 176, 39}, &MainFrame::addToOrder);
	chaiLatteMED = createButton(primary_screen_page_tea_hot_chocolate_drinks, 1044, "Chai Latte MED", {285, 300}, {180, 40}, {0, 0, 0}, {255, 176, 39}, &MainFrame::addToOrder);
	chaiLatteLRG = createButton(primary_screen_page_tea_hot_chocolate_drinks, 1045, "Chai Latte LRG", {495, 300}, {180, 40}, {0, 0, 0}, {255, 176, 39}, &MainFrame::addToOrder);

	// Primary Screen / Page 5 - Frappes
	wxPanel* primary_screen_page_frappe_drinks = new wxPanel(primary_screen);
	coffeeCreamFrappeSML = createButton(primary_screen_page_frappe_drinks, 1046, "Coffee w/ Cream SML", {75, 60}, {180, 40}, {0, 0, 0}, {196, 164, 132}, &MainFrame::addToOrder);
	coffeeCreamFrappeMED = createButton(primary_screen_page_frappe_drinks, 1047, "Coffee w/ Cream MED", {285, 60}, {180, 40}, {0 ,0, 0}, {196, 164, 132}, &MainFrame::addToOrder);
	strawberryCreamFrappeWithCoffeeSML = createButton(primary_screen_page_frappe_drinks, 1048, "Strawberry Cream w/ Coffee SML", {75, 115}, {180, 40}, {0, 0, 0}, {250, 80, 83}, &MainFrame::addToOrder);
	strawberryCreamFrappeWithCoffeeMED = createButton(primary_screen_page_frappe_drinks, 1049, "Strawberry Cream w/ Coffee MED", {285, 115}, {180, 40}, {0, 0, 0}, {250, 80, 83}, &MainFrame::addToOrder);
	strawberryCreamFrappeSML = createButton(primary_screen_page_frappe_drinks, 1050, "Strawberry Cream SML", {515, 115}, {180, 40}, {0, 0, 0}, {250, 80, 83}, &MainFrame::addToOrder);
	strawberryCreamFrappeMED = createButton(primary_screen_page_frappe_drinks, 1051, "Strawberry Cream MED", {725, 115}, {180, 40}, {0, 0, 0}, {250, 80, 83}, &MainFrame::addToOrder);
	saltedCaramelFrappeWithCoffeeSML = createButton(primary_screen_page_frappe_drinks, 1052, "Salted Caramel w/ Coffee SML", {75, 170}, {180, 40}, {0, 0, 0}, {178, 126, 71}, &MainFrame::addToOrder);
	saltedCaramelFrappeWithCoffeeMED = createButton(primary_screen_page_frappe_drinks, 1053, "Salted Caramel w/ Coffee MED", {285, 170}, {180, 40}, {0, 0, 0}, {178, 126, 71}, &MainFrame::addToOrder);
	saltedCaramelFrappeSML = createButton(primary_screen_page_frappe_drinks, 1054, "Salted Caramel SML", {515, 170}, {180, 40}, {0, 0, 0}, {178, 126, 71}, &MainFrame::addToOrder);
	saltedCaramelFrappeMED = createButton(primary_screen_page_frappe_drinks, 1055, "Salted Caramel MED", {725, 170}, {180, 40}, {0, 0, 0}, {178, 126, 71}, &MainFrame::addToOrder);
	chocolateFudgeBrownieFrappeWithCoffeeSML = createButton(primary_screen_page_frappe_drinks, 1056, "Choc Fudge Brownie w/ Coffee SML", {75, 225}, {180, 40}, {0, 0, 0}, {160, 132, 112}, &MainFrame::addToOrder);
	chocolateFudgeBrownieFrappeWithCoffeeMED = createButton(primary_screen_page_frappe_drinks, 1057, "Choc Fudge Brownie w/ Coffee MED", {285, 225}, {180, 40}, {0, 0, 0}, {160, 132, 112}, &MainFrame::addToOrder);
	chocolateFudgeBrownieFrappeSML = createButton(primary_screen_page_frappe_drinks, 1058, "Choc Fudge Brownie SML", {515, 225}, {180, 40}, {0, 0, 0}, {160, 132, 112}, &MainFrame::addToOrder);
	chocolateFudgeBrownieFrappeMED = createButton(primary_screen_page_frappe_drinks, 1059, "Choc Fudge Brownie MED", {725, 225}, {180, 40}, {0, 0, 0}, {160, 132, 112}, &MainFrame::addToOrder);
	mangoBubbleFrappeSML = createButton(primary_screen_page_frappe_drinks, 1060, "Mango Bubble SML", {515, 280}, {180, 40}, {0, 0, 0}, {253, 190, 2}, &MainFrame::addToOrder);
	mangoBubbleFrappeMED = createButton(primary_screen_page_frappe_drinks, 1061, "Mango Bubble MED", {725, 280}, {180, 40}, {0, 0, 0}, {253, 190, 2}, &MainFrame::addToOrder);

	// Primary Screen - Page 6 - Fruit Drinks
	wxPanel* primary_screen_page_fruit_drinks = new wxPanel(primary_screen);
	peachIceTeaSML = createButton(primary_screen_page_fruit_drinks, 1062, "Peach Ice Tea SML", {75, 60}, {180, 40}, {0, 0, 0}, {255, 229, 180}, &MainFrame::addToOrder);
	peachIceTeaMED = createButton(primary_screen_page_fruit_drinks, 1063, "Peach Ice Tea MED", {285, 60}, {180, 40}, {0, 0, 0}, {255, 229, 180}, &MainFrame::addToOrder);
	mangoPassionCoolerSML = createButton(primary_screen_page_fruit_drinks, 1064, "Mango and Passion Fruit Cooler SML", {75, 115}, {180, 40}, {0, 0, 0}, {253, 190, 2}, &MainFrame::addToOrder);
	mangoPassionCoolerMED = createButton(primary_screen_page_fruit_drinks, 1065, "Mango and Passion Fruit Cooler MED", {285, 115}, {180, 40}, {0, 0, 0}, {253, 190, 2}, &MainFrame::addToOrder);
	redBerriesCoolerSML = createButton(primary_screen_page_fruit_drinks, 1066, "Red Summer Berries Cooler SML", {75, 170}, {180, 40}, {0, 0, 0}, {118, 32, 35}, &MainFrame::addToOrder);
	redBerriesCoolerMED = createButton(primary_screen_page_fruit_drinks, 1067, "Red Summer Berries Cooler MED", {285, 170}, {180, 40}, {0, 0, 0}, {118, 32, 35}, &MainFrame::addToOrder);

	// Primary Sreen - Page 7 - Prepackaged Drinks
	wxPanel* primary_screen_page_prepackaged_drinks = new wxPanel(primary_screen);
	cocaCola = createButton(primary_screen_page_prepackaged_drinks, 1068, "Coca-Cola™", {75, 60}, {180, 40}, {255, 255, 255}, {0, 0, 0}, &MainFrame::addToOrder);
	cocaColaDiet = createButton(primary_screen_page_prepackaged_drinks, 1069, "Coca-Cola™ Diet", {285, 60}, {180, 40}, {0, 0, 0}, {128, 128, 128}, &MainFrame::addToOrder);
	cocaColaZero = createButton(primary_screen_page_prepackaged_drinks, 1070, "Coca-Cola™ Zero", {495, 60}, {180, 40}, {0, 0, 0}, {254, 0, 26}, &MainFrame::addToOrder);
	irnBru = createButton(primary_screen_page_prepackaged_drinks, 1071, "Irn Bru™", {75, 115}, {180, 40}, {0, 0, 0}, {254, 133, 30}, &MainFrame::addToOrder);
	irnBruSugarFree = createButton(primary_screen_page_prepackaged_drinks, 1072, "Irn Bru™ Sugar Free", {285, 115}, {180, 40}, {0, 0, 0}, {211, 211, 211}, &MainFrame::addToOrder);
	fanta = createButton(primary_screen_page_prepackaged_drinks, 1073, "Fanta™", {495, 115}, {180, 40}, {255, 255, 255}, {255, 131, 0}, &MainFrame::addToOrder);
	sprite = createButton(primary_screen_page_prepackaged_drinks, 1074,"Sprite™", {75, 170}, {180, 40}, {255, 255, 255}, {0, 139, 71}, &MainFrame::addToOrder);
	smartWater = createButton(primary_screen_page_prepackaged_drinks, 1075, "Smart Water™", {285, 170}, {180, 40}, {255, 255, 255}, {35, 137, 218}, &MainFrame::addToOrder);
	smartWaterSparkling = createButton(primary_screen_page_prepackaged_drinks, 1076, "Smart Water™ Sparkling", {495, 170}, {180, 40}, {255, 255, 255}, {116, 204, 244}, &MainFrame::addToOrder);

	// Primary Screen - Page 8 - Breakfast Food
	wxPanel* primary_screen_page_breakfast_food = new wxPanel(primary_screen);
	white_toast = createButton(primary_screen_page_breakfast_food, 1078, "1 White Toast", {75, 60}, {180, 40}, {0, 0, 0}, {255, 255, 255}, &MainFrame::addToOrder);
	white_toast_round = createButton(primary_screen_page_breakfast_food, 1079, "2 White Toast", {285, 60}, {180, 40}, {0, 0, 0}, {255, 255, 255}, &MainFrame::addToOrder);

	// Primary Screen - Page 9 - Sign In Page
	wxPanel* primary_screen_page_sign_in = new wxPanel(primary_screen);
	nameLabel = new wxStaticText(primary_screen_page_sign_in, wxID_ANY, "Enter Name:", wxPoint((screenWidth/2)-350, (screenHeight/2)-410), wxSize(400, 30));
	nameField = new wxTextCtrl(primary_screen_page_sign_in, wxID_ANY, "", wxPoint((screenWidth/2)-350, (screenHeight/2)-410+40), wxSize(400, 30));
	numberLabel = new wxStaticText(primary_screen_page_sign_in, wxID_ANY, "Enter Employee Number:", wxPoint((screenWidth/2)-350, (screenHeight/2)-410+80), wxSize(400, 30));
	numberField = new wxTextCtrl(primary_screen_page_sign_in, wxID_ANY, "", wxPoint((screenWidth/2)-350, (screenHeight / 2)-410+120), wxSize(400, 30));
	signInButton = createButton(primary_screen_page_sign_in, wxID_ANY, "Sign In", {(screenWidth/2)-350, (screenHeight/2)-410+160}, {400, 30}, {0, 0, 0}, {255, 255, 255}, &MainFrame::signUserIn);

	wxFont staticTextFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
	wxFont textCtrlFont(16, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	wxColour* colour = new wxColour(255, 255, 255);

	nameLabel->SetFont(staticTextFont);
	nameLabel->SetForegroundColour(*colour);
	nameField->SetFont(textCtrlFont);

	numberLabel->SetFont(staticTextFont);
	numberLabel->SetForegroundColour(*colour);
	numberField->SetFont(textCtrlFont);

	// Primary Screen - Page 10 - Receipts Page
	wxPanel* primary_screen_page_receipts = new wxPanel(primary_screen);
	receiptsLabel = new wxStaticText(primary_screen_page_receipts, wxID_ANY, "Receipts:", wxPoint( (screenWidth / 2) - 400, 20), wxSize(500, 30));
	receiptsLabel->SetFont(*new wxFont(22, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	receiptsLabel->SetForegroundColour(*new wxColour(255, 255, 255));

	wxArrayString* wxAS_receipt = new wxArrayString();
	wxListBox* receipt_box = new wxListBox(primary_screen_page_receipts, wxID_ANY, wxPoint( (screenWidth / 2) - 400, 60), wxSize(500, 600), *wxAS_receipt);

	/*
		PAGES FOR THE RIGHTHAND
	*/

	// Righthand / Page 1 - Empty
	wxPanel* righthand_page_empty = new wxPanel(righthand);

	// Righthand / Page 2 - Order List
	wxPanel* righthand_page_orderlist = new wxPanel(righthand);
	display_items = new wxArrayString();
	listbox = new wxListBox(righthand_page_orderlist, wxID_ANY, wxPoint(0, 60), wxSize(500, 600), *display_items, wxLB_SINGLE);
	itemCorrect = createButton(righthand_page_orderlist, wxID_ANY, "Item Correct", {0, 670}, {245, 40}, {0, 0, 0}, {255, 255, 255}, &MainFrame::removeItem);
	voidOrder = createButton(righthand_page_orderlist, wxID_ANY, "Void Order", {255, 670}, {245, 40}, {0, 0, 0}, {255, 255, 255}, &MainFrame::removeOrder);
	selectQuantity = createButton(righthand_page_orderlist, wxID_ANY, "Quantity", {0, 720}, {245, 40}, {0, 0, 0}, {255, 255, 255}, &MainFrame::SelectItemQuantity);
	inputQuantity = new wxTextCtrl(righthand_page_orderlist, wxID_ANY, "", wxPoint(255, 720), wxSize(245, 40));
	inputQuantity->SetFont(*new wxFont(22, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	goToPayment = createButton(righthand_page_orderlist, wxID_ANY, "Pay", {255, 770}, {245, 60}, {0, 0, 0}, {255, 255, 255}, &MainFrame::GoToPayment);
	currentPriceLabel = new wxStaticText(righthand_page_orderlist, wxID_ANY, "£0.00", wxPoint(0, 770), wxSize(245, 500));
	currentPriceLabel->SetFont(*new wxFont(40, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	currentPriceLabel->SetForegroundColour(*new wxColour(255, 255, 255));

	// Righthand / Page 3 - Payment Screen
	wxPanel* righthand_page_payment = new wxPanel(righthand);
	paymentListbox = new wxListBox(righthand_page_payment, wxID_ANY, wxPoint(0, 60), wxSize(500, 300), *display_items, wxLB_SINGLE);
	backToSales = createButton(righthand_page_payment, wxID_ANY, "Back To Sales", {0, 370}, {245, 40}, {0, 0, 0}, {255, 255, 255}, &MainFrame::BackToSales);
	payCard = createButton(righthand_page_payment, wxID_ANY, "Card", {255, 370}, {245, 40}, {0, 0, 0}, {255, 255, 255}, &MainFrame::placeholder);
	payCash = createButton(righthand_page_payment, wxID_ANY, "Cash", {0, 420}, {245, 40}, {0, 0, 0}, {255, 255, 255}, &MainFrame::CheckCash);
	payGiftCard = createButton(righthand_page_payment, wxID_ANY, "Gift Card", {255, 420}, {245, 40}, {0, 0, 0}, {255, 255, 255}, &MainFrame::placeholder);
	cashLabel = new wxTextCtrl(righthand_page_payment, wxID_ANY, "£", wxPoint(0, 470), wxSize(500, 40));
	one = createButton(righthand_page_payment, 1, "1", {0, 520}, {60, 60}, {0, 0, 0}, {255, 255, 255}, &MainFrame::NumpadButtons);
	two = createButton(righthand_page_payment, 2, "2", {70, 520}, {60, 60}, {0, 0, 0}, {255, 255, 255}, &MainFrame::NumpadButtons);
	three = createButton(righthand_page_payment, 3, "3", {140, 520}, {60, 60}, {0, 0, 0}, {255, 255, 255}, &MainFrame::NumpadButtons);
	clear = createButton(righthand_page_payment, 10, "Clear", {210, 520}, {60, 60}, {0, 0, 0}, {255, 255, 255}, &MainFrame::NumpadButtons);
	four = createButton(righthand_page_payment, 4, "4", {0, 590}, {60, 60}, {0, 0, 0}, {255, 255, 255}, &MainFrame::NumpadButtons);
	five = createButton(righthand_page_payment, 5, "5", {70, 590}, {60, 60}, {0, 0, 0}, {255, 255, 255}, &MainFrame::NumpadButtons);
	six = createButton(righthand_page_payment, 6, "6", {140, 590}, {60, 60}, {0, 0, 0}, {255, 255, 255}, &MainFrame::NumpadButtons);
	decimal_char = createButton(righthand_page_payment, 11, ".", {210, 590}, {60, 60}, {0, 0, 0}, {255, 255, 255}, &MainFrame::NumpadButtons);
	seven = createButton(righthand_page_payment, 7, "7", {0, 660}, {60, 60}, {0, 0, 0}, {255, 255, 255}, &MainFrame::NumpadButtons);
	eight = createButton(righthand_page_payment, 8, "8", {70, 660}, {60, 60}, {0, 0, 0}, {255, 255, 255}, &MainFrame::NumpadButtons);
	nine = createButton(righthand_page_payment, 9, "9", {140, 660}, {60, 60}, {0, 0, 0}, {255, 255, 255}, &MainFrame::NumpadButtons);
	zero = createButton(righthand_page_payment, 0, "0", {210, 660}, {60, 60}, {0, 0, 0}, {255, 255, 255}, &MainFrame::NumpadButtons);

	cashLabel->SetFont(*new wxFont(22, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

	/*
		PAGES FOR BOTTOM BAND
	*/

	// Bottom Band / Page 1 - Empty
	wxPanel* bottom_band_page_empty = new wxPanel(bottom_band);

	// Bottom Band / Page 2 - Drink Addons
	wxPanel* bottom_band_page_drink_addons = new wxPanel(bottom_band);
	decaf = new wxButton(bottom_band_page_drink_addons, wxID_ANY, "Decaf", wxPoint(75, 0), wxSize(285, 40));
	MIShot = new wxButton(bottom_band_page_drink_addons, wxID_ANY, "MI Shot", wxPoint(), wxSize());
	reuseCup = new wxButton(bottom_band_page_drink_addons, wxID_ANY, "Reuse Cup", wxPoint(), wxSize());
	caramel = new wxButton(bottom_band_page_drink_addons, wxID_ANY, "Caramel", wxPoint(), wxSize());
	caramelSF = new wxButton(bottom_band_page_drink_addons, wxID_ANY, "Caramel SF", wxPoint(), wxSize());
	vanilla = new wxButton(bottom_band_page_drink_addons, wxID_ANY, "Vanilla", wxPoint(), wxSize());
	vanillaSF = new wxButton(bottom_band_page_drink_addons, wxID_ANY, "Vanilla SF", wxPoint(), wxSize());
	hazelnut = new wxButton(bottom_band_page_drink_addons, wxID_ANY, "Hazelnut", wxPoint(), wxSize());
	hazelnutSF = new wxButton(bottom_band_page_drink_addons, wxID_ANY, "Hazelnut SF", wxPoint(), wxSize());

	// Bottom Band / Page 3 - Homescreen Bottom Bar
	wxPanel* bottom_band_homescreen_bar = new wxPanel(bottom_band);
	employee = new wxStaticText(bottom_band_homescreen_bar, wxID_ANY, "No staff signed in", wxPoint(110, 167), wxSize(500, 30));
	employee->SetFont(textCtrlFont);
	employee->SetForegroundColour(*colour);


	/*
		ADD PAGES TO SIMPLE BOOKS
	*/

	order_top_band->AddPage(order_top_band_page_empty, "Empty");
	order_top_band->AddPage(order_top_band_page_navigation, "Navigation");
	order_top_band->AddPage(order_top_band_sign_in, "Sign In");

	order_side_tabs->AddPage(order_side_tabs_page_empty, "Empty");
	order_side_tabs->AddPage(order_side_tabs_page_drinks, "Drinks");
	order_side_tabs->AddPage(order_side_tabs_page_food, "Food");
	order_side_tabs->AddPage(order_side_tabs_page_homescreen, "Homescreen");

	primary_screen->AddPage(primary_screen_page_homescreen, "Homescreen");
	primary_screen->AddPage(primary_screen_page_hot_drinks, "Hot Drinks");
	primary_screen->AddPage(primary_screen_page_iced_drinks, "Iced Drinks");
	primary_screen->AddPage(primary_screen_page_tea_hot_chocolate_drinks, "Tea / Hot Chocolate Drinks");
	primary_screen->AddPage(primary_screen_page_frappe_drinks, "Frappe Drinks");
	primary_screen->AddPage(primary_screen_page_fruit_drinks, "Fruit Drinks");
	primary_screen->AddPage(primary_screen_page_prepackaged_drinks, "Prepackaged Drinks");
	primary_screen->AddPage(primary_screen_page_breakfast_food, "Breakfast Food");
	primary_screen->AddPage(primary_screen_page_sign_in, "Sign In");
	primary_screen->AddPage(primary_screen_page_receipts, "Receipts");

	righthand->AddPage(righthand_page_empty, "Empty");
	righthand->AddPage(righthand_page_orderlist, "Order List");
	righthand->AddPage(righthand_page_payment, "Payment Screen");

	bottom_band->AddPage(bottom_band_page_empty, "Empty");
	bottom_band->AddPage(bottom_band_page_drink_addons, "Drink Addons");
	bottom_band->AddPage(bottom_band_homescreen_bar, "Homescreen Bar");

	bottom_band->SetSelection(2);
	order_side_tabs->SetSelection(3);
}


/*
	Sit-In & Takeaway Methods begin order process and method for changing order location
*/

void MainFrame::SitIn(wxCommandEvent& event) {

	if (signedInName == "") {
		wxMessageBox("Must have staff member signed in", "Popup", wxOK | wxICON_INFORMATION);
		return;
	}

	order_top_band->SetSelection(1);
	order_side_tabs->SetSelection(1);
	primary_screen->SetSelection(1);
	righthand->SetSelection(1);
	bottom_band->SetSelection(1);
	location = 1;
	change_location->SetLabel("Go to TA");

	if (display_items->IsEmpty()) {
		display_items->Add("Sit In:");
		listbox->Set(*display_items);
	}
}

void MainFrame::TakeAway(wxCommandEvent& event) {

	if (signedInName == "") {
		wxMessageBox("Must have staff member signed in", "Popup", wxOK | wxICON_INFORMATION);
		return;
	}

	order_top_band->SetSelection(1);
	order_side_tabs->SetSelection(1);
	primary_screen->SetSelection(1);
	righthand->SetSelection(1);
	bottom_band->SetSelection(1);
	location = 0;
	change_location->SetLabel("Go to EI");

	if (display_items->IsEmpty()) {
		display_items->Add("Take Away:");
		listbox->Set(*display_items);
	}
}

void MainFrame::ChangeLocation(wxCommandEvent& event) {

	if (onPaymentScreen == true) {
		wxMessageBox("Return to Sales to amend order!");
		return;
	}

	if (location == 1) {
		location = 0;
		change_location->SetLabel("Go to EI");
	}
	else {
		location = 1;
		change_location->SetLabel("Go to TA");
	}
}

void MainFrame::SignIn(wxCommandEvent& event) {
	primary_screen->SetSelection(8);
	order_top_band->SetSelection(2);
}

void MainFrame::Homescreen(wxCommandEvent& event) {
	GoHome();
}


/*
	Access receipts
*/

void MainFrame::Receipts(wxCommandEvent& event) {

	if (signedInName == "") {
		wxMessageBox("Must have staff member signed in", "Popup", wxOK | wxICON_INFORMATION);
		return;
	}

	primary_screen->SetSelection(9);
	bottom_band->SetSelection(0);
	order_top_band->SetSelection(2);
	order_side_tabs->SetSelection(0);
}


/*
	Event handlers for navigation buttons
*/

void MainFrame::Drinks(wxCommandEvent& event) {
	order_side_tabs->SetSelection(1);
	primary_screen->SetSelection(1);
	bottom_band->SetSelection(1);
}

void MainFrame::Food(wxCommandEvent& event) {
	order_side_tabs->SetSelection(2);
	primary_screen->SetSelection(7);
	bottom_band->SetSelection(0);
}

void MainFrame::HotDrinks(wxCommandEvent& event) {
	primary_screen->SetSelection(1);
	bottom_band->SetSelection(1);
}

void MainFrame::IcedDrinks(wxCommandEvent& event) {
	primary_screen->SetSelection(2);
	bottom_band->SetSelection(1);
}

void MainFrame::TeaHotChocolate(wxCommandEvent& event) {
	primary_screen->SetSelection(3);
	bottom_band->SetSelection(1);
}

void MainFrame::Frappe(wxCommandEvent& event) {
	primary_screen->SetSelection(4);
	bottom_band->SetSelection(1);
}

void MainFrame::Fruit(wxCommandEvent& event) {
	primary_screen->SetSelection(5);
	bottom_band->SetSelection(1);
}

void MainFrame::PrepackagedDrinks(wxCommandEvent& event) {
	primary_screen->SetSelection(6);
	bottom_band->SetSelection(1);
}

void MainFrame::BreakfastFood(wxCommandEvent& event) {
	primary_screen->SetSelection(7);
}

void MainFrame::GoToPayment(wxCommandEvent& event) {
	
	onPaymentScreen = true;
	paymentListbox->Set(*display_items);
	righthand->SetSelection(2);
}

void MainFrame::BackToSales(wxCommandEvent& event) {
	righthand->SetSelection(1);
	onPaymentScreen = false;
}


/*
	Event handlers for operations on the order
*/

void MainFrame::addToOrder(wxCommandEvent& event) {

	if (onPaymentScreen == true) {
		wxMessageBox("Return to Sales to amend order!");
		return;
	}

	int buttonID = event.GetId();
	auto [name, price, type, size] = ProductMap::getProduct(buttonID);
	Item item(name, price, type);

	if (size != "") {
		item.setSize(size);
	}

	recentItem = item;

	std::string loc = "";
	if (location == 1) {
		loc = "EI";
	}
	else { loc = "TA"; }

	for (int i = 0; i < addQuantity; i++) {
		order.addItem(item);
		if (type == "Addon") {
			display_items->Add(" - £" + wxString::Format("%.2f", price) + " " + name + " " + " " + loc);
		}
		else if (size == "") {
			display_items->Add("£" + wxString::Format("%.2f", price) + " " + name + " " + " " + loc);
		}
		else {
			display_items->Add("£" + wxString::Format("%.2f", price) + " " + name + " " + size + " " + loc);
		}
		orderCurrentPrice += price;
	}

	listbox->Set(*display_items);
	currentPriceLabel->SetLabelText("£" + std::format("{:.2f}", orderCurrentPrice));

	if (item_corrected == true) {
		item_corrected = false;
	}

	addQuantity = 1;
}

void MainFrame::removeItem(wxCommandEvent& event) {

	if (item_corrected == false) {
		order.removeRecent();
		orderCurrentPrice -= recentItem.getPrice();
		currentPriceLabel->SetLabelText("£" + std::format("{:.2f}", orderCurrentPrice));

		if (!display_items->IsEmpty()) {
			display_items->pop_back();
			listbox->Set(*display_items);
		}

		item_corrected = true;
	}
}

void MainFrame::removeOrder(wxCommandEvent& event) {

	if (signedInRole != "Barista") {
		order.clearOrder();
		orderCurrentPrice = NULL;
		currentPriceLabel->SetLabelText("£" + std::format("{:.2f}", orderCurrentPrice));
		inputQuantity->SetLabelText("");
		display_items->clear();
		listbox->Set(*display_items);
		item_corrected = false;
		GoHome();
	}
}

void MainFrame::SelectItemQuantity(wxCommandEvent& event) {

	std::string num_str = inputQuantity->GetValue().ToStdString();
	unsigned int num;

	try {
		int result = stoi(num_str);
		if (result < 0) {
			wxMessageBox("Error: Please enter a positive number!");
			return;
		}
		num = result;
	}
	catch (const std::invalid_argument& e) {
		wxMessageBox("Error: Please enter an integer!");
		return;
	}

	if (num == 0) {
		addQuantity = 1;
	}
	else {
		addQuantity = num;
	}

	inputQuantity->SetLabelText("");
}

void MainFrame::NumpadButtons(wxCommandEvent& event) {

	std::string current = cashLabel->GetValue().ToStdString();

	switch (event.GetId()) {
	case 0:
		current.append(std::to_string(event.GetId()));
		break;
	case 1:
		current.append(std::to_string(event.GetId()));
		break;
	case 2:
		current.append(std::to_string(event.GetId()));
		break;
	case 3:
		current.append(std::to_string(event.GetId()));
		break;
	case 4:
		current.append(std::to_string(event.GetId()));
		break;
	case 5:
		current.append(std::to_string(event.GetId()));
		break;
	case 6:
		current.append(std::to_string(event.GetId()));
		break;
	case 7:
		current.append(std::to_string(event.GetId()));
		break;
	case 8:
		current.append(std::to_string(event.GetId()));
		break;
	case 9:
		current.append(std::to_string(event.GetId()));
		break;
	case 10:
		current = "£";
		break;
	case 11:
		current.append(".");
		break;
	}

	cashLabel->SetLabelText(current);
}

/*
	Utility Methods
*/


void MainFrame::signUserIn(wxCommandEvent& event) {

	std::string name = nameField->GetValue().ToStdString();
	std::string str_number = numberField->GetValue().ToStdString();

	if (name != "" && str_number != "") {
		int number = std::stoi(str_number);
		auto [eName, eNumber, eRole] = db.fetchUser(name, number);

		if (eName != "") {
			std::string result;
			result += "| " + eName + " | " +
				std::to_string(eNumber) + " | " +
				eRole + " |";
			employee->SetLabel(result);
			nameField->SetLabelText("");
			numberField->SetLabelText("");
			signedInName = eName;
			signedInNumber = eNumber;
			signedInRole = eRole;
		}

		else {
			wxMessageBox("User does not exist", "Popup", wxOK | wxICON_INFORMATION);
			return;
		}
	}

	else {
		wxMessageBox("Please fill out both fields", "Popup", wxOK | wxICON_INFORMATION);
		return;
	}
}

void MainFrame::signUserOut(wxCommandEvent& event) {
	signedInName = "";
	signedInNumber = NULL;
	signedInRole = "";
	employee->SetLabel("No staff signed in");
}

void MainFrame::CheckCash(wxCommandEvent& event) {
	std::string cash_str = cashLabel->GetLabelText().ToStdString();

	if (cash_str == "£") {
		wxMessageBox("Please enter cash amount!");
		return;
	}

	cash_str.erase(remove(cash_str.begin(), cash_str.end(), '£'), cash_str.end());
	float cash = std::stof(cash_str);

	if (cash < orderCurrentPrice) {
		wxMessageBox("Insufficent Cash!", "Warning", wxOK || wxICON_WARNING);
		return;
	}

	float change = cash - orderCurrentPrice;
	wxMessageBox("£" + std::format("{:.2f}", change), "Message", wxOK || wxICON_INFORMATION);
}


/*
	Helper method for creating wxButtons
*/

wxButton* MainFrame::createButton(wxPanel* panel, int id, std::string name, std::tuple<int, int> pos, std::tuple<int, int> size, std::tuple<int, int, int> foreground, std::tuple<int, int, int> background, void (MainFrame::*handler)(wxCommandEvent&)) {
	temp_button = new wxButton(panel, id, name, wxPoint(std::get<0>(pos), std::get<1>(pos)), wxSize(std::get<0>(size), std::get<1>(size)));
	wxColour foregroundColour(std::get<0>(foreground), std::get<1>(foreground), std::get<2>(foreground));
	wxColour backgroundColour(std::get<0>(background), std::get<1>(background), std::get<2>(background));
	temp_button->SetForegroundColour(foregroundColour);
	temp_button->SetBackgroundColour(backgroundColour);
	temp_button->Bind(wxEVT_BUTTON, handler, this);
	return temp_button;
}

void MainFrame::GoHome() {
	primary_screen->SetSelection(0);
	order_top_band->SetSelection(0);
	order_side_tabs->SetSelection(3);
	righthand->SetSelection(0);
	bottom_band->SetSelection(2);
}

void MainFrame::placeholder(wxCommandEvent& event) {
	// DO NOTHING
}