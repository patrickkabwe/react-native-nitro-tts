package com.nitrotexttospeech

import android.os.Bundle
import android.speech.tts.SynthesisRequest
import android.util.Log
import com.margelo.nitro.core.Promise
import com.margelo.nitro.nitrotexttospeech.EventName
import com.margelo.nitro.nitrotexttospeech.HybridTextToSpeechSpec
import com.margelo.nitro.nitrotexttospeech.TextToSpeechOptions
import com.margelo.nitro.nitrotexttospeech.TextToSpeechVoice
import android.speech.tts.TextToSpeech
import android.speech.tts.Voice
import com.margelo.nitro.NitroModules
import java.util.Locale


class HybridTextToSpeech: HybridTextToSpeechSpec(), TextToSpeech.OnInitListener {
    var context = NitroModules.applicationContext
    private var tts = TextToSpeech(context,this)
    private var initSuccess = false

    init {
        Log.d(TAG, "HybridTextToSpeech ${tts.defaultEngine}")
    }

    override fun speak(text: String, options: TextToSpeechOptions?): Promise<Unit> {
        return Promise.async {
            if (!initSuccess) {
                throw Error("$TAG Failed to initialize TextToSpeech.")
            }
            options?.rate?.toFloat()?.let { tts.setSpeechRate(it) }
            options?.pitch?.toFloat()?.let { tts.setPitch(it) }

            tts.voices.find { it?.name == options?.voiceIdentifier }.let {
                Log.d(TAG, "Found voice: $it")
                if (it != null) {
                    tts.voice = it
                }
            }

            val volume = options?.volume?.toFloat()
            val params = Bundle().apply {
                volume?.let { putFloat(TextToSpeech.Engine.KEY_PARAM_VOLUME, it) }
            }

            tts.speak(text, TextToSpeech.QUEUE_FLUSH, params, null)
        }
    }

    override fun stop(): Promise<Boolean> {
       return Promise.async {
           if (!tts.isSpeaking) {
               false
           } else {
               tts.stop()
              true
           }
       }
    }

    override fun pause(): Promise<Boolean> {
        return Promise.async {
            if (!tts.isSpeaking) {
                false
            } else {
                tts.stop()
                true
            }
        }
    }

    override fun resume(): Promise<Boolean> {
        TODO("Not yet implemented")
    }

    override fun getVoices(): Promise<Array<TextToSpeechVoice>> {
        return Promise.async {
            if (!initSuccess) {
                throw Error("$TAG Failed to initialize TextToSpeech.")
            }
            val voices = tts.voices
            val textToSpeechVoices = voices.map {
                TextToSpeechVoice(
                    name = it.name,
                    gender = "",
                    quality = it.quality.toString(),
                    identifier = it.name,
                )
            }
            textToSpeechVoices.toTypedArray()
        }

    }

    override fun addListener(event: EventName, listener: (word: String?) -> Unit): () -> Unit {
        Log.d("NitroTextToSpeech", "addEventListener: $event")
        return {}
    }


    override fun onInit(status: Int) {
        initSuccess = status == TextToSpeech.SUCCESS
        Log.d("NitroTextToSpeech", "onInit done with status: $status")
    }

    companion object {
        const val TAG = "NitroTTS"
    }

    override val memorySize: Long
        get() = 5
}
