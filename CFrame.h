/*!
 * \file CFrame.h
 *
 * \author Team Land Shark
 */

#pragma once
#ifndef CFRAME_H
#define	CFRAME_H

#include "wx/prec.h"
#include "CAquarium.h"
#include "CItem.h"
#include "CReporter.h"

//! Program main display frame
class CFrame : public wxFrame
{
public:
    CFrame();
    //! Default copy constructor
    CFrame(const CFrame &orig);
    virtual ~CFrame();
    
    DECLARE_EVENT_TABLE()
    //!  Ids Handles for the event table       
    enum Ids 
    {
        ID_Exit=1, 
        ID_About, 
        ID_AddFishBeta, 
        ID_AddFishNemo, 
        ID_AddFishMolly, 
        ID_FileTrashCan,
        ID_AddDecorTreasure, 
        ID_AddAnimatedChest, 
        ID_SaveAs,
        ID_FileOpen, 
        ID_Timer,
        ID_ReportDisplay,
        ID_Clean, 
        ID_Feed,
    };
    
    // Add object events
    // - Fish
    void OnAddFishBeta(wxCommandEvent& event);
    void OnAddFishNemo(wxCommandEvent& event);
    void OnAddFishMolly(wxCommandEvent& event);
    
    // - Chests
    void OnAddDecorTreasure(wxCommandEvent& event);
    void OnAddAnimatedChest(wxCommandEvent& event);
    
    // - Environment
    void OnClean(wxCommandEvent& event);
    void OnFeed(wxCommandEvent& event);
    
    // - User interaction
    void OnLeftButtonDown(wxMouseEvent &event);
    void OnMouseMove(wxMouseEvent &event);
    
    // - Event handlers for save/load the aquarium
    void OnFileSaveAs(wxCommandEvent& event);
    void OnFileOpen(wxCommandEvent& event);
    
    // - File Menu event handlers
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnFileTrashCan(wxCommandEvent& event);
    
    // - Other Event handlers
    void OnTimer(wxTimerEvent &event);
    void OnReport(wxTimerEvent &event);
    void OnPaint(wxPaintEvent &event);
    
    /*! \brief Getter for frame
     *  \returns A pointer to this frame
     */
    CFrame* GetFrame() { return this; }
    
    /*! \brief Getter for the current frame width
     *  \returns int value for frame width
     */
    int GetCurrWidth() {return this->m_width;}
    
    /*! \brief Getter for the current frame height
     *  \returns int value for frame height
     */
    int GetCurrHeight() {return this->m_height;}
    
    //! Toggle for scroll mode
    void ToggleScrollMode() { mIsScrollMode = mIsScrollMode ? false:true; }
    
private:
    wxBitmap    mScrollModeActive;      //!< Scroll mode active button image to use
    wxBitmap    mScrollModeInactive;    //!< Scroll mode inactive button image to use
    
    //! An object that describes our aquarium
    CAquarium  mAquarium;
    
    //! Any item we are currently dragging
    CItem *mGrabbedItem;
    
    //! Pointer to the trash can menu option
    wxMenuItem *mFileTrashCanMenuOption;
    
    //! A timer for animation
    wxTimer mTimer;
    
    //! A timer for report display
    wxTimer mReport;
    
    //! The current Unix time
    long long mCurrentTime;
    
    //! control key is pressed?
    bool m_controlDown;
    
    //! scroll mode boolean
    bool mIsScrollMode;
    
    //! A reporter window
    CReporter *mReporter;
    
    //! Current mouse location X and Y
    double mMouseLocationX;
    double mMouseLocationY;
};

#endif	/* CFRAME_H */

