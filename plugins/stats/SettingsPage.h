/***************************************************************************
 *   Copyright © 2007 by Krzysztof Kundzicz                                *
 *   athantor@gmail.com                                                    *
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
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.             *
 ***************************************************************************/

#ifndef SettingsPage_H_
#define SettingsPage_H_

#include <QWidget>

#include <KColorButton>

#include <interfaces/prefpageinterface.h>

#include <libktcore/settings.h>

#include <PluginPage.h>
#include <statspluginsettings.h>

#include <ui_Settings.h>

namespace kt
{

/** \brief Settings page
\author Krzysztof Kundzicz <athantor@gmail.com>
*/

class SettingsPage : public PrefPageInterface, public Ui_StatsSettingsWgt
{
    Q_OBJECT

public:
    /** \brief Constructor
    \param  p Parent
    */
    SettingsPage(QWidget* p);
    ///Destructor
    ~SettingsPage() override;

public Q_SLOTS:
    void updateSettings() override;

private Q_SLOTS:
    void UpdGuiUpdatesToMs(int);

Q_SIGNALS:
    ///Settings has been applied
    void Applied();

};

} //ns end

#endif
