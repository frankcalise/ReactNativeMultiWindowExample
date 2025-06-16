#include "pch.h"
#include "MenuModule.h"
#include <NativeModules.h>
#include <winrt/Microsoft.ReactNative.h>
#include <winrt/Microsoft.UI.Xaml.h>           // for Window::Current()
#include <microsoft.ui.xaml.window.h>          // for ::IWindowNative
#include <windows.h>
#include <map>
#include <string>

namespace winrt::ReactNativeMultiWindowExample::implementation {
    constexpr int IDM_EXIT = 1;

    MenuModule::MenuModule() noexcept {}

    void MenuModule::Initialize(React::ReactContext const &reactContext) noexcept {
      m_reactContext = reactContext;
    }

    LRESULT MenuModule::OnCommand(int id) noexcept {
        switch (id) {
            case IDM_EXIT:
                exitApp();
                return 0;

        default:
            return 1;
        }
    }

    LRESULT CALLBACK MenuModule::WndProcStatic(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) noexcept {
        auto self = reinterpret_cast<MenuModule*>(
            GetWindowLongPtr(hwnd, GWLP_USERDATA)
        );

        if (!self) {
            // shouldn�t happen, but fall back
            return DefWindowProc(hwnd, message, wparam, lparam);
        }

        if (message == WM_COMMAND) {
            // pull out the command ID
            int cmd = LOWORD(wparam);
            // dispatch to your member handler
            LRESULT result = self->OnCommand(cmd);
            if (result != 1) {
                return 0;
            }
        }

        return DefWindowProc(hwnd, message, wparam, lparam);
    }

    void MenuModule::SubclassWindow() noexcept {
      if (m_hwnd && !m_oldProc) {
          m_oldProc = reinterpret_cast<WNDPROC>(
              SetWindowLongPtr(
                  m_hwnd,
                  GWLP_WNDPROC,
                  reinterpret_cast<LONG_PTR>(&MenuModule::WndProcStatic)
              )
          );
          SetWindowLongPtr(m_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
      }
    }

    void MenuModule::initializeMenu(
      std::vector<RNModulesCodegen::MenuModuleSpec_TopMenuItem> const &items) noexcept {
        // TODO: parse items into HMENU, AppendMenuW, etc.

        // 1) First time only: grab HWND & subclass
        if (!m_hwnd) {
            uint64_t hwnd = 0;
            winrt::Microsoft::ReactNative::ReactPropertyBag pb{ m_reactContext.Properties() };
            hwnd = winrt::Microsoft::ReactNative::ReactCoreInjection::GetTopLevelWindowId(pb.Handle());
            if (!hwnd) return;
			m_hwnd = reinterpret_cast<HWND>(hwnd);
            SubclassWindow();
        }
        
        // 2) Build the menu bar
        HMENU hMenuBar = CreateMenu();
        HMENU hFileMenu = CreatePopupMenu();
            
        AppendMenuW(hFileMenu, MF_STRING, IDM_EXIT, L"E&xit");
        AppendMenuW(hMenuBar, MF_POPUP, reinterpret_cast<UINT_PTR>(hFileMenu), L"&File");

        SetMenu(m_hwnd, hMenuBar);
        DrawMenuBar(m_hwnd);
    }

    void MenuModule::exitApp() noexcept {
      PostMessageW(m_hwnd, WM_CLOSE, 0, 0);
    }

    void MenuModule::addListener(std::string const &eventName) noexcept {
      // No-op or track listener count
    }

    void MenuModule::removeListeners(double count) noexcept {
      // No-op or cleanup
    }
} // namespace winrt::ReactNativeMultiWindowExample::implementation