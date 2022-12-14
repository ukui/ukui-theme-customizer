#ifndef UKUITHEMECUSTOMIZER_H
#define UKUITHEMECUSTOMIZER_H

#include "../globalthemecreator/globalthemecreator.h"
#include "../packagecreator/packagecreator.h"
#include "../ukuithemeelement/ukuithemeelement.h"
#include <QFileDialog>
#include <QMainWindow>
#include <QMutex>
#include <QPushButton>
#include <QScopedPointer>
#include <QSettings>

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
    QPointer<packageCreator> creator;
    QMutex creatorMutex;
    QScopedPointer<Ui::UKUIThemeCustomizer> m_ui;
    UKUIThemeModel globalThemeModel, wallpaperCollectionModel, iconModel,
                   cursorModel, soundModel, gtkStyleModel, qtStyleModel;

private slots:
    void onGlobalThemeAddPressed();
    void onGlobalThemeDeletePressed();
    void onGlobalThemeAddExistingPressed();
    void onIconAddPressed();
    void onIconDeletePressed();
    void onIconAddExistingPressed();
    void onCursorAddPressed();
    void onCursorDeletePressed();
    void onCursorAddExistingPressed();
    void onWallpaperCollectionAddPressed();
    void onWallpaperCollectionDeletePressed();
    void onWallpaperCollectionAddExistingPressed();
    void onSoundAddPressed();
    void onSoundDeletePressed();
    void onSoundAddExistingPressed();
    void unsupportNow();
    void onGtkStyleDeletePressed();
    void onGtkStyleAddExistingPressed();
    void onQtStyleDeletePressed();
    void onQtStyleAddExistingPressed();
    void updateLogBox(QString s);
};

#endif // UKUITHEMECUSTOMIZER_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; ;
