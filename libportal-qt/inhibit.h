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

#ifndef LIBPORTALQT_INHIBIT_H
#define LIBPORTALQT_INHIBIT_H

#include <QFlags>

namespace Xdp {

enum class InhibitFlag
{
    None = 0x0,
    Logout = 0x1,
    UserSwitch = 0x2,
    Suspend = 0x4,
    Idle = 0x8
};
Q_DECLARE_FLAGS(InhibitFlags, InhibitFlag)

enum class LoginSessionState
{
    Running = 1,
    QueryEnd = 2,
    Ending = 3
};

enum class SessionMonitorFlag
{
    None = 0x0
};
Q_DECLARE_FLAGS(SessionMonitorFlags, SessionMonitorFlag)

}
Q_DECLARE_OPERATORS_FOR_FLAGS(Xdp::InhibitFlags)
Q_DECLARE_OPERATORS_FOR_FLAGS(Xdp::SessionMonitorFlags)

#endif // LIBPORTALQT_INHIBIT_H




