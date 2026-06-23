### Study project of 2D game engine

Based on course from pikuma.com

Depends on 
- lua 5.3.5   [5.4.8](https://sourceforge.net/projects/luabinaries/files/5.4.8/Windows%20Libraries/Dynamic/lua-5.4.8_Win64_dllw6_lib.zip/download)   static lib bulid with msvc 15 x64
- [SDL2 2.0.22](https://github.com/libsdl-org/SDL/releases/download/release-2.0.22/SDL2-devel-2.0.22-VC.zip)
- [SDL2_image 2.8.10](https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.10/SDL2_image-devel-2.8.10-VC.zip)
- [SDL2_mixer 2.6.0](https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.6.0/SDL2_mixer-devel-2.6.0-VC.zip)
- [SDL2_ttf 2.0.15](https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.0.15/SDL2_ttf-devel-2.0.15-VC.zip)
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

ECS implementation
1) Component Pool
- Registry class
- Pool of components
- Two axes of components in pool (by component type and by component ID)
2) Pool of components
- Implementation as wrapper around std::vector
3) Implementing the Pool class
- coding Registry (only pool member and numEntities)
- coding Pool
- coding IPool
4) Registry systems and entity signatures
- in registry class a vector of signatures of entities
- in registry class vector of systems
- discuss registry class interface
5) Entity creation and management
- focus on add entity and add component and add component to system
- vector of components to add and to remove
- discuss Registry::CreateEntity method
- coding Registry::CreateEntity method
- coding Registry::Update method (WIP)
- discuss Registry::addEntityToSystem method and add signature to class
- discuss template<typename T> Registry::addComponent method 
6) Function templates to manage components
- discuss this video context and process of adding an entity to system
- discuss template <typename T>Registry::addComponent and its template nature
- Registry::addComponent must accept parameters for component constructor (which may be of any number and types)
- all component management methods must be templates
- example of using component management methods
- C++ template syntax details for declaring a variadic template class member
7) Add component function
- coding template \<typename T\>Registry::addComponent
8)
- coding template \<typename T\>Registry::addComponent
9) Remembering to Define nextId
- Initialize int BaseComponent::nextId in ECS.cpp file
10) implementing System funcitons
- overview of system management functions
- system management functions must be templates
- coding template function definitions
