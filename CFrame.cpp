/*!
 * \file CFrame.cpp
 *
 * \author David Warner
 */

#include "wx/prec.h"
#include <string>
#include <sstream>

#include "CFrame.h"
#include "CFishBeta.h"
#include "CFishNemo.h"
#include "CFishMolly.h"
#include "CDecorTreasure.h"

BEGIN_EVENT_TABLE(CFrame, wxFrame)
    EVT_MENU(ID_Exit, CFrame::OnExit)
    EVT_MENU(ID_SaveAs, CFrame::OnFileSaveAs)
    EVT_MENU(ID_FileOpen, CFrame::OnFileOpen)
    EVT_MENU(ID_FileTrashCan, CFrame::OnFileTrashCan)
    EVT_MENU(ID_OnFileCountBetaFish, CFrame::OnFileCountBetaFish)
    EVT_MENU(ID_About, CFrame::OnAbout)
    EVT_MENU(ID_AddFishBeta, CFrame::OnAddFishBeta)
    EVT_MENU(ID_AddFishNemo, CFrame::OnAddFishNemo)
    EVT_MENU(ID_AddFishMolly, CFrame::OnAddFishMolly)
    EVT_MENU(ID_AddDecorTreasure, CFrame::OnAddDecorTreasure)
    EVT_PAINT(CFrame::OnPaint)
    EVT_LEFT_DOWN(CFrame::OnLeftButtonDown)
    EVT_MOTION(CFrame::OnMouseMove)
    EVT_LEFT_UP(CFrame::OnMouseMove)
    EVT_TIMER(ID_Timer, CFrame::OnTimer)
END_EVENT_TABLE()

//! Milliseconds
const int FrameDuration = 30;

/*! \brief Default constructor
 * 
 * Creates the frame and sets its initial size and name
 */
CFrame::CFrame() : wxFrame( NULL, -1, L"Aquarium", 
                           wxPoint(20, 20), wxSize(1024,800) ),
                            mTimer(this, ID_Timer)
{
     //
     // File menu
     //

     wxMenu *menuFile = new wxMenu;
     wxMenuItem *exitItem = menuFile->Append( ID_Exit, L"&Exit" );
     exitItem->SetHelp(L"Exit the program");
     menuFile->Append( ID_SaveAs, L"&Save &As...");
     menuFile->Append( ID_FileOpen, L"&File/Open...");
     mFileTrashCanMenuOption = menuFile->Append(ID_FileTrashCan, 
                                         L"&Trash Can", 
                                         L"Toggle Trash Can Menu Option", 
                                         wxITEM_CHECK);
     menuFile->Append( ID_OnFileCountBetaFish, L"&Count Beta Fish");
     menuFile->AppendSeparator();
     menuFile->Append(ID_About, L"&About");
     
     //
     // Fish Menu
     //
     wxMenu *menuFish = new wxMenu;
     menuFish->Append(ID_AddFishBeta, L"&Beta");
     menuFish->Append(ID_AddFishNemo, L"&Nemo");
     menuFish->Append(ID_AddFishMolly, L"&Molly");
     
     //
     // Decor Menu
     //
     wxMenu *menuDecor = new wxMenu;
     menuDecor->Append(ID_AddDecorTreasure, L"&Treasure Chest");
     
     //
     // Menu Bar
     //
     wxMenuBar *menuBar = new wxMenuBar;
     menuBar->Append( menuFile, L"&File");
     menuBar->Append( menuFish, L"&Add Fish");
     menuBar->Append( menuDecor, L"&Add Decor");

     SetMenuBar( menuBar );
     
     CreateStatusBar();
     SetStatusText(L"Status");
     SetBackgroundColour(wxColour(0, 0, 0));
     
     mGrabbedItem = NULL;
     
     mTimer.Start(FrameDuration);
     mCurrentTime = wxGetLocalTimeMillis().GetValue();
}

CFrame::CFrame(const CFrame& orig)
{
}

CFrame::~CFrame()
{
}

/*!  File/About menu option handler
 * \param event  An object that describes the event.
 */ 
void CFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(L"This is a simple wxWidgets application",
                 L"About Step 2",
                  wxOK | wxICON_INFORMATION, this);
}

/*! \brief Function called whenever we need to redraw the window
 *
 * This function is called in response to a drawing message
 * whenever we need to redraw the window on the screen.
 * It is responsible for painting the window.
 * \param event An event associated with the message.
 */
void CFrame::OnPaint(wxPaintEvent &event)
{
    // Create a device context
    wxPaintDC dc(this);

    mAquarium.OnDraw(dc);

    dc.SetPen(wxNullPen);
    dc.SetBrush(wxNullBrush);
    dc.SetFont(wxNullFont);
  
    // Handle updates
    long long newTime = wxGetLocalTimeMillis().GetValue();
    double elapsed = (newTime - mCurrentTime) * 0.001;
    mCurrentTime = newTime;
    
    mAquarium.Update(elapsed);
}

