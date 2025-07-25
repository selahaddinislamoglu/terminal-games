cmake_minimum_required(VERSION 3.14)
project(terminal-games)

include(ExternalProject)

# External project: build ncurses using its Autotools system
ExternalProject_Add(
    ncurses_project
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/ncurses
    CONFIGURE_COMMAND ${CMAKE_SOURCE_DIR}/external/ncurses/configure --prefix=${CMAKE_BINARY_DIR}/ncurses-install --with-termlib
    BUILD_COMMAND make
    INSTALL_COMMAND make install
)

add_subdirectory(snake)