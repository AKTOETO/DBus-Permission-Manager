#include <iostream>
#include <sdbus-c++/sdbus-c++.h>
#include <string>
#include <vector>

/**
 * @brief Права доступа
 *
 */
enum class Permissions : int32_t { SystemTime = 0 };

int main(int argc, char *argv[]) {
  // создадим прокси для подключения к серверной части permissions
  sdbus::ServiceName serviceName{"com.system.permissions"};
  sdbus::ObjectPath objectPath{"/"};
  auto connection =
      sdbus::createProxy(std::move(serviceName), std::move(objectPath));

  // отправка запроса на сервер permissions к методу RequestPermission
  {
    try {
      Permissions perm = Permissions::SystemTime;
      connection->callMethod("RequestPermission")
          .onInterface("com.system.permissions")
          .withArguments(perm);
      std::cout << "Отправлен запрос на получение прав: " << int32_t(perm)
                << "\n";
    } catch (const sdbus::Error &er) {
      std::cerr << "Ошибка: " << er.getName() << ":" << er.getMessage()
                << std::endl;
    }
  }

  // отправка запроса на сервер permissions к методу
  // CheckApplicationHasPermission
  {
    try {
      Permissions perm = Permissions::SystemTime;
      std::string name = "oleg123";
      bool result;
      connection->callMethod("CheckApplicationHasPermission")
          .onInterface("com.system.permissions")
          .withArguments(name, perm)
          .storeResultsTo(result);
      std::cout << "Получен ответ от сервера на запрос "
                   "CheckApplicationHasPermission: "
                << std::boolalpha << result << "\n";
    } catch (const sdbus::Error &er) {
      std::cerr << "Ошибка: " << er.getName() << ":" << er.getMessage()
                << std::endl;
    }
  }
}