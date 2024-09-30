#include "permission_server.h"

int main() {
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
}