cmake_minimum_required(VERSION 3.23)

################
# ПЕРЕМЕННЫЕ
################

# заголовочные файлы
file(GLOB HDRS include/*.h)

message("###### PERMISSIONS ######")
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
add_executable(permissions ${HDRS} ${SRCS})

# подключение библиотек
target_link_libraries(permissions ${LIBS})

# подключаем заголовочные файлы
target_include_directories(permissions
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
