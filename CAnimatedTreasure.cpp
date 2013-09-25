/*! 
 * \file CAnimatedTreasure.cpp
 * 
 * \author Jacob M. Riesser
 */

#include "wx/prec.h"
#include "CAnimatedTreasure.h"
#include "CItem.h"
#include "CAquarium.h"

//! treasure chest filename, closed is default image
const std::wstring CAnimatedTreasureFileName(L"chest1.png");

/*! Constructor
 * \param *aquarium The aquarium to draw to
 */
CAnimatedTreasure::CAnimatedTreasure(CAquarium *aquarium) 
: CItem(aquarium, CAnimatedTreasureFileName)
{   

}

/*! \brief Copy Constructor
 * \param orig The object we are copying
 */
CAnimatedTreasure::CAnimatedTreasure(const CAnimatedTreasure &orig) : CItem(orig)
{
    
}

/*! \brief Default Destructor
 */
CAnimatedTreasure::~CAnimatedTreasure()
{
}

/*! \brief Clone function
 * \returns a copy of this object.
 */
CItem *CAnimatedTreasure::Clone()
{
    return new CAnimatedTreasure(*this);
}

wxXmlNode *CAnimatedTreasure::XmlSave()
{
    wxXmlNode *node = CItem::XmlSave();
    node->AddAttribute(L"type", L"animated-treasure-chest");
    return node;
}
