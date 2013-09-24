/*!
 * \file CFishNemo.cpp
 *
 * \author David Warner
 */

#include "wx/prec.h"
#include "CFishNemo.h"
#include "CAquarium.h"

//! Fish filename 
const std::wstring FishNemoImageName(L"nemo.png");

//! Maximum speed in the X direction in
//! in pixels per second
const double MaxSpeedX = 29;
//! Minimum speed in the X direction in
//! in pixels per second
const double MinSpeedX = 10;

//! Maximum speed in the Y direction in
//! in pixels per second
const double MaxSpeedY = 29;
//! Minimum speed in the Y direction in
//! in pixels per second
const double MinSpeedY = 10;

/*! Constructor
 * \param *aquarium The aquarium to draw to
 */
CFishNemo::CFishNemo(CAquarium *aquarium) : CFish(aquarium, FishNemoImageName)
{   
    CFish::SetSpeedX(MinSpeedX + ((double)rand() / RAND_MAX) * (MaxSpeedX - MinSpeedX));
    CFish::SetSpeedY(MinSpeedY + ((double)rand() / RAND_MAX) * (MaxSpeedY - MinSpeedY));
}

/*! \brief Clone function
 * \returns a copy of this object.
 */
CItem *CFishNemo::Clone()
{
    return new CFishNemo(*this);
}

/*! \brief Copy Constructor
 * \param orig The object we are copying
 */
CFishNemo::CFishNemo(const CFishNemo &orig) : CFish(orig)
{
    
}

//! Destructor
CFishNemo::~CFishNemo()
{
}

wxXmlNode *CFishNemo::XmlSave()
{
    // Use the version in the base class to create the node
    // and include common information
    wxXmlNode *node = CFish::XmlSave();
    node->AddAttribute(L"type", L"nemo");
    return node;
}