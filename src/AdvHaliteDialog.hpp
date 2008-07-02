
//         Copyright Eoin O'Callaghan 2006 - 2008.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include "stdAfx.hpp"
#include "DdxEx.hpp"

#include "HaliteTabCtrl.hpp"
#include "advtabs/ThemeTestDialog.hpp"
#include "advtabs/Torrent.hpp"
#include "advtabs/Peers.hpp"
#include "advtabs/Tracker.hpp"
#include "advtabs/Debug.hpp"
#include "advtabs/Files.hpp"

#include "HaliteListManager.hpp"

class HaliteWindow;

class AdvHaliteDialog :
	public ATL::CDialogImpl<AdvHaliteDialog>,
	private WTL::CDialogResize<AdvHaliteDialog>
{
protected:
	typedef AdvHaliteDialog thisClass;
	typedef ATL::CDialogImpl<AdvHaliteDialog> baseClass;
	typedef WTL::CDialogResize<AdvHaliteDialog> resizeClass;
	friend class resizeClass;
	
public:
	enum { IDD = IDD_ADVHALITEDLG };

	AdvHaliteDialog(HaliteWindow& halWindow) :
		m_torrent(halWindow),
		m_peers(halWindow),
		m_files(halWindow),
		m_tracker(halWindow),
		m_debug(halWindow)
	{}

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		return tabCtrl_.PreTranslateMessage(pMsg);
	}

	BEGIN_MSG_MAP_EX(thisClass)
		MSG_WM_INITDIALOG(onInitDialog)
		MSG_WM_CLOSE(onClose)
		MSG_WM_SIZE(OnSize)

		if(uMsg == WM_FORWARDMSG)
			if(PreTranslateMessage((LPMSG)lParam)) return TRUE;

		CHAIN_MSG_MAP(resizeClass)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	BEGIN_DLGRESIZE_MAP(thisClass)
		DLGRESIZE_CONTROL(IDC_TAB, (DLSZ_SIZE_X | DLSZ_SIZE_Y))
		DLGRESIZE_CONTROL(IDC_ADVDLG_VERSION, (DLSZ_MOVE_X))

	END_DLGRESIZE_MAP()

	LRESULT onInitDialog(HWND, LPARAM);
		void OnSize(UINT, WTL::CSize);
	void onClose();

protected:
	void InitializeControls(void);
	void InitializeValues(void);

	CHalTabCtrl tabCtrl_;
	boost::scoped_ptr<ThemeTestDialog> mp_dlg;
	boost::scoped_ptr<AdvTorrentDialog> mp_dlg2;

	AdvTorrentDialog m_torrent;
	AdvPeerDialog m_peers;
	AdvFilesDialog m_files;
	AdvTrackerDialog m_tracker;
	AdvDebugDialog m_debug;

	HaliteWindow* mainHaliteWindow;
};
