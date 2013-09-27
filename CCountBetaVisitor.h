/*!
 * \file CCountBetaVisitor.h
 *
 * Class that counts the beta fish 
 *
 * \author David Warner
 */

#ifndef CCOUNTBETAVISITOR_H
#define	CCOUNTBETAVISITOR_H

#include "CItemVisitor.h"

class CCountBetaVisitor : public CItemVisitor
{
public:
    CCountBetaVisitor() {mNum = 0;}
    virtual ~CCountBetaVisitor();
    
    virtual void VisitBeta(CFishBeta *beta);
    
    int GetCount() const {return mNum;}
    
private:
    int mNum;

};

#endif	/* CCOUNTBETAVISITOR_H */

