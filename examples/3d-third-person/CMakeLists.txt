cmake_minimum_required(VERSION 3.16)

if (WIN32)
    add_compile_definitions(LOOPXIA_PLATFORM_WINDOWS WIN32_LEAN_AND_MEAN )
endif (WIN32)

if(MSVC)
    # Default to statically-linked runtime.
    if("${MSVC_RUNTIME}" STREQUAL "")
      set(MSVC_RUNTIME "static")
    endif()

    #I want to link statically to the runtime library. This will help in sharing the game with others
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

endif()

if(CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo;MinSizeRel" CACHE STRING "" FORCE)
endif()

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE) #link time optimization


#set glfw to NOT use dynamic runtime and not build unnecessary stuff, do this before declaring projects
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE) #under no circumstance we want this to happen so please cmake DON'T compile my project using shared libs


if(MSVC)
add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)

project ("third_person")

set(LOOPXIA_INCLUDE_DIRS "include/loopxia")

# Add source to this project's executable.
add_executable (third_person main.cpp )

copy_engine_assets_dev(third_person "${CMAKE_CURRENT_BINARY_DIR}")

#set exe type to be windowed
if(MSVC)
  set_target_properties(third_person PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET third_person PROPERTY CXX_STANDARD 20)
endif()

target_precompile_headers(third_person
  PUBLIC
  PRIVATE
)

find_package(OpenGL REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS} )

target_include_directories(third_person PRIVATE
    ${LOOPXIA_INCLUDE_DIRS}
)

target_link_libraries(third_person PRIVATE loopxia-engine)

message("Include directories: ${loopxia-engine_INCLUDE_DIRS}")

set(targets third_person)  # List of target names
foreach(target ${targets})
    get_target_property(INCLUDE_DIRS ${target} INCLUDE_DIRECTORIES)
    message(STATUS "Include directories for target ${target}: ${INCLUDE_DIRS}")
endforeach()

message(STATUS "Include directories for target: third_person: $<TARGET_PROPERTY:third_person,INCLUDE_DIRECTORIES>")