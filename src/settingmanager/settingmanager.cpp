#include "settingmanager.h"

static logger standardLog;
static settingManager settings;

void logger::log(QString s) {
    if (s != m_msg) {
        m_msg = s;
        emit msgChanged(m_msg);
    }
}

logger::logger::logger() {}

logger& logger::getStandardLogger() {
    return standardLog;
}

settingManager & settingManager::getSettings()
{
    return settings;
}

settingManager::settingManager()
{
    QPointer <QSettings> settingsFromFile;
    if (QFile::exists("config.ini")) {
        settingsFromFile = new QSettings("config.ini", QSettings::IniFormat);
    } else if (QFile::exists("/etc/ukui-theme-customizer/config.ini")){
        settingsFromFile = new QSettings("/etc/ukui-theme-customizer/config.ini", QSettings::IniFormat);
    } else {
        throw("未读取到配置");
    }
    auto filePath = settingsFromFile->value("workDirectory", "./").toString();
    if (!QFileInfo(filePath).isDir()) {
        throw("非法工作目录");
    }
    settings.totalWorkDir.setPath(filePath);
    if (!QFileInfo(settings.totalWorkDir.filePath("icons")).isDir()) {
        throw("非法工作目录: icons");
    }
}

QDir settingManager::iconDir() {
    return QDir(totalWorkDir.filePath("icons"));
}


QDir settingManager::cursorDir() {
    return QDir(totalWorkDir.filePath("cursors"));
}

