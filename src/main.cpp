#include "src/ukuithemecustomizerwindow/ukuithemecustomizerwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    UKUIThemeCustomizer w;
    w.show();

    return app.exec();
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
