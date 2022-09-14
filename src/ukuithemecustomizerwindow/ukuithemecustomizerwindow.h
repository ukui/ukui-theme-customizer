#ifndef UKUITHEMECUSTOMIZER_H
#define UKUITHEMECUSTOMIZER_H

#include <QMainWindow>
#include <QScopedPointer>
#include <QFileDialog>
//#include "src/ukuithemeelement/ukuithemeelement.h"
#include "../packagecreator/packagecreator.h"
//#include "src/globalthemecreator/globalthemecreator.h"
#include <QSettings>
#include <QPushButton>
#include <QDebug>

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
    QScopedPointer<Ui::UKUIThemeCustomizer> m_ui;
    //UKUIIconModel globalThemeModel, wallpaperCollectionModel, iconModel,
    //              cursorModel, soundModel, gtkStyleModel, qtStyleModel;
    //void log(const QString &message);
private slots:
    void onIconAddPressed();
};

#endif // UKUITHEMECUSTOMIZER_H
