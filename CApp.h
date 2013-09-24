/*!
 * \file CApp.h
 *
 * \author David Warner
 */

#pragma once
#ifndef CAPP_H
#define	CAPP_H

//! Application main class
class CApp : public wxApp
{
public:
    CApp();
    //! Default copy constructor
    CApp(const CApp &orig);
    virtual ~CApp();

    virtual bool OnInit();
};

#endif	/* CAPP_H */

