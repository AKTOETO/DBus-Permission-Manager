cmake_minimum_required(VERSION 3.23)

# добавляем библиотеку с описанием API
add_subdirectory(general_lib)

# добавляем библиотеку для клиента
add_subdirectory(client_lib)

# добавляем директорию сервиса permissions-server
add_subdirectory(server)

