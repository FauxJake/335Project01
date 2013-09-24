/*! 
 * \file CFishStar.cpp
 * 
 * \author Jacob M. Riesser
 */

#include "CFishStar.h"
#include "CAquarium.h"

/*! Constructor
 * \param aquarium The aquarium our Starfish is in
 */
CFishStar::CFishStar(CAquarium *aquarium) : CFish(aquarium, FishStarImageName)
{   
    SetSpeedX(0 + 7 * ((double)rand() / RAND_MAX));
    SetSpeedY(0 + 7 * ((double)rand() / RAND_MAX));
}

/*! \brief Default Destructor
 */
CFishStar::~CFishStar()
{
}

/*! \brief Clone function
 * \returns pointer to cloned item
 */
CFishStar* CFishStar::Clone() const
{
    return new CFishStar(GetAquarium());
}

/*! Create an XML node for this item type
 *
 * Create the XML node using the base class version of 
 * this function and add information to it specific to this
 * derived class. 
 * 
 * \returns The newly created node
 */
wxXmlNode *CFishStar::XmlSave()
{
    // Use the version in the base class to create the node
    // and include common information
    wxXmlNode *node = CFish::XmlSave();
    node->AddAttribute(L"type", L"star");

    return node;
}