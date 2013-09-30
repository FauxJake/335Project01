/*! 
 * \file CEffectBubbles.h
 * \author Jacob M. Riesser
 *
 * \brief  
 * 
 * 
 */


#pragma once
#ifndef CEFFECTBUBBLES_H
#define	CEFFECTBUBBLES_H

#include "CItem.h"

/*! \brief Objects of type bubbles are bubbles
 */
class CEffectBubbles : public CItem
{
public:
    CEffectBubbles(CAquarium*);
    CEffectBubbles(const CEffectBubbles &orig);
    virtual ~CEffectBubbles();
    
    /*! \brief Setter for bubble speed
     * \param speed A double representing speed
     */
    void SetSpeed(double speed) { mBubblesSpeed = speed; }
    
    wxXmlNode* XmlSave();
    
    void Update(double elapsed);
    
    void Accept(CItemVisitor *){};
    
    CItem *Clone();
    
private:
    //! disabled default constructor
    CEffectBubbles();
    
    double mBubblesSpeed;               //!< speed of bubbles (-Y value))
};

#endif	/* CEFFECTBUBBLES_H */

