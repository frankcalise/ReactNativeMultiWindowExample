/**
 * Sample React Native App
 * https://github.com/facebook/react-native
 *
 * @format
 */

import React, {useEffect} from 'react';
import type {PropsWithChildren} from 'react';
import {
  TurboModuleRegistry,
  ScrollView,
  StatusBar,
  StyleSheet,
  Text,
  useColorScheme,
  View,
  Alert,
} from 'react-native';

import {
  Colors,
  DebugInstructions,
  Header,
  LearnMoreLinks,
  ReloadInstructions,
} from 'react-native/Libraries/NewAppScreen';

// Import and initialize the native menu turbo module
import {} from 'react-native';
import type {Spec as MenuModuleSpec} from './specs/NativeMenuModule';

const MenuModule =
  TurboModuleRegistry.getEnforcing<MenuModuleSpec>('MenuModule');

type SectionProps = PropsWithChildren<{
  title: string;
}>;

function Section({children, title}: SectionProps): React.JSX.Element {
  const isDarkMode = useColorScheme() === 'dark';
  return (
    <View style={styles.sectionContainer}>
      <Text
        style={[
          styles.sectionTitle,
          {
            color: isDarkMode ? Colors.white : Colors.black,
          },
        ]}>
        {title}
      </Text>
      <Text
        style={[
          styles.sectionDescription,
          {
            color: isDarkMode ? Colors.light : Colors.dark,
          },
        ]}>
        {children}
      </Text>
    </View>
  );
}

function App(): React.JSX.Element {
  const isDarkMode = useColorScheme() === 'dark';

  const backgroundStyle = {
    backgroundColor: isDarkMode ? Colors.darker : Colors.lighter,
  };

  /*
   * To keep the template simple and small we're adding padding to prevent view
   * from rendering under the System UI.
   * For bigger apps the recommendation is to use `react-native-safe-area-context`:
   * https://github.com/AppAndFlow/react-native-safe-area-context
   *
   * You can read more about it here:
   * https://github.com/react-native-community/discussions-and-proposals/discussions/827
   */
  const safePadding = '5%';

  const usingFabric = global.nativeFabricUIManager != null;

  const [menuEvent, setMenuEvent] = React.useState<string>('');

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

    MenuModule.initializeMenu([
      {
        id: 'file',
        label: '&File',
        submenu: [
          {
            type: 'item',
            id: 'exit',
            label: 'E&xit\tAlt+F4',
          },
        ],
      },
      {
        id: 'help',
        label: '&Help',
        submenu: [
          {type: 'item', id: 'updates', label: 'Check for updates...'},
          {type: 'separator'},
          {type: 'item', id: 'about', label: '&About\tF1'},
        ],
      },
    ]);

    // Cleanup the subscription on unmount
    return () => {
      sub.remove();
    };
  }, []);

  return (
    <View style={backgroundStyle}>
      <StatusBar
        barStyle={isDarkMode ? 'light-content' : 'dark-content'}
        backgroundColor={backgroundStyle.backgroundColor}
      />
      <ScrollView style={backgroundStyle}>
        <View style={{paddingRight: safePadding}}>
          <Header />
        </View>
        <View
          style={{
            backgroundColor: isDarkMode ? Colors.black : Colors.white,
            paddingHorizontal: safePadding,
            paddingBottom: safePadding,
          }}>
          <Section title="Using Fabric?">{usingFabric ? 'Yes' : 'No.'}</Section>
          <Section title="Menu Event">
            {menuEvent ?? 'No menu event received yet.'}
          </Section>
          <Section title="See Your Changes">
            <ReloadInstructions />
          </Section>
          <Section title="Debug">
            <DebugInstructions />
          </Section>
          <Section title="Learn More">
            Read the docs to discover what to do next:
          </Section>
          <LearnMoreLinks />
        </View>
      </ScrollView>
    </View>
  );
}

const styles = StyleSheet.create({
  sectionContainer: {
    marginTop: 32,
    paddingHorizontal: 24,
  },
  sectionTitle: {
    fontSize: 24,
    fontWeight: '600',
  },
  sectionDescription: {
    marginTop: 8,
    fontSize: 18,
    fontWeight: '400',
  },
  highlight: {
    fontWeight: '700',
  },
});

export default App;
