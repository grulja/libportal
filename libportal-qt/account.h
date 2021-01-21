/*
 * Copyright (C) 2020-2021, Jan Grulich
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

#ifndef LIBPORTALQT_ACCOUNT_H
#define LIBPORTALQT_ACCOUNT_H

#include <QFlags>

namespace Xdp {

enum class UserInformationFlag
{
    None = 0x0
};
Q_DECLARE_FLAGS(UserInformationFlags, UserInformationFlag)
}
Q_DECLARE_OPERATORS_FOR_FLAGS(Xdp::UserInformationFlags)

#endif // LIBPORTALQT_ACCOUNT_H

