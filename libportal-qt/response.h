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

#ifndef LIBPORTALQT_RESPONSE_H
#define LIBPORTALQT_RESPONSE_H

#include <QVariantMap>

#include "libportalqt_export.h"

namespace Xdp {

class ResponsePrivate;

class LIBPORTALQT_EXPORT Response
{
public:
    explicit Response(bool success, const QString &errorMessage, const QVariantMap &result = QVariantMap());
    ~Response();

    bool isError() const;

    bool isSuccess() const;

    QString errorMessage() const;

    QVariantMap result() const;

private:
    Q_DECLARE_PRIVATE(Response)

    const QScopedPointer<ResponsePrivate> d_ptr;
};
} // namespace Xdp

#endif // LIBPORTALQT_RESPONSE_H

