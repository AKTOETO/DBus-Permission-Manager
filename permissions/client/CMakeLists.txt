cmake_minimum_required(VERSION 3.23)

################
# ПЕРЕМЕННЫЕ
################

# заголовочные файлы
file(GLOB HDRS include/*.h)

message("###### PERMISSIONS CLIENT ######")
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
SQLite::SQLite3
SDBusCpp::sdbus-c++
)
message("############")

################

# создание исполняемого файла
add_executable(permissions-client ${HDRS} ${SRCS})

# подключение библиотек
target_link_libraries(permissions-client ${LIBS})

# подключаем заголовочные файлы
target_include_directories(permissions-client
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# проверка утечек памяти и вывод варнингов в дебаге
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(permissions-client PRIVATE -W -Wall -fsanitize=address -g)
    target_link_options(permissions-client PRIVATE -fsanitize=address)
endif()