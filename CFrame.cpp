/*!
 * \file CFrame.cpp
 *
 * \author Team Land Shark
 */

#include "wx/prec.h"
#include <string>
#include <sstream>

#include "CFrame.h"
#include "CFishBeta.h"
#include "CFishNemo.h"
#include "CFishMolly.h"
#include "CDecorTreasure.h"
#include "CAnimatedTreasure.h"
#include "CCountFishVisitor.h"
#include "CReporter.h"

BEGIN_EVENT_TABLE(CFrame, wxFrame)
EVT_MENU(ID_Exit, CFrame::OnExit)
EVT_MENU(ID_SaveAs, CFrame::OnFileSaveAs)
EVT_MENU(ID_FileOpen, CFrame::OnFileOpen)
EVT_MENU(ID_FileTrashCan, CFrame::OnFileTrashCan)
EVT_MENU(ID_About, CFrame::OnAbout)
EVT_MENU(ID_AddFishBeta, CFrame::OnAddFishBeta)
EVT_MENU(ID_AddFishNemo, CFrame::OnAddFishNemo)
EVT_MENU(ID_AddFishMolly, CFrame::OnAddFishMolly)
EVT_MENU(ID_AddDecorTreasure, CFrame::OnAddDecorTreasure)
EVT_MENU(ID_AddAnimatedChest, CFrame::OnAddAnimatedChest)
EVT_MENU(ID_Clean, CFrame::OnClean)
EVT_MENU(ID_Feed, CFrame::OnFeed)
EVT_PAINT(CFrame::OnPaint)
EVT_LEFT_DOWN(CFrame::OnLeftButtonDown)
EVT_MOTION(CFrame::OnMouseMove)
EVT_LEFT_UP(CFrame::OnMouseMove)
EVT_TIMER(ID_Timer, CFrame::OnTimer)
EVT_TIMER(ID_ReportDisplay, CFrame::OnReport)
END_EVENT_TABLE()

//! Milliseconds
const int FrameDuration = 30;
const int ReporterDisplay = 50;

/*! \brief Default constructor
 * 
 * Creates the frame and sets its initial size and name
 */
CFrame::CFrame() : wxFrame(NULL, -1, L"Aquarium",
                           wxPoint(20, 20), wxSize(1024, 800)),
mTimer(this, ID_Timer), mReport(this, ID_ReportDisplay)
{
    //
    // File menu
    //

    wxMenu *menuFile = new wxMenu;
    wxMenuItem *exitItem = menuFile->Append(ID_Exit, L"&Exit");
    exitItem->SetHelp(L"Exit the program");
    menuFile->Append(ID_SaveAs, L"&Save &As...");
    menuFile->Append(ID_FileOpen, L"&File/Open...");
    mFileTrashCanMenuOption = menuFile->Append(ID_FileTrashCan,
                                               L"&Trash Can",
                                               L"Toggle Trash Can Menu Option",
                                               wxITEM_CHECK);
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
    wxMenuItem *addAnimatedTreasureItem = menuDecor->Append(ID_AddAnimatedChest,
                                                            L"&Animated Chest");

    addAnimatedTreasureItem->SetHelp(L"Add an animated chest to the aquarium");

    //
    // Care Menu
    //

    wxMenu *menuCare = new wxMenu;
    menuCare->Append(ID_Clean, L"&Clean");
    menuCare->Append(ID_Feed, L"&Feed");

    //
    // Menu Bar
    //
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, L"&File");
    menuBar->Append(menuFish, L"&Add Fish");
    menuBar->Append(menuDecor, L"&Add Decor");
    menuBar->Append(menuCare, L"&Care");

    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText(L"Status");
    SetBackgroundColour(wxColour(0, 0, 0));

    mGrabbedItem = NULL;
    
    mReporter = new CReporter(this);
    mReport.Start(ReporterDisplay);
    
    mTimer.Start(FrameDuration);
    mCurrentTime = wxGetLocalTimeMillis().GetValue();

    if (!mScrollModeActive.LoadFile(L"images/nav2.png", wxBITMAP_TYPE_PNG))
        wxMessageBox(L"Failed to open image nav2.png");

    if (!mScrollModeInactive.LoadFile(L"images/nav1.png", wxBITMAP_TYPE_PNG))
        wxMessageBox(L"Failed to open image nav1.png");

    mIsScrollMode = false;

}

CFrame::CFrame(const CFrame& orig)
{
}

CFrame::~CFrame()
{
}

