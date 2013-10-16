/*!
 * \file CFrame.cpp
 *
 * \author Team Land Shark
 */

#include "wx/prec.h"
#include <string>
#include <iostream>
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
EVT_MENU(ID_Pause, CFrame::OnPause)
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
    menuFile->AppendSeparator();
    wxMenuItem *pauseItem = menuFile->Append(ID_Pause, L"&Pause\tp");
    pauseItem->SetHelp(L"Pause the game");

    //
    // Fish Menu + costs
    //
    wxMenu *menuFish = new wxMenu;
    menuFish->Append(ID_AddFishBeta, L"&Beta - 1 Bubble\tb");
    menuFish->Append(ID_AddFishNemo, L"&Nemo - 7 Bubbles\tn");
    menuFish->Append(ID_AddFishMolly, L"&Molly - 4 Bubbles\tm");

    //
    // Decor Menu + costs
    //
    wxMenu *menuDecor = new wxMenu;
    menuDecor->Append(ID_AddDecorTreasure, L"&Treasure Chest - 0 Bubbles");
    wxMenuItem *addAnimatedTreasureItem = menuDecor->Append(ID_AddAnimatedChest,
                                                            L"&Animated Chest - 10 Bubbles\ta");

    addAnimatedTreasureItem->SetHelp(L"Add an animated chest to the aquarium");

    //
    // Care Menu + costs
    //

    wxMenu *menuCare = new wxMenu;
    menuCare->Append(ID_Clean, L"&Clean - 5 Bubbles\tC");
    menuCare->Append(ID_Feed, L"&Feed - 3 Bubbles\tF");

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

    // Display introduction (pause game)
    mAquarium.Pause(true);

    wxMessageBox(L"Welcome to Bubble-arium!  The goal is to collect 100 bubbles."
                 "Watch out though!  If you don't feed your fish, you lose."
                 "\n\nRules:"
                 "\n 1. Add items, grab the bubbles"
                 "\n 2. Use bubbles, clean tank and feed your fish (and get more items)"
                 "\n 3. Profit"
                 "\n\nBe Aware:"
                 "\n 1. You can't grab things in scroll mode!"
                 "\n 2. Your fish will die if you don't feed them!"
                 "\n 3. You will lose bubbles if you don't clean the tank!"
                 "\n\nHotkeys:"
                 "\n C - Clean the tank"
                 "\n F - Feed the fish"
                 "\n B - Add Beta fish"
                 "\n N - Add Nemo fish"
                 "\n M - Add Molly fish"
                 "\n A - Add Animated treasure chest",
                 L"Bubble-arium",
                 wxOK | wxICON_INFORMATION, this);

    mAquarium.Pause(false);
}

CFrame::CFrame(const CFrame& orig)
{
}

CFrame::~CFrame()
{
}

/*! \brief File/About menu option handler (pause game)
 *  \param event  An object that describes the event.
 */
void CFrame::OnAbout(wxCommandEvent& event)
{
    mAquarium.Pause(true);

    wxMessageBox(L"Welcome to Bubble-arium!  The goal is to collect 100 bubbles."
                 "Watch out though!  If you don't feed your fish, you lose."
                 "\n\nRules:"
                 "\n 1. Add items, grab the bubbles"
                 "\n 2. Use bubbles, clean tank and feed your fish (and get more items)"
                 "\n 3. Profit"
                 "\n\nBe Aware:"
                 "\n 1. You can't grab things in scroll mode!"
                 "\n 2. Your fish will die if you don't feed them!"
                 "\n 3. You will lose bubbles if you don't clean the tank!"
                 "\n\nHotkeys:"
                 "\n C - Clean the tank"
                 "\n F - Feed the fish"
                 "\n B - Add Beta fish"
                 "\n N - Add Nemo fish"
                 "\n M - Add Molly fish"
                 "\n A - Add Animated treasure chest",
                 L"Bubble-arium",
                 wxOK | wxICON_INFORMATION, this);

    mAquarium.Pause(false);
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
    
    wxFont font(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);
    dc.SetFont(font);
    dc.SetTextForeground(wxColor(255, 0, 0));

    mAquarium.OnDraw(dc);

    // Snap frame size to max height/width
    // Background width = 806
    if (this->m_height > 806)
        this->SetSize(this->m_width, 806);
    // Background height = 2560
    if (this->m_width > 2560)
        this->SetSize(2560, this->m_height);

    // draw interface stuff
    if (mIsScrollMode)
    {
        dc.DrawBitmap(mScrollModeActive, 0, this->m_height - 59 * 2);
    }
    else
        dc.DrawBitmap(mScrollModeInactive, 0, this->m_height - 59 * 2);



    // Handle updates
    long long newTime = wxGetLocalTimeMillis().GetValue();
    double elapsed = (newTime - mCurrentTime) * 0.001;
    mCurrentTime = newTime;

    mAquarium.Update(elapsed);

    if (mAquarium.GetLastFed() >= 20)
    {
        std::wstringstream fishDeath;
        fishDeath
                << L"TIME UNTIL FISH DEATH: "
                << (30 - mAquarium.GetLastFed()) << std::ends;

        dc.DrawText(fishDeath.str(), 0, 30);
    }
    
    std::wstringstream bubbleCount;
        bubbleCount
                << L"Bubble Count: "
                << mAquarium.GetBubbleCount() << std::ends;
        
    dc.DrawText(bubbleCount.str(), 0, 0);

    dc.SetPen(wxNullPen);
    dc.SetBrush(wxNullBrush);
    dc.SetFont(wxNullFont);
}

