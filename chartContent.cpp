#include "chartContent.h"
chartContent::chartContent(wxBoxSizer* parent, wxPanel* parentpn, CSerialCommHelper* portCom, string* filePath, int& saveInterval) : wxPanel(parentpn)
{
    //Parent setting
    chartParent = parentpn;
    fileDir = filePath;
    //Definition
    wxStaticText* m_text = new wxStaticText(this, -1, wxT("Light and Energy chart"),
        wxPoint(0, 0), wxSize(-1, -1), wxALIGN_CENTRE_HORIZONTAL);
    wxPanel* PanelCt = new wxPanel(this, 4, wxPoint(-1, -1),
        wxSize(-1, -1), wxTOP | wxBORDER_SUNKEN);
    chart1 = new EnergyCharts(PanelCt, portCom, fileDir, saveInterval);

    //Sizers
    wxBoxSizer* PanelSizer = new wxBoxSizer(wxVERTICAL);

    //Add Sizers
    parent->Add(this, 15, wxEXPAND | wxBOTTOM, 0);
    PanelSizer->Add(m_text, 1, wxEXPAND | wxBOTTOM, 0);
    PanelSizer->Add(PanelCt, 40, wxEXPAND | wxBOTTOM, 0);

    //Set Sizers 
    this->SetSizer(PanelSizer);

    //BackgroundColors
    m_text->SetBackgroundColour("#e7e7e7");

    //Fonts
    wxFont sum_font = m_text->GetFont();
    sum_font.SetWeight(wxFONTWEIGHT_BOLD);
    m_text->SetFont(sum_font);    
     
}
//Functions
void chartContent::hide() {
    this->Hide();

}
void chartContent::show() {
    this->SetClientSize(this->chartParent->GetClientSize());
    this->Show();
}