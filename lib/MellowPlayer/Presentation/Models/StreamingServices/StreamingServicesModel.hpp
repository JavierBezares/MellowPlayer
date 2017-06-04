#pragma once

#include <QObject>
#include <QAbstractListModel>
#include <MellowPlayer/Presentation/Models/StreamingServices/StreamingServicePluginModel.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(Application, Settings)
PREDECLARE_MELLOWPLAYER_CLASS(Application, Setting)
PREDECLARE_MELLOWPLAYER_CLASS(Application, PlayerService)
PREDECLARE_MELLOWPLAYER_CLASS(Application, StreamingServicePluginService)
PREDECLARE_MELLOWPLAYER_CLASS(Entities, StreamingServicePlugin)

class QQmlApplicationEngine;
template <class T> class QQmlObjectListModel;

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class StreamingServicesModel: public QObject {
    Q_OBJECT
    Q_PROPERTY(QAbstractListModel* model READ getModel CONSTANT)

    Q_PROPERTY(QObject* currentService READ getCurrentService WRITE setCurrentService NOTIFY currentServiceChanged)
    Q_PROPERTY(int currentIndex READ getCurrentIndex NOTIFY currentIndexChanged)
public:
    StreamingServicesModel(Application::StreamingServicePluginService& pluginService,
                               Application::PlayerService& playerService,
                               Application::Settings& settings);
    void initialize();

    Q_INVOKABLE void reload();
    QQmlObjectListModel<StreamingServicePluginModel>* getModel() { return model; }
    QObject* getCurrentService() const;
    int getCurrentIndex() const;

public slots:
    void setCurrentService(QObject* value);
    void setCurrentIndex(int value);

signals:
    void currentServiceChanged(QObject* currentService);
    void currentIndexChanged(int currentIndex);

private slots:
    void onPluginAdded(Entities::StreamingServicePlugin* plugin);

private:
    Application::StreamingServicePluginService& pluginService;
    Application::PlayerService& playerService;
    Application::Settings& settings;
    Application::Setting& currentServiceSetting;
    QQmlObjectListModel<StreamingServicePluginModel>* model;
    QObject* currentService;
    int currentIndex;
};

END_MELLOWPLAYER_NAMESPACE