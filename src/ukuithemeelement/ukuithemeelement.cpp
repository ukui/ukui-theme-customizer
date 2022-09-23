#include "ukuithemeelement.h"

UKUIIconModel::UKUIIconModel(): workDir(settingManager::getSettings().iconDir()) {
    workDir.setNameFilters(QStringList()<<"*.deb");
    for (auto i : workDir.entryInfoList() ) {
        addItem(i.baseName(), i.filePath());
    }
}

QVariant UKUIIconModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) return QVariant();
    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0:
            return IconData[index.row()].first;
        case 1:
            return IconData[index.row()].second;
        default:
            return QVariant();
        }
    }
    return QVariant();
}

int UKUIIconModel::columnCount(const QModelIndex& parent) const {
    return 2;
}

int UKUIIconModel::rowCount(const QModelIndex& parent) const {
    return IconData.length();
}

void UKUIIconModel::addItem(const QString &name, const QString &path)
{
    IconData.append({name, path});
}

void UKUIIconModel::deleteItem(const QModelIndexList &model)
{
    for (auto i : model) {
        IconData.remove(i.row());
    }
}


