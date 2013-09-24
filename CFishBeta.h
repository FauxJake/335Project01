/*!
 * \file CFishBeta.h
 *
 * \author David Warner
 */

#pragma once
#ifndef CFISHBETA_H
#define	CFISHBETA_H

#include "wx/prec.h"
#include "CFish.h"

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
    
    
private:
    //! Default constructor (disabled)
    CFishBeta();

    //! Copy constructor (disabled)
    CFishBeta(const CFishBeta &);    
};

#endif	/* CFISHBETA_H */
