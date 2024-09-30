#include "time_server.h"

int main() {
  // Создание шины на DBus
  sdbus::ServiceName serviceName{"com.system.time"};
  auto connection = sdbus::createSessionBusConnection(serviceName);

  // Создаем DBus объект
  sdbus::ObjectPath objectPath{"/"};
  auto object = sdbus::createObject(*connection, std::move(objectPath));

  // создание сервера для работы с временем
  TimeServer server(std::move(object));

  // запуск работы сервиса
  connection->enterEventLoop();
}