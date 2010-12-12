/*
 * $Id: movieplayer.h,v 1.10 2006/01/27 09:48:46 digi_casi Exp $
 *
 * (C) 2005 by digi_casi <digi_casi@tuxbox.org>
 *          based on vlc plugin by mechatron
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include <lib/gui/emessage.h>
#include <lib/gui/eskin.h>
#include <lib/gui/listbox.h>
#include <lib/gui/ewindow.h>
#include <lib/system/econfig.h>
#include <lib/movieplayer/movieplayer.h>
#include <lib/movieplayer/mpconfig.h>
#include <lib/gui/echeckbox.h>
#include <lib/gui/combobox.h>
#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>
#include <lib/gui/ePLiWindow.h>
#include <lib/gui/slider.h>
#include <lib/gui/enumber.h>

#include <lib/gui/eprogress.h>
#include <lib/gui/egauge.h>

eString pathcfg = "/enigma/plugins/movieplayer/";

class PLAYLIST
{
public:
	int Filetype;
	eString Filename, Fullname, Filesize;
	eListBoxEntryText *listEntry;
};

typedef std::vector<PLAYLIST> PlayList;

class eSCGui: public eWindow
{
	enum {GOUP, DIRS, FILES};
	enum {DATA, VCD, DVD, CFG};

	eString VLC_IP, VLC_IF_PORT, VLC_AUTH;

	PlayList playList;
	
	struct serverConfig server;

	eString startdir, cddrive, path;
	
	bool menu;
	unsigned int val, nFiles, skip_time;
	
	int VLC8;
	
	eListBox<eListBoxEntryText> *list;
	eTimer *timer, *volumeTimer;
	eMessageBox *bufferingBox, *pauseBox, *infoBox, *jumpBox;
	eStatusBar *status;

	void loadList(int mode, eString path);
	void viewList();
	void setStatus(int val);
	bool supportedFileType(eString filename);

	void listSelected(eListBoxEntryText *item);
	void listSelChanged(eListBoxEntryText *item);
	int eventHandler(const eWidgetEvent &);

	void timerHandler();
	void playerStart(int val);
	void showMenu();
	
	CURLcode sendGetRequest (const eString& url, eString& response);
	
	void pause();
	eString getPar(eString buf, const char* par);
	void changeSout();
	eString filePos(int both, eString name, eString size, eString& text);
	void getSavedPath();
	eString UrlEncode(const eString & src);
	int isLargeRC();
	int silver_large_rc;
	eProgress *VolumeBar; /* this is the standard volumebar, in it's own widget */
	eMultiProgress *IBVolumeBar; /* these are all custom volume bars/gauges, integrated in the OSD widgets */
	eLabel *volume;
	void volumeUp();
	void volumeDown();
	void hideVolumeSlider();
	void updateVolume(int mute_state, int vol);
	void init_volume_bar();
public:
	eSCGui();
	~eSCGui();
};

class eSCGuiHelp: public eWindow
{
	eListBox<eListBoxEntryText> *list;
public:
    eSCGuiHelp();
      
};

class eSCGuiConfig: public ePLiWindow
{
private:
    eLabel *lNrSec;
    eLabel *lmsgTime;
    eLabel *lbuff, *lbuff1;
    eLabel *l_width,*l_height;     
    eCheckbox *playNext;
    eCheckbox *stopErr;
	eCheckbox *savePath;
	eCheckbox *aSync;
	eCheckbox *subTitles;
	eCheckbox *resDVB;
	eCheckbox *setNsf;
	eCheckbox *setVlc8;
	eCheckbox *setRes;
	eComboBox *comNrSec;
    eComboBox *comMsgTime;
    eSlider *sBuff;
    eNumber *setWidth, *setHeight;

    int play_next;
	void saveCFG();
	void setDVB(int status);
	void BuffChanged(int i);
	void setCheckRes(int status);
public:
	eSCGuiConfig();
};





