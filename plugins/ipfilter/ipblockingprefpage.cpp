/***************************************************************************
 *   Copyright (C) 2005 by Joris Guisson                                   *
 *   joris.guisson@gmail.com                                               *
 *   ivasic@gmail.com                                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.             *
 ***************************************************************************/
#include "ipblockingprefpage.h"
#include "ipblockingpref.h"
#include "ipfilterpluginsettings.h"
#include "ipfilterplugin.h"
#include "convertdialog.h"

#include <kapplication.h>
#include <kglobal.h>
#include <kstandarddirs.h>
#include <klocale.h>
#include <kiconloader.h>
#include <kurlrequester.h>
#include <kurl.h>
#include <kmessagebox.h>
#include <kio/netaccess.h>
#include <kprogress.h>
#include <kmimetype.h>

#include <util/log.h>
#include <torrent/globals.h>
#include <interfaces/coreinterface.h>

#include <qthread.h>
#include <qlabel.h>
#include <qcheckbox.h>
#include <qregexp.h>
#include <qvalidator.h>
#include <qlayout.h>
#include <qdialog.h>
#include <qobject.h>

using namespace bt;

#define MAX_RANGES 500

namespace kt
{
	IPBlockingPrefPageWidget::IPBlockingPrefPageWidget(QWidget* parent) : IPBlockingPref(parent)
	{
		m_filter->setURL(IPBlockingPluginSettings::filterFile());
		m_url->setURL(IPBlockingPluginSettings::filterURL());
		if (m_url->url() == "")
			m_url->setURL(QString("http://www.bluetack.co.uk/config/splist.zip"));
		
		bool use_level1 = IPBlockingPluginSettings::useLevel1();
		bool use_filter = IPBlockingPluginSettings::useFilter();
		checkUseLevel1->setChecked(use_level1);
		checkUseKTfilter->setChecked(use_filter);
		
		if(use_level1)
		{
			lbl_status1->setText(i18n("Status: Loaded and running."));
			m_url->setEnabled(true);
			btnDownload->setEnabled(true);
		}
		else
		{
			lbl_status1->setText(i18n("Status: Not loaded."));
			m_url->setEnabled(false);
			btnDownload->setEnabled(false);
		}
		
		if(use_filter)
		{
			lbl_status2->setText(i18n("Status: Loaded and running."));
			m_filter->setEnabled(true);
		}
		else
		{
			lbl_status2->setText(i18n("Status: Not loaded."));
			m_filter->setEnabled(false);
		}
		
		m_plugin = 0;
	}

	void IPBlockingPrefPageWidget::apply()
	{
		KURLRequester* filter = m_filter;
		if(IPBlockingPluginSettings::filterFile() != filter->url() && m_prefpage)
			m_prefpage->filterChanged();
		
		IPBlockingPluginSettings::setFilterFile(filter->url());
		IPBlockingPluginSettings::setFilterURL(m_url->url());
		IPBlockingPluginSettings::setUseLevel1(checkUseLevel1->isChecked());
		IPBlockingPluginSettings::setUseFilter(checkUseKTfilter->isChecked());
		IPBlockingPluginSettings::writeConfig();
		
		if(checkUseLevel1->isChecked())
		{
			QFile target(KGlobal::dirs()->saveLocation("data","ktorrent") + "level1.dat");
			if(target.exists())
				lbl_status1->setText(i18n("Status: Loaded and running."));
			else
				lbl_status1->setText(i18n("Status: <font color=\"#ff0000\">Filter file not found.</font> Download and convert filter file."));
		}
		else
			lbl_status1->setText(i18n("Status: Not loaded."));
		
		if(checkUseKTfilter->isChecked())
		{
			QString filter = IPBlockingPluginSettings::filterFile();
			if(!filter.isEmpty())
			{
				lbl_status2->setText("Status: Loaded and running.");
			}
			else
				lbl_status2->setText("Status: <font color=\"#ff0000\">Filter file not found.</font> Choose one.");
		}
		else
			lbl_status2->setText(i18n("Status: Not loaded."));
	}

