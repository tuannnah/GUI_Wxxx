#include "menuContent.h"
menuContent::menuContent(wxBoxSizer* parent, wxPanel* parentpn) : wxPanel(parentpn)
{
    //Parent setting
    ContentParent = parentpn;

    //Sizers
    PanelContentSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* LeftPanelSizer = new wxBoxSizer(wxVERTICAL);

    //Definition
    wxPanel* LeftPanel = new wxPanel(this, 4, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_SUNKEN);
    wxStaticText* m_text = new wxStaticText(LeftPanel, -1, wxT("Infomations"),
        wxPoint(0, 0), wxSize(-1, -1), wxALIGN_CENTRE_HORIZONTAL);
    wxPanel* LeftPanelCt = new wxPanel(LeftPanel, 4, wxPoint(-1, -1),
        wxSize(-1, -1), wxTOP | wxBORDER_SUNKEN);
    wxPanel* RightContent = new wxPanel(this, 8, wxPoint(-1, -1),
        wxSize(-1, -1), wxBORDER_SUNKEN);
    wxStaticText* m_text1 = new wxStaticText(RightContent, -1, wxT("Gioi thieu ve project: \n -1 board Aduino Uno R3 \n-1 dong co servo \n -4 con Quang dien tro CDS 5mm\n -1 cam bien dien the*\n\n *Khoa sat cuong do anh sang va muc dien nang pin san sinh theo thoi gian thuc\n -Dieu khien DC Servo"));
    //wxListBox* cptr = new wxListBox(PanelContent, 4, wxPoint(0, 0),
        //wxSize(500, 500));

    //Set Sizers
    this->SetSizer(PanelContentSizer);
    LeftPanel->SetSizer(LeftPanelSizer);

    //Add Sizers
    parent->Add(this, 15, wxEXPAND | wxBOTTOM, 0);
    LeftPanelSizer->Add(m_text, 1, wxEXPAND | wxBOTTOM, 0);
    LeftPanelSizer->Add(LeftPanelCt, 40, wxEXPAND | wxBOTTOM, 0);
    PanelContentSizer->Add(LeftPanel, 4, wxEXPAND | wxRight, 1);
    PanelContentSizer->Add(RightContent, 8, wxEXPAND | wxALL, 0);

    //BackgroundColors
    m_text->SetBackgroundColour("#e7e7e7");

    //Fonts
    wxFont sum_font = m_text->GetFont();
    sum_font.SetWeight(wxFONTWEIGHT_BOLD);
    m_text->SetFont(sum_font);
    //
       
}
//Functions
void menuContent::hide() {
    this->Hide();

}
void menuContent::show() {
    this->SetClientSize(this->ContentParent->GetClientSize());
    this->Show();


}
