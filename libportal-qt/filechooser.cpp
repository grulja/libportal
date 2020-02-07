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

#include "filechooser.h"
#include "portal.h"
#include "parent.h"
#include "parent_p.h"
#include "portal_p.h"

#include <QFile>

namespace Xdp
{

class FileChooserFilterRulePrivate
{
public:
    FileChooserFilterRulePrivate(FileChooserFilterRule::Type type, const QString &rule);
    FileChooserFilterRulePrivate(const FileChooserFilterRulePrivate &other);
    ~FileChooserFilterRulePrivate() { };

    FileChooserFilterRule::Type m_type;
    QString m_rule;
};

FileChooserFilterRulePrivate::FileChooserFilterRulePrivate(FileChooserFilterRule::Type type, const QString &rule)
    : m_type(type)
    , m_rule(rule)
{
}

FileChooserFilterRulePrivate::FileChooserFilterRulePrivate(const FileChooserFilterRulePrivate &other)
    : FileChooserFilterRulePrivate(other.m_type, other.m_rule)
{
}

FileChooserFilterRule::FileChooserFilterRule(FileChooserFilterRule::Type type, const QString &rule)
    : d_ptr(new FileChooserFilterRulePrivate(type, rule))
{
}

FileChooserFilterRule::FileChooserFilterRule(const FileChooserFilterRule &other)
    : FileChooserFilterRule(other.type(), other.rule())
{
}

FileChooserFilterRule::~FileChooserFilterRule()
{
}

FileChooserFilterRule::Type FileChooserFilterRule::type() const
{
    Q_D(const FileChooserFilterRule);
    return d->m_type;
}

QString FileChooserFilterRule::rule() const
{
    Q_D(const FileChooserFilterRule);
    return d->m_rule;
}

class FileChooserFilterPrivate
{
public:
    FileChooserFilterPrivate() { };
    FileChooserFilterPrivate(const QString &label, const FileChooserFilterRules &rules);
    FileChooserFilterPrivate(const FileChooserFilterPrivate &other);
    ~FileChooserFilterPrivate() { };

    QString m_label;
    FileChooserFilterRules m_rules;
};

FileChooserFilterPrivate::FileChooserFilterPrivate(const QString &label, const FileChooserFilterRules &rules)
    : m_label(label)
    , m_rules(rules)
{
}

FileChooserFilterPrivate::FileChooserFilterPrivate(const FileChooserFilterPrivate &other)
    : FileChooserFilterPrivate(other.m_label, other.m_rules)
{
}

FileChooserFilter::FileChooserFilter()
    : d_ptr(new FileChooserFilterPrivate())
{
}

FileChooserFilter::FileChooserFilter(const QString &label, const FileChooserFilterRules &rules)
    : d_ptr(new FileChooserFilterPrivate(label, rules))
{
}

FileChooserFilter::FileChooserFilter(const FileChooserFilter &other)
    : FileChooserFilter(other.label(), other.rules())
{
}

FileChooserFilter::~FileChooserFilter()
{
}

bool FileChooserFilter::isEmpty() const
{
    Q_D(const FileChooserFilter);
    return d->m_label.isEmpty() || d->m_rules.isEmpty();
}

QString FileChooserFilter::label() const
{
    Q_D(const FileChooserFilter);
    return d->m_label;
}

FileChooserFilterRules FileChooserFilter::rules() const
{
    Q_D(const FileChooserFilter);
    return d->m_rules;
}

class FileChooserChoicePrivate
{
public:
    FileChooserChoicePrivate(const QString &id, const QString &label, const QMap<QString, QString> &options, const QString &selected);
    FileChooserChoicePrivate(const FileChooserChoicePrivate &other);
    ~FileChooserChoicePrivate() { };

