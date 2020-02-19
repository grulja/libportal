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

#include "portal-test-qt.h"
#include "ui_portal-test-qt.h"

#include <QStringLiteral>

PortalTestQt::PortalTestQt(QWidget *parent, Qt::WindowFlags f)
    : QMainWindow(parent, f)
    , m_mainWindow(new Ui_PortalTestQt)
    , m_portal(new Xdp::Portal(this))
{
    m_mainWindow->setupUi(this);

    connect(m_mainWindow->openFileButton, &QPushButton::clicked, [=] (bool clicked) {
        Xdp::Parent xdpParent(windowHandle());
        Xdp::FileChooserFilterRule rule(Xdp::FileChooserFilterRule::Type::Mimetype, QStringLiteral("image/jpeg"));
        Xdp::FileChooserFilterRule rule2;
        rule2.setType(Xdp::FileChooserFilterRule::Type::Pattern);
        rule2.setRule(QStringLiteral("*.png"));
        Xdp::FileChooserFilter filter(QStringLiteral("Images"), {rule});
        filter.addRule(rule2);
        Xdp::FileChooserChoice choice(QStringLiteral("choice-id"), QStringLiteral("choice-label"),
                                      QMap<QString, QString>{{QStringLiteral("option1-id"), QStringLiteral("option1-value")}}, QStringLiteral("option1-id"));
        choice.addOption(QStringLiteral("option2-id"), QStringLiteral("option2-value"));

        m_portal->openFile(xdpParent, QStringLiteral("Portal Test Qt"), {filter}, filter, {choice}, Xdp::OpenFileFlag::Multiple);
        connect(m_portal, &Xdp::Portal::openFileResponse, this, &PortalTestQt::onFileOpened);
    });
    connect(m_mainWindow->saveFileButton, &QPushButton::clicked, [=] (bool clicked) {
        Xdp::Parent xdpParent(windowHandle());
        m_portal->saveFile(xdpParent, QStringLiteral("Portal Test Qt "), QStringLiteral("name.txt"), QStringLiteral("/tmp"), QStringLiteral("name_old.txt"),
                           {}, Xdp::FileChooserFilter(), {}, Xdp::SaveFileFlag::None);
    });
    connect(m_mainWindow->saveFilesButton, &QPushButton::clicked, [=] (bool clicked) {
        Xdp::Parent xdpParent(windowHandle());
        m_portal->saveFiles(xdpParent, QStringLiteral("Portal Test Qt "), QStringLiteral("/tmp"), QStringList{QStringLiteral("foo.txt"), QStringLiteral("bar.txt")}, {}, Xdp::SaveFileFlag::None);
    });
}

PortalTestQt::~PortalTestQt()
{
    delete m_mainWindow;
    delete m_portal;
}

void PortalTestQt::onFileOpened(const Xdp::Response &response)
{
    if (response.isSuccess()) {
        QStringList uris = response.result().value(QStringLiteral("uris")).toStringList();
        if (!uris.isEmpty()) {
            Xdp::Parent xdpParent(windowHandle());
            m_portal->openUri(xdpParent, uris.at(0), Xdp::OpenUriFlag::Ask);
        }
    }
}
