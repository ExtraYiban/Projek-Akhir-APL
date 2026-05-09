#include "pch.h"
#include "users.h"
#if __has_include("users.g.cpp")
#include "users.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::ProjekAkhirAPL::implementation
{
    int32_t users::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void users::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void users::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }
}
