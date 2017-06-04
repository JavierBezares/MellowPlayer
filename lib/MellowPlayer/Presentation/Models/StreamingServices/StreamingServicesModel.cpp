#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtWebEngine/QtWebEngine>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Application/Services/StreamingServicePluginService.hpp>
#include <MellowPlayer/Entities/StreamingServices/StreamingServicePlugin.hpp>
#include "StreamingServicesModel.hpp"
#include "QQmlObjectListModel.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(Application)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

StreamingServicesModel::StreamingServicesModel(StreamingServicePluginService& pluginService,
                                               PlayerService& playerService,
                                               Settings& settings) :
        QObject(), pluginService(pluginService), playerService(playerService),
        settings(settings),
        currentServiceSetting(settings.get(SettingKey::PRIVATE_CURRENT_SERVICE)),
        model(new QQmlObjectListModel<StreamingServicePluginModel>(this)),
        currentService(nullptr), currentIndex(-1) {

    connect(&pluginService, &StreamingServicePluginService::pluginAdded, this, &StreamingServicesModel::onPluginAdded);

    for (auto& plugin: pluginService.getAll()) {
        onPluginAdded(plugin.get());
    }
}

void StreamingServicesModel::initialize() {
    auto currentServiceName = currentServiceSetting.getValue().toString();
    for (auto service: model->toList()) {
        if (service->getName() == currentServiceName)
            setCurrentService(service);
    }
}

QObject* StreamingServicesModel::getCurrentService() const {
    return currentService;
}

int StreamingServicesModel::getCurrentIndex() const {
    return currentIndex;
}

void StreamingServicesModel::setCurrentService(QObject* value) {
    if (currentService == value)
        return;

    auto service = static_cast<StreamingServicePluginModel*>(value);
    currentServiceSetting.setValue(value->property("name").toString());
    currentService = value;
    pluginService.setCurrent(service->getPlugin());
    setCurrentIndex(model->toList().indexOf(service));
    emit currentServiceChanged(currentService);
}

void StreamingServicesModel::setCurrentIndex(int value) {
    if (currentIndex == value)
        return;

    currentIndex = value;
    emit currentIndexChanged(currentIndex);
}

void StreamingServicesModel::reload() {
    pluginService.load();
}

void StreamingServicesModel::onPluginAdded(StreamingServicePlugin* plugin) {
    model->append(new StreamingServicePluginModel(
            *plugin, settings.getSettingsProvider(), playerService, this));
}