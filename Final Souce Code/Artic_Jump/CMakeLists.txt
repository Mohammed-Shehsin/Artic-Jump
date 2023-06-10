cmake_minimum_required(VERSION 3.5)

project(Artic_Jump LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "C:/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(Artic_Jump
    main.cpp
    Sprites.hpp
    Sprites.cpp
    Immovable.hpp
    Immovable.cpp
    Player.hpp
    Player.cpp
    Fireball.hpp
    Fireball.cpp
    Pickable.hpp
    Pickable.cpp
    Heart.hpp
    Heart.cpp
    Gold.hpp
    Gold.cpp
    utilities.hpp
    utilities.cpp
)

target_link_libraries(Artic_Jump sfml-graphics sfml-audio)
target_include_directories(Artic_Jump PRIVATE "C:/SFML-2.5.1/include")


install(TARGETS Artic_Jump
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(TARGETS Artic_Jump
    DESTINATION bin
)
