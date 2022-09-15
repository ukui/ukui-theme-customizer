#include "ukuithemecustomizerwindow.h"
#include "ui_ukuithemecustomizerwindow.h"

UKUIThemeCustomizer::UKUIThemeCustomizer(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::UKUIThemeCustomizer)
{
    m_ui->setupUi(this);
    connect(m_ui->iconAdd, &QPushButton::pressed, this, &UKUIThemeCustomizer::onIconAddPressed);
    connect(&standardLog, &logger::msgChanged, this, &UKUIThemeCustomizer::updateLogBox);
}

UKUIThemeCustomizer::~UKUIThemeCustomizer(){}

void UKUIThemeCustomizer::onIconAddPressed()
{
    auto iconConfigFile = QFileDialog::getOpenFileName(this, tr("打开Theme文件"), "./", tr("Theme文件 (*.theme)"));
    if (iconConfigFile == "") return;
    iconPackageCreator package(iconConfigFile, this);
    package.exec();
}


void UKUIThemeCustomizer::updateLogBox(const QString& s) {
    m_ui->logbox->setText(s);
}

