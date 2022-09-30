#include "packagecreator.h"
#include "../settingmanager/settingmanager.h"
#include "../ukuithemeelement/ukuithemeelement.h"
#include "ui_packagecreator.h"

packageCreator::packageCreator() : m_ui(new Ui::packageCreator), state(packageState::NotStart)
{
    m_ui->setupUi(this);
    connect(this, &packageCreator::accepted, this, &packageCreator::onAccepted);
    connect(this, &packageCreator::rejected, this, &packageCreator::onCanceled);
}

packageCreator::~packageCreator() {}

void packageCreator::handleConfigFile(const QString &source,
                                      const QString &dest)
{
    QFile postInitSource(source), postInitDest(dest);

    if (!postInitSource.open(QIODevice::ReadOnly) ||
            !postInitDest.open(QIODevice::WriteOnly))
        return;

    while (!postInitSource.atEnd()) {
        postInitDest.write(QString(postInitSource.readAll())
                           .replace("$NAME", name)
                           .replace("$MAINTAINER", maintainer)
                           .replace("$VERSION", version)
                           .replace("$DESCRIPTION", description)
                           .toLocal8Bit());
    }
    postInitDest.setPermissions(QFileDevice::ReadOwner | QFileDevice::ExeOwner |
                                QFileDevice::ReadGroup | QFileDevice::ExeGroup |
                                QFileDevice::ReadOther | QFileDevice::ExeOther);
    postInitSource.close();
    postInitDest.close();
}

void packageCreator::onAccepted()
{
    name = m_ui->name->text();
    if (name == "") {
        logger::getStandardLogger().log("名称不能为空");
        emit packageDone();
        return;
    }
    version = m_ui->version->text();
    if (version == "") {
        logger::getStandardLogger().log("版本号不能为空");
        emit packageDone();
        return;
    }
    maintainer = m_ui->maintainer->text();
    if (maintainer == "") {
        logger::getStandardLogger().log("维护者不能为空");
        emit packageDone();
        return;
    }
    description = m_ui->description->toPlainText();
    if (description == "") {
        logger::getStandardLogger().log("描述不能为空");
        emit packageDone();
        return;
    }
    if (!setWorkDir()) {
        logger::getStandardLogger().log("已存在同名包");
        emit packageDone();
        return;
    }
    workDir.mkdir("DEBIAN");
    if (!parseConfig()) {
        emit packageDone();
        return;
    }
    package();
    emit packageDone();
}

void packageCreator::onCanceled()
{
    emit packageDone();
}

packageCreator::packageState packageCreator::getState()
{
    return state;
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
        for (auto i = std::begin(sourceEntryList); i != std::end(sourceEntryList);
                ++i) {
            if (i->fileName() == "." || i->fileName() == "..")
                continue;
            copy(i->absoluteFilePath(), destDir.absoluteFilePath(i->fileName()));
        }
    } else {
        QFile::copy(source, dest);
    }
}

void packageCreator::package()
{
    packageProcess.setWorkingDirectory(workDir.absoluteFilePath(".."));
    packageProcess.start("dpkg-deb", QStringList() << "-b" << name);
    logger::getStandardLogger().log("正在执行dpkg-deb");
    connect(
        &packageProcess,
        QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
        [ = ](int exitCode Q_DECL_UNUSED,
    QProcess::ExitStatus exitStatus Q_DECL_UNUSED) {
        if (QDir(workDir.absoluteFilePath("..")).exists(name + ".deb")) {
            logger::getStandardLogger().log("打包成功");
            workDir.removeRecursively();
            state = packageState::Success;
            info = QFileInfo(workDir.absoluteFilePath("../" + name + ".deb"));
        } else {
            state = packageState::Failed;
            logger::getStandardLogger().log("错误：" + QString(packageProcess.readAllStandardError()));
        }
        emit packageDone();
    });
}

QFileInfo &packageCreator::getFileInfo()
{
    return info;
}


