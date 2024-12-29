///
/// JHybridTextToSpeechSpec.cpp
/// This file was generated by nitrogen. DO NOT MODIFY THIS FILE.
/// https://github.com/mrousavy/nitro
/// Copyright © 2024 Marc Rousavy @ Margelo
///

#include "JHybridTextToSpeechSpec.hpp"

// Forward declaration of `TextToSpeechVoice` to properly resolve imports.
namespace margelo::nitro::nitrotexttospeech { struct TextToSpeechVoice; }
// Forward declaration of `TextToSpeechOptions` to properly resolve imports.
namespace margelo::nitro::nitrotexttospeech { struct TextToSpeechOptions; }
// Forward declaration of `EventName` to properly resolve imports.
namespace margelo::nitro::nitrotexttospeech { enum class EventName; }

#include <NitroModules/Promise.hpp>
#include <NitroModules/JPromise.hpp>
#include <vector>
#include "TextToSpeechVoice.hpp"
#include "JTextToSpeechVoice.hpp"
#include <string>
#include <functional>
#include "JFunc_void.hpp"
#include <optional>
#include "TextToSpeechOptions.hpp"
#include "JTextToSpeechOptions.hpp"
#include "EventName.hpp"
#include "JEventName.hpp"
#include "JFunc_void_std__optional_std__string_.hpp"

namespace margelo::nitro::nitrotexttospeech {

  jni::local_ref<JHybridTextToSpeechSpec::jhybriddata> JHybridTextToSpeechSpec::initHybrid(jni::alias_ref<jhybridobject> jThis) {
    return makeCxxInstance(jThis);
  }

  void JHybridTextToSpeechSpec::registerNatives() {
    registerHybrid({
      makeNativeMethod("initHybrid", JHybridTextToSpeechSpec::initHybrid),
    });
  }

  size_t JHybridTextToSpeechSpec::getExternalMemorySize() noexcept {
    static const auto method = _javaPart->getClass()->getMethod<jlong()>("getMemorySize");
    return method(_javaPart);
  }

  // Properties
  

  // Methods
  std::shared_ptr<Promise<void>> JHybridTextToSpeechSpec::speak(const std::string& text, const std::optional<TextToSpeechOptions>& options) {
    static const auto method = _javaPart->getClass()->getMethod<jni::local_ref<JPromise::javaobject>(jni::alias_ref<jni::JString> /* text */, jni::alias_ref<JTextToSpeechOptions> /* options */)>("speak");
    auto __result = method(_javaPart, jni::make_jstring(text), options.has_value() ? JTextToSpeechOptions::fromCpp(options.value()) : nullptr);
    return [&]() {
      auto __promise = Promise<void>::create();
      __result->cthis()->addOnResolvedListener([=](const jni::alias_ref<jni::JObject>& /* unit */) {
        __promise->resolve();
      });
      __result->cthis()->addOnRejectedListener([=](const jni::alias_ref<jni::JThrowable>& __throwable) {
        jni::JniException __jniError(__throwable);
        __promise->reject(std::make_exception_ptr(__jniError));
      });
      return __promise;
    }();
  }
  std::shared_ptr<Promise<bool>> JHybridTextToSpeechSpec::stop() {
    static const auto method = _javaPart->getClass()->getMethod<jni::local_ref<JPromise::javaobject>()>("stop");
    auto __result = method(_javaPart);
    return [&]() {
      auto __promise = Promise<bool>::create();
      __result->cthis()->addOnResolvedListener([=](const jni::alias_ref<jni::JObject>& __boxedResult) {
        auto __result = jni::static_ref_cast<jni::JBoolean>(__boxedResult);
        __promise->resolve(static_cast<bool>(__result->value()));
      });
      __result->cthis()->addOnRejectedListener([=](const jni::alias_ref<jni::JThrowable>& __throwable) {
        jni::JniException __jniError(__throwable);
        __promise->reject(std::make_exception_ptr(__jniError));
      });
      return __promise;
    }();
  }
  std::shared_ptr<Promise<bool>> JHybridTextToSpeechSpec::pause() {
    static const auto method = _javaPart->getClass()->getMethod<jni::local_ref<JPromise::javaobject>()>("pause");
    auto __result = method(_javaPart);
    return [&]() {
      auto __promise = Promise<bool>::create();
      __result->cthis()->addOnResolvedListener([=](const jni::alias_ref<jni::JObject>& __boxedResult) {
        auto __result = jni::static_ref_cast<jni::JBoolean>(__boxedResult);
        __promise->resolve(static_cast<bool>(__result->value()));
      });
      __result->cthis()->addOnRejectedListener([=](const jni::alias_ref<jni::JThrowable>& __throwable) {
        jni::JniException __jniError(__throwable);
        __promise->reject(std::make_exception_ptr(__jniError));
      });
      return __promise;
    }();
  }
  std::shared_ptr<Promise<bool>> JHybridTextToSpeechSpec::resume() {
    static const auto method = _javaPart->getClass()->getMethod<jni::local_ref<JPromise::javaobject>()>("resume");
    auto __result = method(_javaPart);
    return [&]() {
      auto __promise = Promise<bool>::create();
      __result->cthis()->addOnResolvedListener([=](const jni::alias_ref<jni::JObject>& __boxedResult) {
        auto __result = jni::static_ref_cast<jni::JBoolean>(__boxedResult);
        __promise->resolve(static_cast<bool>(__result->value()));
      });
      __result->cthis()->addOnRejectedListener([=](const jni::alias_ref<jni::JThrowable>& __throwable) {
        jni::JniException __jniError(__throwable);
        __promise->reject(std::make_exception_ptr(__jniError));
      });
      return __promise;
    }();
  }
  std::shared_ptr<Promise<std::vector<TextToSpeechVoice>>> JHybridTextToSpeechSpec::getVoices() {
    static const auto method = _javaPart->getClass()->getMethod<jni::local_ref<JPromise::javaobject>()>("getVoices");
    auto __result = method(_javaPart);
    return [&]() {
      auto __promise = Promise<std::vector<TextToSpeechVoice>>::create();
      __result->cthis()->addOnResolvedListener([=](const jni::alias_ref<jni::JObject>& __boxedResult) {
        auto __result = jni::static_ref_cast<jni::JArrayClass<JTextToSpeechVoice>>(__boxedResult);
        __promise->resolve([&]() {
          size_t __size = __result->size();
          std::vector<TextToSpeechVoice> __vector;
          __vector.reserve(__size);
          for (size_t __i = 0; __i < __size; __i++) {
            auto __element = __result->getElement(__i);
            __vector.push_back(__element->toCpp());
          }
          return __vector;
        }());
      });
      __result->cthis()->addOnRejectedListener([=](const jni::alias_ref<jni::JThrowable>& __throwable) {
        jni::JniException __jniError(__throwable);
        __promise->reject(std::make_exception_ptr(__jniError));
      });
      return __promise;
    }();
  }
  std::function<void()> JHybridTextToSpeechSpec::addEventListener(EventName event, const std::function<void(const std::optional<std::string>& /* word */)>& listener) {
    static const auto method = _javaPart->getClass()->getMethod<jni::local_ref<JFunc_void::javaobject>(jni::alias_ref<JEventName> /* event */, jni::alias_ref<JFunc_void_std__optional_std__string_::javaobject> /* listener */)>("addEventListener");
    auto __result = method(_javaPart, JEventName::fromCpp(event), JFunc_void_std__optional_std__string_::fromCpp(listener));
    return __result->toCpp();
  }

} // namespace margelo::nitro::nitrotexttospeech
