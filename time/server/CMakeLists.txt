cmake_minimum_required(VERSION 3.23)

project(time_server)

################
# ПЕРЕМЕННЫЕ
################

# заголовочные файлы
file(GLOB HDRS include/*.h)

message("###### ${PROJECT_NAME} ######")
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
    utils_lib
    time_general_lib
    permission_client_lib
    #SQLite::SQLite3
    SDBusCpp::sdbus-c++
)
message("############")

################

# создание исполняемого файла
add_executable(${PROJECT_NAME} ${HDRS} ${SRCS})

# подключение библиотек
target_link_libraries(${PROJECT_NAME} ${LIBS})

# подключаем заголовочные файлы
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# проверка утечек памяти и вывод варнингов в дебаге
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${PROJECT_NAME} PRIVATE -W -Wall -fsanitize=address -g)
    target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address)
endif()