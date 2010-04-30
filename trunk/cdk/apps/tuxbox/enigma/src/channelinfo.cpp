#include <channelinfo.h>
#include <lib/base/i18n.h>
#include <lib/system/init.h>
#include <lib/system/init_num.h>
#include <lib/gui/eskin.h>
#include <lib/gdi/font.h>
#include <lib/dvb/epgcache.h>
#include <lib/dvb/dvbservice.h>
#include <lib/dvb/frontend.h>
#include <lib/socket/dpopen.h>
#include <lib/system/info.h>
#include <sys/stat.h>
#include <time.h>
#include <epgwindow.h>
#include <enigma_main.h>
#include <sselect.h>
#include <lib/driver/rc.h>

eChannelInfo::eChannelInfo( eWidget* parent, const char *deco)
	:eDecoWidget(parent, 0, deco),
	ctime(this), cname(this), copos(this), cdescr(this),
	cdolby(this), cstereo(this),
	cformat(this), cscrambled(this),cntime(this), eit(0)
{
	init_eChannelInfo();
}
void eChannelInfo::init_eChannelInfo()
{
	foregroundColor=eSkin::getActive()->queryColor("eStatusBar.foreground");
	backgroundColor=eSkin::getActive()->queryColor("eStatusBar.background");
	gFont fn = eSkin::getActive()->queryFont("eChannelInfo");
	lineheight=(int)fontRenderClass::getInstance()->getLineHeight(fn )+4;

	int percentprogress=0;
	eConfig::getInstance()->getKey("/ezap/osd/PercentProgress", percentprogress);
	setDisplayMode(percentprogress);

	perc=-1;

	cdescr.setFont( fn );
	cdescr.setLineHeight(lineheight);
	cdescr.setForegroundColor( foregroundColor );
	cdescr.setBackgroundColor( backgroundColor );
	cdescr.setFlags(RS_WRAP);
	cdescr.hide();

	copos.setFont( fn );
	copos.setAlign( eTextPara::dirRight );
	copos.setForegroundColor( foregroundColor );
	copos.setBackgroundColor( backgroundColor );
	copos.setFlags( RS_FADE );

	cname.setFont( fn );
	cname.setLineHeight(lineheight);
	cname.setForegroundColor( foregroundColor );
	cname.setBackgroundColor( backgroundColor );
	cname.setFlags( RS_FADE );

	ctime.setFont( fn );
	ctime.setLineHeight(lineheight);
	ctime.setForegroundColor( foregroundColor );
	ctime.setBackgroundColor( backgroundColor );
	ctime.setFlags( RS_FADE );

	cntime.setFont( fn );
	cntime.setLineHeight(lineheight);
	cntime.setForegroundColor( foregroundColor );
	cntime.setBackgroundColor( backgroundColor );
	cntime.setFlags( RS_FADE );

	gPixmap *pm=eSkin::getActive()->queryImage("sselect_dolby");
	cdolby.setPixmap(pm);
	cdolby.pixmap_position = ePoint(0,0);
	cdolby.hide();
	
	pm = eSkin::getActive()->queryImage("sselect_stereo");
	cstereo.setPixmap(pm);
	cstereo.pixmap_position = ePoint(0,0);
	cstereo.hide();

	pm = eSkin::getActive()->queryImage("sselect_format");
	cformat.setPixmap(pm);
	cformat.pixmap_position = ePoint(0,0);
	cformat.hide();

	pm = eSkin::getActive()->queryImage("sselect_crypt");
	cscrambled.setPixmap(pm);
	cscrambled.pixmap_position = ePoint(0,0);
	cscrambled.hide();
	
	p_event=new eProgress(this);
	p_event->setName("event_progress");
	p_event->resize(eSize(80,15));
	p_event->move(ePoint(140,5));
	p_event->hide();
}

