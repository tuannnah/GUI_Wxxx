#include "Window.h"
#include "FirstFrame.h"

IMPLEMENT_APP(Window)

bool Window::OnInit()
{
    //Break leak alloc 
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(14631);
    //_CrtSetBreakAlloc(6576);
    //_CrtSetBreakAlloc(6575);
    //_CrtSetBreakAlloc(14632);
    //_CrtSetBreakAlloc(20811);
   // _CrtSetBreakAlloc(14633);
    //_CrtSetBreakAlloc(20814);
    //_CrtSetBreakAlloc(20811);
   // _CrtSetBreakAlloc(20815);

    FirstFrame* MainFrame = new FirstFrame(wxT("Solar Battery"));
    MainFrame->Show(true);
    return true;
}