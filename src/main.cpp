#include "src/ukuithemecustomizerwindow/ukuithemecustomizerwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    UKUIThemeCustomizer w;
    w.show();

    return app.exec();
}

