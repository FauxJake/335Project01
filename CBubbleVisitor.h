/* 
 * File:   CBubbleVisitor.h
 * Author: morga199
 *
 * Created on October 1, 2013, 4:17 PM
 */

#ifndef CBUBBLEVISITOR_H
#define	CBUBBLEVISITOR_H

#include "CItemVisitor.h"

class CBubbleVisitor : public CItemVisitor
{
public:
    CBubbleVisitor() {mBubbles=0;}
    virtual ~CBubbleVisitor();
    
    virtual void VisitBubble(CEffectBubbles *bubble);
    
    int GetBubbleCount() {return mBubbles;}
    
private:

    //! number of bubbles in tank
    int mBubbles;
    
    
};

#endif	/* CBUBBLEVISITOR_H */

