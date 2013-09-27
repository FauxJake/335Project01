/*!
 * \file CFishMolly.h
 *
 * Class for a Molly fish
 *
 * \author David Warner
 */

#ifndef CFISHMOLLY_H
#define	CFISHMOLLY_H

#include "CFish.h"

//! Class that implements a fish of type Molly
class CFishMolly : public CFish
{
public:
    CFishMolly(CAquarium *aquarium);

    virtual ~CFishMolly();
    
    wxXmlNode *XmlSave();
    
    CItem *Clone();
    
    virtual void Accept(CItemVisitor *visitor) {visitor->VisitMolly(this);}
    
private:
    //! Default constructor (disabled)
    CFishMolly();

    //! Copy constructor (disabled)
    CFishMolly(const CFishMolly &);    
};

#endif	/* CFISHMOLLY_H */