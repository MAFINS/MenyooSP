cmake_minimum_required(VERSION 3.20)

project(Menyoo CXX)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/source)

message("\nFetching modules")

include(scripts/pugixml.cmake)
include(scripts/dirent.cmake)
include(scripts/simpleini.cmake)


file(GLOB_RECURSE SRC_MAIN
    "${SRC_DIR}/**.hpp"
    "${SRC_DIR}/**.h"
    "${SRC_DIR}/**.cpp"
    "${SRC_DIR}/**.cc"
    "${SRC_DIR}/**.cxx"
    "${SRC_DIR}/**.rc"
)

add_library(Menyoo MODULE ${SRC_MAIN})

source_group(TREE ${SRC_DIR} PREFIX "source" FILES ${SRC_MAIN} )

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(TARGET Menyoo PROPERTY CXX_STANDARD 17)

target_include_directories(Menyoo PRIVATE 
    ${SRC_DIR}
    ${dirent_SOURCE_DIR}/include
    ${simpleini_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/vendor
)
target_link_libraries(Menyoo PRIVATE pugixml ${PROJECT_SOURCE_DIR}/vendor/ScriptHookV/SDK/lib/ScriptHookV.lib)

set_target_properties(Menyoo PROPERTIES SUFFIX ".asi")


add_compile_definitions(Menyoo _CRT_SECURE_NO_WARNINGS)
add_compile_definitions(Menyoo MENYOO_CURRENT_VER_="1.17.3")
add_compile_definitions(Menyoo GAME_PLAYERCOUNT=32)

