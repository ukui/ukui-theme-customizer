#ifndef UKUITHEMEELEMENT_H_INCLUDED
#define UKUITHEMEELEMENT_H_INCLUDED

#include "../settingmanager/settingmanager.h"
#include <QAbstractItemView>
#include <QAbstractTableModel>
#include <QDir>
#include <QObject>
#include <QDebug>

class UKUIThemeModel : public QAbstractTableModel
{
    QVector<std::pair<QString, QString>> ThemeData;
    QDir workDir;

public:
    UKUIThemeModel(const QDir &dir);
    virtual QVariant data(const QModelIndex &index, int role) const override;
    void addItem(const QString &name, const QString &path);
    void deleteItem(const QModelIndexList &list);
    virtual int
    columnCount(const QModelIndex &parent Q_DECL_UNUSED) const override;
    virtual int rowCount(const QModelIndex &parent Q_DECL_UNUSED) const override;
};

#endif // UKUITHEMEELEMENT_H_INCLUDED
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; ;
