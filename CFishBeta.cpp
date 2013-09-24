/*!
 * \file CFishBeta.cpp
 *
 * \author David Warner
 */

#include "wx/prec.h"
#include "CFishBeta.h"
#include "CAquarium.h"

//! Fish filename 
const std::wstring FishBetaImageName(L"beta.png");

//! Maximum speed in the X direction in
//! in pixels per second
const double MaxSpeedX = 69;
//! Minimum speed in the X direction in
//! in pixels per second
const double MinSpeedX = 50;

//! Maximum speed in the Y direction in
//! in pixels per second
const double MaxSpeedY = 69;
//! Minimum speed in the Y direction in
//! in pixels per second
const double MinSpeedY = 50;

/*! Constructor
 * \param *aquarium The aquarium to draw to
 */
CFishBeta::CFishBeta(CAquarium *aquarium) : CFish(aquarium, FishBetaImageName)
{   
    CFish::SetSpeedX(MinSpeedX + ((double)rand() / RAND_MAX) * (MaxSpeedX - MinSpeedX));
    CFish::SetSpeedY(MinSpeedY + ((double)rand() / RAND_MAX) * (MaxSpeedY - MinSpeedY));
}

/*! \brief Clone function
 * \returns a copy of this object.
 */
CItem *CFishBeta::Clone()
{
    return new CFishBeta(*this);
}

/*! \brief Copy Constructor
 * \param orig The object we are copying
 */
CFishBeta::CFishBeta(const CFishBeta &orig) : CFish(orig)
{
    
}

//! Destructor
CFishBeta::~CFishBeta()
{
}

/*! Create an XML node for this item type
 *
 * Create the XML node using the base class version of 
 * this function and add information to it specific to this
 * derived class. 
 * 
 * \returns The newly created node
 */
wxXmlNode *CFishBeta::XmlSave()
{
    // Use the version in the base class to create the node
    // and include common information
    wxXmlNode *node = CFish::XmlSave();
    node->AddAttribute(L"type", L"beta");
    return node;
}