import { type HybridObject } from 'react-native-nitro-modules'

export type TextToSpeechVoice = {
  identifier: string
  name: string
  quality: string
  gender: string
}

export type TextToSpeechOptions = {
  voiceIdentifier?: string
  rate?: number
  pitch?: number
  postUtteranceDelay?: number
  preUtteranceDelay?: number
  volume?: number
}

export type EventName = 'word' | 'finish' | 'start'

export interface TextToSpeech extends HybridObject<{ ios: 'swift', android: 'kotlin' }> {
  speak(text: string, options?: TextToSpeechOptions): Promise<void>
  stop(): Promise<boolean>
  pause(): Promise<boolean>
  resume(): Promise<boolean>
  getVoices(): Promise<TextToSpeechVoice[]>
  addListener(event: EventName, listener: (word?: string) => void): () => void
}
