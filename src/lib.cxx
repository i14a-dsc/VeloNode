#include <napi.h>
#include "NativeWindow.h"

Napi::Object Initialize(Napi::Env env, Napi::Object exports) {
  return NativeWindow::Initialize(env, exports);
}

NODE_API_MODULE(velo, Initialize)

