/*! 
 * \file CFishTetra.cpp
 * 
 * \author Jacob M. Riesser
 */

#include "CFishTetra.h"
#include "CAquarium.h"

/*! \brief Constructor
 */
CFishTetra::CFishTetra(CAquarium *aquarium) : CFish(aquarium, FishTetraImageName)
{   
    SetSpeedX(0 + 30 * ((double)rand() / RAND_MAX));
    SetSpeedY(0 + 25 * ((double)rand() / RAND_MAX));
}

/*! \brief Default Destructor
 */
CFishTetra::~CFishTetra()
{
}

/*! \brief Clone function
 * \returns pointer to cloned item
 */
CFishTetra* CFishTetra::Clone() const
{
    return new CFishTetra(GetAquarium());
}

/*! Create an XML node for this item type
 *
 * Create the XML node using the base class version of 
 * this function and add information to it specific to this
 * derived class. 
 * 
 * \returns The newly created node
 */
wxXmlNode *CFishTetra::XmlSave()
{
    // Use the version in the base class to create the node
    // and include common information
    wxXmlNode *node = CFish::XmlSave();
    node->AddAttribute(L"type", L"tetra");

    return node;
}