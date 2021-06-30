/*
 * Copyright (C) 2020-2021, Jan Grulich
 *
 * This file is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, version 3.0 of the
 * License.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: LGPL-3.0-only
 */

#include "notification.h"
#include "parent.h"
#include "parent_p.h"
#include "portal_p.h"

static GVariant *convertQVariant(const QVariant &variant)
{
    if (variant.type() == QVariant::Bool) {
        return g_variant_new_boolean(variant.toBool());
    } else if (variant.type() == QVariant::Int) {
        return g_variant_new_int32(variant.toInt());
    } else if (variant.type() == QVariant::UInt) {
        return g_variant_new_uint32(variant.toUInt());
    } else if (variant.type() == QVariant::Double) {
        return g_variant_new_double(variant.toDouble());
    } else if (variant.type() == QVariant::String) {
        return g_variant_new_string(variant.toString().toLatin1());
    } else if (variant.type() == QVariant::Char) {
        return g_variant_new_byte(variant.toChar().toLatin1());
    } else {
        return nullptr;
    }
}

static QVariant convertGVariant(GVariant *variant)
{
    return QVariant();
}

namespace Xdp
{

void PortalPrivate::addNotification(const Parent &parent, const QString &id, const QVariantMap &notification, NotificationFlags flags)
{
    GVariantBuilder builder;

    g_variant_builder_init(&builder, G_VARIANT_TYPE_VARDICT);

    if (notification.contains(QStringLiteral("title"))) {
        g_variant_builder_add(&builder, "{sv}", "title", g_variant_new_string(notification.value(QStringLiteral("title")).toString().toLatin1()));
    } else if (notification.contains(QStringLiteral("body"))) {
        g_variant_builder_add(&builder, "{sv}", "body", g_variant_new_string(notification.value(QStringLiteral("body")).toString().toLatin1()));
    } else if (notification.contains(QStringLiteral("icon"))) {
        // TODO
    } else if (notification.contains(QStringLiteral("priority"))) {
        g_variant_builder_add(&builder, "{sv}", "priority", g_variant_new_string(notification.value(QStringLiteral("priority")).toString().toLatin1()));
    } else if (notification.contains(QStringLiteral("default-action"))) {
        g_variant_builder_add(&builder, "{sv}", "default-action", g_variant_new_string(notification.value(QStringLiteral("default-action")).toString().toLatin1()));
    } else if (notification.contains(QStringLiteral("default-action-target"))) {
        GVariant *var = convertQVariant(notification.value(QStringLiteral("default-action-target")));
        if (!var) {
            g_variant_builder_add(&builder, "{sv}", "default-action-target", g_variant_new("v", var));
        }
    } else if (notification.contains(QStringLiteral("buttons"))) {
        // TODO
    }

    xdp_portal_add_notification(m_xdpPortal, id.toLatin1(), g_variant_new("(a{sv})", &builder),
                                static_cast<XdpNotificationFlags>((int)flags), nullptr /* cancellable */, notificationAdded, this);
}

void PortalPrivate::removeNotification(const QString &id)
{

}

void PortalPrivate::notificationAdded(GObject *object, GAsyncResult *result, gpointer data)
{

}

void PortalPrivate::onNotificationActionInvoked(XdpPortal *portal, const char *id, const char *actionName, GVariant *parameter, gpointer data)
{

}

}
