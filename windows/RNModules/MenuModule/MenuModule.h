#pragma once

#include <pch.h>

#include <winrt/Microsoft.ReactNative.h>
#include <windows.h>
#include <map>
#include <string>


#include "../codegen/NativeMenuModuleDataTypes.g.h"
#include "../codegen/NativeMenuModuleSpec.g.h"

namespace winrt::ReactNativeMultiWindowExample::implementation {

REACT_TURBO_MODULE(MenuModule);
struct MenuModule {
  using ModuleSpec = RNModulesCodegen::MenuModuleSpec;
  MenuModule() noexcept;

  // Called by RNW to initialize with the ReactContext
  REACT_INIT(Initialize)
  void Initialize(React::ReactContext const &context) noexcept;

  // Spec methods
  REACT_METHOD(initializeMenu)
  void initializeMenu(std::vector<RNModulesCodegen::MenuModuleSpec_TopMenuItem> const &items) noexcept;
  REACT_METHOD(exitApp)
  void exitApp() noexcept;
  REACT_METHOD(addListener)
  void addListener(std::string const &eventName) noexcept;
  REACT_METHOD(removeListeners)
  void removeListeners(double count) noexcept;
  REACT_EVENT(onMenuItemSelected, L"onMenuItemSelected");
  std::function<void(std::string)> onMenuItemSelected;

  static const winrt::Microsoft::ReactNative::ReactPropertyId<winrt::Microsoft::UI::Windowing::AppWindow>& AppWindowPropertyId() noexcept {
      static const winrt::Microsoft::ReactNative::ReactPropertyId<winrt::Microsoft::UI::Windowing::AppWindow> prop{ L"MenuModule", L"AppWindow" };
      return prop;
  }

private:
  React::ReactContext                        m_reactContext;
  HWND                                       m_hwnd{ nullptr };
  WNDPROC                                    m_oldProc{ nullptr };
  int                                        m_lastCmdId{ 100 };
  std::map<int, std::string>                 m_idMap;

  // Helper to subclass the window proc once the HWND is set
  void SubclassWindow() noexcept;

  static LRESULT CALLBACK WndProcStatic(
      HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam
  ) noexcept;
};

} // namespace winrt::ReactNativeMultiWindowExample::implementation
