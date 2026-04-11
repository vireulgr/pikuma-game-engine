param([switch]$configure)
# dependencies:
# lua 5.3.5 bulid with msvc 15 x64
# SDL2-2.0.22       with dynamic linking
# SDL2_image-2.8.10  with dynamic linking
# SDL2_mixer-2.5.2  with dynamic linking
# SDL2_ttf-2.0.15   with dynamic linking
# sol2 ver. 3.2+
# glm 0.9.9.4 (https://glm.g-truc.net)
# imgui 1.79 (https://github.com/ocornut/imgui)
$sysEnv = ConvertFrom-Json $(.\get-env.ps1)
$ninjaPath = $sysEnv.NinjaBuildPath

$cmakeCall = @('cmake', '-S', '.', '-B', './build', '-G', 'Ninja', 
          '-DCMAKE_EXPORT_COMPILE_COMMANDS=1', 
          '-DCMAKE_C_COMPILER=clang',
          '-DCMAKE_CXX_COMPILER=clang++',
          "-DCMAKE_MAKE_PROGRAM=$($sysEnv.NinjaBuildPath)")

if ($configure) {
  New-Item -ItemType Directory -Name 'build' -Force | Out-Null
  invoke-expression $($cmakeCall -join ' ')
  #cmake -S . -B ./build -G "Ninja" -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_MAKE_PROGRAM="$($sysEnv.NinjaBuildPath)"
}
else {
  cmake --build ./build
  Copy-Item "$($sysEnv.Sdl2.Core)\lib\x64\SDL2.dll" .\build\ -ErrorAction SilentlyContinue
  Copy-Item "$($sysEnv.Sdl2.Image)\lib\x64\SDL2_image.dll" .\build\ -ErrorAction SilentlyContinue
  Copy-Item "$($sysEnv.Sdl2.Mixer)\lib\x64\SDL2_mixer.dll" .\build\ -ErrorAction SilentlyContinue
  Copy-Item "$($sysEnv.Sdl2.Ttf)\lib\x64\SDL2_ttf.dll" .\build\ -ErrorAction SilentlyContinue
}

if (-not $(Test-path ./build/compile_commands.json)) {
  return;
}

if (-not $(Test-Path ./compile_commands.json) `
  -or $(Get-Item ./build/compile_commands.json).LastWriteTime -gt $(Get-Item ./compile_commands.json).LastWriteTime) {
  Copy-Item ./build/compile_commands.json ./ 
}
