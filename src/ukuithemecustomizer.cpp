#include "ukuithemecustomizer.h"
#include "ui_ukuithemecustomizer.h"

UKUIThemeCustomizer::UKUIThemeCustomizer(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::UKUIThemeCustomizer)
{
    m_ui->setupUi(this);
}

UKUIThemeCustomizer::~UKUIThemeCustomizer() = default;
