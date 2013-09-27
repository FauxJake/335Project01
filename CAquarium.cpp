/*!
 * \file CAquarium.cpp
 *
 * \author David Warner
 */

#include "wx/prec.h"
#include <map>
#include <list>
#include <string>
#include <sstream>

#include "CFish.h"
#include "CAquarium.h"
#include "CFishBeta.h"
#include "CFishMolly.h"
#include "CFishNemo.h"
#include "CDecorTreasure.h"
#include "CItemVisitor.h"

//! Images Directory
const std::wstring DirectoryContainingImages(L"images/");

CAquarium::CAquarium()
{
    if(!mBackground.LoadFile(L"images/backgroundW.png", wxBITMAP_TYPE_PNG))
        wxMessageBox(L"Failed to open image background.png");
    
    if(!mTrashcan.LoadFile(L"images/trashcan.png", wxBITMAP_TYPE_PNG))
        wxMessageBox(L"Failed to open image trashcan.png");
    
    mTrashCanActive = false;
    
    mTimerClean = mTimerFeed = 0.00;
}

//! \brief Destructor
/*! Deallocates any allocated memory
 */
CAquarium::~CAquarium()
{
    Clear();
}

/*! Draw the aquarium
 * \param dc The device context to draw onto
 */
void CAquarium::OnDraw(wxDC &dc)
{
     dc.DrawBitmap(mBackground, 0, 0);
     
     if(mTrashCanActive) 
     {
        dc.DrawBitmap(mTrashcan, 0, 0);
     }
     
     for(std::list<CItem *>::iterator t=mItems.begin(); t!=mItems.end(); t++)
     {
         CItem *item = *t;
         item->Draw(dc);
     }
}

/*! \brief Get an image from the image cache
 *
 * Given a base name for an image file, determine if
 * we have already loaded it. If we have, return a pointer
 * to the wxBitmap object in the cache. If we have not
 * previously loaded it, load it into the cache and then
 * return a pointer to the image.
 * \param name The base name of the image file. We put images/ onto
 * the front of this because that is where the file is located.
 * \returns Pointer to cached image object or NULL if file not found.
 */
wxImage *CAquarium::GetCachedImage(const std::wstring name)
{
    // See if the name exists in the cache already.
    std::map<std::wstring, wxImage>::iterator i = mImageCache.find(name);
    if(i != mImageCache.end())
    {
        // If we got here, it does exist and i->second is a
        // reference to the bitmap object.
        return &i->second;
    }

    // We'll add the path to the name of the file here.
    std::wstring realname = DirectoryContainingImages + name;

    // Create a bitmap image and load the file into it.
    wxImage bitmap;
    if(!bitmap.LoadFile(realname.c_str()))
    {
         std::wstring msg = std::wstring(L"Unable to open image ") + realname;
         wxMessageBox(msg.c_str());
         return NULL;
    }

    // Add it to the cache and return it.
    mImageCache[name] = bitmap;
    return &mImageCache[name];
}

/*! \brief Add an item to the aquarium
 * 
 * This automatically centers the new item in the background image.
 * 
 * \param item New item to add
 */
void CAquarium::AddItem(CItem *item)
{
    item->SetLocation(mBackground.GetWidth()/2, mBackground.GetHeight()/2);
    mItems.push_back(item);
    
    // Check if first fish added
    int fishCount = 0;
    for(std::list<CItem *>::iterator i=mItems.begin(); 
            i != mItems.end();  i++) 
    {
        CItem *item = *i;
        
        if((*i)->IsFish())
            fishCount++;
    }
    
    // Start feed timer if first fish added
    if (fishCount == 1 && mTimerFeed == 0.00)
        mTimerFeed = 0.01;
}

/*! \brief Test an x,y click location to see if it clicked
 * on some item in the aquarium.
 * \param x X location
 * \param y Y location
 * \returns Pointer item we clicked on or null if none.
 */
CItem *CAquarium::HitTest(int x, int y) 
{
    for(std::list<CItem *>::reverse_iterator i=mItems.rbegin();  i != mItems.rend();  i++) 
    {
        if((*i)->HitTest(x, y)) 
        {
            return *i;
        }
    }
    return  NULL;
}

/*! \brief Move an item to the front of the list of items.
 * 
 * Removes item from the list and adds it to the end so it 
 * will display last.
 * \param item The item to move
 */
void CAquarium::MoveToFront(CItem *item) 
{
    mItems.remove(item);
    mItems.push_back(item);
}

/*! \brief Toggle the state of the flag mTrashCanActive
 */
void CAquarium::ToggleTrashCanActive()
{
    mTrashCanActive = !mTrashCanActive;
}

/*! \brief Returns true if over trashcan
 */
bool CAquarium::IsOverTrashcan(int x, int y) 
{
    if(!mTrashCanActive) 
    {
        return false;
    }
    
    return x < mTrashcan.GetWidth() && y < mTrashcan.GetHeight();
}

/*! \brief Delete an item from the aquarium
 * 
 * Note that the item is destroyed after deletion.
 * 
 * \param item The item to delete.
 */
void CAquarium::DeleteItem(CItem *item)
{
    mItems.remove(item);
    delete item;
}

/*! \brief Save the aquarium as a .aqua XML file.
 * 
 * Open an XML file and stream the aquarium data to it.
 * 
 * \param filename - The filename of the file to save the aquarium to
 */
