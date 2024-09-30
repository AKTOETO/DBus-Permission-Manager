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
    try {
      // получение времени
      time = time_client.getSystemTime();
      got_time = 1;

    } catch (const sdbus::Error &e) {

      got_time = 0;

      // если произошла ошибка sdbus, обрабатываем ее
      if (e.getName() == "com.system.time.Error.UnauthorizedAccess") {
        // если же ошибка связана с неполученным доступом, получаем его
        std::cout << "Доступа к SystemTime нет. Запрашиваем его.\n";

        // Подключение к сервису с правами доступа
        PermissionsClient perm_client(
            std::move(Utils::createProxy("com.system.permissions")));

        // запрашивание прав доступа
        perm_client.requestPermission(Permissions::PermissionType::SystemTime);
      } else {

        // произошло другое DBus исключение
        std::cout << "Ошибка: " << e.getName() << " : " << e.getMessage()
                  << std::endl;
        // если какой-то из сервисов не работает, выходим
        if (e.getName() == "org.freedesktop.DBus.Error.ServiceUnknown")
          break;
      }

    } catch (const std::exception &e) {

      // если произошла другая ошибка, печатаем ее
      std::cerr << "Ошибка: " << e.what() << std::endl;
    }
  }

  // печать времени
  if (got_time)
    Utils::printTime(std::cout, time);

  return 0;
}