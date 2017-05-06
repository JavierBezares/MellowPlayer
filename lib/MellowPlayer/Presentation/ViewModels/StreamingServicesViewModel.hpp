#pragma once

#include <QObject>
#include <QAbstractListModel>
#include <MellowPlayer/Presentation/Models/StreamingServiceModel.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(UseCases, IApplicationSettings)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, PlayerService)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, PluginService)
PREDECLARE_MELLOWPLAYER_CLASS(Entities, Plugin)

class QQmlApplicationEngine;
template <class T> class QQmlObjectListModel;

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class StreamingServicesViewModel: public QObject {
    Q_OBJECT
    Q_PROPERTY(QAbstractListModel* model READ getModel CONSTANT)

    Q_PROPERTY(QObject* currentService READ getCurrentService WRITE setCurrentService NOTIFY currentServiceChanged)
    Q_PROPERTY(int currentIndex READ getCurrentIndex NOTIFY currentIndexChanged)
public:
    StreamingServicesViewModel(UseCases::PluginService& pluginService,
                               UseCases::PlayerService& playerService,
                               UseCases::IApplicationSettings& applicationSettings);
    void initialize();

    Q_INVOKABLE void reload();
    QQmlObjectListModel<StreamingServiceModel>* getModel() { return model; }
    QObject* getCurrentService() const;
    int getCurrentIndex() const;

public slots:
    void setCurrentService(QObject* value);
    void setCurrentIndex(int value);

signals:
    void currentServiceChanged(QObject* currentService);
    void currentIndexChanged(int currentIndex);

private slots:
    void onPluginAdded(Entities::Plugin* plugin);

private:
    UseCases::PluginService& pluginService;
    UseCases::PlayerService& playerService;
    UseCases::IApplicationSettings& applicationSettings;
    QQmlObjectListModel<StreamingServiceModel>* model;
    QObject* currentService;
    QObject* currentPlayer;
    int currentIndex;
};

END_MELLOWPLAYER_NAMESPACE