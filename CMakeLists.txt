# Check that we aren't building in the source tree
IF(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
	MESSAGE(FATAL_ERROR "In-tree build is bad practice.")
ENDIF(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})

# settings
CMAKE_MINIMUM_REQUIRED(VERSION 3.6)
PROJECT(Chess-frontend)


# Set compiler and linker flags
SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "-g")
set(CMAKE_BUILD_TYPE Debug)

SET(SOURCES
	src/Game.cpp src/Game.hpp
	src/Board.cpp src/Board.hpp
	src/Piece.cpp src/Piece.hpp
	src/Pawn.cpp src/Pawn.hpp
	src/Rook.cpp src/Rook.hpp
	src/Knight.cpp src/Knight.hpp
	src/Bishop.cpp src/Bishop.hpp
	src/Queen.cpp src/Queen.hpp
	src/King.cpp src/King.hpp
	src/main.cpp)


ADD_EXECUTABLE(chess-gui ${SOURCES})
TARGET_LINK_LIBRARIES(chess-gui sfml-graphics sfml-window sfml-system)