/*!
 * \file CFrame.h
 *
 * \author David Warner
 */

#pragma once
#ifndef CFRAME_H
#define	CFRAME_H

#include "wx/prec.h"
#include "CAquarium.h"
#include "CItem.h"

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
        ID_OnFileCountBetaFish, 
        ID_AddDecorTreasure, 
        ID_AddAnimatedChest, 
        ID_SaveAs,
        ID_FileOpen, 
        ID_Timer, 
        ID_Clean, 
        ID_Feed
    };
    
    // Add object events
    // - Fish
    void OnAddFishBeta(wxCommandEvent& event);
    void OnAddFishNemo(wxCommandEvent& event);
    void OnAddFishMolly(wxCommandEvent& event);
    
    // - Chests
    void OnAddDecorTreasure(wxCommandEvent& event);
    void OnAddAnimatedChest(wxCommandEvent& event);
    
    void OnClean(wxCommandEvent& event);
    void OnFeed(wxCommandEvent& event);
    
    void OnLeftButtonDown(wxMouseEvent &event);
    void OnMouseMove(wxMouseEvent &event);
    
    // Event handlers for save/load the aquarium
    void OnFileSaveAs(wxCommandEvent& event);
    void OnFileOpen(wxCommandEvent& event);
    
    //File Menu event handlers
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnFileTrashCan(wxCommandEvent& event);
    void OnFileCountBetaFish(wxCommandEvent& event);
    
    // Other Event handlers
    void OnTimer(wxTimerEvent &event);
    void OnPaint(wxPaintEvent &event);
    
private:
    //! An object that describes our aquarium
    CAquarium  mAquarium;
    
    //! Any item we are currently dragging
    CItem *mGrabbedItem;
    
    //! Pointer to the trash can menu option
    wxMenuItem *mFileTrashCanMenuOption;
    
    //! A timer for animation
    wxTimer mTimer;
    
    //! The current Unix time
    long long mCurrentTime;
    
    //! control key is pressed?
    bool m_controlDown;
    
    //! scroll mode boolean
    bool mIsScrollMode;
};

#endif	/* CFRAME_H */

