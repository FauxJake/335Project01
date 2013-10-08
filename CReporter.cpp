/* 
 * \file CReporter.h
 *
 * \author Charles B. Owen
 */

#include "wx/prec.h"
#include "CReporter.h"

BEGIN_EVENT_TABLE(CReporter, wxFrame)
    EVT_CLOSE(CReporter::OnClose)
END_EVENT_TABLE()

/*! \brief Constructor
 * 
 * Construct this object and the child window.
 * \param parent The parent top level window.
 */
CReporter::CReporter(wxFrame *parent) : wxFrame( parent, -1, L"Tank Reporter", 
                            wxPoint(1048, 20), wxDefaultSize )
{
    wxBoxSizer *vertSizer = new wxBoxSizer(wxVERTICAL);
    
    mReport = new wxTextCtrl(this, wxID_ANY, wxEmptyString,
                                 wxDefaultPosition, wxSize(300, 300),
                                 wxTE_READONLY | wxTE_MULTILINE | wxSUNKEN_BORDER);
    vertSizer->Add(mReport, 1, wxALL | wxEXPAND);
    
    SetSizer(vertSizer);
    Layout();
    vertSizer->Fit(this);
    Show(true);
}

//! \brief Destructor
CReporter::~CReporter()
{
}

/*! \brief Function called when window is closed.
 * 
 * This function is called when the window is closed.
 * It closes the parent window as well.
 * 
 * \param event The event associated with the close
 */
void CReporter::OnClose(wxCloseEvent &event)
{
    GetParent()->Close();
}

/*! \brief Add an output line to the report.
 * 
 * This will add a single line of output to the
 * report. A newline is automatically added at
 * the end of the string.
 * 
 * \param str String to add to the report.
 */
void CReporter::Report(const wxString &str)
{
    const char* endl = "\n";
    wxString newLine = wxString::FromUTF8(endl);
    mReport->AppendText(str);
    mReport->AppendText(newLine);
}