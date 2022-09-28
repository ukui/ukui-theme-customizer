#ifndef UKUITHEMECUSTOMIZER_H
#define UKUITHEMECUSTOMIZER_H

#include <QMainWindow>
#include <QScopedPointer>
#include <QFileDialog>
#include "../ukuithemeelement/ukuithemeelement.h"
#include "../packagecreator/packagecreator.h"
//#include "src/globalthemecreator/globalthemecreator.h"
#include <QSettings>
#include <QPushButton>
#include <QMutex>

namespace Ui
{
class UKUIThemeCustomizer;
}

class UKUIThemeCustomizer : public QMainWindow
{
    Q_OBJECT
public:
    explicit UKUIThemeCustomizer(QWidget *parent = nullptr);
    ~UKUIThemeCustomizer();

private:
    QPointer <packageCreator> creator;
    QMutex creatorMutex;
    QScopedPointer<Ui::UKUIThemeCustomizer> m_ui;
    UKUIThemeModel globalThemeModel, wallpaperCollectionModel, iconModel,
                  cursorModel, soundModel, gtkStyleModel, qtStyleModel;

private slots:
    void onIconAddPressed();
    void onIconDeletePressed();
    void onCursorAddPressed();
    void onCursorDeletePressed();
    void onWallpaperCollectionAddPressed();
    void onWallpaperCollectionDeletePressed();
    void updateLogBox(QString s);
};

#endif // UKUITHEMECUSTOMIZER_H
// kate: indent-mode cstyle; indent-width 1; replace-tabs on; ;
