#include "BoolSettingViewModel.hpp"

using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Application;

BoolSettingViewModel::BoolSettingViewModel(Setting& setting, QObject* parent) : SettingViewModel(setting, parent)
{
}

bool BoolSettingViewModel::getValue() const
{
    return setting_.value().toBool();
}

void BoolSettingViewModel::setValue(bool value)
{
    setting_.setValue(value);
}

void BoolSettingViewModel::onValueChanged()
{
    emit valueChanged();
}

QString BoolSettingViewModel::qmlComponent()
{
    return "qrc:/MellowPlayer/Presentation/Views/MellowPlayer/Delegates/BoolSettingDelegate.qml";
}
