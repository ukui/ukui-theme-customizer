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

template <typename T>
static void log(const T & s) {
    qDebug() << s;
}

class packageCreator : public QDialog
{
    Q_OBJECT

public:
    packageCreator(QWidget *parent = nullptr);
    ~packageCreator();

protected:
    QString name, maintainer, version, description;
    QDir workDir;
    virtual void parseConfig() = 0;
    virtual void package() = 0;
    void handleConfigFile(const QString & source, const QString & dest);
    void copy(const QString & source, const QString & dest);

private:
    QScopedPointer<Ui::packageCreator> m_ui;

protected slots:
    void onAccepted();
};

class iconPackageCreator : public packageCreator {
public:
    iconPackageCreator(const QString & configFilePath, QWidget *parent);
    void parseConfig();
    void package();
private:
    QString configFilePath;
};

#endif // PACKAGECREATOR_H
