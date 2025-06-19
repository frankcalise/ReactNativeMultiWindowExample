# Refactoring Plan: Switch to "Primitive" Menu APIs

This document breaks down the work needed to replace the current `initializeMenu`-centric implementation with lower-level primitives (`addMenu`, `addSubMenu`, `addItem`, `addSeparator`, `enableMenu`, etc.).

---

## 1. Design & Spec Updates

1. **Define new JS-side primitives in `NativeMenuModule.ts`**

   - Add methods to the `Spec` interface:
     - `clearMenu(): void`
     - `addMenu(id: string, label: string): void`
     - `addSubMenu(parentId: string, id: string, label: string): void`
     - `addItem(parentId: string, id: string, label: string): void`
     - `addSeparator(parentId: string): void`
     - `enableMenu(id: string, enabled: boolean): void`
   - Deprecate or remove `initializeMenu` once primitives are fully supported. :contentReference[oaicite:0]{index=0}

2. **Regenerate codegen artifacts**
   - After updating `NativeMenuModule.ts`, run the RN codegen (`bunx react-native codegen-windows`) to refresh:
     - `NativeMenuModuleSpec.g.h`
     - `NativeMenuModuleDataTypes.g.h`

---

## 2. Module Header (`MenuModule.h`) Changes

1. **Register new methods**  
   In `MenuModule.h`, replace the single `REACT_METHOD(initializeMenu)` with:

   ```cpp
   REACT_METHOD(clearMenu)
   REACT_METHOD(addMenu)
   REACT_METHOD(addSubMenu)
   REACT_METHOD(addItem)
   REACT_METHOD(addSeparator)
   REACT_METHOD(enableMenu)
   ```

2. Comment out the old `initializeMenu` declaration

## 3. Native Implementation (MenuModule.cpp) Work

- Maintain a single HMENU bar

  - Introduce a member HMENU m_menuBar (initialized via CreateMenu() in clearMenu()).

- Implement clearMenu()

```cpp
void MenuModule::clearMenu() noexcept {
  if (m_hwnd) {
    SetMenu(m_hwnd, nullptr);
    DestroyMenu(m_menuBar);
  }
  m_menuBar = CreateMenu();
  DrawMenuBar(m_hwnd);
}
```

## 4. Implement addMenu(id, label)

-Lookup HMENU for parentId in your std::map<string, HMENU>

- Create a new HMENU popup (CreatePopupMenu())

- Store mapping from id → newly created popup handle

- Append to m_menuBar with AppendMenuW(m_menuBar, MF_POPUP, (UINT_PTR)hSub, to_hstring(label).c_str())

## 5. Implement addSubMenu(parentId, id, label)

- Lookup HMENU for parentId in your std::map<string, HMENU>

- Create child popup via CreatePopupMenu()

- Store mapping id → child popup

- Append it with AppendMenuW(parentHMenu, MF_POPUP, (UINT_PTR)childHMenu, to_hstring(label).c_str())

## 6. Implement addItem(parentId, id, label)

Generate a unique cmdId = ++m_lastCmdId; map cmdId → JS id in m_idMap

- Lookup HMENU parentHMenu by parentId; then AppendMenuW(parentHMenu, MF_STRING, cmdId, to_hstring(label).c_str())

## 7. Implement addSeparator(parentId)

- Lookup parentHMenu and call AppendMenuW(parentHMenu, MF_SEPARATOR, 0, nullptr)

## 8. Implement enableMenu(id, enabled)

- Find cmdId in m_idMap by JS id

- Call EnableMenuItem(m_menuBar, cmdId, MF_BYCOMMAND | (enabled ? MF_ENABLED : MF_GRAYED))

- DrawMenuBar(m_hwnd);

- Retain window subclassing & WndProc

- Ensure m_hwnd is initialized on first primitive call (as current initializeMenu does)

- Keep WndProcStatic logic for dispatching WM_COMMAND events.

---

## Example: Building the Same Menu with Primitives (JS-side)

Below is how you would construct the same menu as the previous `initializeMenu` call in `app.tsx`, but using the new primitive methods:

```ts
useEffect(() => {
  const sub = MenuModule.onMenuItemSelected((id: string) => {
    setMenuEvent(id);
    if (id === 'exit') {
      MenuModule.exitApp();
    } else if (id === 'about') {
      Alert.alert(
        'About',
        'This is a sample React Native app with a native menu.',
      );
    }
  });

  // Build menu bar using primitives
  MenuModule.clearMenu();

  // File menu
  MenuModule.addMenu('file', '&File');
  MenuModule.addItem('file', 'exit', 'E&xit\tAlt+F4');

  // Help menu
  MenuModule.addMenu('help', '&Help');
  MenuModule.addItem('help', 'updates', 'Check for updates...');
  MenuModule.addSeparator('help');
  MenuModule.addItem('help', 'about', '&About\tF1');

  // Cleanup the subscription on unmount
  return () => {
    sub.remove();
  };
}, []);
```

This approach replaces the single `initializeMenu` call with a sequence of primitive operations, matching the menu structure and behavior in the original example.
