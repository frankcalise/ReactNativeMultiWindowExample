
/*
 * This file is auto-generated from a NativeModule spec file in js.
 *
 * This is a C++ Spec class that should be used with MakeTurboModuleProvider to register native modules
 * in a way that also verifies at compile time that the native module matches the interface required
 * by the TurboModule JS spec.
 */
#pragma once
// clang-format off

// #include "NativeMenuModuleDataTypes.g.h" before this file to use the generated type definition
#include <NativeModules.h>
#include <tuple>

namespace RNModulesCodegen {

inline winrt::Microsoft::ReactNative::FieldMap GetStructInfo(MenuModuleSpec_SubMenuItem*) noexcept {
    winrt::Microsoft::ReactNative::FieldMap fieldMap {
        {L"id", &MenuModuleSpec_SubMenuItem::id},
        {L"label", &MenuModuleSpec_SubMenuItem::label},
    };
    return fieldMap;
}

inline winrt::Microsoft::ReactNative::FieldMap GetStructInfo(MenuModuleSpec_TopMenuItem*) noexcept {
    winrt::Microsoft::ReactNative::FieldMap fieldMap {
        {L"id", &MenuModuleSpec_TopMenuItem::id},
        {L"label", &MenuModuleSpec_TopMenuItem::label},
        {L"submenu", &MenuModuleSpec_TopMenuItem::submenu},
    };
    return fieldMap;
}

struct MenuModuleSpec : winrt::Microsoft::ReactNative::TurboModuleSpec {
  static constexpr auto methods = std::tuple{
      Method<void(std::vector<MenuModuleSpec_TopMenuItem>) noexcept>{0, L"initializeMenu"},
      Method<void() noexcept>{1, L"exitApp"},
      Method<void(std::string) noexcept>{2, L"addListener"},
      Method<void(double) noexcept>{3, L"removeListeners"},
      EventEmitter<void(std::string)>{4, L"onMenuItemSelected"},
  };

  template <class TModule>
  static constexpr void ValidateModule() noexcept {
    constexpr auto methodCheckResults = CheckMethods<TModule, MenuModuleSpec>();

    REACT_SHOW_METHOD_SPEC_ERRORS(
          0,
          "initializeMenu",
          "    REACT_METHOD(initializeMenu) void initializeMenu(std::vector<MenuModuleSpec_TopMenuItem> const & items) noexcept { /* implementation */ }\n"
          "    REACT_METHOD(initializeMenu) static void initializeMenu(std::vector<MenuModuleSpec_TopMenuItem> const & items) noexcept { /* implementation */ }\n");
    REACT_SHOW_METHOD_SPEC_ERRORS(
          1,
          "exitApp",
          "    REACT_METHOD(exitApp) void exitApp() noexcept { /* implementation */ }\n"
          "    REACT_METHOD(exitApp) static void exitApp() noexcept { /* implementation */ }\n");
    REACT_SHOW_METHOD_SPEC_ERRORS(
          2,
          "addListener",
          "    REACT_METHOD(addListener) void addListener(std::string eventName) noexcept { /* implementation */ }\n"
          "    REACT_METHOD(addListener) static void addListener(std::string eventName) noexcept { /* implementation */ }\n");
    REACT_SHOW_METHOD_SPEC_ERRORS(
          3,
          "removeListeners",
          "    REACT_METHOD(removeListeners) void removeListeners(double count) noexcept { /* implementation */ }\n"
          "    REACT_METHOD(removeListeners) static void removeListeners(double count) noexcept { /* implementation */ }\n");
    REACT_SHOW_EVENTEMITTER_SPEC_ERRORS(
          4,
          "onMenuItemSelected",
          "    REACT_EVENT(onMenuItemSelected) std::function<void(std::string)> onMenuItemSelected;\n");
  }
};

} // namespace RNModulesCodegen
