#pragma once

#include "users.g.h"

namespace winrt::ProjekAkhirAPL::implementation
{
    struct users : usersT<users>
    {
        users() 
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::ProjekAkhirAPL::factory_implementation
{
    struct users : usersT<users, implementation::users>
    {
    };
}
