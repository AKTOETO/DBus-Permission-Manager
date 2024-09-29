#include <iostream>

#include "test.h"

#include <sdbus-c++/sdbus-c++.h>
#include <sqlite3.h>

#include <unistd.h>

int main(int argv, char **argc) {

  // создание сервиса с соответсвующим именем
  sdbus::ServiceName service_name{"com.system.permissions"};

  // подключаемся к определенной шине
  auto connection = sdbus::createBusConnection(service_name);

  // создаем объект DBus
  sdbus::ObjectPath obj_path{"/com/system/permissions"};
  auto request_perm_obj = sdbus::createObject(*connection, std::move(obj_path));

  // регистрируем методы в request_perm_obj
  sdbus::InterfaceName interface { "com.system.Permissions" };
  //   request_perm_obj->addVTable()

  return 0;
}