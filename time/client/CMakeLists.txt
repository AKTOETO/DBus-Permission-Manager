cmake_minimum_required(VERSION 3.23)

project(time_client)

################
# ПЕРЕМЕННЫЕ ТЕСТОВОГО КЛИЕНТА
################

message("###### ${PROJECT_NAME} ######")
# файлы исходного кода
file(GLOB SRCS src/*)

message("Файлы исходного кода:")
foreach(src ${SRCS})
    message("  ${src}")
endforeach()

# список библиотек
set(LIBS 
    time_client_lib
    SDBusCpp::sdbus-c++
)
message("############")

################

# создание исполняемого файла
add_executable(${PROJECT_NAME} ${SRCS})

# подключение библиотек
target_link_libraries(${PROJECT_NAME} ${LIBS})

# проверка утечек памяти и вывод варнингов в дебаге
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${PROJECT_NAME} PRIVATE -W -Wall -fsanitize=address -g)
    target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address)
endif()