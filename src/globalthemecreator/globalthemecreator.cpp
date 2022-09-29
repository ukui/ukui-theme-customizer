#include "globalthemecreator.h"
#include "ui_globalthemecreator.h"
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; ;

globalThemeCreator::globalThemeCreator(UKUIThemeModel *wallpaperCollectionModel,
                                       UKUIThemeModel *iconModel,
                                       UKUIThemeModel *cursorModel,
                                       UKUIThemeModel *soundModel,
                                       UKUIThemeModel *gtkStyleModel,
                                       UKUIThemeModel *qtStyleModel)
    : m_ui(new Ui::globalThemeCreator)
{
    m_ui->setupUi(this);
    m_ui->wallpaperCollection->setModel(wallpaperCollectionModel);
    m_ui->iconName->setModel(iconModel);
    m_ui->cursorName->setModel(cursorModel);
    m_ui->soundName->setModel(soundModel);
    m_ui->gtkStyle1->setModel(gtkStyleModel);
    m_ui->gtkStyle2->setModel(gtkStyleModel);
    m_ui->qtStyle1->setModel(qtStyleModel);
    m_ui->qtStyle2->setModel(qtStyleModel);

    connect(this, &globalThemeCreator::accepted, this, &globalThemeCreator::onAccepted);
    connect(m_ui->gtk2Enabled, &QCheckBox::stateChanged, m_ui->gtkStyle2, &QComboBox::setEnabled);
    connect(m_ui->qt2Enabled, &QCheckBox::stateChanged, m_ui->qtStyle2, &QComboBox::setEnabled);
}

globalThemeCreator::~globalThemeCreator() noexcept {}

void globalThemeCreator::onAccepted()
{
    QStringList depends;
    if (m_ui->wallpaperCollection->currentIndex() == -1) {
        logger::getStandardLogger().log("wallpaper未设置");
        return;
    }
    depends << m_ui->wallpaperCollection->model()->index(m_ui->wallpaperCollection->currentIndex(), 0).data().toString();

    if (m_ui->iconName->currentIndex() == -1) {
        logger::getStandardLogger().log("icon未设置");
        return;
    }
    depends << m_ui->iconName->model()->index(m_ui->iconName->currentIndex(), 0).data().toString();

    if (m_ui->cursorName->currentIndex() == -1) {
        logger::getStandardLogger().log("cursor未设置");
        return;
    }
    depends << m_ui->cursorName->model()->index(m_ui->cursorName->currentIndex(), 0).data().toString();

    if (m_ui->soundName->currentIndex() == -1) {
        logger::getStandardLogger().log("sound未设置");
        return;
    }
    depends << m_ui->soundName->model()->index(m_ui->soundName->currentIndex(), 0).data().toString();

    if (m_ui->gtkStyle1->currentIndex() == -1) {
        logger::getStandardLogger().log("gtk主题未设置");
        return;
    }
    auto gtkName = m_ui->gtkStyle1->model()->index(m_ui->gtkStyle1->currentIndex(), 0).data().toString();
    if (m_ui->gtk2Enabled->isChecked()) {
        if (m_ui->gtkStyle2->currentIndex() == -1) {
            logger::getStandardLogger().log("gtk主题2勾选但未设置");
            return;
        }
        auto gtkName2 = m_ui->gtkStyle1->model()->index(m_ui->gtkStyle1->currentIndex(), 0).data().toString();
        if (gtkName2 == gtkName) {
            logger::getStandardLogger().log("gtk主题重复");
            return;
        }
        depends << gtkName2;
    }
    depends << gtkName;

    if (m_ui->qtStyle1->currentIndex() == -1) {
        logger::getStandardLogger().log("qt主题未设置");
        return;
    }
    auto qtName = m_ui->qtStyle1->model()->index(m_ui->qtStyle1->currentIndex(), 0).data().toString();
    if (m_ui->qt2Enabled->isChecked()) {
        if (m_ui->qtStyle2->currentIndex() == -1) {
            logger::getStandardLogger().log("qt主题2勾选但未设置");
            return;
        }
        auto qtName2 = m_ui->qtStyle1->model()->index(m_ui->qtStyle1->currentIndex(), 0).data().toString();
        if (qtName2 == qtName) {
            logger::getStandardLogger().log("qt主题重复");
            return;
        }
        depends << qtName2;
    }
    depends << qtName;
}
