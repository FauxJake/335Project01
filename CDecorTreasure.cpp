/*!
 * \file CDecorTreasure.cpp
 *
 * \author Team Land Shark
 */

#include "wx/prec.h"
#include "CItem.h"
#include "CDecorTreasure.h"
#include "CAquarium.h"

//! Decor filename 
const std::wstring DecorTreasureImageName(L"treasure-chest.png");

/*! Constructor
 * \param *aquarium The aquarium to draw to
 */
CDecorTreasure::CDecorTreasure(CAquarium *aquarium) : CItem(aquarium, DecorTreasureImageName)
{   

}

/*! \brief Clone function
 * \returns a copy of this object.
 */
CItem *CDecorTreasure::Clone()
{
    return new CDecorTreasure(*this);
}

/*! \brief Copy Constructor
 * \param orig The object we are copying
 */
CDecorTreasure::CDecorTreasure(const CDecorTreasure &orig) : CItem(orig)
{
    
}

//! Destructor
CDecorTreasure::~CDecorTreasure()
{
}

wxXmlNode *CDecorTreasure::XmlSave()
{
    // Use the version in the base class to create the node
    // and include common information
    wxXmlNode *node = CItem::XmlSave();
    node->AddAttribute(L"type", L"treasure-chest");
    return node;
}