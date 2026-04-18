cmake_minimum_required(VERSION 3.30)

project(2dgameengine VERSION 0.0.1)

add_executable(engine)

target_sources(engine PRIVATE
  src/main.cpp
  src/game.cpp
  src/resources/resource.cpp
  src/resources/sound-resource.cpp
  src/resources/image-resource.cpp
  src/resources/font-resource.cpp
  src/resources/resource-manager.cpp
  src/objects/simple-object.cpp
)

target_compile_options(engine PRIVATE -Wall -Wextra)
target_compile_features(engine PRIVATE cxx_std_17)

if (WIN32)
  execute_process(
    COMMAND pwsh.exe -File "${CMAKE_CURRENT_SOURCE_DIR}/get-env.ps1"
    OUTPUT_VARIABLE ENV_SCRIPT_STDOUT
    ERROR_VARIABLE ENV_SCRIPT_STDERROR
    RESULT_VARIABLE ENV_SCRIPT_RESULT
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  if (ENV_SCRIPT_RESULT EQUAL 0)
    message(STATUS "Env script finished successfully")
    string(JSON SDL2_CORE_HOME GET "${ENV_SCRIPT_STDOUT}" "Sdl2" "Core")
    string(JSON SDL2_IMAGE_HOME GET "${ENV_SCRIPT_STDOUT}" "Sdl2" "Image")
    string(JSON SDL2_MIXER_HOME  GET "${ENV_SCRIPT_STDOUT}" "Sdl2" "Mixer")
    string(JSON SDL2_TTF_HOME GET "${ENV_SCRIPT_STDOUT}" "Sdl2" "Ttf")
    string(JSON MY_THIRDPARTY_LIBS_REL_X64  GET "${ENV_SCRIPT_STDOUT}" "LibsReleaseX64") # for lua static lib
    string(JSON MY_THIRDPARTY_LIBS_DEB_X64  GET "${ENV_SCRIPT_STDOUT}" "LibsDebugX64") # for lua static.lib
    string(JSON MY_THIRDPARTY_INCLUDE GET "${ENV_SCRIPT_STDOUT}" "Include") # for lua headers (used by sol)
    # string(JSON LUA_INCLUDE GET "${ENV_SCRIPT_STDOUT}" "Lua" "include") # for lua headers (used by sol)
  else()
    message(FATAL_ERROR "Cannot determine libraries location ${ENV_SCRIPT_STDERROR}")
  endif()

  target_link_libraries(engine PRIVATE
    "${SDL2_CORE_HOME}/lib/x64/SDL2.lib"
    "${SDL2_CORE_HOME}/lib/x64/SDL2main.lib"
    "${SDL2_IMAGE_HOME}/lib/x64/SDL2_image.lib"
    "${SDL2_MIXER_HOME}/lib/x64/SDL2_mixer.lib"
    "${SDL2_TTF_HOME}/lib/x64/SDL2_ttf.lib"
    #"${MY_THIRDPARTY_LIBS_DEB_X64}/lua53.lib"
    "${MY_THIRDPARTY_LIBS_DEB_X64}/lua-5.4.4.lib"
  )
  target_include_directories(engine PRIVATE 
    "${SDL2_CORE_HOME}/include"
    "${SDL2_IMAGE_HOME}/include"
    "${SDL2_MIXER_HOME}/include"
    "${SDL2_TTF_HOME}/include"
    "${MY_THIRDPARTY_INCLUDE}"
    "libs/"
  )
elseif (UNIX)
  message(FATAL_ERROR "Unix platforms are not supported, sorry")
endif()