/*! \brief Add Fish/Beta menu option handler
 *  \param event  An object that describes the event.
 */
void CFrame::OnAddFishBeta(wxCommandEvent& event)
{
    if (mAquarium.GetBubbleCount() >= 1)
    {
        mAquarium.BubblePoints(-1);
        mAquarium.AddItem(new CFishBeta(&mAquarium));
    }
    Refresh();
}

/*! \brief Add Fish/Nemo menu option handler
 *  \param event  An object that describes the event.
 */
void CFrame::OnAddFishNemo(wxCommandEvent& event)
{
    if (mAquarium.GetBubbleCount() >= 7)
    {
        mAquarium.BubblePoints(-7);
        mAquarium.AddItem(new CFishNemo(&mAquarium));
    }
    Refresh();
}

/*! \brief Add Fish/Molly menu option handler
 *  \param event  An object that describes the event.
 */
void CFrame::OnAddFishMolly(wxCommandEvent& event)
{
    if (mAquarium.GetBubbleCount() >= 4)
    {
        mAquarium.BubblePoints(-4);
        mAquarium.AddItem(new CFishMolly(&mAquarium));
    }
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
    if (mAquarium.GetBubbleCount() >= 10)
    {
        mAquarium.BubblePoints(-10);
        mAquarium.AddItem(new CAnimatedTreasure(&mAquarium));
    }
    Refresh();
}

/*! \breif Add Care/Clean menu option handler
 *  \param event  An object that describes the event.
 */
void CFrame::OnClean(wxCommandEvent& event)
{
    if (mAquarium.GetBubbleCount() >= 5)
    {
        mAquarium.BubblePoints(-5);
        mAquarium.Clean();
    }
    Refresh();
}

/*! \brief Add Care/Feed menu option handler
 *  \param event  An object that describes the event.
 */
