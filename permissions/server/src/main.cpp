#include "permission_server.h"

int main(int argc, char *argv[]) {
  // Создание шины на DBus
  sdbus::ServiceName serviceName{"com.system.permissions"};
  auto connection = sdbus::createSessionBusConnection(serviceName);

  // Создаем DBus объект
  sdbus::ObjectPath objectPath{"/"};
  auto object = sdbus::createObject(*connection, std::move(objectPath));

  // нужно ли сбросить бд
  bool need_drop = 0;

  // если ввели -с, значит надо сбросить BD
  if (argc > 1 && strcmp(argv[1], "-c") == 0) {
    std::cout << "Сбрасываем базу данных\n";
    need_drop = 1;
  }

  // создание сервера для работы с правами доступа
  PermissionsServer server(std::move(object), need_drop);

  // запуск работы сервиса
  connection->enterEventLoop();
}