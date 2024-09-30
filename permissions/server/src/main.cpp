#include "permission_server.h"

int main(int argc, char *argv[]) {
  //try {
    // Создание шины на DBus
    sdbus::ServiceName serviceName{"com.system.permissions"};
    auto connection = sdbus::createSessionBusConnection(serviceName);

    // Создаем DBus объект
    sdbus::ObjectPath objectPath{"/"};
    auto object = sdbus::createObject(*connection, std::move(objectPath));

    // создание сервера для работы с правами доступа
    PermissionsServer server(std::move(object));

    // запуск работы сервиса
    connection->enterEventLoop();
  // } catch (const sdbus::Error &e) {
  //   std::cerr << "Ошибка: " << e.getName() << ":" << e.getMessage()
  //             << std::endl;
  // } catch (const std::exception &e) {
  //   std::cerr << "Ошибка: " << e.what() << std::endl;
  // }
}