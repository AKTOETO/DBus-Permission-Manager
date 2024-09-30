#include <iostream>
#include <string>
#include <vector>

#include "permission_client.h"

/**
 * @brief Права доступа
 *
 */

int main(int argc, char *argv[]) {
  // создадим прокси для подключения к серверной части permissions
  sdbus::ServiceName serviceName{"com.system.permissions"};
  sdbus::ObjectPath objectPath{"/"};
  auto connection =
      sdbus::createProxy(std::move(serviceName), std::move(objectPath));

  PermissionsClient client(std::move(connection));

  client.checkApplicationHasPermission("dyadas", Permissions::PermissionType::SystemTime);

  client.requestPermission(Permissions::PermissionType(100));
  client.requestPermission(Permissions::PermissionType::SystemTime);
  client.checkApplicationHasPermission("oleg", Permissions::PermissionType::SystemTime);
  client.requestPermission(Permissions::PermissionType::SystemTime);
  client.checkApplicationHasPermission("oleg123", Permissions::PermissionType::SystemTime);

}