const char *eChannelInfo::genresTableShort[256] =
{
	/* 0x0 undefined */    	NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
							NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL, 

	/* 0x1 Movie */        	_("Movie"),("Thriller"),_("Adventure"),_("SciFi"),_("Comedy"),
							_("Soap"),_("Romance"),_("Serious"),_("Adult"),
							NULL,NULL,NULL,NULL,NULL,NULL,NULL,

	/* 0x2 News */         	_("News"),_("Weather"),_("Magazine"),_("Documentary"),_("Discussion"),
							NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
							NULL,NULL,NULL,

	/* 0x3 Show */         	_("Show"),_("Game Show"),_("Variety"),_("Talk"),
							NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
							NULL,NULL,NULL,NULL,

	/* 0x4 Sports */       	_("Sports"),_("Special Event"),_("Sports Mag."),_("Football"),_("Tennis"),_("Team Sports"),
							_("Athletics"),_("Motor Sports"),_("Water Sports"),_("Winter Sports"),_("Equestrian"),
							_("Martial Sports"),
							NULL,NULL,NULL,NULL,

	/* 0x5 Children */     	_("Children"),_("Pre-School"),_("Age 6-14"),_("Age 10-16"),_("School"),
							_("Cartoons"),
							NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
							NULL,NULL,

	/* 0x6 Music */        	_("Music"),_("Rock/Pop"),_("Classical"),_("Folk"),_("Jazz"),_("Musical"),_("Ballet"),
							NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
							NULL,

	/* 0x7 Culture */      	_("Culture"),_("Perf. Arts"),_("Fine Arts"),_("Religion"),_("Pop. Arts"),_("Literature"),
							_("Film"),_("Experimental"),_("Press"),_("New Media"),_("Art Mag."),_("Fashion"),
							NULL,NULL,NULL,NULL,

	/* 0x8 Social */       	_("Social"),_("Soc. Mag."),_("Economics"),_("Remark. People"),
							NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
							NULL,NULL,NULL,NULL,

	/* 0x9 Education */    	_("Education"),_("Nature"),_("Technology"),_("Medicine"),_("Expeditions"),_("Spiritual"),
							_("Further Ed."),_("Languages"),
							NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,

	/* 0xa Leisure */      	_("Hobbies"),_("Travel"),_("Handicraft"),_("Motoring"),_("Fitness"),_("Cooking"),
							_("Shopping"),_("Gardening"),
							NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,

	/* 0xb Special */      	_("Orig. Lang."),_("B&W"),_("Unpublished"),_("Live"),
							NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
							NULL,NULL,NULL,NULL,

	/* 0xc reserved */     	NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
							NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,

	/* 0xd reserved */     	NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
							NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,

	/* 0xe reserved */     	NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
							NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,

	/* 0xf user defined */ 	NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
							NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
};