/*! Add Fish/Beta menu option handler
 * \param event  An object that describes the event.
 */ 
void CFrame::OnAddFishBeta(wxCommandEvent& event) 
{
    mAquarium.AddItem(new CFishBeta(&mAquarium));
    Refresh();
}

/*! Add Fish/Nemo menu option handler
 * \param event  An object that describes the event.
 */ 
void CFrame::OnAddFishNemo(wxCommandEvent& event) 
{
    mAquarium.AddItem(new CFishNemo(&mAquarium));
    Refresh();
}

/*! Add Fish/Molly menu option handler
 * \param event  An object that describes the event.
 */ 
void CFrame::OnAddFishMolly(wxCommandEvent& event) 
{
    mAquarium.AddItem(new CFishMolly(&mAquarium));
    Refresh();
}

/*! Add Fish/Molly menu option handler
 * \param event  An object that describes the event.
 */ 
void CFrame::OnAddDecorTreasure(wxCommandEvent& event) 
{
    mAquarium.AddItem(new CDecorTreasure(&mAquarium));
    Refresh();
}

void CFrame::OnFileSaveAs(wxCommandEvent& event)
{
    wxFileDialog dlg(this, L"Save File", L"", L"", 
                     L"Aquarium Files (*.aqua)|*.aqua", 
                     wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if(dlg.ShowModal() != wxID_OK)
        return;
    
    // Get the filename into a local string
    std::wstring filename = dlg.GetPath().wc_str();

    // If no suffix is supplied for the file, supply it here
    std::wstring suffix(L".aqua");
    if(!std::equal(suffix.rbegin(), suffix.rend(), filename.rbegin()))
    {
        filename += suffix;
    }
    
    mAquarium.Save(filename);
}

void CFrame::OnFileOpen(wxCommandEvent& event)
{
    wxFileDialog dlg(this, L"Open File", L"", L"", 
                     L"Aquarium Files (*.aqua)|*.aqua",
                     wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if(dlg.ShowModal() != wxID_OK)
        return;

    std::wstring filename = dlg.GetPath().wc_str();
    
    mAquarium.Load(filename);
    Refresh();
}

/*! \brief Left mouse button handler
 *
 * This function is called when the left mouse button is clicked
 * on the window.
 * \param event An event describing the mouse click
 */
void CFrame::OnLeftButtonDown(wxMouseEvent &event)
{
    mGrabbedItem = mAquarium.HitTest(event.m_x, event.m_y);
    if(mGrabbedItem != NULL) 
    {
        // We grabbed something
        bool ctrl = event.m_controlDown;	
        if(ctrl) 
        {
            // Make a copy of the item we grabbed
            CItem *clone = mGrabbedItem->Clone();
            
            mAquarium.AddItem(clone);
            clone->SetLocation(event.m_x, event.m_y);
            mGrabbedItem = clone;
            Refresh();
        }
        else 
        {
            // Move it to the front
            mAquarium.MoveToFront(mGrabbedItem);
            Refresh();
        }
    }
}

/*! \brief Mouse move handler
 *
 * This function is called whenever the mouse is 
 * moved over the window.
 * \param event The mouse event
 */
void CFrame::OnMouseMove(wxMouseEvent &event)
{
    // See if an item is currently being moved by the mouse
    if(mGrabbedItem != NULL)
    { 
        // If an item is being moved, we only continue to 
        // move it while the left button is down.
        if(event.m_leftDown)
        {
            mGrabbedItem->SetLocation(event.m_x, event.m_y);
        }
        else
        {
            // When the left button is released, we release the
            // item.
            if(mAquarium.IsOverTrashcan(event.m_x, event.m_y))
            {
                mAquarium.DeleteItem(mGrabbedItem);
            }

            mGrabbedItem = NULL;
        }

        // Force the screen to redraw
        Refresh();
    } 
}

/*! Add File/Trash Can menu option handler
 * \param event  An object that describes the event.
 */ 
void CFrame::OnFileTrashCan(wxCommandEvent& event) 
{
    mAquarium.ToggleTrashCanActive();
    mFileTrashCanMenuOption->Check(mAquarium.IsTrashCanActive());
    Refresh();   
}

/*! Count the number of Beta Fish menu option
 * \param event  An object that describes the event.
 */ 
void CFrame::OnFileCountBetaFish(wxCommandEvent& event) 
{
    std::wstringstream str;
    int cnt = mAquarium.NumBetaFish();
    str << L"There are " << cnt << " Beta Fish" << std::ends;

    wxMessageBox(str.str().c_str(),
                 L"Astounding Aquarium Information",
                  wxOK | wxICON_INFORMATION, this);
}

/*! \brief Timer handler function
 * 
 * This function is called on a regular basis to invalidate
 * the window, allowing for animation.
 * 
 * \param event The timer event
 */
void CFrame::OnTimer(wxTimerEvent &event)
{
    Refresh();
}