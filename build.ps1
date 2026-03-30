param([switch]$configure)
# dependencies:
# lua 5.3.5 bulid with msvc 15 x64
# SDL2-2.0.14       with dynamic linking
# SDL2_image-2.5.3  with dynamic linking
# SDL2_mixer-2.5.2  with dynamic linking
# SDL2_ttf-2.0.15   with dynamic linking
# sol2 ver. 3.2+
# glm (see libs folder)

if ($configure) {
  cmake -S . -B ./build -G "Ninja" -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_MAKE_PROGRAM="E:\Portable\Ninja\ninja.exe"
  Copy-Item ./build/compile_commands.json ./
}
else {
  cmake --build ./build
  Copy-Item E:\code\Thirdparty\SDL2-2.0.14\lib\x64\SDL2.dll .\build\ -ErrorAction SilentlyContinue
  Copy-Item E:\code\Thirdparty\SDL2_image-2.5.3\lib\x64\SDL2_image.dll .\build\ -ErrorAction SilentlyContinue
  Copy-Item E:\code\Thirdparty\SDL2_mixer-2.5.2\lib\x64\SDL2_mixer.dll .\build\ -ErrorAction SilentlyContinue
  Copy-Item E:\code\Thirdparty\SDL2_ttf-2.0.15\lib\x64\SDL2_ttf.dll .\build\ -ErrorAction SilentlyContinue
}
