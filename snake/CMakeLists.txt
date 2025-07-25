
add_executable(snake
    snake.c
)

add_dependencies(snake ncurses_project)

target_link_libraries(snake PRIVATE
    ${CMAKE_BINARY_DIR}/ncurses-install/lib/libncurses++w.a
    ${CMAKE_BINARY_DIR}/ncurses-install/lib/libncursesw.a
    ${CMAKE_BINARY_DIR}/ncurses-install/lib/libpanelw.a
    ${CMAKE_BINARY_DIR}/ncurses-install/lib/libmenuw.a
    ${CMAKE_BINARY_DIR}/ncurses-install/lib/libformw.a
    ${CMAKE_BINARY_DIR}/ncurses-install/lib/libtinfow.a
)

target_include_directories(snake
    PRIVATE ${CMAKE_BINARY_DIR}/ncurses-install/include/ncursesw
    PRIVATE ${CMAKE_BINARY_DIR}/ncurses-install/include/
)

