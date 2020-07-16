cmake_minimum_required(VERSION 3.1)
project(opencv-sandbox CXX)

file(COPY ${CMAKE_SOURCE_DIR}/images/ DESTINATION ${PROJECT_BINARY_DIR}/images/)
add_definitions(-DRESOURCE_DIR="${PROJECT_BINARY_DIR}/resource/")

set(SOURCES
    main.cpp
)

add_executable(Main
    ${SOURCES}
    ${HEADERS}
)

find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    target_include_directories(Main PUBLIC ${OpenCV_INCLUDE_DIRS})
    target_link_libraries(Main ${OpenCV_LIBS})
 endif(OpenCV_FOUND)