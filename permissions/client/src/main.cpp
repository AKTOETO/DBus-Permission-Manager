#include <iostream>
#include <sdbus-c++/sdbus-c++.h>
#include <string>
#include <vector>

/**
 * @brief Права доступа
 *
 */
enum class Permissions : int32_t { SystemTime = 0 };

/**
 * @brief Запрос прав доступа
 *
 * @param call тут лежит код права доступа, которое запрашивается
 */
// void RequestPermission(sdbus::MethodCall call) {
//   // получаем запрашиваемый тип доступа
//   Permissions perm;
//   call >> perm;
//   /*
//    * Получаем путь до исполняемого файла
//    */
//   std::cout << "Запрошенынй тип доступа: " << int32_t(perm) << std::endl;
//   /*
//     Сохраняем в бд запрос приложения о праве доступа
//   */
//   // возвращаем пустой ответ
//   call.createReply().send();
// }

void RequestPermission(Permissions perm) {
  /*
   * Получаем путь до исполняемого файла
   */

  std::cout << "Запрошенынй тип доступа: " << int32_t(perm) << std::endl;

  /*
    Сохраняем в бд запрос приложения о праве доступа
  */

  // возвращаем пустой ответ
  return;
}

/**
 * @brief Проверка: есть ли у приложения определенные права доступа
 *
 * @param call запрашиваемое право доступа
 */
// void CheckApplicationHasPermission(sdbus::MethodCall call) {
//   //if(call.isEmpty())
//     throw
//     sdbus::Error(sdbus::Error::Name{"com.system.permissions.CheckApplicationHasPermission"},
//     "Нужна строка и число");
//   // получаем путь до файла
//   std::string str;
//   call >> str;
//   //if(call.isEmpty())
//     throw
//     sdbus::Error(sdbus::Error::Name{"com.system.permissions.CheckApplicationHasPermission"},
//     "Нужна строка и число");
//   // получаем код заправшиваемого права доступа
//   Permissions perm;
//   call >> perm;
//   std::cout << "Запрос права доступа: " << int32_t(perm)
//             << " у приложения: " << str << std::endl;
//   /*
//    * Обращаемся к бд и узнаем, есть ли у приложения str права perm
//    */
//   // результат запроса: если права есть = 1, если нет = 0
//   bool result = 0;
//   // возвращаем результат запроса
//   auto reply = call.createReply();
//   reply << result;
//   reply.send();
// }

bool CheckApplicationHasPermission(std::string str, Permissions perm) {

  std::cout << "Запрос права доступа: " << int32_t(perm)
            << " у приложения: " << str << std::endl;

  /*
   * Обращаемся к бд и узнаем, есть ли у приложения str права perm
   */

  // результат запроса: если права есть = 1, если нет = 0
  bool result = 0;

  // возвращаем результат запроса
  return result;
}

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