/*!
 * \file CFishNemo.h
 *
 * Class for a Nemo fish
 *
 * \author Team Land Shark
 */

#ifndef CFISHNEMO_H
#define	CFISHNEMO_H

#include "CFish.h"

//! Class that implements a fish of type Nemo
class CFishNemo : public CFish
{
public:
    CFishNemo(CAquarium *aquarium);

    virtual ~CFishNemo();
    
    //! \brief Test if this item is a Nemo Fish
    //! \returns true if it is
    virtual bool IsNemoFish() const {return true;}
    
    wxXmlNode *XmlSave();
    
    CItem *Clone();
    
    virtual void Accept(CItemVisitor *visitor) {visitor->VisitNemo(this);}
    
    //! virtual function to sell this fish for bubble points
    void Sell();
        
private:
    //! Default constructor (disabled)
    CFishNemo();

    //! Copy constructor (disabled)
    CFishNemo(const CFishNemo &);  
};

#endif	/* CFISHNEMO_H */