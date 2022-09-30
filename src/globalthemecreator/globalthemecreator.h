#ifndef GLOBALTHEMECREATOR_H
#define GLOBALTHEMECREATOR_H

#include <QScopedPointer>
#include <QDialog>
#include "../ukuithemeelement/ukuithemeelement.h"

namespace Ui
{
class globalThemeCreator;
}

class globalThemeCreator : public QDialog
{
    Q_OBJECT

public:
    globalThemeCreator(UKUIThemeModel *wallpaperCollectionModel,
                       UKUIThemeModel *iconModel,
                       UKUIThemeModel *cursorModel,
                       UKUIThemeModel *soundModel,
                       UKUIThemeModel *gtkStyleModel,
                       UKUIThemeModel *qtStyleModel);
    ~globalThemeCreator();
    void onAccepted();
    QStringList getDepends();
    bool isReadyToPackage();
private:
    QScopedPointer<Ui::globalThemeCreator> m_ui;
    QStringList depends;
    bool readyToPackage;
};

#endif // GLOBALTHEMECREATOR_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; ;



