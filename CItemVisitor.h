/*!
 * \file CItemVisitor.h
 *
 * Base class for visitors
 *
 * \author Team Land Shark
 */

#ifndef CITEMVISITOR_H
#define	CITEMVISITOR_H

class CFishBeta;
class CFishMolly;
class CFishNemo;
class CDecorTreasure;
class CAnimatedTreasure;
class CEffectBubbles;

class CItemVisitor {
public:
    CItemVisitor();
    virtual ~CItemVisitor();
    
    virtual void VisitBeta(CFishBeta *beta) {}
    virtual void VisitMolly(CFishMolly *molly) {}
    virtual void VisitNemo(CFishNemo *nemo) {}
    virtual void VisitTreasure(CDecorTreasure *chest) {}
    virtual void VisitAnimatedTreasure(CAnimatedTreasure *animated) {}
    virtual void VisitBubble(CEffectBubbles *bubble) {}
    
private:

};

#endif	/* CITEMVISITOR_H */

