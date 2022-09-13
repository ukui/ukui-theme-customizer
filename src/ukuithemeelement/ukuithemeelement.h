#ifndef UKUITHEMEELEMENT_H_INCLUDED
#define UKUITHEMEELEMENT_H_INCLUDED

#include <QObject>
#include <QAbstractItemView>
#include <QAbstractTableModel>

class UKUIIconModel: public QAbstractTableModel {
    QVector <std::pair<QString,QString>> IconData;
public:
    virtual QVariant data(const QModelIndex &index, int role) const override {
        if (!index.isValid()) return QVariant();
        if (role == Qt::DisplayRole) {
            switch (index.column()) {
                case 0: return IconData[index.row()].first;
                case 1: return IconData[index.row()].second;
                default: return QVariant();
            }
        }
        return QVariant();
    }
    virtual int columnCount(const QModelIndex &parent Q_DECL_UNUSED) const override {
        return 2;
    }
    virtual int rowCount(const QModelIndex &parent Q_DECL_UNUSED) const override {
        return IconData.length();
    }
};

#endif // UKUITHEMEELEMENT_H_INCLUDED
