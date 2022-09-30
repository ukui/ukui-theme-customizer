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
    auto absoluteFilePath = settingsFromFile->value("workDirectory", "./").toString();
    if (!QFileInfo(absoluteFilePath).isDir()) {
        QFile::remove(absoluteFilePath);
    }
    if (!QFile::exists(absoluteFilePath)) {
        QDir().mkdir(absoluteFilePath);
    }
    settings.totalWorkDir.setPath(absoluteFilePath);

    for (auto subDir : {
                "icons", "cursors", "globalThemes", "wallpaperCollections", "gtkStyles",
                "qtStyles", "sounds"
            }) {
        if (!QFileInfo(settings.totalWorkDir.absoluteFilePath(subDir)).isDir()) {
            QFile::remove(settings.totalWorkDir.absoluteFilePath(subDir));
        }
        if (!settings.totalWorkDir.exists(subDir))
            settings.totalWorkDir.mkdir(subDir);
    }
}

QDir settingManager::iconDir()
{
    return QDir(totalWorkDir.absoluteFilePath("icons"));
}

QDir settingManager::cursorDir()
{
    return QDir(totalWorkDir.absoluteFilePath("cursors"));
}

QDir settingManager::globalThemeDir()
{
    return QDir(totalWorkDir.absoluteFilePath("globalThemes"));
}

QDir settingManager::wallpaperCollectionDir()
{
    return QDir(totalWorkDir.absoluteFilePath("wallpaperCollections"));
}

QDir settingManager::gtkStyleDir()
{
    return QDir(totalWorkDir.absoluteFilePath("gtkStyles"));
}

QDir settingManager::qtStyleDir()
{
    return QDir(totalWorkDir.absoluteFilePath("qtStyles"));
}

QDir settingManager::soundDir()
{
    return QDir(totalWorkDir.absoluteFilePath("sounds"));
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; ;
