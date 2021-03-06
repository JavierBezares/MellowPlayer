#pragma once

#include <MellowPlayer/Application/AlbumArt/IAlbumArtDownloader.hpp>
#include <fakeit.hpp>

using namespace MellowPlayer::Application;
using namespace fakeit;

#define LOCAL_URL "/path/to/art/songId"

class AlbumArtDownloaderMock : public IAlbumArtDownloader
{
public:
    bool download(const QString&, const QString&) override
    {
        emit downloadFinished(LOCAL_URL);
        return true;
    }

    QFileInfo localArtUrl(const QString&) override
    {
        return QFileInfo(LOCAL_URL);
    }
};
