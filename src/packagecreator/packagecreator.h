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

class packageCreator : public QDialog
{
    Q_OBJECT

signals:
    void packageSuccess(const QFileInfo & info);

public:
    packageCreator();
    ~packageCreator();

protected:
    QProcess packageProcess;
    QString name, maintainer, version, description;
    QDir workDir;
    virtual void parseConfig() = 0;
    virtual void package() = 0;
    virtual bool setWorkDir() = 0;
    void handleConfigFile(const QString & source, const QString & dest);
    void copy(const QString & source, const QString & dest);

private:
    QScopedPointer<Ui::packageCreator> m_ui;

protected slots:
    void onAccepted();
};

class iconPackageCreator : public packageCreator {
public:
    iconPackageCreator(const QString & configFilePath);
    void parseConfig() override;
    void package() override;
    bool setWorkDir() override;
private:
    QString configFilePath;
};

#endif // PACKAGECREATOR_H
