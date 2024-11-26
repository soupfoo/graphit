cmake_minimum_required(VERSION 3.30)

# C++ standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Helps language servers find libraries.
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

project(
  GraphIt
  VERSION 0.0.1
  LANGUAGES CXX)

# Aliases.
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(EXECUTABLE_NAME graphit)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

add_executable(${EXECUTABLE_NAME})

# External libraries:
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

if(WIN32)
    add_custom_command(
        TARGET main
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()

target_link_libraries(${EXECUTABLE_NAME} PRIVATE sfml-graphics)

# target_compile_features(${EXECUTABLE_NAME} PRIVATE cxx_std_20)

# Grab source files from src directory.
add_subdirectory(${SOURCE_DIR})

# Include headers inside the src folder.
include_directories(${SOURCE_DIR})
