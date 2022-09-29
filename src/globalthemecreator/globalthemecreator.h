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
    globalThemeCreator(UKUIThemeModel * wallpaperCollectionModel,
                       UKUIThemeModel * iconModel,
                       UKUIThemeModel * cursorModel,
                       UKUIThemeModel * soundModel,
                       UKUIThemeModel * gtkStyleModel,
                       UKUIThemeModel * qtStyleModel);
    ~globalThemeCreator();
private:
    QScopedPointer<Ui::globalThemeCreator> m_ui;
};

#endif // GLOBALTHEMECREATOR_H
// kate: indent-mode cstyle; indent-width 1; replace-tabs on; ;
