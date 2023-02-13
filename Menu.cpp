#include "Menu.h"
Menu::Menu(wxFrame* parent) : wxMenuBar()
{
    mparent = parent;
    file = new wxMenu;
    file->Append(wxID_ANY, wxT("&Option 1"));
    file->Append(wxID_ANY, wxT("&Option 2"));
    file->Append(wxID_ANY, wxT("&Option 3"));

    imp = new wxMenu;
    imp->Append(wxID_ANY, wxT("Import newsfeed list..."));
    imp->Append(wxID_ANY, wxT("Import bookmarks..."));
    imp->Append(wxID_ANY, wxT("Import mail..."));
    file->AppendSubMenu(imp, wxT("Import"));

    quit = new wxMenuItem(file, wxID_EXIT, wxT("&Quit\tCtrl+W"));
    file->AppendSeparator();
    file->Append(quit);

    this->Append(file, wxT("&File"));

    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
        wxCommandEventHandler(Menu::OnQuit));
    parent->SetMenuBar(this);
}
void Menu::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    mparent->Close(true);
}