void eChannelInfo::ParseEITInfo(EITEvent *e)
{
		name=descr=genre=starttime=endtime="";
		cflags=0;
		eString t;

		p_event->hide();

		if(e->start_time!=0)
		{
			tm *stime=localtime(&e->start_time);
			time_t etime=e->start_time + e->duration;
			time_t ntime=time(0) + eDVB::getInstance()->time_difference;
			perc=(time(0) - e->start_time + eDVB::getInstance()->time_difference)*100/e->duration;
			starttime = getTimeStr(stime, 0);
			endtime = getTimeStr(localtime(&etime),0);
			nowtime = getTimeStr(localtime(&ntime),0);

			int show_current_remaining=1;
			eConfig::getInstance()->getKey("/ezap/osd/showCurrentRemaining", show_current_remaining);
			if (show_current_remaining)
			{
				time_t now = time(0) + eDVB::getInstance()->time_difference;
				int duration = e->duration - (now - e->start_time);
				if ( duration > e->duration )
					duration = e->duration;
				else if ( duration < 0 )
					duration = 0;
				t.sprintf("  (+%dmin)", (int)(duration/60));
			}
			else
				t.sprintf("  (%dmin)", (int)(e->duration/60));
		}

		if (e->free_CA_mode )
			cflags |= cflagScrambled;

		LocalEventData led;
		led.getLocalData(e, &name, &descr);

		int formatEvent=0;
		eConfig::getInstance()->getKey("/ezap/osd/formatEvent",formatEvent);

		if(formatEvent && !access("/var/etc/enigma_format_event.sh",X_OK)){
		   FILE *fi=dpopen("/var/etc/enigma_format_event.sh channelinfo");
		   if(fi){
			fprintf(fi,"%s",descr.c_str());
  		        if (dphalfclose(fi) >= 0) {
				char temp[4096];
				int len;
				eString temp_description;
				temp_description.clear();
				while(len=fread(temp,sizeof(char),sizeof(temp)-1,fi)){
					temp[len]='\0';
					temp_description += temp;
				}
				if(temp_description != "")
					descr=temp_description;
			}
			dpclose(fi);
		   }
		}

		DescriptionForEPGSearch = name;  // EPG search
		for (ePtrList<Descriptor>::iterator d(e->descriptor); d != e->descriptor.end(); ++d)
		{
			Descriptor *descriptor=*d;
			if (descriptor->Tag()==DESCR_COMPONENT)
			{
				ComponentDescriptor *cd=(ComponentDescriptor*)descriptor;
				
				if( cd->stream_content == 2 && cd->component_type == 5)
					cflags |= cflagDolby;
				else if( cd->stream_content == 2 && cd->component_type == 3)
					cflags |= cflagStereo;
				else if( cd->stream_content == 1 && (cd->component_type == 2 || cd->component_type == 3) )
					cflags |= cflagWide;
			}
			else if(descriptor->Tag()==DESCR_CONTENT)
			{
				ContentDescriptor *cod=(ContentDescriptor*)descriptor;

				for(ePtrList<descr_content_entry_struct>::iterator ce(cod->contentList.begin()); ce != cod->contentList.end(); ++ce)
				{
					if(genresTableShort[ce->content_nibble_level_1*16+ce->content_nibble_level_2])
					{
/*						if ( !genre.length() )
							genre+=_("GENRE: ");*/
						genre += gettext( genresTableShort[ce->content_nibble_level_1*16+ce->content_nibble_level_2] );
						genre += " ";
					}
				}
			}
		}
		if (mode==modePLI)   
			if(!t.isNull()) name += t;

		cname.setText( name );
		if ( genre.size() )
		{
			if ( name.size() )
				descr+=" / ";
			descr+=genre;
		}
		cdescr.setText( descr );
		if(mode==modePLI)
			ctime.setText( starttime );
		else 	
			ctime.setText( starttime + " - " + endtime);
		
		cntime.setText(nowtime);

		int n = 0;
		
		if(mode==modePLI){
			n = LayoutIcon(&cdolby, (cflags & cflagDolby), n);
			n = LayoutIcon(&cstereo, (cflags & cflagStereo), n);
			n = LayoutIcon(&cformat, (cflags & cflagWide), n );
			n = LayoutIcon(&cscrambled, (cflags & cflagScrambled), n );
			p_event->hide();
			cname.show();
			cdescr.show();
			copos.show();

		}
		else{
			p_event->setPerc(perc);
			cname.show();
			ctime.show();
			p_event->show();
			copos.show();
			cdescr.show();
			copos.show();
			cdolby.hide();
			cstereo.hide();
			cformat.hide();
			cscrambled.hide();

		}
}
eString eChannelInfo::GetDescription()  // EPG search 
{
	return DescriptionForEPGSearch;
}

void eChannelInfo::closeEIT()
{
	if (eit)
		eit->abort();
}