void CFrame::OnFeed(wxCommandEvent& event)
{
    if (mAquarium.GetBubbleCount() >= 3)
    {
        mAquarium.BubblePoints(-3);
        mAquarium.Feed();
    }
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

/*! \brief On Pause event handler
 *
 * \param event A wxEvent item describing the event
 */
void CFrame::OnPause(wxCommandEvent& event)
{
    if (!mAquarium.IsPaused())
        mAquarium.Pause(true);
    else
        mAquarium.Pause(false);
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
    if ((event.m_x >= 0 && event.m_x <= 68)
            && ((event.m_y <= this->m_height) && event.m_y >= this->m_height - 59 * 2))
    {
        ToggleScrollMode();
    }

    if (!mAquarium.IsPaused() && !mIsScrollMode)
    {
        mGrabbedItem = mAquarium.HitTest(event.m_x - mAquarium.GetAquariumTestPointX(),
                                         event.m_y - mAquarium.GetAquariumTestPointY());
        if (mGrabbedItem != NULL)
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
    }
    else
    {
        // Check mouse clicked and scroll mode is active
        if (event.m_leftDown && mIsScrollMode)
        {
            //! Any image outside the frame
            double imageOutsideX = 2560 - this->m_width;
            double imageOutsideY = 806 - this->m_height;

            // Set image bounds
            if (mAquarium.GetAquariumTestPointX() <= 0.0 &&
                    mAquarium.GetAquariumTestPointX() >= -imageOutsideX)
            {
                // Stop scrolling too far right
                if (mMouseLocationX > event.m_x &&
                        mAquarium.GetAquariumTestPointX() > -imageOutsideX + (mMouseLocationX - event.m_x))
                {
                    mAquarium.SetAquariumTestPointX(mAquarium.GetAquariumTestPointX()
                                                    - (mMouseLocationX - event.m_x));
                    mMouseLocationX = event.m_x;
                }
                    // Stop scrolling too far left
                else if (mMouseLocationX < event.m_x &&
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
            if (mAquarium.GetAquariumTestPointY() <= 0.0 &&
                    mAquarium.GetAquariumTestPointY() >= -imageOutsideY)
            {
                // Stop scrolling too far right
                if (mMouseLocationY > event.m_y &&
                        mAquarium.GetAquariumTestPointY() > -imageOutsideY + (mMouseLocationY - event.m_y))
                {
                    mAquarium.SetAquariumTestPointY(mAquarium.GetAquariumTestPointY()
                                                    - (mMouseLocationY - event.m_y));
                    mMouseLocationY = event.m_y;
                }
                    // Stop scrolling too far left
                else if (mMouseLocationY < event.m_y &&
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

    // Create space to make appearance of replacing text
    std::wstringstream strSpace;
    for (int i = 0; i < 100; i++)
        strSpace << "\n";
    strSpace << std::ends;
    mReporter->Report(strSpace.str());

    // Display basic statistics
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

    // Display time since last cleaned
    std::wstringstream strDirty;
    strDirty << L"Time since last cleaned: " << mAquarium.GetLastClean() << "\n";

    // Tell user bubble loss rate from not cleaning (see CAquarium.cpp::Update())
    // 0-20 = clean
    // 20-40 = stage 1
    // 40-60 = stage 2
    // 60+   = stage 3
    strDirty << L"Bubble loss rate: ";
    if (mAquarium.GetLastClean() <= 20.00)
        strDirty << L"0 bubbles/second" << std::ends;
    else if (mAquarium.GetLastClean() >= 20.00 && mAquarium.GetLastClean() <= 40.00)
        strDirty << L"1 bubbles/second" << std::ends;
    else if (mAquarium.GetLastClean() >= 40.00 && mAquarium.GetLastClean() <= 60.00)
        strDirty << L"2 bubbles/second" << std::ends;
    else
        strDirty << L"3 bubbles/second" << std::ends;
    mReporter->Report(strDirty.str());

    // Display time since last fed
    std::wstringstream strFed;
    strFed << L"Time since last fed: " << mAquarium.GetLastFed() << "\n";

    // Warn user if fish will starve and when
    if (mAquarium.GetLastFed() >= 20.00)
    {
        // 30.00 = time when fish will starve (see CAquarium.cpp::Update())
        strFed << L"!!!WARNING!!! Fish will starve in: "
                << (30.00 - mAquarium.GetLastFed()) << std::ends;
    }
    else
        strFed << std::ends;

    // Lose if fish are not fed (see Game Outline on project website)
    if (mAquarium.GetLastFed() >= 30.00)
    {
        wxMessageBox(L"You lose!  Your fish have died.  Why would you not feed"
                     "them?  Animal cruelty!  Feel free to try again.",
                     L"Game Over...",
                     wxOK | wxICON_INFORMATION, this);
        mAquarium.EndGame();
        if (mIsScrollMode)
            ToggleScrollMode();
    }

    mReporter->Report(strFed.str());

    // Display total number of bubbles collected and how many to go
    std::wstringstream strBubbles;
    if (mAquarium.GetBubbleCount() >= 1 && mAquarium.GetBubbleCount() < 100)
    {
        strBubbles << L"Number of Bubbles: " << mAquarium.GetBubbleCount() << "\n";
        strBubbles << (100 - mAquarium.GetBubbleCount()) << L" bubbles to go!" << std::ends;
    }
    else if (mAquarium.GetBubbleCount() >= 100)
    {
        // Play has won (goal, collect 100 bubbles)
        wxMessageBox(L"You managed to collect 100 bubbles!  Sadly, you also wasted"
                     " a good chunk of time plaything this simple game and won't get"
                     " that time back.  Please feel free to play again.",
                     L"You Win!",
                     wxOK | wxICON_INFORMATION, this);
        mAquarium.EndGame();
        if (mIsScrollMode)
            ToggleScrollMode();
    }
    else
    {
        // Player has lost (ran out of bubbles)
        wxMessageBox(L"You lose!  You have lost all your bubbles.  How pathetic..."
                     "feel free to try again.",
                     L"Game Over...",
                     wxOK | wxICON_INFORMATION, this);
        mAquarium.EndGame();
        if (mIsScrollMode)
            ToggleScrollMode();
    }
    mReporter->Report(strBubbles.str());
}
