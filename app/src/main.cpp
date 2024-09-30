#include "permission_client.h"
#include "time_client.h"

#include <iostream>

int main() {
  // обращение к com.system.time
  TimeClient time_client(std::move(Utils::createProxy("com.system.time")));

  // смог ли я получить время
  bool got_time = false;

  // текущее время
  uint64_t time;

  // пока время не получено, пытаемся его получить
  while (!got_time) {
    got_time = 1;
    try {
      // получение времени
      time = time_client.getSystemTime();

    } catch (const sdbus::Error &e) {
      // если произошла ошибка sdbus, обрабатываем ее
      if (e.getName() == "com.system.time.Error.UnauthorizedAccess") {
        got_time = 0;
        // если же ошибка связана с неполученным доступом, получаем его
        std::cout << "Доступа к SystemTime нет. Запрашиваем его.\n";

        PermissionsClient perm_client(
            std::move(Utils::createProxy("com.system.permissions")));
        perm_client.requestPermission(Permissions::PermissionType::SystemTime);
      }

    } catch (const std::exception &e) {
      // если произошла другая ошибка, печатаем ее
      std::cerr << "Ошибка: " << e.what() << std::endl;
    }
  }

  // печать времени
  Utils::printTime(std::cout, time);

  return 0;
}