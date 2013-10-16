/*!
 * \file CAnimatedTreasure.h
 *
 * \author Team Land Shark
 */

#pragma once
#ifndef CANIMATEDTREASURE_H
#define	CANIMATEDTREASURE_H

#include "CItem.h"

/*! \brief Objects of this class represent a treasure chest
 *
 * The treasure chest object is an animated object that updates
 * itself over time.  The treasure check should stay closed for a little while, 
 * then open using the five images. Air bubbles should then rise to the top of 
 * the tank. Stay open for a short period of time, then close, 
 * again using the five images.
 * 
 */
class CAnimatedTreasure : public CItem
{
public:
    CAnimatedTreasure(CAquarium *aquarium);

    virtual ~CAnimatedTreasure();
    
    wxXmlNode *XmlSave();
    
    CItem *Clone();
    
    void Accept(CItemVisitor *visitor) {visitor->VisitAnimatedTreasure(this);}
    
    void Update(double elapsed);
    int AdvanceAnimation(int currStage);
    
    //! virtual function to sell this Animated Chest for bubble points
    void Sell(); 
    
private:
    //! Default constructor (disabled)
    CAnimatedTreasure();

    //! Copy constructor (disabled)
    CAnimatedTreasure(const CAnimatedTreasure &);  
    
    double mChestAnimationTimer;            //!< The timer for chest animation
    int mChestStage;                        //!< The current stage of the chest
    bool mChestOpening;                     //!< var to keep track of direction of animation
    wxBitmap mChestImage;                   //!< The current image
};

#endif	/* CDECORTREASURE_H */

