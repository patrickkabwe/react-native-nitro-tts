//
//  HybridTextToSpeech.swift
//  NitroTextToSpeech
//
//  Created by Patrick Kabwe on 29/12/2024.
//

import Foundation
import AVFAudio
import NitroModules

typealias TextToSpeechListener = (String?) -> Void

final class HybridTextToSpeech: HybridTextToSpeechSpec {
    private let textToSpeechService: TextToSpeechService
    
    var listeners: Dictionary<EventName, TextToSpeechListener> = [:]

    init(textToSpeechSrv: TextToSpeechService = TextToSpeechService()) {
        self.textToSpeechService = textToSpeechSrv
        super.init()
        self.textToSpeechService.delegate = self
    }

    func speak(text: String, options: TextToSpeechOptions?) throws -> Promise<Void> {
        return Promise.async { [weak self] in
            guard let self = self else { throw RuntimeError.error(withMessage: "TextToSpeech is not initialized") }
            try await self.textToSpeechService.speak(string: text, with: options)
        }
    }
    
    func getVoices() throws -> Promise<[TextToSpeechVoice]> {
        return Promise.async { [weak self] in
            guard let self else { return [] }
            return await self.textToSpeechService.getVoices()
        }
    }

    func stop() throws -> Promise<Bool> {
        return Promise.async { [weak self] in
            guard let self = self else { throw RuntimeError.error(withMessage: "TextToSpeech is not initialized") }
            return await self.textToSpeechService.stop(at: .immediate)
        }
    }
    
    func pause() throws -> Promise<Bool> {
        return Promise.async { [weak self] in
            guard let self = self else { throw RuntimeError.error(withMessage: "TextToSpeech is not initialized")}
            return await self.textToSpeechService.pause(at: .immediate)
        }
    }

    func resume() throws -> Promise<Bool> {
        return Promise.async { [weak self] in
            guard let self = self else { throw RuntimeError.error(withMessage: "TextToSpeech is not initialized") }
            return await self.textToSpeechService.resume()
        }
    }

    
    func addListener(event: EventName, listener: @escaping ((_ word: String?) -> Void)) throws -> (() -> Void) {
        listeners[event] = listener
        
        return { [weak self] in
            self?.listeners[event] = nil
        }
    }
}

extension HybridTextToSpeech: TextToSpeechDelegate {
    internal func textToSpeechDidStart(_ synthesizer: AVSpeechSynthesizer) {
        notifyListeners(withEvent: .start, nil)
    }
    
    internal func textToSpeechDidFinish(_ synthesizer: AVSpeechSynthesizer) {
        notifyListeners(withEvent: .finish, nil)
    }

    internal func textToSpeechDidReadText(_ synthesizer: AVSpeechSynthesizer, word: String) {
        notifyListeners(withEvent: .word, word)
    }
    
    private func notifyListeners(withEvent event: EventName, _ data: String?) {
        DispatchQueue.main.async { [weak self] in
            guard let self = self else { return }
            listeners[event]?(data)
        }
    }
}
