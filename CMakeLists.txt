cmake_minimum_required(VERSION 3.26)

# ArtAttack — a 2D game engine and the paint-shooter built on it.
# docs/design/ARCHITECTURE.md describes the shape this build moves toward;
# until the engine/game split, targets are converted in place.
project(ArtAttack LANGUAGES CXX RC)

include(cmake/settings.cmake)

enable_testing()

add_subdirectory(engine)
add_subdirectory(ArtAttack)
add_subdirectory(tests/core)
add_subdirectory(tests/math)