void CAquarium::Save(const std::wstring &filename)
{
    // Create an empty XML document
    wxXmlDocument xmlDoc;
    // Create a root node
    wxXmlNode *root = new wxXmlNode(wxXML_ELEMENT_NODE, L"aqua");
    xmlDoc.SetRoot(root);
    // This variable keeps track of the last child node we
    // added. There is not yet, so it is initially NULL.
    wxXmlNode *lastChild = NULL;

    // Iterate over all of the aquarium items so we can save each to the
    // XML document.
    for(std::list<CItem *>::const_iterator t=mItems.begin(); t!=mItems.end();  t++)
    {
        // And the tile to create a node for itself
        wxXmlNode *node = (*t)->XmlSave();

        // If we have a previous child, add this node after
        // the child.
        if(lastChild == NULL)
        {
            root->AddChild(node);
        }
        else
        {
            lastChild->SetNext(node);
        }

        lastChild = node;
    }
    // And save the file to disk
    xmlDoc.Save(filename.c_str());
}

/*! \brief Load the aquarium from a .aqua XML file.
 * 
 * Opens the XML file and reads the nodes, creating items as appropriate.
 * 
 * \param filename The filename of the file to load the aquarium from.
 */
void CAquarium::Load(const std::wstring &filename)
{
    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename.c_str()))
    {
        std::wstringstream str;
        str << L"Unable to open file " << filename << std::ends;
        wxMessageBox(str.str().c_str(),
                         L"Error",
                          wxOK | wxICON_ERROR);
        return;
    }

    // Clear our existing aquarium data
    Clear();
    
    wxXmlNode *root = xmlDoc.GetRoot();
    wxXmlNode *child = root->GetChildren();
    while(child != NULL)
    {
        // This is the tile we will create
        CItem *item = NULL;
        CFish *fish = NULL;

        // We have a tile. What type?
        wxString type = child->GetAttribute(L"type", L"");
        if(type == L"beta")
        {
            fish = new CFishBeta(this);
        }
        else if(type == L"treasure-chest")
        {
            item = new CDecorTreasure(this);
        }
        else if(type == L"molly")
        {
            fish = new CFishMolly(this);
        }
        else if(type == L"nemo")
        {
            fish = new CFishNemo(this);
        }

        if(item != NULL)
        {
            item->XmlLoad(child);
            mItems.push_back(item);
        }
        else if(fish != NULL)
        {
            fish->XmlLoad(child);
            mItems.push_back(fish);
        }
        
        // Move to the next child
        child = child->GetNext();
    }
    
}

/*! \brief Clear the aquarium data.
 * Deletes all known items in the aquarium.
 */
void CAquarium::Clear()
{
    while(!mItems.empty())
    {
        delete mItems.front();
        mItems.pop_front();
    }
}

/*! \brief Handle updates for animation, clean, and feed
 * \param elapsed The time since the last update
 */
void CAquarium::Update(double elapsed)
{
    bool unFedFish = false;
    
    mTimerClean += elapsed;
    
    if (mTimerFeed != 0.00)
        mTimerFeed += elapsed;
    
    // Change background depending on cleaning needed
    // Only check if statements if within range (save run speed)
    if (mTimerClean > 9.00 && mTimerClean < 46.00)
    {
        if (mTimerClean >= 10.00 && mTimerClean <= 10.10)
        {
            // Stage 1
            if(!mBackground.LoadFile(L"images/backgroundW1.png", wxBITMAP_TYPE_PNG))
                wxMessageBox(L"Failed to open image backgroundW1.png");
        } else if (mTimerClean >= 25.00 && mTimerClean <= 25.10)
        {
            // Stage 2
            if(!mBackground.LoadFile(L"images/backgroundW2.png", wxBITMAP_TYPE_PNG))
                wxMessageBox(L"Failed to open image backgroundW2.png");
        } else if (mTimerClean >= 45.00 && mTimerClean <= 45.10)
        {
            // Stage 3
            if(!mBackground.LoadFile(L"images/backgroundW3.png", wxBITMAP_TYPE_PNG))
                wxMessageBox(L"Failed to open image backgroundW3.png");
        }
    }
    
    if (mTimerFeed >= 80.00)
        unFedFish = true;
    
    for(std::list<CItem *>::iterator i=mItems.begin(); 
            i != mItems.end();  i++) 
    {
        CItem *item = *i;
        
        // Fish were not fed (all fish die)
        if (unFedFish)
        {   
            if((item)->IsFish())
            {
                mItems.remove(item);
                
                // mItems.end() is one back, prevent seg-fault
                i--;
            }
            
            // No fish, no feed timer
            mTimerFeed == 0.00;
        } else
            item->Update(elapsed);
    }
}

/*! \brief Resets clean timer and background
 */
void CAquarium::Clean()
{
    mTimerClean = 0.00;
    if(!mBackground.LoadFile(L"images/backgroundW.png", wxBITMAP_TYPE_PNG))
        wxMessageBox(L"Failed to open image backgroundW.png");
}

/*! \brief Resets feed timer
 */
void CAquarium::Feed()
{
    mTimerFeed == 0.01;
}

void CAquarium::Accept(CItemVisitor *visitor)
{
    for(std::list<CItem *>::iterator i=mItems.begin(); i != mItems.end(); i++)
    {
        CItem *item = *i;
        item->Accept(visitor);
    }
}