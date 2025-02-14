import { NitroModules } from 'react-native-nitro-modules'
import type { EventName, TextToSpeechOptions, TextToSpeech as TextToSpeechSpec, TextToSpeechVoice } from './specs/text-to-speech.nitro'

export const TextToSpeechNitroModule =
  NitroModules.createHybridObject<TextToSpeechSpec>('TextToSpeech')


export const TextToSpeech = {
  speak: async (text: string, options?: TextToSpeechOptions): Promise<void> => {
    return TextToSpeechNitroModule.speak(text, options)
  },
  stop: async (): Promise<boolean> => {
    return TextToSpeechNitroModule.stop()
  },
  pause: async (): Promise<boolean> => {
    return TextToSpeechNitroModule.pause()
  },
  resume: async (): Promise<boolean> => {
    return TextToSpeechNitroModule.resume()
  },
  getVoices: async (): Promise<TextToSpeechVoice[]> => {
    return TextToSpeechNitroModule.getVoices()
  },
  addListener: (event: EventName, listener: (word?: string) => void): (() => void) => {
    return TextToSpeechNitroModule.addListener(event, listener)
  },
}