	void IPBlockingPrefPageWidget::btnDownload_clicked()
	{
		QString target(KGlobal::dirs()->saveLocation("data","ktorrent") + "level1");
		QFile target_file(target);
		QFile txtfile(target + ".txt");
		KURL url(m_url->url());
		KURL dest(target);
		KURL temp(KGlobal::dirs()->saveLocation("data","ktorrent") + "level1.tmp");

		bool download = true;

		if(txtfile.exists())
		{
			if((KMessageBox::questionYesNo(this, i18n("Selected file already exists, do you want to download it again?"),i18n("File Exists")) == 4))
				download = false;
			else
				KIO::NetAccess::move(target, temp);
		}

		if(download)
		{
			if(!url.isLocalFile())
			{
				if (KIO::NetAccess::download(url,target,NULL))
				{
					//Level1 list successfully downloaded, remove temporary file
					KIO::NetAccess::removeTempFile(target);
					KIO::NetAccess::del(temp, this);
				}
				else
				{
					QString err = KIO::NetAccess::lastErrorString();
					if(err != QString::null)
						KMessageBox::error(0,KIO::NetAccess::lastErrorString(),i18n("Error"));
					else
						KIO::NetAccess::move(temp, target);
					
					
					//we don't want to convert since download failed
					return;
				}
			}
			else
			{
				if (!KIO::NetAccess::file_copy(url,dest, -1, true))
				{
					KMessageBox::error(0,KIO::NetAccess::lastErrorString(),i18n("Error"));
					return;
				}
			}
			
			//now determine if it's ZIP or TXT file
			KMimeType::Ptr ptr = KMimeType::findByPath(target);
			if(ptr->name() == "application/x-zip")
			{
				KURL zipfile("zip:" + target + "/splist.txt");
				KURL destinationfile(target + ".txt");
				KIO::NetAccess::file_copy(zipfile,destinationfile, -1, true);
			}
			else
			{
				KURL zipfile(target);
				KURL destinationfile(target + ".txt");
				KIO::NetAccess::file_copy(zipfile,destinationfile, -1, true);
			}
			
		}
		convert();
	}
	
	void IPBlockingPrefPageWidget::checkUseLevel1_toggled(bool check)
	{
		if(check)
		{
			m_url->setEnabled(true);
			btnDownload->setEnabled(true);
		}
		else
		{
			lbl_status1->setText("");
			m_url->setEnabled(false);
			btnDownload->setEnabled(false);
		}
	}
	
	void IPBlockingPrefPageWidget::checkUseKTfilter_toggled(bool check)
	{
		if(check)
		{
			m_filter->setEnabled(true);
		}
		else
		{
			lbl_status2->setText("");
			m_filter->setEnabled(false);
		}
	}

	void IPBlockingPrefPageWidget::convert()
	{
		QFile target(KGlobal::dirs()->saveLocation("data","ktorrent") + "level1.dat");
		if(target.exists())
		{
			if((KMessageBox::questionYesNo(this,i18n("Filter file (level1.dat) already exists, do you want to convert it again?"),i18n("File Exists")) == 4))
				return;
// 			else
// 				KIO::NetAccess::del(KGlobal::dirs()->saveLocation("data","ktorrent") + "level1.dat", NULL);
		}
		ConvertDialog dlg(m_plugin);
		dlg.exec();
	}
	
	void IPBlockingPrefPageWidget::setPlugin(IPFilterPlugin* p)
	{
		m_plugin = p;
	}
	
	void IPBlockingPrefPageWidget::setPrefPage( IPBlockingPrefPage * p )
	{
		m_prefpage = p;
	}
	
