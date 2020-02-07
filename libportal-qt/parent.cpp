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

#include "parent.h"
#include "parent_p.h"

using namespace Xdp;

ParentPrivate::ParentPrivate(QWindow *window, Parent *q)
    : m_xdpParent(xdp_parent_new_qt(window))
    , q_ptr(q)
{
}

ParentPrivate::~ParentPrivate()
{
    if (m_xdpParent) {
        xdp_parent_free(m_xdpParent);
    }
}

Parent::Parent(QWindow *window, QObject *parent)
    : QObject(parent)
    , d_ptr(new ParentPrivate(window, this))
{
}

Parent::~Parent()
{
}

