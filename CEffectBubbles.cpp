/*! 
 * \file CEffectBubbles.cpp
 * 
 * \author Team Land Shark
 */

#include "wx/prec.h"
#include "CEffectBubbles.h"
#include "CAquarium.h"
#include "CItem.h"

//! bubble filename 
const std::wstring BubblesFileName(L"airbubbles.png");


/*! Constructor
 * \param *aquarium The aquarium to draw to
 */
CEffectBubbles::CEffectBubbles(CAquarium *aquarium) : CItem(aquarium, BubblesFileName)
{   
    mBubblesSpeed = ((int)10 + (rand() % (int)50))*(-1);
}

/*! \brief Default Destructor
 */
CEffectBubbles::~CEffectBubbles()
{
}

/*! \brief saves bubbles
 *
 * \returns the node
 */
wxXmlNode *CEffectBubbles::XmlSave()
{
    wxXmlNode *node = CItem::XmlSave();
    wxString SpeedY = wxString::Format(wxT("%f"), mBubblesSpeed);
    node->AddAttribute(L"speed", SpeedY);
    node->AddAttribute(L"type", L"bubbles");
    return node;
}

/*! \brief Handle updates in time of our fish
 * 
 * This is called before we draw and allows us to 
 * move our fish. We add our speed times the amount
 * of time that has elapsed.
 * \param elapsed Time elapsed since the class call
 * */
void CEffectBubbles::Update(double elapsed) 
{
    SetLocation(GetX(), 
                GetY() + mBubblesSpeed * elapsed);
}

/*! \brief Clone function
 * \returns a copy of this object.
 */
CItem *CEffectBubbles::Clone()
{
    return new CEffectBubbles(*this);
}

/*! \brief Copy Constructor
 * \param orig The object we are copying
 */
CEffectBubbles::CEffectBubbles(const CEffectBubbles &orig) : CItem(orig)
{
}

bool CEffectBubbles::HitTest(int x, int y)
{
    if (CItem::HitTest(x,y))
    {
        //Point add here
        GetAquarium()->DeleteItem(this);
    }
}