#include <jni.h>
#include "NitroTextToSpeechOnLoad.hpp"

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void*) {
  return margelo::nitro::nitrotexttospeech::initialize(vm);
}
