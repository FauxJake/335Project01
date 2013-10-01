/*!
 * \file CFish.cpp
 *
 * \author Team Land Shark
 */

#include "wx/prec.h"
#include <string>

#include "CFish.h"
#include "CAquarium.h"

/*! Constructor
 * \param aquarium The aquarium we are in
 * \param filename Filename for the image we use
 */
CFish::CFish(CAquarium *aquarium, const std::wstring &filename) :
        CItem(aquarium, filename) 
{
}

/*! \brief Copy Constructor
 * \param orig The object we are copying
 */
CFish::CFish(const CFish &orig) : CItem(orig)
{
    mSpeedX = orig.mSpeedX;
    mSpeedY = orig.mSpeedY;
}

CFish::~CFish()
{
}

/*! \brief Handle updates in time of our fish
 * 
 * This is called before we draw and allows us to 
 * move our fish. We add our speed times the amount
 * of time that has elapsed.
 * \param elapsed Time elapsed since the class call
 */
void CFish::Update(double elapsed) 
{
    //for scrolling ad offset here
    SetLocation(GetX() + mSpeedX * elapsed, 
                GetY() + mSpeedY * elapsed);
    
    if(mSpeedX > 0 && GetX() >= GetAquarium()->GetWidth() - 50 - GetImage()->GetWidth()/2 ||
       mSpeedX < 0 && GetX() <= GetImage()->GetWidth()/2 + 50)
    {
        mSpeedX = -mSpeedX;
        Mirror(mSpeedX < 0);
    }
    
    if(mSpeedY > 0 && GetY() >= GetAquarium()->GetHeight() - 80 - GetImage()->GetHeight()/2 ||
       mSpeedY < 0 && GetY() <= GetImage()->GetHeight()/2 + 40)
    {
        mSpeedY = -mSpeedY;
    }
}

/*! Create an XML node for this item type
 *
 * Create the XML node using the base class version of 
 * this function and add information to it specific to this
 * derived class. 
 * 
 * \returns The newly created node
 */
wxXmlNode *CFish::XmlSave()
{
    // Use the version in the base class to create the node
    // and include common information
    wxXmlNode *node = CItem::XmlSave();
    wxString SpeedX = wxString::Format(wxT("%f"), mSpeedX);
    wxString SpeedY = wxString::Format(wxT("%f"), mSpeedY);
    node->AddAttribute(L"SpeedX", SpeedX);
    node->AddAttribute(L"SpeedY", SpeedY);
    return node;
}

/*!  \brief Load the attributes for an fish node. 
 *
 * This is the  base class version that load the attributes 
 * common to all fish. Override this to load custom attributes
 * for specific fish.
 * 
 * \param node The Xml node we are loading the fish from
 */
void CFish::XmlLoad(wxXmlNode *node)
{
    CItem::XmlLoad(node);
    mSpeedX = wcstol(node->GetAttribute(L"SpeedX", L"0"), NULL, 10);
    mSpeedY = wcstol(node->GetAttribute(L"SpeedY", L"100"), NULL, 10);
    if (mSpeedX < 0) { Mirror(true);}
}