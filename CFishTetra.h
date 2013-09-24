/*! 
 * \file CFishTetra.h
 * \author Jacob M. Riesser
 *
 * \brief  The header file for the CFishTetra class
 * 
 * This file contains the declaration and header information that allows us
 * to add a Beta Fish item to our aquarium.
 */

#ifndef CFISHTETRA_H
#define	CFISHTETRA_H

#include <string>
#include "CItem.h"
#include "CFish.h"

using namespace std;

//! Fish filename 
const wstring FishTetraImageName(L"neon-tetra.png");

/*! \brief Objects of this class represent items that are Beta Fish
 *
 * An object of this class is an item that we can add to our aquarium.
 * CFishTetra inherits from CItem to allow for this.
 */
class CFishTetra : public CFish
{
public:
    CFishTetra(CAquarium *aquarium);
    virtual ~CFishTetra();
    CFishTetra* Clone() const;
    
    wxXmlNode* XmlSave();
    
private:
    private:
    //! Default constructor (disabled)
    CFishTetra();

    //! Copy constructor (disabled)
    CFishTetra(const CFishTetra &); 
};

#endif	/* CFISHTETRA_H */

