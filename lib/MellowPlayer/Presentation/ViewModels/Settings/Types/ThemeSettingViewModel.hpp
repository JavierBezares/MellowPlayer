#pragma once

#include "EnumSettingViewModel.hpp"

namespace MellowPlayer::Presentation
{
    class ThemeViewModel;

    class ThemeSettingViewModel : public EnumSettingViewModel
    {
        Q_OBJECT
    public:
        ThemeSettingViewModel(Application::Setting& setting, QObject* parent, ThemeViewModel& themeViewModel);
        QStringList values() const override;

    private:
        ThemeViewModel& themeViewModel_;
    };
}
