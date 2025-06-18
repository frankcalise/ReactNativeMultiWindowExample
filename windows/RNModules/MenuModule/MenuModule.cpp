#include <pch.h>
#include "MenuModule.h"
#include <NativeModules.h>
#include <winrt/Microsoft.ReactNative.h>
#include <windows.h>
#include <string>

namespace winrt::ReactNativeMultiWindowExample::implementation {
    MenuModule::MenuModule() noexcept {}

    void MenuModule::Initialize(React::ReactContext const &reactContext) noexcept {
      m_reactContext = reactContext;
    }

    LRESULT CALLBACK MenuModule::WndProcStatic(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) noexcept {
        auto self = reinterpret_cast<MenuModule*>(
            GetWindowLongPtr(hwnd, GWLP_USERDATA)
        );

        if (!self) {
            // shouldn't happen, but fall back
            return DefWindowProc(hwnd, message, wparam, lparam);
        }

        if (message == WM_COMMAND) {
            // pull out the command ID
            int cmd = LOWORD(wparam);
            auto it = self->m_idMap.find(cmd);
            if (it != self->m_idMap.end()) {
                self->onMenuItemSelected({ it->second });
            }
            return 0;  // we handled the menu click
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
        // 1) First time only: grab HWND & subclass
        if (!m_hwnd) {
            uint64_t hwnd = 0;
            winrt::Microsoft::ReactNative::ReactPropertyBag pb{ m_reactContext.Properties() };
            hwnd = winrt::Microsoft::ReactNative::ReactCoreInjection::GetTopLevelWindowId(pb.Handle());
            if (!hwnd) return;
			m_hwnd = reinterpret_cast<HWND>(hwnd);
            SubclassWindow();
        }

        // Create menu and submenus
        HMENU hMenuBar = CreateMenu();
        for (auto const& top : items) {
            // Create the drop-down
            HMENU hSub = CreatePopupMenu();
            for (auto const& sub : top.submenu) {
                // Assign a unique cmd ID and remember its JS id
                int cmdId = ++m_lastCmdId;
                m_idMap[cmdId] = sub.id;

                AppendMenuW(hSub, MF_STRING, cmdId, winrt::to_hstring(sub.label).c_str());
            }

            // Attach this submenu under the top label
            AppendMenuW(hMenuBar, MF_POPUP,
                reinterpret_cast<UINT_PTR>(hSub),
                winrt::to_hstring(top.label).c_str()
            );
        }

        // 3) Set it on the window
        SetMenu(m_hwnd, hMenuBar);
        DrawMenuBar(m_hwnd);
    }

    void MenuModule::exitApp() noexcept {
        // dispatch the exit on the UI thread
        m_reactContext.UIDispatcher().Post([=]() {
            auto appWindow = winrt::Microsoft::ReactNative::ReactPropertyBag{ m_reactContext.Properties() }.Get(AppWindowPropertyId());
            appWindow.Destroy();
        });
    }

    void MenuModule::addListener(std::string const &eventName) noexcept {
        // noop
    }

    void MenuModule::removeListeners(double count) noexcept {
        // noop
    }
} // namespace winrt::ReactNativeMultiWindowExample::implementation
