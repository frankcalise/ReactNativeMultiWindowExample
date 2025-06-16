// specs/NativeMenuModule.ts
import type {TurboModule} from 'react-native';
import {TurboModuleRegistry} from 'react-native';

/**
 * Sub-menu items have no further nesting.
 */
export type SubMenuItem = {
  /** unique JS ID */
  id: string;
  /** visible label */
  label: string;
  /** optional “Ctrl+X” style shortcut */
  accelerator?: string;
  /** optional single mnemonic character */
  mnemonic?: string;
};

/**
 * Top-level menu entries must include a submenu,
 * but those sub-entries use the non-recursive `SubMenuItem`.
 */
export type TopMenuItem = {
  id: string;
  label: string;
  accelerator?: string;
  mnemonic?: string;
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
}

export default TurboModuleRegistry.getEnforcing<Spec>(
  'MenuModule' /* must match your native registration name */,
);
