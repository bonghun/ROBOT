
// Planar.h : main header file for the Planar application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CPlanarApp:
// See Planar.cpp for the implementation of this class
//

class CPlanarApp : public CWinAppEx
{
public:
	CPlanarApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPlanarApp theApp;
