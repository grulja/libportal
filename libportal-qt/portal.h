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

#ifndef LIBPORTALQT_PORTAL_H
#define LIBPORTALQT_PORTAL_H

#include <QObject>

#include "libportalqt_export.h"
#include "filechooser.h"
#include "openuri.h"
#include "parent.h"
#include "response.h"

namespace Xdp {

class PortalPrivate;

class LIBPORTALQT_EXPORT Portal : public QObject
{
    Q_OBJECT
public:
    explicit Portal(QObject *parent = nullptr);
    ~Portal();

    void openFile(const Parent &parent, const QString &title, const FileChooserFilterList &filters, const FileChooserFilter &currentFilter,
                  const FileChooserChoices &choices, OpenFileFlags flags);
    void saveFile(const Parent &parent, const QString &title, const QString &currentName, const QString &currentFolder, const QString &currentFile,
                  const FileChooserFilterList &filters, const FileChooserFilter &currentFilter, const FileChooserChoices &choices, SaveFileFlags flags);
    void saveFiles(const Parent &parent, const QString &title, const QString &currentFolder, const QStringList &files,
                   const FileChooserChoices &choices, SaveFileFlags flags);

    void openUri(const Parent &parent, const QString &uri, OpenUriFlags flags);
    void openDirectory(const Parent &parent, const QString &uri, OpenUriFlags flags);
Q_SIGNALS:
    void openUriResponse(const Response &response);
    void openDirectoryResponse(const Response &response);

    void openFileResponse(const Response &response);
    void saveFileResponse(const Response &response);
    void saveFilesResponse(const Response &response);
private:
    Q_DECLARE_PRIVATE(Portal)

    const QScopedPointer<PortalPrivate> d_ptr;
};
} // namespace Xdp

#endif // LIBPORTALQT_PORTAL_H
