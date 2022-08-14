#ifndef UKUITHEMECUSTOMIZER_H
#define UKUITHEMECUSTOMIZER_H

#include <QMainWindow>
#include <QScopedPointer>

namespace Ui {
class UKUIThemeCustomizer;
}

class UKUIThemeCustomizer : public QMainWindow
{
    Q_OBJECT

public:
    explicit UKUIThemeCustomizer(QWidget *parent = nullptr);
    ~UKUIThemeCustomizer() override;

private:
    QScopedPointer<Ui::UKUIThemeCustomizer> m_ui;
};

#endif // UKUITHEMECUSTOMIZER_H