iconPackageCreator::iconPackageCreator(const QString &configFilePath)
    : configFilePath(configFilePath) {}

bool iconPackageCreator::setWorkDir()
{
    auto iconDir = settingManager::getSettings().iconDir();
    if (iconDir.exists(name + ".deb"))
        return false;
    if (iconDir.exists(name)) {
        QDir(iconDir.absoluteFilePath(name)).removeRecursively();
    }
    iconDir.mkdir(name);
    workDir.setPath(iconDir.absoluteFilePath(name));
    return true;
}

bool iconPackageCreator::parseConfig()
{
    workDir.mkpath("usr/share/icons/" + name);
    QDir iconDir(workDir.absoluteFilePath("usr/share/icons/" + name));
    copy(configFilePath, iconDir.absoluteFilePath("index.theme"));

    QSettings iconConfig(configFilePath, QSettings::Format::IniFormat);
    iconConfig.beginGroup("Icon Theme");
    if (!iconConfig.contains("Name") || !iconConfig.contains("Directories")) {
        logger::getStandardLogger().log("不合法的icon文件");
        return false;
    }

    QFileInfo info(configFilePath);
    auto baseDir = info.dir();

    auto dirList = iconConfig.value("Directories").toStringList();
    for (auto dir = std::begin(dirList); dir != std::end(dirList); ++dir) {
        if (*dir != "" && baseDir.exists(*dir)) {
            copy(baseDir.absoluteFilePath(*dir), iconDir.absoluteFilePath(*dir));
        }
    }
    workDir.mkdir("DEBIAN");
    QDir controlPath(workDir.absoluteFilePath("DEBIAN"));

    handleConfigFile(":/templates/icon/postinst",
                     controlPath.absoluteFilePath("postinst"));
    handleConfigFile(":/templates/icon/postrm", controlPath.absoluteFilePath("postrm"));
    handleConfigFile(":/templates/control", controlPath.absoluteFilePath("control"));
    return true;
}

cursorPackageCreator::cursorPackageCreator(const QString &configFilePath)
    : configFilePath(configFilePath) {}

bool cursorPackageCreator::setWorkDir()
{
    auto cursorDir = settingManager::getSettings().cursorDir();
    if (cursorDir.exists(name + ".deb"))
        return false;
    if (cursorDir.exists(name)) {
        QDir(cursorDir.absoluteFilePath(name)).removeRecursively();
    }
    cursorDir.mkdir(name);
    workDir.setPath(cursorDir.absoluteFilePath(name));
    return true;
}

bool cursorPackageCreator::parseConfig()
{
    workDir.mkpath("usr/share/icons/" + name);
    QDir cursorDir(workDir.absoluteFilePath("usr/share/icons/" + name));
    copy(configFilePath, cursorDir.absoluteFilePath("cursor.theme"));
    cursorDir.mkpath("../default");

    QFileInfo info(configFilePath);
    auto baseDir = info.dir();

    copy(baseDir.absoluteFilePath("cursors"), cursorDir.absoluteFilePath("cursors"));

    workDir.mkdir("DEBIAN");
    QDir controlPath(workDir.absoluteFilePath("DEBIAN"));

    handleConfigFile(":/templates/cursor/postinst",
                     controlPath.absoluteFilePath("postinst"));
    handleConfigFile(":/templates/cursor/prerm", controlPath.absoluteFilePath("postrm"));
    handleConfigFile(":/templates/control", controlPath.absoluteFilePath("control"));
    return true;
}

wallpaperCollectionPackageCreator::wallpaperCollectionPackageCreator(
    const QStringList &imagePath)
    : imagePath(imagePath) {}

bool wallpaperCollectionPackageCreator::setWorkDir()
{
    auto wallpaperCollectionDir =
        settingManager::getSettings().wallpaperCollectionDir();
    if (wallpaperCollectionDir.exists(name + ".deb"))
        return false;
    if (wallpaperCollectionDir.exists(name)) {
        QDir(wallpaperCollectionDir.absoluteFilePath(name)).removeRecursively();
    }
    wallpaperCollectionDir.mkdir(name);
    workDir.setPath(wallpaperCollectionDir.absoluteFilePath(name));
    return true;
}

