#include "packagecreator.h"
#include "ui_packagecreator.h"
#include "../settingmanager/settingmanager.h"
#include "../ukuithemeelement/ukuithemeelement.h"

packageCreator::packageCreator()
    : m_ui(new Ui::packageCreator)
{
    m_ui->setupUi(this);
    connect(this, &packageCreator::accepted, this, &packageCreator::onAccepted);
}

packageCreator::~packageCreator() {}

void packageCreator::handleConfigFile(const QString &source, const QString &dest)
{
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

void packageCreator::onAccepted()
{
    name = m_ui->name->text();
    version = m_ui->version->text();
    maintainer = m_ui->maintainer->text();
    description = m_ui->description->toPlainText();
    if (!setWorkDir()) {
        logger::getStandardLogger().log("已存在同名包");
        return;
    }
    workDir.mkdir("DEBIAN");
    parseConfig();
    package();
}

void packageCreator::copy(const QString &source, const QString &dest)
{
    if (QFile::exists(dest)) {
        QFile::remove(dest);
    }
    logger::getStandardLogger().log("复制" + source + "->" + dest);
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

void packageCreator::package()
{
    packageProcess.setWorkingDirectory(workDir.filePath(".."));
    packageProcess.start("dpkg-deb", QStringList() << "-b" << name);
    logger::getStandardLogger().log("正在执行dpkg-deb");
    connect(&packageProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
    [ = ](int exitCode Q_DECL_UNUSED, QProcess::ExitStatus exitStatus Q_DECL_UNUSED) {
        if (QDir(workDir.filePath("..")).exists(name + ".deb")) {
            logger::getStandardLogger().log("打包成功");
            emit packageSuccess(QFileInfo(QDir(workDir.filePath("..")).absoluteFilePath(name + ".deb")));
            workDir.removeRecursively();
        } else {
            logger::getStandardLogger().log("打包出现错误");
        }
    });
}

iconPackageCreator::iconPackageCreator(const QString &configFilePath)
    : configFilePath(configFilePath) {}

bool iconPackageCreator::setWorkDir()
{
    auto iconDir = settingManager::getSettings().iconDir();
    if (iconDir.exists(name + ".deb"))
        return false;
    if (iconDir.exists(name)) {
        iconDir.remove(name);
    }
    iconDir.mkdir(name);
    workDir.setPath(iconDir.filePath(name));
    return true;
}

void iconPackageCreator::parseConfig()
{
    workDir.mkpath("usr/share/icons/" + name);
    QDir iconDir(workDir.filePath("usr/share/icons/" + name));
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

cursorPackageCreator::cursorPackageCreator(const QString &configFilePath)
    : configFilePath(configFilePath) {}

bool cursorPackageCreator::setWorkDir()
{
    auto cursorDir = settingManager::getSettings().cursorDir();
    if (cursorDir.exists(name + ".deb"))
        return false;
    if (cursorDir.exists(name)) {
        cursorDir.remove(name);
    }
    cursorDir.mkdir(name);
    workDir.setPath(cursorDir.filePath(name));
    return true;
}

void cursorPackageCreator::parseConfig()
{
    workDir.mkpath("usr/share/icons/" + name);
    QDir cursorDir(workDir.filePath("usr/share/icons/" + name));
    copy(configFilePath, cursorDir.filePath("cursor.theme"));
    cursorDir.mkpath("../default");

    QFileInfo info(configFilePath);
    auto baseDir = info.dir();

    copy(baseDir.filePath("cursors"), cursorDir.filePath("cursors"));

    workDir.mkdir("DEBIAN");
    QDir controlPath(workDir.filePath("DEBIAN"));

    handleConfigFile(":/templates/cursor/postinst", controlPath.filePath("postinst"));
    handleConfigFile(":/templates/cursor/prerm", controlPath.filePath("postrm"));
    handleConfigFile(":/templates/control", controlPath.filePath("control"));
}

wallpaperCollectionPackageCreator::wallpaperCollectionPackageCreator(const QStringList& imagePath) : imagePath(imagePath){}

bool wallpaperCollectionPackageCreator::setWorkDir()
{
    auto wallpaperCollectionDir = settingManager::getSettings().wallpaperCollectionDir();
    if (wallpaperCollectionDir.exists(name + ".deb"))
        return false;
    if (wallpaperCollectionDir.exists(name)) {
        wallpaperCollectionDir.remove(name);
    }
    wallpaperCollectionDir.mkdir(name);
    workDir.setPath(wallpaperCollectionDir.filePath(name));
    return true;
}

void wallpaperCollectionPackageCreator::parseConfig()
{
    workDir.mkpath("usr/share/backgrounds/");

    for (auto picture : imagePath) {
        QFile::copy(picture, workDir.filePath("usr/share/backgrounds/" + QFileInfo(picture).fileName()));
    }

    workDir.mkdir("DEBIAN");
    QDir controlPath(workDir.filePath("DEBIAN"));

    handleConfigFile(":/templates/control", controlPath.filePath("control"));
}


soundPackageCreator::soundPackageCreator(const QString &configFilePath)
    : configFilePath(configFilePath) {}

bool soundPackageCreator::setWorkDir()
{
    auto soundDir = settingManager::getSettings().soundDir();
    if (soundDir.exists(name + ".deb"))
        return false;
    if (soundDir.exists(name)) {
        soundDir.remove(name);
    }
    soundDir.mkdir(name);
    workDir.setPath(soundDir.filePath(name));
    return true;
}

void soundPackageCreator::parseConfig()
{
    workDir.mkpath("usr/share/sounds/" + name);
    QDir soundDir(workDir.filePath("usr/share/sounds/" + name));
    copy(configFilePath, soundDir.filePath("index.theme"));

    QSettings soundConfig(configFilePath, QSettings::Format::IniFormat);
    soundConfig.beginGroup("Sound Theme");
    if (!soundConfig.contains("Name") || !soundConfig.contains("Directories")) {
        logger::getStandardLogger().log("不合法的sound文件");
        return;
    }

    QFileInfo info(configFilePath);
    auto baseDir = info.dir();

    auto dirList = soundConfig.value("Directories").toStringList();
    for (auto dir = std::begin(dirList); dir != std::end(dirList); ++dir) {
        if (*dir != "" && baseDir.exists(*dir)) {
            copy(baseDir.filePath(*dir), soundDir.filePath(*dir));
        }
    }
    workDir.mkdir("DEBIAN");
    QDir controlPath(workDir.filePath("DEBIAN"));

    handleConfigFile(":/templates/control", controlPath.filePath("control"));
}

// kate: indent-mode cstyle; indent-width 1; replace-tabs on; ;
