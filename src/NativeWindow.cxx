#include "NativeWindow.h"
#include "napi.h"
#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_vulkan.h>

NativeWindow::NativeWindow(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<NativeWindow>(info) {
  WNDCLASS windowClass{.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH),
                       .lpfnWndProc = DefWindowProc,
                       .hInstance = nullptr,
                       .hCursor = LoadCursor(nullptr, IDC_ARROW),
                       .style = CS_HREDRAW | CS_VREDRAW,
                       .lpszClassName = "NativeWindow"};
  RegisterClass(&windowClass);
  native =
      CreateWindow("NativeWindow", nullptr, WS_POPUP, 0, 0,
                   GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
                   nullptr, nullptr, nullptr, nullptr);
}

Napi::Object NativeWindow::Initialize(Napi::Env env, Napi::Object exports) {
  Napi::Function JsConstructor = DefineClass(
      env, "NativeWindow",
      {
        InstanceMethod<&NativeWindow::show>("show", static_cast<napi_property_attributes>(napi_enumerable)),
        InstanceMethod<&NativeWindow::initializeUI>("initializeUI", static_cast<napi_property_attributes>(napi_enumerable))

      });
  Napi::FunctionReference *constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent(JsConstructor);
  exports.Set("NativeWindow", JsConstructor);

  env.SetInstanceData(constructor);
  return exports;
}


Napi::Value NativeWindow::show(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();
  if (ShowWindow(native, SW_MINIMIZE)) {
    throw Napi::Error::New(env, "Window Already showed");
  }
  bool a;
  if(ImGui::ShowDemoWindow(&a); !a) {
    throw Napi::Error::New(env, "Failed to render UI");
  }
  return env.Undefined();
}

Napi::Value NativeWindow::initializeUI(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();
  
  ImGui_ImplWin32_Init(native);
  return env.Undefined();
}

NativeWindow::~NativeWindow() { DestroyWindow(native); }
