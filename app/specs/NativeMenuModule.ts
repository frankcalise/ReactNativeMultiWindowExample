// specs/NativeMenuModule.ts
import type {TurboModule} from 'react-native';
import {TurboModuleRegistry} from 'react-native';
import {EventEmitter} from 'react-native/Libraries/Types/CodegenTypes';

/**
 * Sub-menu items
 */
export type SubMenuItem = {
  type: 'item' | 'separator';
  id: string;
  /** visible label */
  label: string;
};

/**
 * Top-level menu entries must include a submenu,
 * but those sub-entries use the non-recursive `SubMenuItem`.
 */
export type TopMenuItem = {
  id: string;
  label: string;
  submenu: SubMenuItem[];
};

export interface Spec extends TurboModule {
  /**
   * (Re)build the entire menu bar, including optional accelerators and mnemonics.
   * @param items an array of top-level menu items
   * @deprecated Use primitives (clearMenu, addMenu, etc.) instead.
   */
  initializeMenu(items: Array<TopMenuItem>): void;

  /**
   * Remove all menus and reset the menu bar.
   */
  clearMenu(): void;

  /**
   * Add a top-level menu to the menu bar.
   * @param id Unique menu id
   * @param label Menu label (may include & for mnemonics)
   */
  addMenu(id: string, label: string): void;

  /**
   * Add a submenu to a parent menu.
   * @param parentId Id of the parent menu
   * @param id Unique submenu id
   * @param label Submenu label
   */
  addSubMenu(parentId: string, id: string, label: string): void;

  /**
   * Add an item to a parent menu or submenu.
   * @param parentId Id of the parent menu or submenu
   * @param id Unique item id
   * @param label Item label
   */
  addItem(parentId: string, id: string, label: string): void;

  /**
   * Add a separator to a parent menu or submenu.
   * @param parentId Id of the parent menu or submenu
   */
  addSeparator(parentId: string): void;

  /**
   * Enable or disable a menu item by id.
   * @param id Item id
   * @param enabled True to enable, false to disable
   */
  enableMenu(id: string, enabled: boolean): void;

  /** Convenience method: force an app-exit on the native side */
  exitApp(): void;

  /** Subscribe to native events (e.g. menu clicks) */
  addListener(eventName: string): void;

  /** Required: remove listeners when JS side cleans up */
  removeListeners(count: number): void;

  /**
   * Set a listener for menu item selection events.
   * This is only needed if you want to handle menu selections in JS.
   */
  readonly onMenuItemSelected: EventEmitter<string>;
}

const MenuTurboModule = TurboModuleRegistry.getEnforcing<Spec>('MenuModule');
export default MenuTurboModule;
