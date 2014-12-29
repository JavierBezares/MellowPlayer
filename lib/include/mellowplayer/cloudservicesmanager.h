//---------------------------------------------------------
//
// This file is part of MellowPlayer.
//
// MellowPlayer is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MellowPlayer is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MellowPlayer.  If not, see <http://www.gnu.org/licenses/>.
//
//---------------------------------------------------------

#ifndef CLOUDSERVICESMANAGER_H
#define CLOUDSERVICESMANAGER_H

#include <QObject>
#include <QIcon>

class QPluginLoader;
class ICloudMusicService;


/*!
 * \brief The CloudServicesManager class manages the collection of cloud music
 * services and let you start and changed the current service.
 *
 */
class CloudServicesManager : public QObject
{
    Q_OBJECT
public:
    explicit CloudServicesManager(QObject* parent=0);

    struct PluginMetaData
    {
        QString name;
        QString author;
        QString website;
        QString version;
        QIcon icon;
        QString description;
        QString htmlDescription;
    };

    /*!
     * \brief Adds a cloud music service plugin to the list of managed plugins.
     *
     * **For internal uses only, all the plugins are added by the application.**
     *
     * \param service Service to add.
     * \param pluginLoader Pointer to the plugin loader that loaded the service
     *                     plugin.
     */
    void loadPlugin(ICloudMusicService* iService, QPluginLoader* pluginLoader);

signals:

public slots:

private:
    PluginMetaData extractMetaData(QPluginLoader* pluginLoader);
    std::map<QString, ICloudMusicService*> services;
    std::map<QString, PluginMetaData> metaData;
};

#endif // CLOUDSERVICESMANAGER_H
