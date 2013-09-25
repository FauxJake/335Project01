/*!
 * \file CAnimatedTreasure.h
 *
 * \author Jacob M. Riesser
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
    
private:
    //! Default constructor (disabled)
    CAnimatedTreasure();

    //! Copy constructor (disabled)
    CAnimatedTreasure(const CAnimatedTreasure &);    
};

#endif	/* CDECORTREASURE_H */

