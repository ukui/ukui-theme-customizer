#include "ukuithemecustomizerwindow.h"
#include "ui_ukuithemecustomizerwindow.h"
#include "../settingmanager/settingmanager.h"

UKUIThemeCustomizer::UKUIThemeCustomizer(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::UKUIThemeCustomizer)
{
    m_ui->setupUi(this);
    connect(m_ui->iconAdd, &QPushButton::pressed, this, &UKUIThemeCustomizer::onIconAddPressed);
    connect(&logger::getStandardLogger(), &logger::msgChanged, this, &UKUIThemeCustomizer::updateLogBox);

    m_ui->iconView->setModel(&iconModel);
}

UKUIThemeCustomizer::~UKUIThemeCustomizer() {}

void UKUIThemeCustomizer::onIconAddPressed()
{
    auto iconConfigFile = QFileDialog::getOpenFileName(this, tr("打开Theme文件"), "./", tr("Theme文件 (*.theme)"));
    if (iconConfigFile == "") return;
    if (!creatorMutex.try_lock()) {
        logger::getStandardLogger().log("请等待当前任务完成");
        return;
    }
    creator = new iconPackageCreator(iconConfigFile);
    connect(creator, &packageCreator::packageSuccess, [&](const QFileInfo & info) {
        iconModel.addItem(info.baseName(), info.absolutePath());
        creatorMutex.unlock();
    });
    creator->exec();
}


void UKUIThemeCustomizer::updateLogBox(QString s)
{
    m_ui->logbox->setText(s);
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
