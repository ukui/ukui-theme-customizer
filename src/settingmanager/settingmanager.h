#ifndef LOGGER_H
#define LOGGER_H

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QObject>
#include <QPointer>
#include <QSettings>

class logger : public QObject
{
    Q_OBJECT
signals:
    void msgChanged(const QString &s);

public:
    static logger &getStandardLogger();
    logger();
    void log(QString s);

private:
    QString m_msg;
};

class settingManager
{
public:
    settingManager();
    static settingManager &getSettings();
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
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; ;
