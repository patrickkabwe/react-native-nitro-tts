import React, { useEffect } from 'react';
import { Button, Platform, StyleSheet, Text, View } from 'react-native';
import { TextToSpeech } from 'react-native-nitro-tts';

const text =
  'React Native Text To Speech is amazing! 🎉 Check it out by running npm install react-native-nitro-tts';

function App(): React.JSX.Element {
  const speak = async () => {
    const opts = Platform.select({
      ios: {
        pitch: 0.85,
        rate: 0.4,
        volume: 0.9,
        postUtteranceDelay: 0,
        voiceIdentifier: 'com.apple.voice.premium.en-AU.Karen',
      },
      android: {
        pitch: 1,
        rate: 1,
        volume: 2.0,
        voiceIdentifier: 'en-gb-x-gbd-local',
      },
    });
    try {
      await TextToSpeech.stop();
      await TextToSpeech.speak(text, opts);
    } catch (error) {
      console.error(error);
    }
  };

  useEffect(() => {
    const unsubscribeStart = TextToSpeech.addListener('start', () => {
      console.log('didStart');
    });
    const unsubscribeFinish = TextToSpeech.addListener('finish', () => {
      console.log('didFinish');
    });
    const unsubscribeWord = TextToSpeech.addListener('word', word => {
      console.log('didWordChange', word);
    });

    return () => {
      unsubscribeFinish();
      unsubscribeWord();
      unsubscribeStart();
    };
  }, []);

  return (
    <View style={styles.container}>
      <Text style={styles.header}>React Native Text To Speech</Text>
      <View
        style={{
          gap: Platform.select({
            android: 10,
          }),
        }}>
        <Button title="Press to speak" onPress={speak} />
        <Button title="Press to stop" onPress={TextToSpeech.stop} />
        <Button title="Press to pause" onPress={TextToSpeech.pause} />
        <Button title="Press to resume" onPress={TextToSpeech.resume} />
      </View>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
  },

  header: {
    fontSize: 40,
    textAlign: 'center',
    marginBottom: 20,
  },
});

export default App;
