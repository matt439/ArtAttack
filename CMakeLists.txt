cmake_minimum_required(VERSION 3.26)

# ArtAttack — a 2D game engine and the paint-shooter built on it.
# docs/design/ARCHITECTURE.md describes the shape this build moves toward;
# until the engine/game split, targets are converted in place.
project(ArtAttack LANGUAGES CXX RC)

include(cmake/settings.cmake)

# The module graph, enforced. Runs on every build.
add_custom_target(check_engine_includes ALL
    COMMAND "${CMAKE_COMMAND}"
        "-DENGINE_DIR=${CMAKE_CURRENT_SOURCE_DIR}/engine"
        -P "${CMAKE_CURRENT_SOURCE_DIR}/cmake/check_engine_includes.cmake"
    COMMENT "Checking that no engine file includes a game header"
    VERBATIM
)

enable_testing()

add_subdirectory(engine)
add_subdirectory(game)
add_subdirectory(samples/minimal)
add_subdirectory(tests/assets)
add_subdirectory(tests/collision)
add_subdirectory(tests/core)
add_subdirectory(tests/math)
add_subdirectory(tests/render)
add_subdirectory(tests/ui)
