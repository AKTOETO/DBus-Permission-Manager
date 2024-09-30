cmake_minimum_required(VERSION 3.23)
project(DBus-Permission-Manager)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Условие для добавления определения DEBUG
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif()

# ищем нужные библиотеки
find_package(sdbus-c++ REQUIRED)
find_package(SQLite3 REQUIRED)

# добавление директории с утилитами
add_subdirectory(utils_lib)

# добавляем директорию сервиса permissions
add_subdirectory(permissions) 

# добавляем директорию сервиса time
add_subdirectory(time)

# добавляем директорию главного приложения
add_subdirectory(app)
