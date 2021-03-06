#if !defined(AFX_ICONSTATIC_H__DE300890_E0CF_11D6_B83F_00010207827B__INCLUDED_)
#define AFX_ICONSTATIC_H__DE300890_E0CF_11D6_B83F_00010207827B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IconStatic.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Fenster CIconStatic 

class CIconStatic : public CStatic
{
// Konstruktion
public:
	CIconStatic();

// Attribute
public:

// Operationen
public:

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CIconStatic)
	public:
	//}}AFX_VIRTUAL

// Implementierung
public:
	bool SetIcon(UINT nIconID);
	bool SetIcon(CString strFilePath);
	bool SetText(CString strText);
	bool SetText(CString strText,CString strFilePath);
	bool Init(UINT nIconID);
	virtual ~CIconStatic();

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	CStatic m_wndPicture;
	UINT	m_nIconID;
	CString m_strText;
	CBitmap m_MemBMP;

	//{{AFX_MSG(CIconStatic)
		afx_msg void OnSysColorChange();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_ICONSTATIC_H__DE300890_E0CF_11D6_B83F_00010207827B__INCLUDED_
