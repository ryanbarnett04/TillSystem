#pragma once

#include <wx/wx.h>
#include <wx/simplebook.h>
#include <wx/display.h>
#include "Order.h"

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString &title);

private:

    // Global Variables
    int location = NULL; // 1 = Sit In, 0 = Take Away
    bool item_corrected;
    Order order;
    wxButton* temp_button;
    wxArrayString* display_items;
    std::string signedInName;
    int signedInNumber;
    std::string signedInRole;
    float orderCurrentPrice = NULL;
    Item recentItem;
    int addQuantity = 1;
    bool onPaymentScreen = false;

    // Simple books
    wxSimplebook* order_top_band;
    wxSimplebook* order_side_tabs;
    wxSimplebook* primary_screen;
    wxSimplebook* righthand;
    wxSimplebook* bottom_band;

    // Primary Screen - Homepage
    wxButton* sit_in;
    wxButton* take_away;
    wxButton* receipts;

    // Primary Screen - Hot Drinks
    wxButton* americano_blackSML;
    wxButton* americano_blackMED;
    wxButton* americano_blackLRG;
    wxButton* americano_whiteSML;
    wxButton* americano_whiteMED;
    wxButton* americano_whiteLRG;
    wxButton* latteSML;
    wxButton* latteMED;
    wxButton* latteLRG;
    wxButton* cappuccinoSML;
    wxButton* cappuccinoMED;
    wxButton* cappuccinoLRG;
    wxButton* mochaSML;
    wxButton* mochaMED;
    wxButton* mochaLRG;
    wxButton* flatWhite;
    wxButton* flatBlack;

    // Primary Screen - Iced Drinks
    wxButton* iced_americanoSML;
    wxButton* iced_americanoMED;
    wxButton* iced_americanoLRG;
    wxButton* icedLatteSML;
    wxButton* icedLatteMED;
    wxButton* icedLatteLRG;
    wxButton* icedCappuccinoSML;
    wxButton* icedCappuccinoMED;
    wxButton* icedCappuccinoLRG;
    wxButton* icedMochaSML;
    wxButton* icedMochaMED;
    wxButton* icedMochaLRG;
    wxButton* icedFlatWhite;
    wxButton* icedFlatBlack;

    // Primary Screen - Tea / Hot Chocolate
    wxButton* breakfastTea;
    wxButton* decafTea;
    wxButton* earlGreyTea;
    wxButton* mintTea;
    wxButton* greenTea;
    wxButton* berryTea;
    wxButton* hotChocolateSML;
    wxButton* hotChocolateMED;
    wxButton* hotChocolateLRG;
    wxButton* whiteHotChocolateSML;
    wxButton* whiteHotChocolateMED;
    wxButton* whiteHotChocolateLRG;
    wxButton* chaiLatteSML;
    wxButton* chaiLatteMED;
    wxButton* chaiLatteLRG;

    // Primary Screen - Frappes
    wxButton* coffeeCreamFrappeSML;
    wxButton* coffeeCreamFrappeMED;
    wxButton* strawberryCreamFrappeWithCoffeeSML;
    wxButton* strawberryCreamFrappeWithCoffeeMED;
    wxButton* strawberryCreamFrappeSML;
    wxButton* strawberryCreamFrappeMED;
    wxButton* saltedCaramelFrappeWithCoffeeSML;
    wxButton* saltedCaramelFrappeWithCoffeeMED;
    wxButton* saltedCaramelFrappeSML;
    wxButton* saltedCaramelFrappeMED;
    wxButton* chocolateFudgeBrownieFrappeWithCoffeeSML;
    wxButton* chocolateFudgeBrownieFrappeWithCoffeeMED;
    wxButton* chocolateFudgeBrownieFrappeSML;
    wxButton* chocolateFudgeBrownieFrappeMED;
    wxButton* mangoBubbleFrappeSML;
    wxButton* mangoBubbleFrappeMED;

    // Primary Screen - Fruit Drinks
    wxButton* peachIceTeaSML;
    wxButton* peachIceTeaMED;
    wxButton* mangoPassionCoolerSML;
    wxButton* mangoPassionCoolerMED;
    wxButton* redBerriesCoolerSML;
    wxButton* redBerriesCoolerMED;

    // Primary Screen - Prepackaged Drinks
    wxButton* cocaCola;
    wxButton* cocaColaDiet;
    wxButton* cocaColaZero;
    wxButton* irnBru;
    wxButton* irnBruSugarFree;
    wxButton* fanta;
    wxButton* sprite;
    wxButton* smartWater;
    wxButton* smartWaterSparkling;

    // Primary Screen - Breakfast Food
    wxButton* white_toast;
    wxButton* white_toast_round;
    wxButton* brown_toast;
    wxButton* brown_toast_round;

    // Primary Screen - Sign In
    wxStaticText* nameLabel;
    wxTextCtrl* nameField;
    wxStaticText* numberLabel;
    wxTextCtrl* numberField;
    wxButton* signInButton;

    // Primary Screen - Receipts
    wxStaticText* receiptsLabel;

    // Primary Screen - Club Card
    wxStaticText* clubCardText;
    wxTextCtrl* clubCardInput;

    // Order Top Band - Navigation
    wxButton* change_location;
    wxButton* drinks;
    wxButton* food;
    wxButton* merch;
    wxButton* functions;

    // Order Top Band - Sign-In
    wxButton* signInToHomescreen;

    // Order Side Tabs - Drinks
    wxButton* hot_drinks;
    wxButton* iced_drinks;
    wxButton* tea_hot_chocolate_drinks;
    wxButton* frappe_drinks;
    wxButton* fruit_drinks;
    wxButton* prepackaged_drinks;

    // Order Side Tabs - Food
    wxButton* breakfast_food;
    wxButton* cakes_food;
    wxButton* impulse_food;
    wxButton* prepackaged_food;

    // Order Side Tabs - Homescreen
    wxButton* sign_in;
    wxButton* sign_out;

    // Bottom Band - Drink Add-Ons
    wxButton* decaf;
    wxButton* MIShot;
    wxButton* reuseCup;
    wxButton* caramel;
    wxButton* caramelSF;
    wxButton* vanilla;
    wxButton* vanillaSF;
    wxButton* hazelnut;
    wxButton* hazelnutSF;

    // Bottom Band - Homescreen Bottom Bar
    wxStaticText* employee;

    // Righthand - Order List
    wxListBox* listbox;
    wxButton* itemCorrect;
    wxButton* voidOrder;
    wxButton* selectQuantity;
    wxTextCtrl* inputQuantity;
    wxButton* goToPayment;
    wxStaticText* currentPriceLabel;

    // Righthand - Payment Screen
    wxListBox* paymentListbox;
    wxButton* payCash;
    wxButton* payCard;
    wxButton* payGiftCard;
    wxStaticText* orderTotal;
    wxTextCtrl* cashLabel;
    wxButton* one;
    wxButton* two;
    wxButton* three;
    wxButton* four;
    wxButton* five;
    wxButton* six;
    wxButton* seven;
    wxButton* eight;
    wxButton* nine;
    wxButton* zero;
    wxButton* clear;
    wxButton* backToSales;
    wxButton* decimal_char;

    // Navigation
    void SitIn(wxCommandEvent& evt);
    void TakeAway(wxCommandEvent& evt);
    void Receipts(wxCommandEvent& evt);
    void ChangeLocation(wxCommandEvent& evt);
    void SignIn(wxCommandEvent& evt);
    void Drinks(wxCommandEvent& evt);
    void Food(wxCommandEvent& evt);
    void HotDrinks(wxCommandEvent& evt);
    void IcedDrinks(wxCommandEvent& evt);
    void TeaHotChocolate(wxCommandEvent& evt);
    void Frappe(wxCommandEvent& evt);
    void Fruit(wxCommandEvent& evt);
    void PrepackagedDrinks(wxCommandEvent& evt);
    void BreakfastFood(wxCommandEvent& evt);
    void Homescreen(wxCommandEvent& evt);
    void GoToPayment(wxCommandEvent& evt);
    void BackToSales(wxCommandEvent& evt);

    // Items
    void addToOrder(wxCommandEvent& evt);

    // Utility
    void removeItem(wxCommandEvent& evt);
    void removeOrder(wxCommandEvent& evt);
    void placeholder(wxCommandEvent& evt);
    void signUserIn(wxCommandEvent& evt);
    void signUserOut(wxCommandEvent& evt);
    void SelectItemQuantity(wxCommandEvent& evt);
    void CheckCash(wxCommandEvent& evt);
    void PayCard(wxCommandEvent& evt);
    void PayGiftCard(wxCommandEvent& evt);
    void GoHome();

    // Num Pad
    void NumpadButtons(wxCommandEvent& evt);

    wxButton* createButton(wxPanel* panel, int id, std::string name, std::tuple<int, int> pos, std::tuple<int, int> size, std::tuple<int, int, int> foreground, std::tuple<int, int, int> background, void (MainFrame::* handler)(wxCommandEvent&));
};
