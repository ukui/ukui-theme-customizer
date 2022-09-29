#ifndef PACKAGECREATOR_H
#define PACKAGECREATOR_H

#include <QDebug>
#include <QDialog>
#include <QDir>
#include <QFile>
#include <QProcess>
#include <QScopedPointer>
#include <QSettings>
#include <QTextStream>

namespace Ui
{
class packageCreator;
}

class packageCreator : public QDialog
{
    Q_OBJECT

signals:
    void packageSuccess(const QFileInfo &info);

public:
    packageCreator();
    ~packageCreator();

protected:
    QProcess packageProcess;
    QString name, maintainer, version, description;
    QDir workDir;
    virtual void parseConfig() = 0;
    virtual bool setWorkDir() = 0;
    void handleConfigFile(const QString &source, const QString &dest);
    void copy(const QString &source, const QString &dest);
    virtual void package();

private:
    QScopedPointer<Ui::packageCreator> m_ui;

protected slots:
    void onAccepted();
};

class iconPackageCreator : public packageCreator
{
public:
    iconPackageCreator(const QString &configFilePath);
    void parseConfig() override;
    bool setWorkDir() override;

private:
    QString configFilePath;
};

class cursorPackageCreator : public packageCreator
{
public:
    cursorPackageCreator(const QString &configFilePath);
    void parseConfig() override;
    bool setWorkDir() override;

private:
    QString configFilePath;
};

class wallpaperCollectionPackageCreator : public packageCreator
{
public:
    wallpaperCollectionPackageCreator(const QStringList &imagePath);
    void parseConfig() override;
    bool setWorkDir() override;

private:
    QStringList imagePath;
};

class soundPackageCreator : public packageCreator
{
public:
    soundPackageCreator(const QString &configFilePath);
    void parseConfig() override;
    bool setWorkDir() override;

private:
    QString configFilePath;
};

#endif // PACKAGECREATOR_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; ;
