#ifndef UKUITHEMEELEMENT_H_INCLUDED
#define UKUITHEMEELEMENT_H_INCLUDED

#include <QObject>
#include <QAbstractItemView>
#include <QAbstractTableModel>

class UKUIIconModel: public QAbstractTableModel {
    QVector <std::pair<QString,QString>> IconData;
public:
    virtual QVariant data(const QModelIndex &index, int role) const override;
    void addItem(const QString & name, const QString & path);
    void deleteItem(const QModelIndexList & model);
    virtual int columnCount(const QModelIndex &parent Q_DECL_UNUSED) const override {
        return 2;
    }
    virtual int rowCount(const QModelIndex &parent Q_DECL_UNUSED) const override {
        return IconData.length();
    }
};

#endif // UKUITHEMEELEMENT_H_INCLUDED
