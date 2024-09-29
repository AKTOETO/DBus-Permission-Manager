#include "permission_server.h"


int main(int argc, char *argv[]) {
  // // Создаем DBus шину
  // sdbus::ServiceName serviceName{"com.system.permissions"};
  // auto connection = sdbus::createSessionBusConnection(serviceName);

  // // Создаем DBus объект
  // sdbus::ObjectPath objectPath{"/"};
  // auto concatenator = sdbus::createObject(*connection, std::move(objectPath));

  // // Регистрация методов
  // concatenator
  //     ->addVTable(sdbus::registerMethod("RequestPermission")
  //                     .implementedAs(std::move(RequestPermission))
  //                     .withInputParamNames("Permissions"),

  //                 sdbus::registerMethod("CheckApplicationHasPermission")
  //                     .implementedAs(std::move(CheckApplicationHasPermission))
  //                     .withInputParamNames("filepath", "Permissions"))
  //     .forInterface("com.system.permissions");

  // // Запуск сервиса
  // connection->enterEventLoop();

  Permissions perm;
  perm.run();

}