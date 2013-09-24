/*!
 * \file CFish.h
 *
 * \author David Warner
 */

#pragma once
#ifndef CFISH_H
#define	CFISH_H

#include "CItem.h"

/*! \brief Base class for a fish
 * This applies to all of the fish, but not the decor
 * items in the aquarium.
 */

class CFish : public CItem
{
public:
    virtual ~CFish() = 0;
    
    void Update(double elapsed);
    
    wxXmlNode *XmlSave();
    void XmlLoad(wxXmlNode *node);
    
    //! Sets the x speed of the fish
    void SetSpeedX(double speedx) {mSpeedX = speedx;}
    
    //! Get the y speed of the fish
    void SetSpeedY(double speedy) {mSpeedY = speedy;}
    
protected:
    CFish(CAquarium *aquarium, const std::wstring &filename);
    CFish(const CFish &);
    
private:
    //! Default constructor (disabled)
    CFish();
    
    //! Fish speed in the X direction
    double mSpeedX;
    
    //! Fish speed in the Y direction
    double mSpeedY;

};

#endif	/* CFISH_H */

