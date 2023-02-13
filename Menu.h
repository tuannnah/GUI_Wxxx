#pragma once
#include <wx/wx.h>
#include <wx/menu.h>

class Menu : public wxMenuBar
{
public:
    Menu(wxFrame* parent);
    void OnQuit(wxCommandEvent& event);
    wxFrame* mparent;
    wxMenu* file;
    wxMenu* imp;
    wxMenuItem* quit;

};