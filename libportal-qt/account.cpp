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

#include "account.h"
#include "parent.h"
#include "parent_p.h"
#include "portal_p.h"

using namespace Xdp;

void Portal::getUserInformation(const Parent &parent, const QString &reason, UserInformationFlags flags)
{
    Q_D(Portal);

    d->getUserInformation(parent, reason, flags);
}

void PortalPrivate::getUserInformation(const Parent &parent, const QString &reason, UserInformationFlags flags)
{
    xdp_portal_get_user_information(m_xdpPortal, parent.d_ptr->m_xdpParent, reason.toStdString().c_str(), static_cast<XdpUserInformationFlags>((int)flags), nullptr, gotUserInformation, this);
}

void PortalPrivate::gotUserInformation(GObject *object, GAsyncResult *result, gpointer data)
{
    XdpPortal *xdpPortal = XDP_PORTAL(object);
    PortalPrivate *portalPrivate = static_cast<PortalPrivate*>(data);
    g_autoptr(GError) error = nullptr;
    g_autofree gchar *id = nullptr;
    g_autofree gchar *name = nullptr;
    g_autofree gchar *image = nullptr;

    GVariant *ret = xdp_portal_get_user_information_finish(xdpPortal, result, &error);

    if (ret) {
        QVariantMap responseData;
        if (g_variant_lookup(ret, "id", "s", &id)) {
            responseData.insert(QStringLiteral("id"), id);
        }

        if (g_variant_lookup(ret, "name", "s", &name)) {
            responseData.insert(QStringLiteral("name"), name);
        }

        if (g_variant_lookup(ret, "image", "s", &image)) {
            responseData.insert(QStringLiteral("image"), image);
        }

        Response response(true, QString(), responseData);
        portalPrivate->q_ptr->getUserInformationResponse(response);
    } else {
        Response response(false, error ? QString(error->message) : QString());
        portalPrivate->q_ptr->getUserInformationResponse(response);
    }
}

