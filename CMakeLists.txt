cmake_minimum_required(VERSION 3.10)
project(YouTubeMP3Downloader)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Try to find CURL package (optional, for future enhancements)
find_package(CURL QUIET)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.cpp
    src/youtube_downloader.cpp
)

# Create executable
add_executable(yt-mp3 ${SOURCES})

# Link libraries only if CURL is found
if(CURL_FOUND)
    target_link_libraries(yt-mp3 PRIVATE ${CURL_LIBRARIES})
    target_include_directories(yt-mp3 PRIVATE ${CURL_INCLUDE_DIRS})
    message(STATUS "CURL found - will be used for future enhancements")
else()
    message(STATUS "CURL not found - application will work with yt-dlp and ffmpeg")
endif()

# Installation
install(TARGETS yt-mp3 DESTINATION bin)