    QString m_id;
    QString m_label;
    QMap<QString, QString> m_options;
    QString m_selected;
};

FileChooserChoicePrivate::FileChooserChoicePrivate(const QString &id, const QString &label, const QMap<QString, QString> &options, const QString &selected)
    : m_id(id)
    , m_label(label)
    , m_options(options)
    , m_selected(selected)
{
}

FileChooserChoicePrivate::FileChooserChoicePrivate(const FileChooserChoicePrivate &other)
    : FileChooserChoicePrivate(other.m_id, other.m_label, other.m_options, other.m_selected)
{
}

FileChooserChoice::FileChooserChoice(const QString &id, const QString &label, const QMap<QString, QString> &choices, const QString &selected)
    : d_ptr(new FileChooserChoicePrivate(id, label, choices, selected))
{
}

FileChooserChoice::FileChooserChoice(const FileChooserChoice &other)
    : FileChooserChoice(other.id(), other.label(), other.options(), other.selected())
{
}

FileChooserChoice::~FileChooserChoice()
{
}

QString FileChooserChoice::id() const
{
    Q_D(const FileChooserChoice);
    return d->m_id;
}

QString FileChooserChoice::label() const
{
    Q_D(const FileChooserChoice);
    return d->m_label;
}

QMap<QString, QString> FileChooserChoice::options() const
{
    Q_D(const FileChooserChoice);
    return d->m_options;
}

QString FileChooserChoice::selected() const
{
    Q_D(const FileChooserChoice);
    return d->m_selected;
}

void Portal::openFile(const Parent &parent, const QString &title, const FileChooserFilterList &filters, const FileChooserFilter &currentFilter,
              const FileChooserChoices &choices, OpenFileFlags flags)
{
    Q_D(Portal);

    d->openFile(parent, title, filters, currentFilter, choices, flags);
}

void Portal::saveFile(const Parent &parent, const QString &title, const QString &currentName, const QString &currentFolder, const QString &currentFile,
                      const FileChooserFilterList &filters, const FileChooserFilter &currentFilter, const FileChooserChoices &choices, SaveFileFlags flags)
{
    Q_D(Portal);

    d->saveFile(parent, title, currentName, currentFolder, currentFile, filters, currentFilter, choices, flags);
}

void Portal::saveFiles(const Parent &parent, const QString &title, const QString &currentFolder, const QStringList &files,
                       const FileChooserChoices &choices, SaveFileFlags flags)
{
    Q_D(Portal);

    d->saveFiles(parent, title, currentFolder, files, choices, flags);
}

static GVariant *filterToVariant(const FileChooserFilter &filter)
{
    GVariantBuilder builder;

    g_variant_builder_init(&builder, G_VARIANT_TYPE("a(us)"));

    for (const FileChooserFilterRule &rule : filter.rules()) {
        g_variant_builder_add(&builder, "(us)", static_cast<uint>(rule.type()), rule.rule().toStdString().c_str());
    }

    return g_variant_new("(s@a(us))", filter.label().toStdString().c_str(), g_variant_builder_end(&builder));
}

static GVariant *filterListToVariant(const FileChooserFilterList &filters)
{
    GVariantBuilder builder;

    g_variant_builder_init(&builder, G_VARIANT_TYPE("a(sa(us))"));

    for (const FileChooserFilter &filter : filters) {
        g_variant_builder_add(&builder, "@(sa(us))", filterToVariant(filter));
    }

    return g_variant_builder_end(&builder);
}

static GVariant *choiceToVariant(const FileChooserChoice &choice)
{
    GVariantBuilder builder;

    g_variant_builder_init(&builder, G_VARIANT_TYPE("a(ss)"));

    if (choice.options().count()) {
        for (auto it = choice.options().constBegin(); it != choice.options().constEnd(); ++it) {
            g_variant_builder_add(&builder, "(&s&s)", it.key().toStdString().c_str(), it.value().toStdString().c_str());
        }
    }

    return g_variant_new("(&s&s@a(ss)&s)", choice.id().toStdString().c_str(), choice.label().toStdString().c_str(),
                         g_variant_builder_end(&builder), choice.selected().toStdString().c_str());
}

static GVariant *choicesToVariant(const FileChooserChoices &choices)
{
    GVariantBuilder builder;

    g_variant_builder_init(&builder, G_VARIANT_TYPE("a(ssa(ss)s)"));

    for (const FileChooserChoice &choice : choices) {
        g_variant_builder_add(&builder, "@(ssa(ss)s)",choiceToVariant(choice));
    }

    return g_variant_builder_end(&builder);
}

static GVariant *filesToVariant(const QStringList &files)
{
    GVariantBuilder builder;

    g_variant_builder_init(&builder, G_VARIANT_TYPE_BYTESTRING_ARRAY);

    for (const QString &file : files) {
        QByteArray fileArray = QFile::encodeName(file).append('\0');
        gpointer data = g_memdup(fileArray.data(), fileArray.length());
        g_variant_builder_add(&builder, "@ay", g_variant_new_from_data(G_VARIANT_TYPE("ay"), data, fileArray.length(), false, g_free, data));
    }

    return g_variant_builder_end(&builder);
}

void PortalPrivate::openFile(const Parent &parent, const QString &title, const FileChooserFilterList &filters, const FileChooserFilter &currentFilter,
                             const FileChooserChoices &choices, OpenFileFlags flags)
{
    xdp_portal_open_file(m_xdpPortal, parent.d_ptr->m_xdpParent, title.toStdString().c_str(), filterListToVariant(filters), currentFilter.isEmpty() ? nullptr : filterToVariant(currentFilter),
                         choicesToVariant(choices), static_cast<XdpOpenFileFlags>((int)flags), nullptr /*cancellable*/, openedFile, this);
}

void PortalPrivate::saveFile(const Parent &parent, const QString &title, const QString &currentName, const QString &currentFolder, const QString &currentFile,
                             const FileChooserFilterList &filters, const FileChooserFilter &currentFilter, const FileChooserChoices &choices, SaveFileFlags flags)
{
    xdp_portal_save_file(m_xdpPortal, parent.d_ptr->m_xdpParent, title.toStdString().c_str(),  currentName.toStdString().c_str(),
                         QFile::encodeName(currentFolder).append('\0'), QFile::encodeName(currentFile).append('\0'),
                         filterListToVariant(filters), currentFilter.isEmpty() ? nullptr : filterToVariant(currentFilter),
                         choicesToVariant(choices), static_cast<XdpSaveFileFlags>((int)flags), nullptr /*cancellable*/, savedFile, this);
}

void PortalPrivate::saveFiles(const Parent &parent, const QString &title, const QString &currentFolder, const QStringList &files,
                              const FileChooserChoices &choices, SaveFileFlags flags)
{
    xdp_portal_save_files(m_xdpPortal, parent.d_ptr->m_xdpParent, title.toStdString().c_str(), nullptr /*current_name*/,
                          QFile::encodeName(currentFolder).append('\0'), filesToVariant(files),
                          choicesToVariant(choices), static_cast<XdpSaveFileFlags>((int)flags), nullptr /*cancellable*/, savedFiles, this);
}

void PortalPrivate::openedFile(GObject *object, GAsyncResult *result, gpointer data)
{
    XdpPortal *xdpPortal = XDP_PORTAL(object);
    PortalPrivate *portalPrivate = static_cast<PortalPrivate*>(data);

    const char **uris;
    g_autoptr(GError) error = nullptr;
    GVariant *choices = nullptr;

    GVariant *ret = xdp_portal_open_file_finish(xdpPortal, result, &error);

    if (ret) {
        QVariantMap responseData;
        g_variant_lookup(ret, "uris", "^a&s", &uris);

        choices = g_variant_lookup_value(ret, "choices", G_VARIANT_TYPE("a(ss)"));
        if (choices) {
            QMap<QString, QString> choicesMap;
            for (uint i = 0; i < g_variant_n_children(choices); i++) {
                const char *id;
                const char *selected;
                g_variant_get_child(choices, i, "(&s&s)", &id, &selected);
                choicesMap.insert(QString(id), QString(selected));
            }
            responseData.insert(QStringLiteral("choices"), QVariant::fromValue<QMap<QString, QString> >(choicesMap));
            g_variant_unref (choices);
        }

        QStringList uriList;
        for (int i = 0; uris[i]; i++) {
            uriList << QString(uris[i]);
        }
        responseData.insert(QStringLiteral("uris"), uriList);

        Response response(true, QString(), responseData);
        portalPrivate->q_ptr->openFileResponse(response);
    } else {
        Response response(false, error ? QString(error->message) : QString());
        portalPrivate->q_ptr->openFileResponse(response);
    }
}

void PortalPrivate::savedFile(GObject *object, GAsyncResult *result, gpointer data)
{
    XdpPortal *xdpPortal = XDP_PORTAL(object);
    PortalPrivate *portalPrivate = static_cast<PortalPrivate*>(data);

    const char **uris;
    g_autoptr(GError) error = nullptr;
    GVariant *choices = nullptr;

    GVariant *ret = xdp_portal_save_file_finish(xdpPortal, result, &error);

    if (ret) {
        QVariantMap responseData;
        g_variant_lookup(ret, "uris", "^a&s", &uris);

        choices = g_variant_lookup_value(ret, "choices", G_VARIANT_TYPE("a(ss)"));
        if (choices) {
            QMap<QString, QString> choicesMap;
            for (uint i = 0; i < g_variant_n_children(choices); i++) {
                const char *id;
                const char *selected;
                g_variant_get_child(choices, i, "(&s&s)", &id, &selected);
                choicesMap.insert(QString(id), QString(selected));
            }
            responseData.insert(QStringLiteral("choices"), QVariant::fromValue<QMap<QString, QString> >(choicesMap));
            g_variant_unref (choices);
        }

        QStringList uriList;
        for (int i = 0; uris[i]; i++) {
            uriList << QString(uris[i]);
        }
        responseData.insert(QStringLiteral("uris"), uriList);

        Response response(true, QString(), responseData);
        portalPrivate->q_ptr->saveFileResponse(response);
    } else {
        Response response(false, error ? QString(error->message) : QString());
        portalPrivate->q_ptr->saveFileResponse(response);
    }
}

void PortalPrivate::savedFiles(GObject *object, GAsyncResult *result, gpointer data)
{
    XdpPortal *xdpPortal = XDP_PORTAL(object);
    PortalPrivate *portalPrivate = static_cast<PortalPrivate*>(data);

    const char **uris;
    g_autoptr(GError) error = nullptr;
    GVariant *choices = nullptr;

    GVariant *ret = xdp_portal_save_files_finish(xdpPortal, result, &error);

    if (ret) {
        QVariantMap responseData;
        g_variant_lookup(ret, "uris", "^a&s", &uris);

        choices = g_variant_lookup_value(ret, "choices", G_VARIANT_TYPE("a(ss)"));
        if (choices) {
            QMap<QString, QString> choicesMap;
            for (uint i = 0; i < g_variant_n_children(choices); i++) {
                const char *id;
                const char *selected;
                g_variant_get_child(choices, i, "(&s&s)", &id, &selected);
                choicesMap.insert(QString(id), QString(selected));
            }
            responseData.insert(QStringLiteral("choices"), QVariant::fromValue<QMap<QString, QString> >(choicesMap));
            g_variant_unref (choices);
        }

        QStringList uriList;
        for (int i = 0; uris[i]; i++) {
            uriList << QString(uris[i]);
        }
        responseData.insert(QStringLiteral("uris"), uriList);

        Response response(true, QString(), responseData);
        portalPrivate->q_ptr->saveFilesResponse(response);
    } else {
        Response response(false, error ? QString(error->message) : QString());
        portalPrivate->q_ptr->saveFilesResponse(response);
    }
}

}
