/*!
 * \file CFishNemo.h
 *
 * Class for a Nemo fish
 *
 * \author David Warner
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
    
    wxXmlNode *XmlSave();
    
    CItem *Clone();
        
private:
    //! Default constructor (disabled)
    CFishNemo();

    //! Copy constructor (disabled)
    CFishNemo(const CFishNemo &);  
};

#endif	/* CFISHNEMO_H */