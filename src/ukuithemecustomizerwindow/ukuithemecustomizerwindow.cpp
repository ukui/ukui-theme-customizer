#include "ukuithemecustomizerwindow.h"
#include "ui_ukuithemecustomizerwindow.h"
#include "../logger/logger.h"

UKUIThemeCustomizer::UKUIThemeCustomizer(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::UKUIThemeCustomizer)
{
    m_ui->setupUi(this);
    connect(m_ui->iconAdd, &QPushButton::pressed, this, &UKUIThemeCustomizer::onIconAddPressed);
    connect(&logger::getStandardLogger(), &logger::msgChanged, this, &UKUIThemeCustomizer::updateLogBox);

    m_ui->iconView->setModel(&iconModel);
}

UKUIThemeCustomizer::~UKUIThemeCustomizer(){}

void UKUIThemeCustomizer::onIconAddPressed()
{
    auto iconConfigFile = QFileDialog::getOpenFileName(this, tr("打开Theme文件"), "./", tr("Theme文件 (*.theme)"));
    if (iconConfigFile == "") return;
    iconPackageCreator package(iconConfigFile, this);
    package.exec();
}


void UKUIThemeCustomizer::updateLogBox(QString s) {
    m_ui->logbox->setText(s);
}

