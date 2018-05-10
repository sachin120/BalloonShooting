cmake_minimum_required(VERSION 2.6)
project ("Balloon Shooting")

add_definitions("-std=c++11")

set(SRC src/BalloonShoot.cpp src/Balloon.cpp src/Bow.cpp src/Arrow.cpp src/CreateHorde.cpp src/TextureHolder.cpp)

add_executable(shooting-app ${SRC})

target_link_libraries(shooting-app sfml-graphics)
target_link_libraries(shooting-app sfml-window)
target_link_libraries(shooting-app sfml-system)
target_link_libraries(shooting-app sfml-audio)
