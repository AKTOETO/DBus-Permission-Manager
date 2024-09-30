#include <iostream>
#include <string>
#include <vector>

#include "permission_client.h"

/**
 * @brief Права доступа
 *
 */

int main() {
  // создадим прокси для подключения к серверной части permissions
  //   sdbus::ServiceName serviceName{"com.system.permissions"};
  //   sdbus::ObjectPath objectPath{"/"};
  //   auto connection =
  //       sdbus::createProxy(std::move(serviceName), std::move(objectPath));

  PermissionsClient client(
      std::move(Utils::createProxy("com.system.permissions")));

  std::cout << "Запрос прав доступа 0 для dyadas выполнен с результатом: "
            << client.checkApplicationHasPermission(
                   "dyadas", Permissions::PermissionType::SystemTime)
            << std::endl;

  client.requestPermission(Permissions::PermissionType(0));
  client.requestPermission(Permissions::PermissionType::SystemTime);
  std::cout << "Запрос прав доступа 0 для "
               "/home/bogdan/Documents/MAI/DBus-Permission-Manager/build/Debug/"
               "bin/permission_client выполнен с результатом: "
            << client.checkApplicationHasPermission(
                   "/home/bogdan/Documents/MAI/DBus-Permission-Manager/build/"
                   "Debug/bin/"
                   "permission_client",
                   Permissions::PermissionType::SystemTime)
            << std::endl;
  client.requestPermission(Permissions::PermissionType::SystemTime);

  client.checkApplicationHasPermission("oleg123",
                                       Permissions::PermissionType::SystemTime);
}