void eChannelInfo::getServiceInfo( const eServiceReferenceDVB& service )
{
	closeEIT();
	delete eit;
	eit=0;
	
	// eService *service=eServiceInterface::getInstance()->addRef(service);
	// eDebug("Channelinfo for: %s", service.path.c_str());
	
	if (!service.path.size())
	{
		DescriptionForEPGSearch = "";  // EPG search

		eServiceDVB* pservice( eDVB::getInstance()->settings->getTransponders()->searchService( service ) );
		if(pservice)
			servicename=pservice->service_name;
		else 
			servicename="";

		cdescr.show();
		int opos=service.getDVBNamespace().get()>>16;
		if ( eSystemInfo::getInstance()->getFEType() == eSystemInfo::feSatellite )
			copos.setText(eString().sprintf("%d.%d\xC2\xB0%c", abs(opos / 10), abs(opos % 10), opos>0?'E':'W') );
		EITEvent *e = 0;
		e = eEPGCache::getInstance()->lookupEvent(service);
		if (e && eListBoxEntryService::nownextEPG)
		{
			time_t t = e->start_time+e->duration+61;
			delete e;
			e = eEPGCache::getInstance()->lookupEvent((const eServiceReferenceDVB&)service,t);
		}
			
		if (e)  // data is in cache...
		{
			ParseEITInfo(e);
			delete e;
		}
		else  // we parse the eit...
		{
			//cname.setText(_("no data for this service available"));
			cname.setText("");
			eDVBServiceController *sapi=eDVB::getInstance()->getServiceAPI();
			if (!sapi)
				return;
			eServiceReferenceDVB &ref = sapi->service;

			int type = ((service.getTransportStreamID()==ref.getTransportStreamID())
				&&	(service.getOriginalNetworkID()==ref.getOriginalNetworkID())) ? EIT::tsActual:EIT::tsOther;

			eit = new EIT( EIT::typeNowNext, service.getServiceID().get(), type );
			CONNECT( eit->tableReady, eChannelInfo::EITready );
			eit->start();
		}
	} else
	{
		copos.setText("");
		cdescr.hide();
		cname.setFlags(RS_WRAP);
		cname.resize( eSize( (clientrect.width()/8)*6-14, clientrect.height() ));
		// should be moved to eService
		eString size("\nFilesize: 0kb");
		int filelength=service.getFileLength();
		time_t filetime = service.getFileTime();
		if (filelength <= 0 || filetime <= 0)
		{
			eString filename=service.path;
			int slice=0;
			struct stat64 s;
			while (!stat64((filename + (slice ? eString().sprintf(".%03d", slice) : eString(""))).c_str(), &s))
			{
				filelength+=s.st_size/1024;
				// Use the filetime of the first slice
				if (slice == 0)
				{
					filetime = s.st_mtime;
				}
				slice++;
			}
		}
		int i = service.path.rfind("/");
		i++;
		size.sprintf(_("\nFilesize/date: %d %cB, %s"), filelength > 10240 ? filelength/1024: filelength, filelength > 10240 ? 'M' : 'k', ::ctime(&filetime));
		cname.setText(eString(_("Filename: "))+service.path.mid( i, service.path.length()-i)+size );
		servicename=service.path.mid( i, service.path.length()-i);
	}
}
	
void eChannelInfo::EITready( int err )
{
//	eDebug("Channelinfo eit ready: %d", err);
	DescriptionForEPGSearch = "";  // EPG search
	if (eit->ready && !eit->error)
	{
		if ( eit->events.size() )
			ParseEITInfo(eit->events.begin());
	}
	else if ( err == -ETIMEDOUT )
		closeEIT();
}

void eChannelInfo::update( const eServiceReferenceDVB& service )
{
	int percentprogress=0;
	eConfig::getInstance()->getKey("/ezap/osd/PercentProgress", percentprogress);
	if(mode!=percentprogress){
		setDisplayMode(percentprogress);
		changeSize();
		redraw(eRect());
	}
	if (service)
	{
		current = service;
		DescriptionForEPGSearch = ""; // EPG search
		getServiceInfo(current);
	}
}

void eChannelInfo::clear()
{
	cname.setText("");
	cdescr.setText("");
	ctime.setText("");
	cntime.setText("");
	copos.setText("");
	cdolby.hide();
	cstereo.hide();
	cformat.hide();
	cscrambled.hide();
	p_event->hide();
	invalidate(eRect(), 0);
}

