#include "setBaudRateDlg.h"
BEGIN_EVENT_TABLE(setBaudRateDlg, wxDialog)
EVT_CHOICE(117, setBaudRateDlg::OnChoice)
END_EVENT_TABLE()
setBaudRateDlg::setBaudRateDlg(CSerialCommHelper* com, wxWindow* parent, wxWindowID id, const wxString& title,
	const wxPoint& position, const wxSize& size, long style)
	: wxDialog(parent, id, title, position, size, style)
{
	wxString baudList[4] = { "9600", "14400", "19200" , "38400" };
	baudrate = com->GetBaudRate();
	seCom = com;
	wxPoint p;
	wxSize  sz;
	sz.SetWidth(size.GetWidth() - 20);
	sz.SetHeight(size.GetHeight() - 70);

	p.x = 3; p.y = 2;
	setBaudChoice = new wxChoice(this, 117, wxPoint(5, 2), wxSize(195, -1), 4, baudList);
	setBaudChoice->SetSelection(setBaudChoice->FindString(std::to_string(com->GetBaudRate())));
	p.y += sz.GetHeight() -20;
	wxButton* b = new wxButton(this, wxID_OK, _("OK"), p, wxDefaultSize);
	p.x += 100;
	wxButton* c = new wxButton(this, wxID_CANCEL, _("Cancel"), p, wxDefaultSize);
	this->Center();
}
void setBaudRateDlg::OnChoice(wxCommandEvent& WXUNUSED(event)) {
	wxString CurrentSelect = setBaudChoice->GetString(setBaudChoice->GetSelection());
	long value;
	CurrentSelect.ToLong(&value);
	baudrate = value;
}
long setBaudRateDlg::currentBaud() {
	return baudrate;
}