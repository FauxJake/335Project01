/*!
 * \file CAquarium.h
 *
 * \author David Warner
 */

#pragma once
#ifndef CAQUARIUM_H
#define	CAQUARIUM_H

#include <map>
#include <list>
#include <string>

#include "CItem.h"

//! The aquarium class holds all items within
class CAquarium
{
public:
    CAquarium();
    virtual ~CAquarium();
    
    void OnDraw(wxDC &dc);
    
    wxImage *GetCachedImage(const std::wstring name);

    void AddItem(CItem *item);
    
    virtual CItem *HitTest(int x, int y);
    
    void MoveToFront(CItem *item);
    void ToggleTrashCanActive();
    
    //! \brief Is the trash can active?
    //! \returns true if trash can is active.
    bool IsTrashCanActive() const {return mTrashCanActive;}
    bool IsOverTrashcan(int x, int y);
    void DeleteItem(CItem *item);
    
    void Save(const std::wstring &filename);
    void Load(const std::wstring &filename);
    void Clear();
    
    void Update(double elapsed);
    
    void Clean();
    
    void Feed();
    
    void AddBubbles(CItem* origin);
    
    //! \brief Get the width of the aquarium
    //! \returns Aquarium width
    int GetWidth() const {return mBackground.GetWidth();}
   
    //! \brief Get the height of the aquarium
    //! \returns Aquarium height
    int GetHeight() const {return mBackground.GetHeight();}
    
    void Accept(CItemVisitor *visitor);
    
    //! Gets time since aquarium has been last cleaned
    double GetLastClean() { return mTimerClean; }
    
    //! Gets time since the fish have been last feed
    double GetLastFed() { return mTimerFeed; }
            
private:
    //! Default copy constructor
    CAquarium(const CAquarium& orig);
    wxBitmap    mBackground;            //!< Background image to use
    wxBitmap    mTrashcan;              //!< Trash can image to use
    bool        mTrashCanActive;        //!< Is the trash can active?
    
    //! The image cache
    std::map<std::wstring, wxImage> mImageCache;
    
    //! All of the items that populate our aquarium
    std::list<CItem *> mItems;
    
    //! Timer to check changing background image
    double mTimerClean;
    
    //! Timer to check fish being fed
    double mTimerFeed;
};

#endif	/* CAQUARIUM_H */