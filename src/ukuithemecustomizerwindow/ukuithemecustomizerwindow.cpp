#include "ukuithemecustomizerwindow.h"
#include "ui_ukuithemecustomizerwindow.h"
#include "../settingmanager/settingmanager.h"

UKUIThemeCustomizer::UKUIThemeCustomizer(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::UKUIThemeCustomizer),
    globalThemeModel(settingManager::getSettings().globalThemeDir()),
    wallpaperCollectionModel(settingManager::getSettings().wallpaperCollectionDir()),
    iconModel(settingManager::getSettings().iconDir()),
    cursorModel(settingManager::getSettings().cursorDir()),
    soundModel(settingManager::getSettings().soundDir()),
    gtkStyleModel(settingManager::getSettings().gtkStyleDir()),
    qtStyleModel(settingManager::getSettings().qtStyleDir())
{
    m_ui->setupUi(this);
    connect(&logger::getStandardLogger(), &logger::msgChanged, this, &UKUIThemeCustomizer::updateLogBox);

    m_ui->iconView->setModel(&iconModel);
    connect(m_ui->iconAdd, &QPushButton::pressed, this, &UKUIThemeCustomizer::onIconAddPressed);
    connect(m_ui->iconDel, &QPushButton::pressed, this, &UKUIThemeCustomizer::onIconDeletePressed);

    m_ui->cursorView->setModel(&cursorModel);
    connect(m_ui->cursorAdd, &QPushButton::pressed, this, &UKUIThemeCustomizer::onCursorAddPressed);
    connect(m_ui->cursorDel, &QPushButton::pressed, this, &UKUIThemeCustomizer::onCursorDeletePressed);

    m_ui->wallpaperCollectionView->setModel(&wallpaperCollectionModel);
    connect(m_ui->wallpaperCollectionAdd, &QPushButton::pressed, this, &UKUIThemeCustomizer::onWallpaperCollectionAddPressed);
    connect(m_ui->wallpaperCollectionDel, &QPushButton::pressed, this, &UKUIThemeCustomizer::onWallpaperCollectionDeletePressed);

    m_ui->soundView->setModel(&soundModel);
    connect(m_ui->soundAdd, &QPushButton::pressed, this, &UKUIThemeCustomizer::onSoundAddPressed);
    connect(m_ui->soundDel, &QPushButton::pressed, this, &UKUIThemeCustomizer::onSoundDeletePressed);
}

UKUIThemeCustomizer::~UKUIThemeCustomizer() {}

void UKUIThemeCustomizer::updateLogBox(QString s)
{
    m_ui->logbox->setText(s);
}

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

void UKUIThemeCustomizer::onIconDeletePressed()
{
    iconModel.deleteItem(m_ui->iconView->selectionModel()->selectedIndexes());
}

void UKUIThemeCustomizer::onCursorAddPressed()
{
    auto cursorConfigFile = QFileDialog::getOpenFileName(this, tr("打开Theme文件"), "./", tr("Theme文件 (*.theme)"));
    if (cursorConfigFile == "") return;
    if (!creatorMutex.try_lock()) {
        logger::getStandardLogger().log("请等待当前任务完成");
        return;
    }
    creator = new cursorPackageCreator(cursorConfigFile);
    connect(creator, &packageCreator::packageSuccess, [&](const QFileInfo & info) {
        cursorModel.addItem(info.baseName(), info.absolutePath());
        creatorMutex.unlock();
    });
    creator->exec();
}

void UKUIThemeCustomizer::onCursorDeletePressed()
{
    cursorModel.deleteItem(m_ui->cursorView->selectionModel()->selectedIndexes());
}

void UKUIThemeCustomizer::onWallpaperCollectionAddPressed()
{
    auto wallpaperCollectionList = QFileDialog::getOpenFileNames(this, tr("打开图片文件"), "./", tr("图片文件 (*.png *.jpg)"));
    if (wallpaperCollectionList.empty()) return;
    if (!creatorMutex.try_lock()) {
        logger::getStandardLogger().log("请等待当前任务完成");
        return;
    }
    creator = new wallpaperCollectionPackageCreator(wallpaperCollectionList);
    connect(creator, &packageCreator::packageSuccess, [&](const QFileInfo & info) {
        wallpaperCollectionModel.addItem(info.baseName(), info.absolutePath());
        creatorMutex.unlock();
    });
    creator->exec();
}

void UKUIThemeCustomizer::onWallpaperCollectionDeletePressed()
{
    wallpaperCollectionModel.deleteItem(m_ui->wallpaperCollectionView->selectionModel()->selectedIndexes());
}

void UKUIThemeCustomizer::onSoundAddPressed()
{
    auto soundCollectionConfigFile = QFileDialog::getOpenFileName(this, tr("打开Theme文件"), "./", tr("Theme文件 (*.theme)"));
    if (soundCollectionConfigFile == "") return;
    if (!creatorMutex.try_lock()) {
        logger::getStandardLogger().log("请等待当前任务完成");
        return;
    }
    creator = new soundPackageCreator(soundCollectionConfigFile);
    connect(creator, &packageCreator::packageSuccess, [&](const QFileInfo & info) {
        soundModel.addItem(info.baseName(), info.absolutePath());
        creatorMutex.unlock();
    });
    creator->exec();
}

void UKUIThemeCustomizer::onSoundDeletePressed()
{
    soundModel.deleteItem(m_ui->soundView->selectionModel()->selectedIndexes());
}

// kate: indent-mode cstyle; indent-width 1; replace-tabs on; ;
