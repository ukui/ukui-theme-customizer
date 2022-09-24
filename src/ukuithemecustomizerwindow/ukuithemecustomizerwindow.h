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
#include <iostream>

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
    QScopedPointer<Ui::UKUIThemeCustomizer> m_ui;
    UKUIIconModel globalThemeModel, wallpaperCollectionModel, iconModel,
                  cursorModel, soundModel, gtkStyleModel, qtStyleModel;

private slots:
    void onIconAddPressed();
    void updateLogBox(QString s);
};

#endif // UKUITHEMECUSTOMIZER_H
