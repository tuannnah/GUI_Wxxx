#pragma once
#include <wx/wx.h>
#include "RandWExcel.h"

class refreshContent : public wxPanel
{
public:
	refreshContent(wxBoxSizer* parent, wxPanel* parentpn);
	wxPanel* NotesParent;
	wxBoxSizer* PanelContentSizer;
	wxBitmapButton* refreshBtn;
	void hide();
	void show();

};

