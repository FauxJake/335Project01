/*!
 * \file CCountFishVisitor.cpp
 *
 * \author Team Land Shark
 */

#include "wx/prec.h"
#include "CCountFishVisitor.h"
#include "CFishBeta.h"
#include "CFishNemo.h"
#include "CFishMolly.h"

CCountFishVisitor::~CCountFishVisitor() 
{
}

void CCountFishVisitor::VisitBeta(CFishBeta *beta)
{
    if(beta->IsBetaFish())
        mBetaNum++;
}

void CCountFishVisitor::VisitNemo(CFishNemo *nemo)
{
    if(nemo->IsNemoFish())
        mNemoNum++;
}

void CCountFishVisitor::VisitMolly(CFishMolly *molly)
{
    if(molly->IsMollyFish())
        mMollyNum++;
}