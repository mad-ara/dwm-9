cmake_minimum_required(VERSION 3.13)
project(dwm VERSION 6.2 LANGUAGES C)

set(CMAKE_C_FLAGS "-std=c99 -pedantic -Wall -Wno-deprecated-declarations")

cmake_host_system_information(RESULT HOSTNAME QUERY HOSTNAME)

add_compile_definitions(
        VERSION="${CMAKE_PROJECT_VERSION}"
        _DEFAULT_SOURCE
        _BSD_SOURCE
        _POSIX_C_SOURCE=2
        XINERAMA
        HOST_${HOSTNAME}
)

include_directories(
        /usr/X11R6/include
        /usr/include/freetype2)

add_executable(dwm
        config.h
        drw.c
        drw.h
        dwm.c
        util.c
        util.h)

target_link_libraries(dwm
        X11
        Xinerama
        fontconfig
        Xft)