int eChannelInfo::LayoutIcon(eLabel *icon, int doit, int num )
{
	if( doit )
	{
		int x,y;

		switch(num)
		{
			case 0:
				x=2;
				y=28;
				break;
			case 1:
				x=44;
				y=28;
				break;
			case 2:
				x=2;
				y=50;
				break;
			case 3:
				x=44;
				y=50;
				break;
			default:
				x=0;
				y=0;
				break;
		}
		icon->move(ePoint(x,y));
		icon->show();
		num++;
	}

	return num;

}

void eChannelInfo::redrawWidget(gPainter *target, const eRect& where)
{
	if ( deco )
		deco.drawDecoration(target, ePoint(width(), height()));

	if(mode==modePLI)
		target->line( ePoint(clientrect.left() + clientrect.width()/8 + 1, clientrect.top()),ePoint(clientrect.left() + clientrect.width()/8 + 1,clientrect.bottom()-1));
}
void eChannelInfo::changeSize()
{
		if (deco)
			clientrect=crect;

		int dx=clientrect.width()/8;
		int dy=(clientrect.height()-6)/4;

         	if(mode==modePLI){
			p_event->hide();

			ctime.move( ePoint(0,3) );
			ctime.resize( eSize(dx, 36 ));
		
			cname.move( ePoint( dx + 4, 3 ) );
			cname.resize( eSize( dx*6-14, dy ));
			cname.show();
			cntime.hide();

			int cdescrHeight=(dy>lineheight)?lineheight+lineheight:dy+dy;
			cdescr.move( ePoint(dx + 4, dy+3) );
			cdescr.resize( eSize( clientrect.width() - (dx*2 + 4),cdescrHeight ) );

			copos.move( ePoint( clientrect.width() - (dx+10), 3) );
			copos.resize( eSize(dx + 4, dy) );
			copos.show();

			cdolby.resize( eSize(25,15) );
			cstereo.resize( eSize(25,15) );
			cformat.resize( eSize(25,15) );
			cscrambled.resize( eSize(25,15) );
		} else{

			cname.move( ePoint( 10, 3) );
			cname.resize( eSize( dx*7-10, dy ));
			cname.show();
		
			ctime.move( ePoint(50,dy+3) );
			ctime.resize( eSize(120, dy));

			p_event->move(ePoint(180,dy+3+dy/2-p_event->getSize().height()/2));

			cntime.move( ePoint(280,dy+3) );
			cntime.resize( eSize(80, dy));
			cntime.show();

			cdescr.move( ePoint(10, dy+dy+3) );
			int cdescrHeight=(dy>lineheight)?lineheight+lineheight:dy+dy;
			cdescr.resize( eSize( clientrect.width() - 20, cdescrHeight) );

			copos.move( ePoint( clientrect.width() - (dx+10), 3) );
			copos.resize( eSize(dx + 4, dy) );

			cdolby.hide();
			cstereo.hide();
			cformat.hide();
			cscrambled.hide();
			
		}
		invalidate();

}
int eChannelInfo::eventHandler(const eWidgetEvent &event)
{
	switch (event.type)
	{
		case eWidgetEvent::changedSize:
			changeSize();
			break;
	
		default:
			break;
	}
	return eDecoWidget::eventHandler(event);
}

void eChannelInfo::setDisplayMode(int mode)
{
	this->mode=mode;
}
static eWidget *create_eChannelInfo(eWidget *parent)
{
	return new eChannelInfo(parent);
}

class eChannelInfoSkinInit
{
public:
	eChannelInfoSkinInit()
	{
		eSkin::addWidgetCreator("eChannelInfo", create_eChannelInfo);
	}
	~eChannelInfoSkinInit()
	{
		eSkin::removeWidgetCreator("eChannelInfo", create_eChannelInfo);
	}
};

eAutoInitP0<eChannelInfoSkinInit> init_eChannelInfoSkinInit(eAutoInitNumbers::guiobject, "eChannelInfo");
