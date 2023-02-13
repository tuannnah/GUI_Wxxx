#pragma once
#include <wx/wx.h>
#include "Menu.h"
#include "menuContent.h"
#include "chartContent.h"
#include "notesContent.h"
#include "settingContent.h"
#include "refreshContent.h"
#include "SerialCommHelper.h"
#include "RandWExcel.h"
#include <string.h>
class FirstFrame : public wxFrame
{
        wxColor col1, col2, col3;
        int check;
       
public:
    string fileDir;
    string* path;
    int saveINTERVAL; // milliseconds
    CSVReader* CookieR;
    FirstFrame(const wxString& title);
    CSerialCommHelper* com;
public:
    wxPanel* mainPanel;
    Menu* menu;
    wxPanel* PanelContent;
    wxBoxSizer* PanelToolBarSizer;
    wxBoxSizer* PanelContentSizer;
    //
    wxBitmapButton* button0;
    wxBitmapButton* button1;
    wxBitmapButton* button2;
    wxBitmapButton* button3;
    wxBitmapButton* button4;
    //
    menuContent* menuCt;
    chartContent* chartCt;
    notesContent* notesCt;
    settingContent* settingCt;
    refreshContent* refreshCt;
    //
    void Pressed(int& check);
    //
    DECLARE_EVENT_TABLE()
    void OnMenu(wxCommandEvent& event);
    void OnChart(wxCommandEvent & event);
    void OnNotes(wxCommandEvent& event);
    void OnSetting(wxCommandEvent& event);
    void OnRefresh(wxCommandEvent& event);
    void handlerFuncName(wxUpdateUIEvent& event);  
};