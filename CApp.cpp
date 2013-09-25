//TEST

/*!
 * \file CApp.cpp
 *
 * \author David Warner
 */

#include "wx/prec.h"
#include "CApp.h"
#include "CFrame.h"

IMPLEMENT_APP(CApp)

/*! \brief Constructor
 * 
 * This constructs the application class
 */
CApp::CApp()
{
    srand(time(NULL));
}

CApp::CApp(const CApp& orig)
{
}

CApp::~CApp()
{
}

/*! Application initialization function
 *
 * This function is called once when the
 * application is started. It creates the main frame for
 * the program and displays it.
 * \returns true
 */
bool CApp::OnInit()
{
    wxInitAllImageHandlers();
    CFrame *frame = new CFrame();
    frame->Show(true);
    SetTopWindow(frame);
    return true;
}

/*! \brief This function is called when an exit menu item is selected.
 *
 * It closes the main window, which ends the program.
 * \param event An object that describes the event.
 */
void CFrame::OnExit(wxCommandEvent& event)
{
    Close(TRUE);
}