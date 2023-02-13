#pragma once
#include <wx/wx.h>
class menuContent : public wxPanel
{
public:
	menuContent(wxBoxSizer* parent, wxPanel* parentpn);
	wxPanel* ContentParent;
	wxBoxSizer* PanelContentSizer;
	void hide();
	void show();

};

