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

#ifndef LIBPORTALQT_PARENT_P_H
#define LIBPORTALQT_PARENT_P_H

#include "portal_p.h"

namespace Xdp
{

class ParentPrivate : public QObject
{
    Q_OBJECT
public:
    ParentPrivate(QWindow *window, Parent *q);
    ~ParentPrivate();

    XdpParent *m_xdpParent = nullptr;

    Q_DECLARE_PUBLIC(Parent)
    Parent *q_ptr;
};

}

#endif // LIBPORTALQT_PARENT_P_H