/*! \brief File/About menu option handler
 *  \param event  An object that describes the event.
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
    
    // Background width = 806
    if(this->m_height > 806)
        this->SetSize(this->m_width, 806);
    // Background height = 2560
    if(this->m_width > 2560)
        this->SetSize(2560, this->m_height);

    // draw interface stuff
    if (mIsScrollMode)
    {
        dc.DrawBitmap(mScrollModeActive, 0, this->m_height - 59 * 2);
    }
    else
        dc.DrawBitmap(mScrollModeInactive, 0, this->m_height - 59 * 2);

    dc.SetPen(wxNullPen);
    dc.SetBrush(wxNullBrush);
    dc.SetFont(wxNullFont);

    // Handle updates
    long long newTime = wxGetLocalTimeMillis().GetValue();
    double elapsed = (newTime - mCurrentTime) * 0.001;
    mCurrentTime = newTime;

    mAquarium.Update(elapsed);
}

/*! \brief Add Fish/Beta menu option handler
 *  \param event  An object that describes the event.
 */
void CFrame::OnAddFishBeta(wxCommandEvent& event)
{
    mAquarium.AddItem(new CFishBeta(&mAquarium));
    Refresh();
}

/*! \brief Add Fish/Nemo menu option handler
 *  \param event  An object that describes the event.
 */
void CFrame::OnAddFishNemo(wxCommandEvent& event)
{
    mAquarium.AddItem(new CFishNemo(&mAquarium));
    Refresh();
}

/*! \brief Add Fish/Molly menu option handler
 *  \param event  An object that describes the event.
 */
void CFrame::OnAddFishMolly(wxCommandEvent& event)
{
    mAquarium.AddItem(new CFishMolly(&mAquarium));
    Refresh();
}

/*! \brief Add Fish/Molly menu option handler
 *  \param event  An object that describes the event.
 */
void CFrame::OnAddDecorTreasure(wxCommandEvent& event)
{
    mAquarium.AddItem(new CDecorTreasure(&mAquarium));
    Refresh();
}

/*! \brief Add Animated Chest menu option handler
 *  \param event  An object that describes the event
 */
void CFrame::OnAddAnimatedChest(wxCommandEvent& event)
{
    mAquarium.AddItem(new CAnimatedTreasure(&mAquarium));
    Refresh();
}

/*! \breif Add Care/Clean menu option handler
 *  \param event  An object that describes the event.
 */
void CFrame::OnClean(wxCommandEvent& event)
{
    mAquarium.Clean();
    Refresh();
}

/*! \brief Add Care/Feed menu option handler
 *  \param event  An object that describes the event.
 */
void CFrame::OnFeed(wxCommandEvent& event)
{
    mAquarium.Feed();
}

/*! \brief Add File/Save option handler
 *  \param event  An object that describes the event.
 */
