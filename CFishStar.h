/*! 
 * \file CFishStar.h
 * \author Jacob M. Riesser
 *
 * \brief  
 * 
 * 
 */

#ifndef CFISHSTAR_H
#define	CFISHSTAR_H

#include <string>
#include "CItem.h"
#include "CFish.h"


using namespace std;

//! Fish filename 
const wstring FishStarImageName(L"starfish.png");

/*! \brief Objects of this class represent items that are Beta Fish
 *
 * An object of this class is an item that we can add to our aquarium.
 * CFishStar inherits from CItem to allow for this.
 */
class CFishStar : public CFish
{
public:
    CFishStar(CAquarium *aquarium);
    virtual ~CFishStar();
    CFishStar* Clone() const;
    
    wxXmlNode* XmlSave();
    
private:
    private:
    //! Default constructor (disabled)
    CFishStar();

    //! Copy constructor (disabled)
    CFishStar(const CFishStar &);  
};

#endif	/* CFISHSTAR_H */

