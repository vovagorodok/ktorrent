/***************************************************************************
 *   Copyright (C) 2009 by                                                 *
 *   Joris Guisson <joris.guisson@gmail.com>                               *
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
#ifndef KT_SCANEXTENDER_H
#define KT_SCANEXTENDER_H

#include <QWidget>
#include <QTimer>
#include <view/viewdelegate.h>
#include "scanlistener.h"
#include "ui_scanextender.h"

namespace bt
{
	class TorrentInterface;
}


namespace kt 
{
	
	/**
		Extender widget which displays the results of a data scan
	*/
	class ScanExtender : public Extender,public Ui_ScanExtender
	{
		Q_OBJECT
	public:
		ScanExtender(ScanListener* lst,bt::TorrentInterface* tc,QWidget* parent);
		virtual ~ScanExtender();

	private slots:
		void update();
		void cancelPressed();
		void finished();
		void restart();
		void closeRequested();
		void scanError(const QString & err);
		
	private:
		QTimer timer;
		ScanListener* listener;
	};
}

#endif // KT_SCANEXTENDER_H