#include "App.h"
#include <wx/wx.h>
#include "MainFrame.h"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	MainFrame* mainFrame = new MainFrame("Till System");
	mainFrame->ShowFullScreen(true);
	mainFrame->Show();
	return true;
}
