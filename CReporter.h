/* 
 * \file CReporter.h
 * 
 * This class provides a simple pop-up box 
 * where the results of reporting can appear.
 * It makes a simple scrolling window.
 *
 * \author Charles B. Owen
 */

#ifndef CREPORTER_H
#define	CREPORTER_H

#include "wx/prec.h"

/*! \brief Pop-up reporter window.
 * 
 * This class is a single frame that can be popped
 * up and display reports.
 */
class CReporter : public wxFrame
{
public:
    CReporter(wxFrame *parent);
    virtual ~CReporter();
    
    void OnClose(wxCloseEvent &event);
    
    void Report(const wxString &str);
    
    DECLARE_EVENT_TABLE()
    
private:
    //! Copy constructor (disabled)
    CReporter(const CReporter& orig);
    
    //! The window we display the report in
    wxTextCtrl *mReport;
    
};

#endif	/* CREPORTER_H */