	void IPBlockingPrefPageWidget::setConverting(bool enable)
	{
		btnDownload->setEnabled(enable);
		groupBox2->setEnabled(enable);
		lbl_status1->setText("");
	}
	
	
	////////////////////////////////////////////////////////////////////////////////////

	IPBlockingPrefPage::IPBlockingPrefPage(CoreInterface* core, IPFilterPlugin* p)
	: PrefPageInterface(i18n("IPBlocking Filter"), i18n("IPBlocking Filter Options"), KGlobal::iconLoader()->loadIcon("filter",KIcon::NoGroup)), m_core(core), m_plugin(p)
	{
		widget = 0;
		ktfilter_loaded = IPBlockingPluginSettings::useFilter();
	}

	IPBlockingPrefPage::~IPBlockingPrefPage()
	{}

	bool IPBlockingPrefPage::apply()
	{
		widget->apply();
		
		if(IPBlockingPluginSettings::useFilter())
		{
			if(!ktfilter_loaded)
				loadFilters();
			ktfilter_loaded = true;
		}
		else
		{
			if(ktfilter_loaded)
				unloadFilters();
			ktfilter_loaded = false;
		}
		
		if(IPBlockingPluginSettings::useLevel1())
			m_plugin->loadAntiP2P();
		else
			m_plugin->unloadAntiP2P();
		
		return true;
	}

	void IPBlockingPrefPage::loadFilters()
	{
		/** LOAD KT FILTER LIST **/
		QString filter = IPBlockingPluginSettings::filterFile();
		if(!filter.isEmpty())
		{
			//load list
			QString listURL = IPBlockingPluginSettings::filterFile();
			QFile dat(listURL);
			dat.open(IO_ReadOnly);

			QTextStream stream( &dat );
			QString line;
			int i=0;
			int count=0;
			int var=0;
			while ( !stream.atEnd() && i < MAX_RANGES )
			{
				QRegExp rx("([*]|[0-9]{1,3}).([*]|[0-9]{1,3}).([*]|[0-9]{1,3}).([*]|[0-9]{1,3})");
				QRegExpValidator v( rx,0);
				line = stream.readLine();
				if ( v.validate( line, var ) != QValidator::Acceptable )
					continue;
				else
					++count;
				
				m_core->addBlockedIP(line);
				++i;
			}
			Out() << "Loaded " << count << " blocked IP ranges." << endl;
			dat.close();
		}
		
	}

	void IPBlockingPrefPage::unloadFilters()
	{
		/** UNLOAD KT FILTER LIST **/
		QString filter = IPBlockingPluginSettings::filterFile();
		if(!filter.isEmpty())
		{
			//unload list
			QString listURL = IPBlockingPluginSettings::filterFile();
			QFile dat(listURL);
			dat.open(IO_ReadOnly);

			QTextStream stream( &dat );
			QString line;
			int i=0;
			int count = 0;
			int var = 0;
			while ( !stream.atEnd() && i < MAX_RANGES )
			{
				QRegExp rx("([*]|[0-9]{1,3}).([*]|[0-9]{1,3}).([*]|[0-9]{1,3}).([*]|[0-9]{1,3})");
				QRegExpValidator v( rx,0);
				line = stream.readLine();
				if ( v.validate( line, var ) != QValidator::Acceptable )
					continue;
				else
					++count;
				
				m_core->removeBlockedIP(line);
				++i;
			}
			Out() << "Unloaded " << count << " blocked IP ranges." << endl;
			dat.close();
		}
		
	}
	
	void IPBlockingPrefPage::createWidget(QWidget* parent)
	{
		widget = new IPBlockingPrefPageWidget(parent);
		widget->setPlugin(m_plugin);
		widget->setPrefPage(this);
	}

	void IPBlockingPrefPage::deleteWidget()
	{
		delete widget;
		widget = 0;
	}

	void IPBlockingPrefPage::updateData()
	{}
	
	void IPBlockingPrefPage::filterChanged()
	{
		ktfilter_loaded = false;
	}
}
