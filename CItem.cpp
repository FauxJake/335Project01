/*!
 * \file CItem.cpp
 *
 * \author Team Land Shark
 */

#include "wx/prec.h"
#include "CItem.h"
#include "CAquarium.h"

/*! \brief Constructor
 * \param aquarium The aquarium this item is a member of
 * \param filename The filename of the image for each item
 */
CItem::CItem(CAquarium *aquarium, const std::wstring &filename) : mAquarium(aquarium), mX(0), mY(0)
{
    mItemImageOrig = aquarium->GetCachedImage(filename);
    mItemImage = new wxImage(*mItemImageOrig);
    mItemBitmap = new wxBitmap(*mItemImage);
}

/*! \brief Copy Constructor
 * \param orig The object we are copying
 */
CItem::CItem(const CItem &orig)
{
    mX = orig.mX;
    mY = orig.mY;

    mAquarium = orig.mAquarium;
    mItemImageOrig = orig.mItemImageOrig;
    mItemImage = new wxImage(*orig.mItemImage);
    mItemBitmap = new wxBitmap(*orig.mItemBitmap);
}

//! Destructor

CItem::~CItem()
{
    delete mItemImage;
    delete mItemBitmap;
}

/*! \brief Test to see if we hit this object with a mouse.
 * \param x X position to test
 * \param y Y position to test
 * \return true if hit.
 */
bool CItem::HitTest(int x, int y)
{
    int wid = mItemImage->GetWidth();
    int hit = mItemImage->GetHeight();

    // Make x and y relative to the top-left corner of the bitmap image
    // Subtracting the center makes x, y relative to the center of the image.
    // Adding half the size makes x, y relative to the top corner of the image
    x = x - (int) GetX() + wid / 2;
    y = y - (int) GetY() + hit / 2;

    // Test to see if x, y are in the image
    if (x < 0 || y < 0 || x >= wid || y >= hit)
    {
        // We are outside the image
        return false;
    }

    // Test to see if x, y are in the drawn part of the image
    return !mItemImage->HasAlpha() || mItemImage->GetAlpha(x, y) > 0;
}

/*! Draw our fish
 * \param dc A device context to draw the fish on
 */
void CItem::Draw(wxDC &dc, double offsetX, double offsetY)
{
    int wid = mItemBitmap->GetWidth();
    int hit = mItemBitmap->GetHeight();
    dc.DrawBitmap(*mItemBitmap, int((GetX() - wid/2) + offsetX), 
                  int((GetY() - hit/2) + offsetY), true);
}

bool CItem::Animate(const std::wstring &filename)
{
    mItemImageOrig = mAquarium->GetCachedImage(filename);
    mItemImage = new wxImage(*mItemImageOrig);
    mItemBitmap = new wxBitmap(*mItemImage);
    return true;
}

/*! \brief XML function to save an aquarium item
 * 
 * This is the base class version that does the 
 * work of creating the node. Derived classes 
 * will override this function to add attributes 
 * to the node.
 * \returns The created XML node object
 */
wxXmlNode *CItem::XmlSave()
{
    // Create a new node for the item
    wxXmlNode *node = new wxXmlNode(wxXML_ELEMENT_NODE, L"item");

    node->AddAttribute(L"x", wxString::Format(L"%d", (int) mX));
    node->AddAttribute(L"y", wxString::Format(L"%d", (int) mY));

    return node;
}

/*!  \brief Load the attributes for an item node. 
 *
 * This is the  base class version that load the attributes 
 * common to all items. Override this to load custom attributes
 * for specific items.
 * 
 * \param node The Xml node we are loading the item from
 */
void CItem::XmlLoad(wxXmlNode *node)
{
    mX = wcstol(node->GetAttribute(L"x", L"0"), NULL, 10);
    mY = wcstol(node->GetAttribute(L"y", L"100"), NULL, 10);
}

/*! \brief Optionally mirror the item image
 * 
 * If mirror is true, a copy of the original image
 * will be made that is mirrored and it will be made the 
 * current image. If false, an unmirrored copy is made 
 * instead. 
 * \param mirror true if mirroring is wanted.
 */
void CItem::Mirror(bool mirror)
{
    // Delete the existing image and bitmap
    delete mItemImage;
    delete mItemBitmap;

    if (mirror)
    {
        mItemImage = new wxImage(mItemImageOrig->Mirror(true));
        mItemBitmap = new wxBitmap(*mItemImage);
    }
    else
    {
        mItemImage = new wxImage(*mItemImageOrig);
        mItemBitmap = new wxBitmap(*mItemImage);
    }
}

/*! \brief Adds bubbles to the aquarium using this item as an origin
 */
void CItem::AddBubbles(int xOffset)
{
    mAquarium->AddBubbles(this, xOffset);
}