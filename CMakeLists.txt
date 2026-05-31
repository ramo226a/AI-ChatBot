cmake_minimum_required(VERSION 3.10)
project(AI_ChatBot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(SQLite3 REQUIRED)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${SQLITE3_INCLUDE_DIR})

# Source files
set(SOURCES
    src/main.cpp
    src/chatbot.cpp
    src/database.cpp
    src/nlp.cpp
)

# Create executable
add_executable(chatbot ${SOURCES})

# Link libraries
target_link_libraries(chatbot ${SQLITE3_LIBRARIES})

# Set output directory
set_target_properties(chatbot PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