bool wallpaperCollectionPackageCreator::parseConfig()
{
    workDir.mkpath("usr/share/backgrounds/");

    for (auto picture : imagePath) {
        QFile::copy(picture, workDir.absoluteFilePath("usr/share/backgrounds/" +
                    QFileInfo(picture).fileName()));
    }

    workDir.mkdir("DEBIAN");
    QDir controlPath(workDir.absoluteFilePath("DEBIAN"));

    handleConfigFile(":/templates/control", controlPath.absoluteFilePath("control"));
    return true;
}

soundPackageCreator::soundPackageCreator(const QString &configFilePath)
    : configFilePath(configFilePath) {}

bool soundPackageCreator::setWorkDir()
{
    auto soundDir = settingManager::getSettings().soundDir();
    if (soundDir.exists(name + ".deb"))
        return false;
    if (soundDir.exists(name)) {
        QDir(soundDir.absoluteFilePath(name)).removeRecursively();
    }
    soundDir.mkdir(name);
    workDir.setPath(soundDir.absoluteFilePath(name));
    return true;
}

bool soundPackageCreator::parseConfig()
{
    workDir.mkpath("usr/share/sounds/" + name);
    QDir soundDir(workDir.absoluteFilePath("usr/share/sounds/" + name));
    copy(configFilePath, soundDir.absoluteFilePath("index.theme"));

    QSettings soundConfig(configFilePath, QSettings::Format::IniFormat);
    soundConfig.beginGroup("Sound Theme");
    if (!soundConfig.contains("Name") || !soundConfig.contains("Directories")) {
        logger::getStandardLogger().log("不合法的sound文件");
        return false;
    }

    QFileInfo info(configFilePath);
    auto baseDir = info.dir();

    auto dirList = soundConfig.value("Directories").toStringList();
    for (auto dir = std::begin(dirList); dir != std::end(dirList); ++dir) {
        if (*dir != "" && baseDir.exists(*dir)) {
            copy(baseDir.absoluteFilePath(*dir), soundDir.absoluteFilePath(*dir));
        }
    }
    workDir.mkdir("DEBIAN");
    QDir controlPath(workDir.absoluteFilePath("DEBIAN"));

    handleConfigFile(":/templates/control", controlPath.absoluteFilePath("control"));
    return true;
}


globalThemePackageCreator::globalThemePackageCreator::globalThemePackageCreator(const QStringList &depends)
    : depends(depends) {}

bool globalThemePackageCreator::setWorkDir()
{
    auto globalThemeDir =
        settingManager::getSettings().globalThemeDir();
    if (globalThemeDir.exists(name + ".deb"))
        return false;
    if (globalThemeDir.exists(name)) {
        QDir(globalThemeDir.absoluteFilePath(name)).removeRecursively();
    }
    globalThemeDir.mkdir(name);
    workDir.setPath(globalThemeDir.absoluteFilePath(name));
    return true;
}

bool globalThemePackageCreator::parseConfig()
{
    workDir.mkdir("DEBIAN");
    QDir controlPath(workDir.absoluteFilePath("DEBIAN"));

    handleConfigFile(":/templates/control", controlPath.absoluteFilePath("control"));
    QFile controlFile(controlPath.absoluteFilePath("control"));
    auto rawPermission = controlFile.permissions();
    controlFile.setPermissions(rawPermission | QFileDevice::Permission::WriteOwner);
    controlFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream controlOut(&controlFile);

    controlOut << "Depends: ";
    for (auto dependPackage = std::begin(depends); dependPackage != std::end(depends); ++dependPackage) {
        controlOut << *dependPackage;
        if (dependPackage + 1 != std::end(depends)) controlOut << ", ";
    }

    controlOut << "\n";
    controlFile.setPermissions(rawPermission);
    controlFile.close();
    return true;
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; ;
