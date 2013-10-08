/*!
 * \file CCountFishVisitor.h
 *
 * Class that counts all types of fish 
 *
 * \author Team Land Shark
 */

#ifndef CCOUNTFISHVISITOR_H
#define	CCOUNTFISHVISITOR_H

#include "CItemVisitor.h"

class CCountFishVisitor : public CItemVisitor
{
public:
    CCountFishVisitor() {mBetaNum = 0; mNemoNum = 0; mMollyNum = 0;}
    virtual ~CCountFishVisitor();
    
    virtual void VisitBeta(CFishBeta *beta);
    virtual void VisitNemo(CFishNemo *nemo);
    virtual void VisitMolly(CFishMolly *molly);
    
    int GetBetaCount() const {return mBetaNum;}
    int GetNemoCount() const {return mNemoNum;}  
    int GetMollyCount() const {return mMollyNum;}
    
private:
    int mBetaNum;
    int mNemoNum;
    int mMollyNum;

};

#endif	/* CCOUNTFISHVISITOR_H */

