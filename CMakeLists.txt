cmake_minimum_required(VERSION 3.24)
project(Chess VERSION 0.1.0 LANGUAGES CXX)
add_library(Chess SHARED
    "src/Bishop.cpp"
    "src/Board.cpp"
    "src/Game.cpp"
    "src/King.cpp"
    "src/Knight.cpp"
    "src/MinimaxBot.cpp"
    "src/Move.cpp"
    "src/NeuralBot.cpp"
    "src/Pawn.cpp"
    "src/Point.cpp"
    "src/Queen.cpp"
    "src/Rook.cpp"
)
target_include_directories(Chess PUBLIC include)
find_package(Boost REQUIRED)
target_link_libraries(Chess PUBLIC ${Boost_LIBRARIES})
target_include_directories(Chess PUBLIC ${Boost_INCLUDE_DIRS})
find_package(Torch QUIET)
if(${Torch_FOUND})
    target_link_libraries(Chess PUBLIC ${TORCH_LIBRARIES})
    target_include_directories(Chess PRIVATE ${TORCH_INCLUDE_DIRS})
    target_compile_definitions(Chess PUBLIC HAVE_TORCH)
endif()
option(BUILD_TESTS "Whether to build tests" ON)
if(BUILD_TESTS)
    add_executable(ConsoleChess
        "tests/ConsoleChess.cpp"
    )
    target_link_libraries(ConsoleChess PUBLIC Chess)
endif()