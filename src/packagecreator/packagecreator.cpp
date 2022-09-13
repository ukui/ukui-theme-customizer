#include "packagecreator.h"
#include "ui_packagecreator.h"

packageCreator::packageCreator()
    : m_ui(new Ui::packageCreator)
{
    m_ui->setupUi(this);
    connect(this, &packageCreator::accepted, this, &packageCreator::onAccepted);
}

packageCreator::~packageCreator() {}

void iconThemePackage::ParseConfig() {
    workDir.mkpath("usr/share/icons");
    auto iconDir = workDir.current();
    iconDir.cd("usr/share/icons");
    QFile::copy(configFilePath, iconDir.filePath("index.ini"));

    QSettings iconConfig(configFilePath, QSettings::Format::IniFormat);
    iconConfig.beginGroup("Icon Theme");
    if (!iconConfig.contains("Name")) {
        log("不合法的icon文件");
        return;
    }

    QFileInfo info(configFilePath);
    auto baseDir = info.dir();

    auto iconName = iconConfig.value("Name").toString();
    log("正在为" + iconName + "打包...");

    auto dirList = iconConfig.value("Directories").toString().split(',');
    for (auto dir = std::begin(dirList); dir != std::end(dirList); ++dir) {
        if (baseDir.exists(*dir)) {
            QFile::copy(baseDir.filePath(*dir), iconDir.filePath(QDir("*dir").dirName()));
        }
    }
    workDir.mkdir("DEBIAN");
    QDir controlPath(workDir.filePath("DEBIAN"));

    handleConfigFile(":/templates/icon/postinst", controlPath.filePath("postinst"));
    handleConfigFile(":/templates/icon/postrm", controlPath.filePath("postrm"));
    handleConfigFile(":/templates/control", controlPath.filePath("control"));
}


void themePackage::handleConfigFile(QString source, QString dest) {
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
}


themePackage::themePackage ( const QString& name, const QString& maintainer, const QString& version, const QString& description, const QString& configFilePath ): name(name), maintainer(maintainer), version(version),
    description(description), configFilePath(configFilePath)
{
    if ( totalWorkDir.exists ( name ) ) {
        totalWorkDir.remove ( name );
    }
    totalWorkDir.mkdir ( name );
    workDir.setPath ( totalWorkDir.filePath ( name ) );
    workDir.mkdir ( "DEBIAN" );
}

