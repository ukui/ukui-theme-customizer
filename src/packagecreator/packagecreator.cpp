#include "packagecreator.h"
#include "ui_packagecreator.h"
#include "../settingmanager/settingmanager.h"
#include "../ukuithemeelement/ukuithemeelement.h"

packageCreator::packageCreator(QWidget *parent)
    : QDialog(parent), m_ui(new Ui::packageCreator)
{
    m_ui->setupUi(this);
    connect(this, &packageCreator::accepted, this, &packageCreator::onAccepted);
}

packageCreator::~packageCreator() {}

void iconPackageCreator::parseConfig() {
    workDir.mkpath("usr/share/icons");
    QDir iconDir(workDir.filePath("usr/share/icons"));
    copy(configFilePath, iconDir.filePath("index.theme"));

    QSettings iconConfig(configFilePath, QSettings::Format::IniFormat);
    iconConfig.beginGroup("Icon Theme");
    if (!iconConfig.contains("Name") || !iconConfig.contains("Directories")) {
        logger::getStandardLogger().log("不合法的icon文件");
        return;
    }

    QFileInfo info(configFilePath);
    auto baseDir = info.dir();

    auto dirList = iconConfig.value("Directories").toStringList();
    for (auto dir = std::begin(dirList); dir != std::end(dirList); ++dir) {
        if (*dir != "" && baseDir.exists(*dir)) {
            copy(baseDir.filePath(*dir), iconDir.filePath(*dir));
        }
    }
    workDir.mkdir("DEBIAN");
    QDir controlPath(workDir.filePath("DEBIAN"));

    handleConfigFile(":/templates/icon/postinst", controlPath.filePath("postinst"));
    handleConfigFile(":/templates/icon/postrm", controlPath.filePath("postrm"));
    handleConfigFile(":/templates/control", controlPath.filePath("control"));
}

void packageCreator::handleConfigFile(const QString & source, const QString & dest) {
    QFile postInitSource(source),
          postInitDest(dest);

    if (!postInitSource.open(QIODevice::ReadOnly) || !postInitDest.open(QIODevice::WriteOnly))
        return;

    while (!postInitSource.atEnd()) {
        postInitDest.write(QString(postInitSource.readAll())
                .replace("$NAME", name)
                .replace("$MAINTAINER", maintainer)
                .replace("$VERSION", version)
                .replace("$DESCRIPTION", description)
                .toLocal8Bit()
            );
    }
    postInitDest.setPermissions(
        QFileDevice::ReadOwner |
        QFileDevice::ExeOwner |
        QFileDevice::ReadGroup |
        QFileDevice::ExeGroup |
        QFileDevice::ReadOther |
        QFileDevice::ExeOther
    );
    postInitSource.close();
    postInitDest.close();
}

iconPackageCreator::iconPackageCreator(const QString& configFilePath, QWidget *parent)
        : packageCreator(parent), configFilePath(configFilePath){}

void packageCreator::onAccepted() {
    name = m_ui->name->text();
    version = m_ui->version->text();
    maintainer = m_ui->maintainer->text();
    description = m_ui->description->toPlainText();
    this->setWorkDir();
    workDir.mkdir ( "DEBIAN" );
    this->parseConfig();
    this->package();
}

void iconPackageCreator::package() {
    QProcess packageProcess;
    packageProcess.setWorkingDirectory(workDir.filePath(".."));
    packageProcess.start("dpkg-deb", QStringList()<<"-b"<<name);
    packageProcess.waitForFinished();
    if (QDir(workDir.filePath("..")).exists(name + ".deb")) {
        logger::getStandardLogger().log("打包成功");
        emit packageSuccess(QFileInfo(QDir(workDir.filePath("..")).absoluteFilePath(name + ".deb")));
    } else {
        logger::getStandardLogger().log("打包出现错误");
    }
}


void packageCreator::copy(const QString& source, const QString& dest) {
    if (QFile::exists(dest)) {
        QFile::remove(dest);
    }
    logger::getStandardLogger().log(source + "->" + dest);
    QFileInfo sourceInfo(source);
    if (sourceInfo.isDir()) {
        QDir sourceDir(source), destDir(dest);
        QDir().mkpath(dest);
        auto sourceEntryList = sourceDir.entryInfoList();
        for (auto i = std::begin(sourceEntryList); i != std::end(sourceEntryList); ++i) {
            if (i->fileName() == "." || i->fileName() == "..") continue;
            copy(i->filePath(), destDir.filePath(i->fileName()));
        }
    } else {
        QFile::copy(source, dest);
    }
}

void iconPackageCreator::setWorkDir()
{
    auto iconDir = settingManager::getSettings().iconDir();
    if ( iconDir.exists ( name ) ) {
        iconDir.remove ( name );
    }
    iconDir.mkdir ( name );
    workDir.setPath ( iconDir.filePath ( name ) );
}


