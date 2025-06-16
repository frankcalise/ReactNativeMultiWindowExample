
/*
 * This file is auto-generated from a NativeModule spec file in js.
 *
 * This is a C++ Spec class that should be used with MakeTurboModuleProvider to register native modules
 * in a way that also verifies at compile time that the native module matches the interface required
 * by the TurboModule JS spec.
 */
#pragma once
// clang-format off

#include <string>
#include <optional>
#include <functional>
#include <vector>

namespace RNModulesCodegen {

struct MenuModuleSpec_SubMenuItem {
    std::string id;
    std::string label;
    std::optional<std::string> accelerator;
    std::optional<std::string> mnemonic;
};

struct MenuModuleSpec_TopMenuItem {
    std::string id;
    std::string label;
    std::optional<std::string> accelerator;
    std::optional<std::string> mnemonic;
    std::vector<MenuModuleSpec_SubMenuItem> submenu;
};

} // namespace RNModulesCodegen
