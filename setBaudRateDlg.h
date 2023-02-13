#pragma once
#include <wx/wx.h>
#include <string>
#include "SerialCommHelper.h"

class setBaudRateDlg : public wxDialog
{
private:
	long baudrate;
public:
	setBaudRateDlg(CSerialCommHelper* com, wxWindow* parent, wxWindowID id, const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxDEFAULT_DIALOG_STYLE);
	CSerialCommHelper* seCom;
	wxChoice* setBaudChoice;
	long currentBaud();
public:
	DECLARE_EVENT_TABLE()
	void OnChoice(wxCommandEvent& WXUNUSED(event));
};

