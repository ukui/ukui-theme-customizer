#ifndef PACKAGECREATOR_H
#define PACKAGECREATOR_H

#include <QDialog>
#include <QScopedPointer>
#include <QDir>
#include <QFile>
#include <QSettings>
#include <QTextStream>
#include <QDebug>
#include <QProcess>

namespace Ui
{
class packageCreator;
}

static auto totalWorkDir = QDir::current();

static void log(const QString & s) {
    qDebug() << s;
}

class themePackage {
protected:
    const QString name, maintainer, version, description, configFilePath;
    QDir workDir;
    void handleConfigFile(QString source, QString dest);
public:
    themePackage(const QString & name, const QString & maintainer, const QString & version,
    const QString & description, const QString & configFilePath);
    virtual void ParseConfig() = 0;
    virtual void package() = 0;
};

class iconThemePackage : public themePackage {
public:
    void ParseConfig();
    void package();
};

class packageCreator : public QDialog
{
    Q_OBJECT

    enum class themeType {
        iconTheme,
        cursorTheme
    };

public:
    packageCreator();
    ~packageCreator();

private:
    void onAccepted() {
    }
    QScopedPointer<Ui::packageCreator> m_ui;
    QScopedPointer<themePackage> m_theme;
};

#endif // PACKAGECREATOR_H
