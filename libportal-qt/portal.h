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

#ifndef LIBPORTALQT_PORTAL_H
#define LIBPORTALQT_PORTAL_H

#include <QObject>

#include "account.h"
#include "background.h"
#include "camera.h"
#include "email.h"
#include "libportalqt_export.h"
#include "filechooser.h"
#include "inhibit.h"
#include "location.h"
#include "notification.h"
#include "openuri.h"
#include "parent.h"
#include "response.h"

namespace Xdp {

class LIBPORTALQT_EXPORT Notifier : public QObject
{
    Q_OBJECT
Q_SIGNALS:
    // Account portal
    void getUserInformationResponse(const Response &response);

    // Background portal
    void requestBackgroundResponse(const Response &response);

    // Camera portal
    void accessCameraResponse(const Response &response);

    // Email portal
    void composeEmailResponse(const Response &response);

    // FileChooser portal
    void openFileResponse(const Response &response);
    void saveFileResponse(const Response &response);
    void saveFilesResponse(const Response &response);

    // Inhibit portal
    void sessionInhibitResponse(const Response &response);
    void sessionMonitorStartResponse(const Response &response);
    void sessionStateChanged(bool screenSaverActive, LoginSessionState currentState);

    // Location portal
    void locationMonitorStartResponse(const Response &response);
    void locationUpdated(double latitude, double longitude, double altitude, double accuracy, double speed, double heading, const QString &description, qint64 timestamp_s, qint64 timestamp_ms);

    // Notification portal
    void addNotificationResponse(const Response &response);
    void notificationActionInvoked(const QString &id, const QString &actionName, const QVariant &parameter);

    // OpenURI portal
    void openUriResponse(const Response &response);
    void openDirectoryResponse(const Response &response);
};

    // Account portal
    LIBPORTALQT_EXPORT void getUserInformation(const Parent &parent, const QString &reason, UserInformationFlags flags);

    // Background portal
    LIBPORTALQT_EXPORT void requestBackground(const Parent &parent, const QString &reason, const QStringList &commandline, BackgroundFlags flags);

    // Camera portal
    LIBPORTALQT_EXPORT void accessCamera(const Parent &parent, CameraFlags flags);
    LIBPORTALQT_EXPORT int openPipewireRemoteForCamera();

    // Email portal
    LIBPORTALQT_EXPORT void composeEmail(const Parent &parent, const QStringList &addresses, const QStringList &cc,
                                         const QStringList &bcc, const QString &subject, const QString &body,
                                         const QStringList &attachments, EmailFlags flags);

    // FileChooser portal
    LIBPORTALQT_EXPORT void openFile(const Parent &parent, const QString &title, const FileChooserFilterList &filters, const FileChooserFilter &currentFilter,
                                     const FileChooserChoices &choices, OpenFileFlags flags);
    LIBPORTALQT_EXPORT void saveFile(const Parent &parent, const QString &title, const QString &currentName, const QString &currentFolder, const QString &currentFile,
                                     const FileChooserFilterList &filters, const FileChooserFilter &currentFilter, const FileChooserChoices &choices, SaveFileFlags flags);
    LIBPORTALQT_EXPORT void saveFiles(const Parent &parent, const QString &title, const QString &currentFolder, const QStringList &files,
                                      const FileChooserChoices &choices, SaveFileFlags flags);

    // Inhibit portal
    LIBPORTALQT_EXPORT void sessionInhibit(const Parent &parent, const QString &reason, InhibitFlags flags);
    LIBPORTALQT_EXPORT void sessionUninhibit(int id);
    LIBPORTALQT_EXPORT void sessionMonitorStart(const Parent &parent, SessionMonitorFlags flags);
    LIBPORTALQT_EXPORT void sessionMonitorStop();
    LIBPORTALQT_EXPORT void sessionMonitorQueryEndResponse();

    // Location portal
    LIBPORTALQT_EXPORT void locationMonitorStart(const Parent &parent, uint distanceThreshold, uint timeThreshold, LocationAccuracy accuracy, LocationMonitorFlags flags);
    LIBPORTALQT_EXPORT void locationMonitorStop();

    // Notification portal
    LIBPORTALQT_EXPORT void addNotification(const Parent &parent, const QString &id, const QVariantMap &notification, NotificationFlags flags);
    LIBPORTALQT_EXPORT void removeNotification(const QString &id);

    // OpenURI portal
    LIBPORTALQT_EXPORT void openUri(const Parent &parent, const QString &uri, OpenUriFlags flags);
    LIBPORTALQT_EXPORT void openDirectory(const Parent &parent, const QString &uri, OpenUriFlags flags);

    // Helpers
    LIBPORTALQT_EXPORT bool isSandboxed();

    LIBPORTALQT_EXPORT Notifier *notifier();
} // namespace Xdp

#endif // LIBPORTALQT_PORTAL_H
