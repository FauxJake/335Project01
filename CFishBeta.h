/*!
 * \file CFishBeta.h
 *
 * \author Team Land Shark
 */

#pragma once
#ifndef CFISHBETA_H
#define	CFISHBETA_H

#include "wx/prec.h"
#include "CFish.h"
#include "CItemVisitor.h"

//! Class that implements a fish of type Beta
class CFishBeta : public CFish
{
public:
    CFishBeta(CAquarium *aquarium);

    virtual ~CFishBeta();
    
    //! \brief Test if this item is a Beta Fish
    //! \returns true if it is
    virtual bool IsBetaFish() const {return true;}
    
    wxXmlNode *XmlSave();
    
    CItem *Clone();
    
    virtual void Accept(CItemVisitor *visitor) {visitor->VisitBeta(this);}
    
    //! virtual function to sell this fish for bubble points
    void Sell();
    
private:
    //! Default constructor (disabled)
    CFishBeta();

    //! Copy constructor (disabled)
    CFishBeta(const CFishBeta &);    
};

#endif	/* CFISHBETA_H */