void CFrame::OnFileSaveAs(wxCommandEvent& event)
{
    wxFileDialog dlg(this, L"Save File", L"", L"",
                     L"Aquarium Files (*.aqua)|*.aqua",
                     wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (dlg.ShowModal() != wxID_OK)
        return;

    // Get the filename into a local string
    std::wstring filename = dlg.GetPath().wc_str();

    // If no suffix is supplied for the file, supply it here
    std::wstring suffix(L".aqua");
    if (!std::equal(suffix.rbegin(), suffix.rend(), filename.rbegin()))
    {
        filename += suffix;
    }

    mAquarium.Save(filename);
}
/*! \brief Add File/Open option handler
 *  \param event  An object that describes the event.
 */
void CFrame::OnFileOpen(wxCommandEvent& event)
{
    wxFileDialog dlg(this, L"Open File", L"", L"",
                     L"Aquarium Files (*.aqua)|*.aqua",
                     wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (dlg.ShowModal() != wxID_OK)
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
    // Get mouse location (for scrolling)
    mMouseLocationX = event.m_x;
    mMouseLocationY = event.m_y;
    
    // Test for button hit (exact box for button)
    if((event.m_x >= 0 && event.m_x <= 68 )
            && ((event.m_y <= this->m_height) && event.m_y >= this->m_height - 59*2))
    {
        ToggleScrollMode();
    }
    
    //need to test if scroll mode here then
    mGrabbedItem = mAquarium.HitTest(event.m_x - mAquarium.GetAquariumTestPointX(), 
                                     event.m_y - mAquarium.GetAquariumTestPointY());
    if (mGrabbedItem != NULL)
    {
        // We grabbed something
        bool ctrl = event.m_controlDown;

        if (ctrl)
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
    // See if an item is currently being moved by the mouse and scroll mode false
    if (mGrabbedItem != NULL && !mIsScrollMode)
    {
        // If an item is being moved, we only continue to
        // move it while the left button is down.
        if (event.m_leftDown)
        {
            mGrabbedItem->SetLocation(event.m_x - mAquarium.GetAquariumTestPointX(), 
                                      event.m_y - mAquarium.GetAquariumTestPointY());
        }
        else
        {
            // When the left button is released, we release the
            // item.
            if (mAquarium.IsOverTrashcan(event.m_x, event.m_y))
            {
                mAquarium.DeleteItem(mGrabbedItem);
            }

            mGrabbedItem = NULL;
        }

        // Force the screen to redraw
        Refresh();
    } else
    {
        // Check mouse clicked and scroll mode is active
        if(event.m_leftDown && mIsScrollMode)
        {
            //! Any image outside the frame
            double imageOutsideX = 2560 - this->m_width;
            double imageOutsideY = 806 - this->m_height;
            
            // Set image bounds
            if(mAquarium.GetAquariumTestPointX() <= 0.0 &&
                  mAquarium.GetAquariumTestPointX() >= -imageOutsideX)
            {
                // Stop scrolling too far right
                if(mMouseLocationX > event.m_x &&
                      mAquarium.GetAquariumTestPointX() > -imageOutsideX + (mMouseLocationX - event.m_x))
                {
                    mAquarium.SetAquariumTestPointX(mAquarium.GetAquariumTestPointX()
                                                      - (mMouseLocationX - event.m_x));
                    mMouseLocationX = event.m_x;
                }
                // Stop scrolling too far left
                else if(mMouseLocationX < event.m_x &&
                      mAquarium.GetAquariumTestPointX() < 0 + (event.m_x - mMouseLocationX))
                {
                    mAquarium.SetAquariumTestPointX(mAquarium.GetAquariumTestPointX()
                                                      + (event.m_x - mMouseLocationX));
                    // Prevent image scroll too far (weird issue with left side)
                    if (mAquarium.GetAquariumTestPointX() > 0.0)
                        mAquarium.SetAquariumTestPointX(0.0);
                    mMouseLocationX = event.m_x;
                }
            }
            
            // Set image bounds
            if(mAquarium.GetAquariumTestPointY() <= 0.0 &&
                  mAquarium.GetAquariumTestPointY() >= -imageOutsideY)
            {
                // Stop scrolling too far right
                if(mMouseLocationY > event.m_y &&
                      mAquarium.GetAquariumTestPointY() > -imageOutsideY + (mMouseLocationY - event.m_y))
                {
                    mAquarium.SetAquariumTestPointY(mAquarium.GetAquariumTestPointY()
                                                      - (mMouseLocationY - event.m_y));
                    mMouseLocationY = event.m_y;
                }
                // Stop scrolling too far left
                else if(mMouseLocationY < event.m_y &&
                      mAquarium.GetAquariumTestPointY() < 0 + (event.m_y - mMouseLocationY))
                {
                    mAquarium.SetAquariumTestPointY(mAquarium.GetAquariumTestPointY()
                                                      + (event.m_y - mMouseLocationY));
                    // Prevent image scroll too far (weird issue with left side)
                    if (mAquarium.GetAquariumTestPointY() > 0.0)
                        mAquarium.SetAquariumTestPointY(0.0);
                    mMouseLocationY = event.m_y;
                }
            }
        }
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

/*! \brief Report handler function
 * 
 * This function is called on a regular basis to report status of the
 * the window, allowing for report display.
 * 
 * \param event The timer event
 */
void CFrame::OnReport(wxTimerEvent &event)
{
    CCountFishVisitor countFish;
    mAquarium.Accept(&countFish);
    
    std::wstringstream strSpace;
    for (int i = 0; i < 100; i++)
        strSpace << "\n";
    strSpace << std::ends;
    mReporter->Report(strSpace.str());
    
    std::wstringstream strCount;
    strCount 
        << L"Number of Fish in Tank: "
        << (countFish.GetBetaCount() +
            countFish.GetNemoCount() +
            countFish.GetMollyCount()) << "\n"
        << L"Beta Fish: " << countFish.GetBetaCount() << "\n"
        << L"Nemo Fish: " << countFish.GetNemoCount() << "\n"
        << L"Molly Fish: " << countFish.GetMollyCount() << "\n" << std::ends;
    mReporter->Report(strCount.str());
    
    std::wstringstream strDirty;
    strDirty << L"Time since last cleaned: " << mAquarium.GetLastClean() << std::ends;
    mReporter->Report(strDirty.str());
    
    std::wstringstream strFed;
    strFed << L"Time since last fed: " << mAquarium.GetLastFed() << "\n" << std::ends;
    mReporter->Report(strFed.str());
    
    std::wstringstream strBubbles;
    strBubbles << L"Number of Bubbles: " << mAquarium.GetBubbleCount() << "\n" << std::ends;
    mReporter->Report(strBubbles.str());
}
