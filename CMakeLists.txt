cmake_minimum_required(VERSION 3.30)

project(2dgameengine)

add_executable(engine)

target_sources(engine PRIVATE
  src/main.cpp
)

target_compile_options(engine PRIVATE -Wall -Wextra)
target_compile_features(engine PRIVATE cxx_std_17)


if (WIN32)
  set(SDL2_CORE_HOME "E:/code/Thirdparty/SDL2-2.0.14")
  set(SDL2_IMAGE_HOME "E:/code/Thirdparty/SDL2_image-2.5.3")
  set(SDL2_MIXER_HOME "E:/code/Thirdparty/SDL2_mixer-2.5.2")
  set(SDL2_TTF_HOME "E:/code/Thirdparty/SDL2_ttf-2.0.15")
  #set(LUA_HOME "E:/code/Thirdparty/lua-5.3.5_win64_vc16_lib")
  set(MY_THIRDPARTY_LIBS_REL_X64 "E:/code/Thirdparty/Libs/Release_x64")
  set(MY_THIRDPARTY_INCLUDES "E:/code/Thirdparty/Include")
  #set(MY_THIRDPARTY_LIBS_DEB_X64 "E:/code/Thirdparty/Libs/Debug_x64")

  target_link_libraries(engine PRIVATE
    "${SDL2_CORE_HOME}/lib/x64/SDL2.lib"
    "${SDL2_CORE_HOME}/lib/x64/SDL2main.lib"
    "${SDL2_IMAGE_HOME}/lib/x64/SDL2_image.lib"
    "${SDL2_MIXER_HOME}/lib/x64/SDL2_mixer.lib"
    "${SDL2_TTF_HOME}/lib/x64/SDL2_ttf.lib"
    "${MY_THIRDPARTY_LIBS_REL_X64}/lua53.lib"
  )
  target_include_directories(engine PRIVATE 
    "${SDL2_CORE_HOME}/include"
    "${SDL2_IMAGE_HOME}/include"
    "${SDL2_MIXER_HOME}/include"
    "${SDL2_TTF_HOME}/include"
    "${MY_THIRDPARTY_INCLUDES}"
    "libs/"
  )
elseif (UNIX)
endif()


