#include "AbstractPlatformUpdater.hpp"
#include <MellowPlayer/Application/IFileDownloader.hpp>
#include <MellowPlayer/Application/Updater/Release.hpp>
#include <QtCore/QTemporaryDir>

using namespace MellowPlayer::Application;

AbstractPlatformUpdater::AbstractPlatformUpdater(IFileDownloader& fileDownloader) : fileDownloader_(fileDownloader)
{
    connect(&fileDownloader, &IFileDownloader::progressChanged, this, &AbstractPlatformUpdater::progressUpdated);
    connect(&fileDownloader, &IFileDownloader::finished, this, &AbstractPlatformUpdater::downloadFinished);
}

void AbstractPlatformUpdater::setRelease(const Release* release)
{
    release_ = release;
}

void AbstractPlatformUpdater::download()
{
    if (release_) {
        assetFilePath_ = makeDestinationPath();
        fileDownloader_.download(assetUrl(), assetFilePath_);
    }
}

QString AbstractPlatformUpdater::makeDestinationPath()
{
    QString tempDir = QTemporaryDir().path();
    QDir().mkpath(tempDir);
    return tempDir + "/" + assetFileName();
}

void AbstractPlatformUpdater::install()
{
    emit progressUpdated(-1);
    doInstall(assetFilePath_);
}
