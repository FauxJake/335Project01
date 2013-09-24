/*!
 * \file CFishMolly.cpp
 *
 * \author David Warner
 */

#include "wx/prec.h"
#include "CFishMolly.h"
#include "CAquarium.h"

//! Maximum speed in the X direction in
//! in pixels per second
const double MaxSpeedX = 49;
//! Minimum speed in the X direction in
//! in pixels per second
const double MinSpeedX = 30;

//! Maximum speed in the Y direction in
//! in pixels per second
const double MaxSpeedY = 49;
//! Minimum speed in the Y direction in
//! in pixels per second
const double MinSpeedY = 30;

//! Fish filename 
const std::wstring FishMollyImageName(L"molly.png");

/*! Constructor
 * \param *aquarium The aquarium to draw to
 */
CFishMolly::CFishMolly(CAquarium *aquarium) : CFish(aquarium, FishMollyImageName)
{   
    CFish::SetSpeedX(MinSpeedX + ((double)rand() / RAND_MAX) * (MaxSpeedX - MinSpeedX));
    CFish::SetSpeedY(MinSpeedY + ((double)rand() / RAND_MAX) * (MaxSpeedY - MinSpeedY));
}

/*! \brief Clone function
 * \returns a copy of this object.
 */
CItem *CFishMolly::Clone()
{
    return new CFishMolly(*this);
}

/*! \brief Copy Constructor
 * \param orig The object we are copying
 */
CFishMolly::CFishMolly(const CFishMolly &orig) : CFish(orig)
{
    
}

//! Destructor
CFishMolly::~CFishMolly()
{
}

wxXmlNode *CFishMolly::XmlSave()
{
    // Use the version in the base class to create the node
    // and include common information
    wxXmlNode *node = CFish::XmlSave();
    node->AddAttribute(L"type", L"molly");
    return node;
}