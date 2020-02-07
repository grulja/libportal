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

#ifndef LIBPORTALQT_FILECHOOSER_H
#define LIBPORTALQT_FILECHOOSER_H

#include "libportalqt_export.h"

#include <QStringList>
#include <QMap>
#include <QSharedPointer>

namespace Xdp {

enum class OpenFileFlag
{
    None = 0x0,
    Multiple = 0x1
};
Q_DECLARE_FLAGS(OpenFileFlags, OpenFileFlag)

enum class SaveFileFlag
{
    None = 0x0
};
Q_DECLARE_FLAGS(SaveFileFlags, SaveFileFlag)

class FileChooserFilterRulePrivate;

class LIBPORTALQT_EXPORT FileChooserFilterRule
{
public:
    enum class Type {
        Pattern = 0,
        Mimetype = 1
    };

    FileChooserFilterRule(Type type, const QString &rule);
    FileChooserFilterRule(const FileChooserFilterRule &other);
    ~FileChooserFilterRule();

    Type type() const;
    QString rule() const;
private:
    Q_DECLARE_PRIVATE(FileChooserFilterRule)

    const QScopedPointer<FileChooserFilterRulePrivate> d_ptr;
};
typedef QList<FileChooserFilterRule> FileChooserFilterRules;

class FileChooserFilterPrivate;

class LIBPORTALQT_EXPORT FileChooserFilter
{
public:
    FileChooserFilter();
    FileChooserFilter(const QString &label, const FileChooserFilterRules &rules);
    FileChooserFilter(const FileChooserFilter &other);
    ~FileChooserFilter();

    bool isEmpty() const;
    QString label() const;
    FileChooserFilterRules rules() const;
private:
    Q_DECLARE_PRIVATE(FileChooserFilter)

    const QScopedPointer<FileChooserFilterPrivate> d_ptr;
};
typedef QList<FileChooserFilter> FileChooserFilterList;

class FileChooserChoicePrivate;

class LIBPORTALQT_EXPORT FileChooserChoice
{
public:
    FileChooserChoice(const QString &id, const QString &label, const QMap<QString, QString> &options, const QString &selected = QString());
    FileChooserChoice(const FileChooserChoice &other);
    ~FileChooserChoice();

    QString id() const;
    QString label() const;
    QMap<QString, QString> options() const;
    QString selected() const;

private:
    Q_DECLARE_PRIVATE(FileChooserChoice)

    const QScopedPointer<FileChooserChoicePrivate> d_ptr;
};
typedef QList<FileChooserChoice> FileChooserChoices;

}
Q_DECLARE_OPERATORS_FOR_FLAGS(Xdp::OpenFileFlags)
Q_DECLARE_OPERATORS_FOR_FLAGS(Xdp::SaveFileFlags)

#endif // LIBPORTALQT_FILECHOOSER_H
