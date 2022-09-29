#include "globalthemecreator.h"
#include "ui_globalthemecreator.h"
// kate: indent-mode cstyle; indent-width 1; replace-tabs on; ;

globalThemeCreator::globalThemeCreator(UKUIThemeModel * wallpaperCollectionModel,
                       UKUIThemeModel * iconModel,
                       UKUIThemeModel * cursorModel,
                       UKUIThemeModel * soundModel,
                       UKUIThemeModel * gtkStyleModel,
                       UKUIThemeModel * qtStyleModel)
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
}

globalThemeCreator::~globalThemeCreator() noexcept {}

