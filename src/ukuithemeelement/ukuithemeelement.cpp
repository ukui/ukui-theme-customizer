#include "ukuithemeelement.h"

UKUIThemeModel::UKUIThemeModel(const QDir &dir) : workDir(dir)
{
    workDir.setNameFilters(QStringList() << "*.deb");
    for (auto i : workDir.entryInfoList()) {
        addItem(i.baseName(), i.filePath());
    }
}

QVariant UKUIThemeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0:
            return ThemeData[index.row()].first;
        case 1:
            return ThemeData[index.row()].second;
        default:
            return QVariant();
        }
    }
    return QVariant();
}

int UKUIThemeModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

int UKUIThemeModel::rowCount(const QModelIndex &parent) const
{
    return ThemeData.length();
}

void UKUIThemeModel::addItem(const QString &name, const QString &path)
{
    ThemeData.append({name, path});
    emit dataChanged(QAbstractTableModel::createIndex(ThemeData.size() - 1, 0),
                     QAbstractTableModel::createIndex(ThemeData.size() - 1, 1));
}

void UKUIThemeModel::deleteItem(const QModelIndexList &list)
{
    for (auto i : list) {
        QFile::remove(ThemeData[i.row()].second);
        ThemeData.remove(i.row());
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; ;
