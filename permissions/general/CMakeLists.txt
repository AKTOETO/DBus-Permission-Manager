cmake_minimum_required(VERSION 3.23)

################
# ПЕРЕМЕННЫЕ
################

# заголовочные файлы
file(GLOB HDRS include/*.h)

message("###### UTILS LIB ######")
message( "Заголовочные файлы:")
foreach(header ${HDRS})
message("  ${header}")
endforeach()

# файлы исходного кода
file(GLOB SRCS src/*)

message("Файлы исходного кода:")
foreach(src ${SRCS})
message("  ${src}")
endforeach()

# список библиотек
set(LIBS 
#SQLite::SQLite3
utils
SDBusCpp::sdbus-c++
)
message("############")

################

# объявляем таргет библиотеки с утилитами
add_library(permission_general ${HDRS} ${SRCS})

# подключение библиотек
target_link_libraries(permission_general ${LIBS})

# подключаем заголовочные файлы
target_include_directories(permission_general
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# проверка утечек памяти и вывод варнингов в дебаге
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(permission_general PRIVATE -W -Wall -fsanitize=address -g)
    target_link_options(permission_general PRIVATE -fsanitize=address)
endif()