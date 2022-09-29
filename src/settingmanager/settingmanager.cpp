#include "settingmanager.h"

static logger standardLog;
static settingManager settings;

void logger::log(QString s)
{
    if (s != m_msg) {
        m_msg = s;
        emit msgChanged(m_msg);
    }
}

logger::logger::logger() {}

logger &logger::getStandardLogger()
{
    return standardLog;
}

settingManager &settingManager::getSettings()
{
    return settings;
}

settingManager::settingManager()
{
    QPointer<QSettings> settingsFromFile;
    if (QFile::exists("/etc/ukui-theme-customizer/config.ini")) {
        settingsFromFile = new QSettings("/etc/ukui-theme-customizer/config.ini",
                                         QSettings::IniFormat);
    } else {
        settingsFromFile = new QSettings("config.ini", QSettings::IniFormat);
    }
    auto filePath = settingsFromFile->value("workDirectory", "./").toString();
    if (!QFileInfo(filePath).isDir()) {
        QFile::remove(filePath);
    }
    if (!QFile::exists(filePath)) {
        QDir().mkdir(filePath);
    }
    settings.totalWorkDir.setPath(filePath);

    for (auto subDir : {
                "icons", "cursors", "globalThemes", "wallpaperCollections", "gtkStyles",
                "qtStyles", "sounds"
            }) {
        if (!QFileInfo(settings.totalWorkDir.filePath(subDir)).isDir()) {
            QFile::remove(settings.totalWorkDir.filePath(subDir));
        }
        if (!settings.totalWorkDir.exists(subDir))
            settings.totalWorkDir.mkdir(subDir);
    }
}

QDir settingManager::iconDir()
{
    return QDir(totalWorkDir.filePath("icons"));
}

QDir settingManager::cursorDir()
{
    return QDir(totalWorkDir.filePath("cursors"));
}

QDir settingManager::globalThemeDir()
{
    return QDir(totalWorkDir.filePath("globalThemes"));
}

QDir settingManager::wallpaperCollectionDir()
{
    return QDir(totalWorkDir.filePath("wallpaperCollections"));
}

QDir settingManager::gtkStyleDir()
{
    return QDir(totalWorkDir.filePath("gtkStyles"));
}

QDir settingManager::qtStyleDir()
{
    return QDir(totalWorkDir.filePath("qtStyles"));
}

QDir settingManager::soundDir()
{
    return QDir(totalWorkDir.filePath("sounds"));
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; ;
