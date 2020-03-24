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

#include "portal.h"
#include "portal_p.h"

#include <QFileInfo>

using namespace Xdp;

PortalPrivate::PortalPrivate(Portal *q)
    : m_xdpPortal(xdp_portal_new())
    , q_ptr(q)
{
}

PortalPrivate::~PortalPrivate()
{
    if (m_xdpPortal) {
        g_object_unref(m_xdpPortal);
    }
}

Portal::Portal(QObject *parent)
    : QObject(parent)
    , d_ptr(new PortalPrivate(this))
{
}

Portal::~Portal()
{
}

bool Xdp::Portal::isSandboxed()
{
    return QFileInfo::exists(QStringLiteral("/flatpak-info")) || qEnvironmentVariableIsSet("SNAP");
}
