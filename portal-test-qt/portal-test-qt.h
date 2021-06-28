/*
 * Copyright (C) 2020-2021, Jan Grulich
 *
 * This file is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, version 3.0 of the
 * License.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: LGPL-3.0-only
 */

#ifndef PORTAL_TEST_QT_H
#define PORTAL_TEST_QT_H

#include <QMainWindow>
#include "portal.h"

class Ui_PortalTestQt;

class PortalTestQt : public QMainWindow
{
    Q_OBJECT
public:
    PortalTestQt(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~PortalTestQt();

    void updateLastOpenedFile(const QString &file);
private Q_SLOTS:
    void onUserInformationReceived(const Xdp::Response &response);
    void onFileOpened(const Xdp::Response &response);
    void onSessionInhibited(const Xdp::Response &response);

private:
    Ui_PortalTestQt *m_mainWindow;
    int m_inhibitorId = -1;
};

#endif // PORTAL_TEST_QT_H
