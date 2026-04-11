### Study project of 2D game engine

Based on course from pikuma.com

Depends on 
- lua 5.3.5         static lib bulid with msvc 15 x64
- [SDL2 2.0.22](https://github.com/libsdl-org/SDL/releases/download/release-2.0.22/SDL2-devel-2.0.22-VC.zip)
- [SDL2_image 2.8.10](https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.10/SDL2_image-devel-2.8.10-VC.zip)
- SDL2_mixer 2.5.2  dynamic lib
- SDL2_ttf 2.0.15   dynamic lib
- [sol2](https://github.com/ThePhD/sol2) 3.2.1 header only
- [glm](https://glm.g-truc.net) 0.9.9.4 header only
- [imgui](https://github.com/ocornut/imgui) 1.79 header only

Project configured to build with cmake 3.30+, ninja-build and clang 2.20 on Windows &trade;

## Possible issue
[SDL_endian.h error: definition of builtin function _m_prefetch](https://github.com/libsdl-org/SDL/issues/13952)
```
diff --git a/include/SDL2/SDL_endian.h b/include/SDL2/SDL_endian.h
index 41ad0ce..f3ab18f 100644
--- a/include/SDL3/SDL_endian.h
+++ b/include/SDL3/SDL_endian.h
@@ -46,7 +46,7 @@
 #if defined(_MSC_VER) && (_MSC_VER >= 1400)
  /* As of Clang 11, '_m_prefetchw' is conflicting with the winnt.h's version,
      so we define the needed '_m_prefetch' here as a pseudo-header, until the issue is fixed. */
-#ifdef __clang__
+#if defined(__clang__) &&  !_SDL_HAS_BUILTIN(_m_prefetch)
  #ifndef __PRFCHWINTRIN_H
   #define __PRFCHWINTRIN_H
    static __inline__ void __attribute__((__always_inline__, __nodebug__))
```
