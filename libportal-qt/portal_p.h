/*
 * Copyright (C) 2020, Jan Grulich
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIBPORTALQT_PORTAL_P_H
#define LIBPORTALQT_PORTAL_P_H

#include "portal.h"

#undef signals
#include "portal-qt5.h"
#define signals Q_SIGNALS

namespace Xdp
{

class PortalPrivate : public QObject
{
    Q_OBJECT
public:
    PortalPrivate(Portal *q);
    ~PortalPrivate();

    // Account portal
    void getUserInformation(const Parent &parent, const QString &reason, UserInformationFlags flags);
    static void gotUserInformation(GObject *object, GAsyncResult *result, gpointer data);

    // Background portal
    void requestBackground(const Parent &parent, const QString &reason, const QStringList &commandline, BackgroundFlags flags);
    static void requestedBackground(GObject *object, GAsyncResult *result, gpointer data);

    // Camera portal
    void accessCamera(const Parent &parent, CameraFlags flags);
    static void accessedCamera(GObject *object, GAsyncResult *result, gpointer data);

    int openPipewireRemoteForCamera();

    // FileChooser portal
    void openFile(const Parent &parent, const QString &title, const FileChooserFilterList &filters, const FileChooserFilter &currentFilter,
                  const FileChooserChoices &choices, OpenFileFlags flags);
    static void openedFile(GObject *object, GAsyncResult *result, gpointer data);

    void saveFile(const Parent &parent, const QString &title, const QString &currentName, const QString &currentFolder, const QString &currentFile,
                  const FileChooserFilterList &filters, const FileChooserFilter &currentFilter, const FileChooserChoices &choices, SaveFileFlags flags);
    static void savedFile(GObject *object, GAsyncResult *result, gpointer data);

    void saveFiles(const Parent &parent, const QString &title, const QString &currentFolder, const QStringList &files,
                   const FileChooserChoices &choices, SaveFileFlags flags);
    static void savedFiles(GObject *object, GAsyncResult *result, gpointer data);

    // OpenURI portal
    void openUri(const Parent &parent, const QString &uri, OpenUriFlags flags);
    static void openedUri(GObject *object, GAsyncResult *result, gpointer data);

    void openDirectory(const Parent &parent, const QString &uri, OpenUriFlags flags);
    static void openedDirectory(GObject *object, GAsyncResult *result, gpointer data);

    XdpPortal *m_xdpPortal = nullptr;

    Q_DECLARE_PUBLIC(Portal)
    Portal *q_ptr;
};
}

#endif // LIBPORTALQT_PORTAL_P_H
