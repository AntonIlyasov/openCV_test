cmake_minimum_required(VERSION 3.2)
project(open_img)

set(CMAKE_CXX_STANDARD 17)

# Найти библиотеки Boost
find_package(Boost REQUIRED COMPONENTS system)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
else()
    message(FATAL_ERROR "Boost not found")
endif()

# Найти OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Найдите пакет ncurses
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# Добавьте эту строку, чтобы линковаться с pthread
find_package(Threads REQUIRED)


add_executable(open_img main.cpp)
target_link_libraries( open_img ${OpenCV_LIBS} ${CURSES_LIBRARIES} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})