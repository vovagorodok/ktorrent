/***************************************************************************
 *   Copyright (C) 2009 by Joris Guisson                                   *
 *   joris.guisson@gmail.com                                               *
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
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.          *
 ***************************************************************************/

#include "webview.h"
#include <QAction>
#include <QTextStream>
#include <QApplication>
#include <QNetworkReply>
#include <QWebHistory>
#include <QWebHitTestResult>
#include <KUrl>
#include <KStandardDirs>
#include <KIconLoader>
#include <KLocale>
#include <KWebPage>
#include <util/log.h>
#include <kio/job.h>
#include <kio/accessmanager.h>
#include <KFileDialog>
#include <kio/copyjob.h>



using namespace bt;

namespace kt
{
	
	
	class NetworkAccessManager : public KIO::AccessManager
	{
	public:
		NetworkAccessManager(WebView* parent) : KIO::AccessManager(parent),webview(parent)
		{
		}
		
		virtual ~NetworkAccessManager()
		{}
		
		virtual QNetworkReply* createRequest(Operation op, const QNetworkRequest& req, QIODevice* outgoingData)
		{
			if (req.url().host() == "ktorrent.searchplugin")
			{
				//Out(SYS_GEN|LOG_DEBUG) << "REQUEST " << req.url().toString() << endl;
				QString search_text = req.url().queryItemValue("search_text");
				QUrl url(webview->searchUrl(search_text));
				QNetworkRequest request(url);
				webview->setUrl(url);
				return KIO::AccessManager::createRequest(op,request,outgoingData);
			}
			
			return KIO::AccessManager::createRequest(op,req,outgoingData);
		}
		
		WebView* webview;
	};
	
	
	//////////////////////////////////////////////////////
	
	WebView::WebView(kt::WebViewClient* client, QWidget* parentWidget)
		: KWebView(parentWidget),client(client)
	{
		page()->setNetworkAccessManager(new NetworkAccessManager(this));
		page()->setForwardUnsupportedContent(true);
		
		connect(page(),SIGNAL(downloadRequested(QNetworkRequest)),this,SLOT(downloadRequested(QNetworkRequest)));
	}
		
	WebView::~WebView()
	{
	}

	void WebView::openUrl(const KUrl& url)
	{
		if (url.host() == "ktorrent.searchplugin")
			home();
		else
			load(url);
	}
	
	void WebView::home()
	{
		if (home_page_html.isEmpty())
			loadHomePage();
		
		setHtml(home_page_html, "file://" + home_page_base_url);
	}

	void WebView::loadHomePage()
	{
		QString file = KStandardDirs::locate("data","ktorrent/search/home/home.html");
		QFile fptr(file);
		if (fptr.open(QIODevice::ReadOnly))
		{
			Out(SYS_SRC|LOG_DEBUG) << "Loading home page from " << file << endl;
			home_page_base_url = file.left(file.lastIndexOf('/') + 1);
			home_page_html = QTextStream(&fptr).readAll();
			
			// %1
			home_page_html = home_page_html.arg("ktorrent_infopage.css");
			// %2
			if (qApp->layoutDirection() == Qt::RightToLeft)
			{
				QString link = "<link rel=\"stylesheet\" type=\"text/css\" href=\"%1\" />";
				link = link.arg(KStandardDirs::locate("data", "kdeui/about/kde_infopage_rtl.css"));
				home_page_html = home_page_html.arg(link);
			}
			else
				home_page_html = home_page_html.arg("");
			
			KIconLoader *iconloader = KIconLoader::global();
			int icon_size = iconloader->currentSize(KIconLoader::Desktop);
			home_page_html = home_page_html
				.arg(i18n("Home")) // %3 Title
				.arg(i18n("KTorrent")) // %4
				.arg(i18nc("KDE 4 tag line, see http://kde.org/img/kde40.png", "Be free.")) // %5
				.arg(i18n("Search the web for torrents.")) // %6
				.arg(i18n("Search")) // %7
				.arg("search_text") // %8
				.arg(icon_size).arg(icon_size) // %9 and %10
				.arg(home_page_base_url); // %11
		}
		else
		{
			Out(SYS_SRC|LOG_IMPORTANT) << "Failed to load " << file << " : " << fptr.errorString() << endl;
		}
	}

	KUrl WebView::searchUrl(const QString& search_text)
	{
		if (client)
			return client->searchUrl(search_text);
		else
			return KUrl("http://google.be");
	}
	
	QWebView* WebView::createWindow(QWebPage::WebWindowType type)
	{
		Q_UNUSED(type);
		return client->newTab();
	}
	
	void WebView::downloadRequested(const QNetworkRequest& req)
	{
		QString filename = QFileInfo(req.url().path()).fileName();
		QString path = KFileDialog::getExistingDirectory(KUrl("kfiledialog:///webview"),this,i18n("Save %1 to",filename));
		if (!path.isEmpty())
			KIO::copy(req.url(),KUrl(path));
	}

	void WebView::downloadResponse(QNetworkReply* reply)
	{
		KWebPage* p = (KWebPage*)page();
		p->downloadResponse(reply);
	}

}

