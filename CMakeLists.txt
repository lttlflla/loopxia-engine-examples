cmake_minimum_required(VERSION 3.16)

if (WIN32)
    add_compile_definitions(LOOPXIA_PLATFORM_WINDOWS WIN32_LEAN_AND_MEAN )
endif (WIN32)

if(MSVC)
    # Default to statically-linked runtime.
    if("${MSVC_RUNTIME}" STREQUAL "")
      set(MSVC_RUNTIME "static")
    endif()
endif()

#I want to link statically to the runtime library. This will help in sharing the game with others
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE) #link time optimization


#add engine and examples
add_subdirectory(loopxia-engine)
add_subdirectory(examples/3d-third-person)


if(MSVC)
add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)


