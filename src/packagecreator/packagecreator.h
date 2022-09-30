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
    void packageDone();

public:

    enum class packageState {
        Success,
        Failed,
        NotStart
    };

    packageCreator();
    ~packageCreator();
    packageState getState();
    QFileInfo &getFileInfo();

protected:
    QProcess packageProcess;
    QString name, maintainer, version, description;
    QDir workDir;
    virtual bool parseConfig() = 0;
    virtual bool setWorkDir() = 0;
    void handleConfigFile(const QString &source, const QString &dest);
    void copy(const QString &source, const QString &dest);
    virtual void package();

private:
    QScopedPointer<Ui::packageCreator> m_ui;
    packageState state;
    QFileInfo info;

protected slots:
    void onAccepted();
    void onCanceled();
};

class iconPackageCreator : public packageCreator
{
public:
    iconPackageCreator(const QString &configFilePath);
    bool parseConfig() override;
    bool setWorkDir() override;

private:
    QString configFilePath;
};

class cursorPackageCreator : public packageCreator
{
public:
    cursorPackageCreator(const QString &configFilePath);
    bool parseConfig() override;
    bool setWorkDir() override;

private:
    QString configFilePath;
};

class wallpaperCollectionPackageCreator : public packageCreator
{
public:
    wallpaperCollectionPackageCreator(const QStringList &imagePath);
    bool parseConfig() override;
    bool setWorkDir() override;

private:
    QStringList imagePath;
};

class soundPackageCreator : public packageCreator
{
public:
    soundPackageCreator(const QString &configFilePath);
    bool parseConfig() override;
    bool setWorkDir() override;

private:
    QString configFilePath;
};

class globalThemePackageCreator : public packageCreator
{
public:
    globalThemePackageCreator(const QStringList &depends);
    bool parseConfig() override;
    bool setWorkDir() override;

private:
    QStringList depends;
};

#endif // PACKAGECREATOR_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; ;
