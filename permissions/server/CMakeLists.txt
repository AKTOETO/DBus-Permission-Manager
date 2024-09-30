cmake_minimum_required(VERSION 3.23)

project(permission_server)

################################
# НАСТРОЙКА БАЗЫ ДАННЫх
################################

# Определяем путь к базе данных
set(DATABASE_PATH "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/file.db")

# Создаем файл конфигурации
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config/db_config.h.in"
               "${CMAKE_CURRENT_SOURCE_DIR}/src/db_config.h")

################
# ПЕРЕМЕННЫЕ
################

message("###### ${PROJECT_NAME} ######")

# файлы исходного кода
file(GLOB SRCS src/*)
set(SRCS ${SRCS})

message("Файлы исходного кода:")
foreach(src ${SRCS})
message("  ${src}")
endforeach()

# список библиотек
set(LIBS 
    utils_lib
    permission_general_lib
    SQLite::SQLite3
    SDBusCpp::sdbus-c++
)
message("############")

################

# создание исполняемого файла
add_executable(${PROJECT_NAME} ${SRCS} )

# подключение библиотек
target_link_libraries(${PROJECT_NAME} ${LIBS})

# подключение папки include, где 

# проверка утечек памяти и вывод варнингов в дебаге
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${PROJECT_NAME} PRIVATE -W -Wall -fsanitize=address -g)
    target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address)
endif()

