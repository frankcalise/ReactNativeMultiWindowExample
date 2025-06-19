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

    void MenuModule::initializeMenu(std::vector<RNModulesCodegen::MenuModuleSpec_TopMenuItem> const& items) noexcept {
      // noop
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

    // --- Primitive Menu API Implementation ---
    void MenuModule::clearMenu() noexcept {
        if (!m_hwnd) {
            // Initialize HWND if needed
            uint64_t hwnd = 0;
            winrt::Microsoft::ReactNative::ReactPropertyBag pb{ m_reactContext.Properties() };
            hwnd = winrt::Microsoft::ReactNative::ReactCoreInjection::GetTopLevelWindowId(pb.Handle());
            if (!hwnd) return;
            m_hwnd = reinterpret_cast<HWND>(hwnd);
            SubclassWindow();
        }
        SetMenu(m_hwnd, nullptr);
        if (m_menuBar) {
            DestroyMenu(m_menuBar);
        }
        m_menuBar = CreateMenu();
        m_menuMap.clear();
        m_idMap.clear();
        m_lastCmdId = 100;
        DrawMenuBar(m_hwnd);
    }

    void MenuModule::addMenu(std::string const &id, std::string const &label) noexcept {
        if (!m_menuBar) return;
        HMENU hSub = CreatePopupMenu();
        m_menuMap[id] = hSub;
        AppendMenuW(m_menuBar, MF_POPUP, (UINT_PTR)hSub, winrt::to_hstring(label).c_str());
        SetMenu(m_hwnd, m_menuBar);
        DrawMenuBar(m_hwnd);
    }

    void MenuModule::addSubMenu(std::string const &parentId, std::string const &id, std::string const &label) noexcept {
        auto it = m_menuMap.find(parentId);
        if (it == m_menuMap.end()) return;
        HMENU parentHMenu = it->second;
        HMENU childHMenu = CreatePopupMenu();
        m_menuMap[id] = childHMenu;
        AppendMenuW(parentHMenu, MF_POPUP, (UINT_PTR)childHMenu, winrt::to_hstring(label).c_str());
        SetMenu(m_hwnd, m_menuBar);
        DrawMenuBar(m_hwnd);
    }

    void MenuModule::addItem(std::string const &parentId, std::string const &id, std::string const &label) noexcept {
        auto it = m_menuMap.find(parentId);
        if (it == m_menuMap.end()) return;
        HMENU parentHMenu = it->second;
        int cmdId = ++m_lastCmdId;
        m_idMap[cmdId] = id;
        AppendMenuW(parentHMenu, MF_STRING, cmdId, winrt::to_hstring(label).c_str());
        SetMenu(m_hwnd, m_menuBar);
        DrawMenuBar(m_hwnd);
    }

    void MenuModule::addSeparator(std::string const &parentId) noexcept {
        auto it = m_menuMap.find(parentId);
        if (it == m_menuMap.end()) return;
        HMENU parentHMenu = it->second;
        AppendMenuW(parentHMenu, MF_SEPARATOR, 0, nullptr);
        SetMenu(m_hwnd, m_menuBar);
        DrawMenuBar(m_hwnd);
    }

    void MenuModule::enableMenu(std::string const &id, bool enabled) noexcept {
        // Find the cmdId for this id
        int foundCmdId = -1;
        for (const auto& pair : m_idMap) {
            if (pair.second == id) {
                foundCmdId = pair.first;
                break;
            }
        }
        if (foundCmdId == -1) return;
        EnableMenuItem(m_menuBar, foundCmdId, MF_BYCOMMAND | (enabled ? MF_ENABLED : MF_GRAYED));
        DrawMenuBar(m_hwnd);
    }
} // namespace winrt::ReactNativeMultiWindowExample::implementation
