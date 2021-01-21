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

#include "camera.h"
#include "parent.h"
#include "parent_p.h"
#include "portal_p.h"

using namespace Xdp;

void PortalPrivate::accessCamera(const Parent &parent, CameraFlags flags)
{
    xdp_portal_access_camera(m_xdpPortal, parent.d_ptr->m_xdpParent, static_cast<XdpCameraFlags>((int)flags), nullptr, accessedCamera, this);
}

void PortalPrivate::accessedCamera(GObject *object, GAsyncResult *result, gpointer data)
{
    XdpPortal *xdpPortal = XDP_PORTAL(object);
    PortalPrivate *portalPrivate = static_cast<PortalPrivate*>(data);
    g_autoptr(GError) error = nullptr;

    bool ret = xdp_portal_access_camera_finish(xdpPortal, result, &error);

    Response response(ret, error ? QString(error->message) : QString());
    portalPrivate->accessCameraResponse(response);
}

int PortalPrivate::openPipewireRemoteForCamera()
{
    return xdp_portal_open_pipewire_remote_for_camera(m_xdpPortal);
}
