/*! 
 * \file CAnimatedTreasure.cpp
 * 
 * \author Team Land Shark
 */

#include "wx/prec.h"
#include "CAnimatedTreasure.h"
#include "CAquarium.h"

//! treasure chest filename, closed is default image
const std::wstring CAnimatedTreasureFileNames [5] =
{ 
    L"chest1.png",
    L"chest2.png",
    L"chest3.png",
    L"chest4.png",
    L"chest5.png"
};

/*! Constructor
 * \param *aquarium The aquarium to draw to
 */
CAnimatedTreasure::CAnimatedTreasure(CAquarium *aquarium)
: CItem(aquarium, CAnimatedTreasureFileNames[0])
{
    mChestAnimationTimer = 0.0;
    mChestStage = 0;
    mChestOpening = true;
}

/*! \brief Copy Constructor
 * \param orig The object we are copying
 */
CAnimatedTreasure::CAnimatedTreasure(const CAnimatedTreasure &orig) : CItem(orig)
{

}

/*! \brief Default Destructor
 */
CAnimatedTreasure::~CAnimatedTreasure()
{
}

/*! \brief Clone function
 * \returns a copy of this object.
 */
CItem *CAnimatedTreasure::Clone()
{
    return new CAnimatedTreasure(*this);
}

wxXmlNode *CAnimatedTreasure::XmlSave()
{
    wxXmlNode *node = CItem::XmlSave();
    node->AddAttribute(L"type", L"animated-chest");
    return node;
}

/*! \brief Handles the update over time method
 * 
 *  Breakdown of timing:
 *      0-10s   - Chest is closed (Stage 0)
 *      10-12s  - Stage 1
 *      12-14   - Stage 2
 *      14-16   - Stage 3
 *      18-28   - Open Chest (Stage 4)
 * 
 *  after open is reached the mChestAnimationTimer will reset to 0 and
 *  the animation will cycle through again
 * 
 * \param elapsed A double value that describes the time since the last update
 */
void CAnimatedTreasure::Update(double elapsed)
{
    mChestAnimationTimer += elapsed;
    
    // NOTE: comments are for first iteration only
    // closed -> stage 1, time here represents open AND closed timer
    if(mChestAnimationTimer >= 2.00 && mChestAnimationTimer <= 2.03)
        this->AdvanceAnimation(mChestStage);
    
    // stage 1 -> stage 2
    else if(mChestAnimationTimer >= 4.00 && mChestAnimationTimer <= 4.03)
        this->AdvanceAnimation(mChestStage);
    
    // stage 2 -> stage 3
    else if(mChestAnimationTimer >= 6.00 && mChestAnimationTimer <= 6.03)
        this->AdvanceAnimation(mChestStage);
    
    // stage 3 -> open
    else if(mChestAnimationTimer >= 8.00 && mChestAnimationTimer <= 8.03)
        this->AdvanceAnimation(mChestStage);
    
    // open, reset timer for second iteration
    else if(mChestAnimationTimer >= 10.00)
    {
        this->AdvanceAnimation(mChestStage);
        mChestAnimationTimer = 0.00;
    }
    else
    {}
}

/*! \brief A function to advance the chest animation
 * \param currStage An int representing the current stage of chest animation
 * \returns and int representing the next current stage of animation after
 * advancement
 */
int CAnimatedTreasure::AdvanceAnimation(int currStage)
{
    switch (currStage)
    {
        // chest is closed
        case 0:
            if (!Animate(CAnimatedTreasureFileNames[0]))
                break;
            mChestStage = 1;
            mChestOpening = true;
            break;

        // first animation
        case 1:
            if (!Animate(CAnimatedTreasureFileNames[1]))
                break;
            mChestStage = mChestOpening ? 2:0;
            break;
        
        // second animation
        case 2:
            if (!Animate(CAnimatedTreasureFileNames[2]))
                break;
            mChestStage = mChestOpening ? 3:1;
            break;

        // third animation
        case 3:
            if (!Animate(CAnimatedTreasureFileNames[3]))
                break;
            mChestStage = mChestOpening ? 4:2;
            break;
            
        // chest is open
        case 4:
            if (!Animate(CAnimatedTreasureFileNames[4]))
                break;
            mChestStage = 3;
            mChestOpening = false;
            AddBubbles();
            break;

    }
}