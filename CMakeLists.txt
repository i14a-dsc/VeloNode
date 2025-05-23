cmake_minimum_required(VERSION 3.10)

project(velo CXX)



add_library(addon INTERFACE ${CMAKE_JS_SRC})
target_include_directories(addon INTERFACE ${CMAKE_JS_INC})
target_link_libraries(addon INTERFACE ${CMAKE_JS_LIB})

add_library(
  vulkan
  INTERFACE
)

target_include_directories(
  vulkan
  INTERFACE
  C:/VulkanSDK/1.4.313.0/Include
)

add_library(
    ${PROJECT_NAME}
    SHARED
    src/lib.cxx
    src/NativeWindow.cxx
)

add_library(
  imgui
  STATIC
  imgui/imgui.h
  imgui/imgui.cpp
  imgui/imgui_demo.cpp
  imgui/imgui_draw.cpp
  imgui/imgui_widgets.cpp
  imgui/imgui_tables.cpp
  imgui/backends/imgui_impl_vulkan.cpp
)

target_include_directories(
  imgui
  PUBLIC
  imgui
  imgui/backends
)

target_link_libraries(
  imgui
  PRIVATE
  vulkan
)

target_compile_definitions(
    ${PROJECT_NAME}
    PRIVATE
    NAPI_VERSION=8
)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    PREFIX ""
    SUFFIX ".node"
    CXX_STANDARD 20
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    addon
    delayimp
    imgui
    vulkan
)

if(MSVC AND CMAKE_JS_NODELIB_DEF AND CMAKE_JS_NODELIB_TARGET)
  # Generate node.lib
  execute_process(COMMAND ${CMAKE_AR} /def:${CMAKE_JS_NODELIB_DEF} /out:${CMAKE_JS_NODELIB_TARGET} ${CMAKE_STATIC_LINKER_FLAGS})
endif()
