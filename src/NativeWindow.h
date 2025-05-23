#include <Windows.h>
#include <napi.h>

class NativeWindow: public Napi::ObjectWrap<NativeWindow> {
  HWND native;
public:
  NativeWindow(const Napi::CallbackInfo &info);
  Napi::Value show(const Napi::CallbackInfo &info);
  Napi::Value initializeUI(const Napi::CallbackInfo &info);
  static Napi::Object Initialize(Napi::Env, Napi::Object);
  ~NativeWindow();
};
