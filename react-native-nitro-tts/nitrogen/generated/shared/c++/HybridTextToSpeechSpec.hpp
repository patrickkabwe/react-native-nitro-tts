///
/// HybridTextToSpeechSpec.hpp
/// This file was generated by nitrogen. DO NOT MODIFY THIS FILE.
/// https://github.com/mrousavy/nitro
/// Copyright © 2024 Marc Rousavy @ Margelo
///

#pragma once

#if __has_include(<NitroModules/HybridObject.hpp>)
#include <NitroModules/HybridObject.hpp>
#else
#error NitroModules cannot be found! Are you sure you installed NitroModules properly?
#endif

// Forward declaration of `TextToSpeechOptions` to properly resolve imports.
namespace margelo::nitro::nitrotexttospeech { struct TextToSpeechOptions; }
// Forward declaration of `TextToSpeechVoice` to properly resolve imports.
namespace margelo::nitro::nitrotexttospeech { struct TextToSpeechVoice; }
// Forward declaration of `EventName` to properly resolve imports.
namespace margelo::nitro::nitrotexttospeech { enum class EventName; }

#include <NitroModules/Promise.hpp>
#include <string>
#include <optional>
#include "TextToSpeechOptions.hpp"
#include <vector>
#include "TextToSpeechVoice.hpp"
#include <functional>
#include "EventName.hpp"

namespace margelo::nitro::nitrotexttospeech {

  using namespace margelo::nitro;

  /**
   * An abstract base class for `TextToSpeech`
   * Inherit this class to create instances of `HybridTextToSpeechSpec` in C++.
   * You must explicitly call `HybridObject`'s constructor yourself, because it is virtual.
   * @example
   * ```cpp
   * class HybridTextToSpeech: public HybridTextToSpeechSpec {
   * public:
   *   HybridTextToSpeech(...): HybridObject(TAG) { ... }
   *   // ...
   * };
   * ```
   */
  class HybridTextToSpeechSpec: public virtual HybridObject {
    public:
      // Constructor
      explicit HybridTextToSpeechSpec(): HybridObject(TAG) { }

      // Destructor
      virtual ~HybridTextToSpeechSpec() { }

    public:
      // Properties
      

    public:
      // Methods
      virtual std::shared_ptr<Promise<void>> speak(const std::string& text, const std::optional<TextToSpeechOptions>& options) = 0;
      virtual std::shared_ptr<Promise<bool>> stop() = 0;
      virtual std::shared_ptr<Promise<bool>> pause() = 0;
      virtual std::shared_ptr<Promise<bool>> resume() = 0;
      virtual std::shared_ptr<Promise<std::vector<TextToSpeechVoice>>> getVoices() = 0;
      virtual std::function<void()> addEventListener(EventName event, const std::function<void(const std::optional<std::string>& /* word */)>& listener) = 0;

    protected:
      // Hybrid Setup
      void loadHybridMethods() override;

    protected:
      // Tag for logging
      static constexpr auto TAG = "TextToSpeech";
  };

} // namespace margelo::nitro::nitrotexttospeech
