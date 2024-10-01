cmake_minimum_required(VERSION 3.23)
project(DBus-Permission-Manager)

# Проверяем версию компилятора
execute_process(
  COMMAND ${CMAKE_CXX_COMPILER} --version
  OUTPUT_VARIABLE COMPILER_VERSION
)

message("Текущаяя версия ${CMAKE_CXX_COMPILER}: ${COMPILER_VERSION}")

string(REGEX MATCH "[0-9]+\\.[0-9]+" COMPILER_VERSION "${COMPILER_VERSION}")
if(COMPILER_VERSION LESS 10)
  message(FATAL_ERROR "GCC version 10 or later is required")
endif()

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
