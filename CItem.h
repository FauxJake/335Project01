/*!
 * \file CItem.h
 *
 * Base class for aquarium items
 *
 * \author David Warner
 */

#pragma once
#ifndef CITEM_H
#define	CITEM_H

#include "wx/prec.h"

class CAquarium;

//! Class for an item that appears in our aquarium
class CItem
{
public:
    virtual ~CItem();
    
    //! Get the x location of the item
    //! \returns X location
    double GetX() const {return mX;}
    
    //! Get the y location of the item
    //! \returns Y location
    double GetY() const {return mY;}
    
    //! Set the item location
    //! \param x X location
    //! \param y Y location
    void SetLocation(double x, double y) {mX = x; mY = y;}
    
    //! Draw this item
    //! \param dc Device context to draw on
    void Draw(wxDC &dc);
        
    //! Test to see if we clicked on this item
    //! \param x X location
    //! \param y Y location
    //! \returns true if we clicked on the item
    bool HitTest(int x, int y);
    
    //! \brief Test if this item is a Beta Fish
    //! \returns true if it is
    virtual bool IsBetaFish() const {return false;}
    
    virtual wxXmlNode *XmlSave();
    virtual void XmlLoad(wxXmlNode *node);
    
    //! \brief Handle updates for animation
    //! \param elapsed The time since the last update
    virtual void Update(double elapsed) {}
    
    //! \brief Get the aquarium this item is in
    //! \returns Aquarium pointer
    CAquarium *GetAquarium() {return mAquarium;}
    
    void Mirror(bool mirror);
    
    //! \brief Get the item image this item is in
    //! \returns ItemImage pointer
    wxImage *GetImage() {return mItemImage;}
    
    //! \brief Clone this object
    //! \returns A copy of this object, no matter
    //! what actual underlying type it is.
    virtual CItem *Clone() = 0;
    
    //! Tells item is not a fish
    virtual bool IsFish() { return false; }
    
protected:
    CItem(CAquarium *aquarium, const std::wstring &filename);
    CItem(const CItem &);

private:
    //! Default constructor (disabled)
    CItem();
    
    //! The aquarium this item is contained in
    CAquarium   *mAquarium;
    
    // Item location in the aquarium
    double  mX;         //!< X location for the center of the item
    double  mY;         //!< Y location for the center of the item

    wxImage *mItemImage;        //!< Pointer to the image of the fish
    wxBitmap *mItemBitmap;      //!< Pointer to a bitmap for the fish
    
    wxImage *mItemImageOrig;    //!< Pointner to the original item image
    
};

#endif	/* CITEM_H */