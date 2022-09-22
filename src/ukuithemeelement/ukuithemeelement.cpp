#include "ukuithemeelement.h"


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

