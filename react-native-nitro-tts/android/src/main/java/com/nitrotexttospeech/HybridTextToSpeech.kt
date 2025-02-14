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
import android.speech.tts.UtteranceProgressListener
import android.speech.tts.Voice
import com.margelo.nitro.NitroModules
import java.util.Locale


class HybridTextToSpeech: HybridTextToSpeechSpec(), TextToSpeech.OnInitListener {
    var context = NitroModules.applicationContext
    private var tts = TextToSpeech(context,this)
    private var initSuccess = false
    private var currentText = ""

    override fun speak(text: String, options: TextToSpeechOptions?): Promise<Unit> {
        return Promise.async {
            if (!initSuccess) {
                throw Error("$TAG: Failed to initialize TextToSpeech.")
            }
            currentText = text
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
            val utteranceId = "utterance_${System.currentTimeMillis()}"
            tts.speak(text, TextToSpeech.QUEUE_FLUSH, params, utteranceId)
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

        tts.setOnUtteranceProgressListener(object : UtteranceProgressListener() {
            override fun onStart(utteranceId: String?) {
                Log.i(TAG,"Started $utteranceId")
                if (event == EventName.START) {
                    listener(null)
                }
            }

            override fun onDone(utteranceId: String?) {
                Log.i(TAG,"Finished $utteranceId")
                if (event == EventName.FINISH) {
                    listener(null)
                }
            }

            override fun onRangeStart(utteranceId: String?, start: Int, end: Int, frame: Int) {
                if (event == EventName.WORD) {
                    val word = getWordFromRange(start, end)
                    listener(word)
                }
            }

            override fun onStop(utteranceId: String?, interrupted: Boolean) {
                Log.i(TAG,"Stopped $utteranceId")
                super.onStop(utteranceId, interrupted)
                tts.shutdown()
            }

            @Deprecated("Deprecated in Java")
            override fun onError(utteranceId: String?) {

            }
        })
        return {}
    }

    private fun getWordFromRange(start: Int, end: Int): String {
        return try {
            currentText.substring(start, end)
        } catch (e: Exception) {
            Log.e(TAG, "Error extracting word: ${e.message}")
            ""
        }
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
