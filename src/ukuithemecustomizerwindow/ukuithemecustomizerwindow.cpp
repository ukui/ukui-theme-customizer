#include "ukuithemecustomizerwindow.h"
#include "ui_ukuithemecustomizerwindow.h"
#include <QPushButton>
#include <QDebug>

UKUIThemeCustomizer::UKUIThemeCustomizer(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::UKUIThemeCustomizer)
{
    m_ui->setupUi(this);

    connect(m_ui->iconAdd, &QPushButton::pressed, this, &UKUIThemeCustomizer::onIconAddPressed);
}

UKUIThemeCustomizer::~UKUIThemeCustomizer(){}

void UKUIThemeCustomizer::onIconAddPressed()
{
    auto iconConfigFile = QFileDialog::getOpenFileName(this, tr("打开Theme文件"), "./", tr("Theme文件 (*.theme)"));
    if (iconConfigFile == "") return;
}

