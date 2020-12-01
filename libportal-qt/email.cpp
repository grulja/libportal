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

#include "email.h"
#include "parent.h"
#include "parent_p.h"
#include "portal_p.h"

#include <iostream>

using namespace Xdp;

void Portal::composeEmail(const Parent &parent, const QStringList &addresses, const QStringList &cc,
                          const QStringList &bcc, const QString &subject, const QString &body,
                          const QStringList &attachments, EmailFlags flags)
{
    Q_D(Portal);

    d->composeEmail(parent, addresses, cc, bcc, subject, body, attachments, flags);
}

void PortalPrivate::composeEmail(const Parent &parent, const QStringList &addresses, const QStringList &cc,
                                 const QStringList &bcc, const QString &subject, const QString &body,
                                 const QStringList &attachments, EmailFlags flags)
{
    int i = 0;
    const char *addressesArray[addresses.size() + 1];
    const char *ccArray[cc.size() + 1];
    const char *bccArray[bcc.size() + 1];
    const char *attachmentsArray[attachments.size() + 1];

    while ( i < addresses.size()) {
        addressesArray[i] = addresses.at(i).toStdString().c_str();
        i++;
    }
    addressesArray[i] = nullptr;

    i = 0;
    while (i < cc.size()) {
        ccArray[i] = cc.at(i).toStdString().c_str();
        i++;
    }
    ccArray[i] = nullptr;

    i = 0;
    while (i < bcc.size()) {
        bccArray[i] = bcc.at(i).toStdString().c_str();
        i++;
    }
    bccArray[i] = nullptr;

    i = 0;
    while (i < attachments.size()) {
        attachmentsArray[i] = attachments.at(i).toStdString().c_str();
        i++;
    }
    attachmentsArray[i] = nullptr;

    xdp_portal_compose_email(m_xdpPortal, parent.d_ptr->m_xdpParent, addressesArray, ccArray, bccArray, const_cast<char*>(subject.toStdString().c_str()),
                             const_cast<char*>(body.toStdString().c_str()), attachmentsArray, static_cast<XdpEmailFlags>((int)flags), nullptr, composedEmail, this);
}

void PortalPrivate::composedEmail(GObject *object, GAsyncResult *result, gpointer data)
{
    XdpPortal *xdpPortal = XDP_PORTAL(object);
    PortalPrivate *portalPrivate = static_cast<PortalPrivate*>(data);
    g_autoptr(GError) error = nullptr;

    bool ret = xdp_portal_compose_email_finish(xdpPortal, result, &error);

    Response response(ret, error ? QString(error->message) : QString());
    portalPrivate->q_ptr->composeEmailResponse(response);
}
