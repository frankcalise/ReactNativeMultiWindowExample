
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
        {L"type", &MenuModuleSpec_SubMenuItem::type},
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
      Method<void() noexcept>{1, L"clearMenu"},
      Method<void(std::string, std::string) noexcept>{2, L"addMenu"},
      Method<void(std::string, std::string, std::string) noexcept>{3, L"addSubMenu"},
      Method<void(std::string, std::string, std::string) noexcept>{4, L"addItem"},
      Method<void(std::string) noexcept>{5, L"addSeparator"},
      Method<void(std::string, bool) noexcept>{6, L"enableMenu"},
      Method<void() noexcept>{7, L"exitApp"},
      Method<void(std::string) noexcept>{8, L"addListener"},
      Method<void(double) noexcept>{9, L"removeListeners"},
      EventEmitter<void(std::string)>{10, L"onMenuItemSelected"},
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
          "clearMenu",
          "    REACT_METHOD(clearMenu) void clearMenu() noexcept { /* implementation */ }\n"
          "    REACT_METHOD(clearMenu) static void clearMenu() noexcept { /* implementation */ }\n");
    REACT_SHOW_METHOD_SPEC_ERRORS(
          2,
          "addMenu",
          "    REACT_METHOD(addMenu) void addMenu(std::string id, std::string label) noexcept { /* implementation */ }\n"
          "    REACT_METHOD(addMenu) static void addMenu(std::string id, std::string label) noexcept { /* implementation */ }\n");
    REACT_SHOW_METHOD_SPEC_ERRORS(
          3,
          "addSubMenu",
          "    REACT_METHOD(addSubMenu) void addSubMenu(std::string parentId, std::string id, std::string label) noexcept { /* implementation */ }\n"
          "    REACT_METHOD(addSubMenu) static void addSubMenu(std::string parentId, std::string id, std::string label) noexcept { /* implementation */ }\n");
    REACT_SHOW_METHOD_SPEC_ERRORS(
          4,
          "addItem",
          "    REACT_METHOD(addItem) void addItem(std::string parentId, std::string id, std::string label) noexcept { /* implementation */ }\n"
          "    REACT_METHOD(addItem) static void addItem(std::string parentId, std::string id, std::string label) noexcept { /* implementation */ }\n");
    REACT_SHOW_METHOD_SPEC_ERRORS(
          5,
          "addSeparator",
          "    REACT_METHOD(addSeparator) void addSeparator(std::string parentId) noexcept { /* implementation */ }\n"
          "    REACT_METHOD(addSeparator) static void addSeparator(std::string parentId) noexcept { /* implementation */ }\n");
    REACT_SHOW_METHOD_SPEC_ERRORS(
          6,
          "enableMenu",
          "    REACT_METHOD(enableMenu) void enableMenu(std::string id, bool enabled) noexcept { /* implementation */ }\n"
          "    REACT_METHOD(enableMenu) static void enableMenu(std::string id, bool enabled) noexcept { /* implementation */ }\n");
    REACT_SHOW_METHOD_SPEC_ERRORS(
          7,
          "exitApp",
          "    REACT_METHOD(exitApp) void exitApp() noexcept { /* implementation */ }\n"
          "    REACT_METHOD(exitApp) static void exitApp() noexcept { /* implementation */ }\n");
    REACT_SHOW_METHOD_SPEC_ERRORS(
          8,
          "addListener",
          "    REACT_METHOD(addListener) void addListener(std::string eventName) noexcept { /* implementation */ }\n"
          "    REACT_METHOD(addListener) static void addListener(std::string eventName) noexcept { /* implementation */ }\n");
    REACT_SHOW_METHOD_SPEC_ERRORS(
          9,
          "removeListeners",
          "    REACT_METHOD(removeListeners) void removeListeners(double count) noexcept { /* implementation */ }\n"
          "    REACT_METHOD(removeListeners) static void removeListeners(double count) noexcept { /* implementation */ }\n");
    REACT_SHOW_EVENTEMITTER_SPEC_ERRORS(
          10,
          "onMenuItemSelected",
          "    REACT_EVENT(onMenuItemSelected) std::function<void(std::string)> onMenuItemSelected;\n");
  }
};

} // namespace RNModulesCodegen
