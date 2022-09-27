#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QFile>
#include <QSettings>
#include <QPointer>
#include <QDir>
#include <QFileInfo>

class logger: public QObject
{
        Q_OBJECT
signals:
    void msgChanged(const QString & s);

public:
    static logger & getStandardLogger();
    logger();
    void log(QString s);

private:
    QString m_msg;
};

class settingManager {
public:
    settingManager();
    static settingManager & getSettings();
    QDir totalWorkDir;
    QDir iconDir();
    QDir cursorDir();
    QDir wallpaperCollectionDir();
    QDir soundDir();
    QDir qtStyleDir();
    QDir gtkStyleDir();
    QDir globalThemeDir();
};

#endif // LOGGER_H
// kate: indent-mode cstyle; indent-width 1; replace-tabs on; ;
