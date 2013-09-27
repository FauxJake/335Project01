/*!
 * \file CCountBetaVisitor.cpp
 *
 * \author David Warner
 */

#include "wx/prec.h"
#include "CCountBetaVisitor.h"
#include "CFishBeta.h"

CCountBetaVisitor::~CCountBetaVisitor() 
{
}

void CCountBetaVisitor::VisitBeta(CFishBeta *beta)
{
    if(beta->IsBetaFish()== true)
        mNum++;
}