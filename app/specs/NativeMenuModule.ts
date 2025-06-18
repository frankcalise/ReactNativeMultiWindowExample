// specs/NativeMenuModule.ts
import type {TurboModule} from 'react-native';
import {TurboModuleRegistry} from 'react-native';
import {EventEmitter} from 'react-native/Libraries/Types/CodegenTypes';

/**
 * Sub-menu items have no further nesting.
 */
export type SubMenuItem = {
  /** unique JS ID */
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
   */
  initializeMenu(items: Array<TopMenuItem>): void;

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
