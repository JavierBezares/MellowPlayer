#pragma once
#include <fakeit.hpp>
#include <memory>
#include <MellowPlayer/UseCases/Interfaces/INotificationsService.hpp>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
using namespace fakeit;

class NotificationServiceMock {
public:
    static Mock<INotificationService> get() {
        Mock<INotificationService> mock;
        When(Method(mock, initialize)).AlwaysReturn();
        When(Method(mock, display)).AlwaysReturn(true);
        return mock;
    }
};
