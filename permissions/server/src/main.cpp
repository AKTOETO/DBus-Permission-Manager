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
 * @brief Запрашиваем доступ
 * 
 * @param perm код доступа
 */
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
 * @brief Проверяем: есть ли право доступа perm у приложения str
 * 
 * @param str путь к приложению
 * @param perm код доступа
 * @return true доступ есть \n
 * @return false доступа нет
 */
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
  // Создаем DBus шину
  sdbus::ServiceName serviceName{"com.system.permissions"};
  auto connection = sdbus::createSessionBusConnection(serviceName);

  // Создаем DBus объект 
  sdbus::ObjectPath objectPath{"/"};
  auto concatenator = sdbus::createObject(*connection, std::move(objectPath));

  // Регистрация методов
  concatenator
      ->addVTable(sdbus::registerMethod("RequestPermission")
                      .implementedAs(std::move(RequestPermission)),
                  sdbus::registerMethod("CheckApplicationHasPermission")
                      .implementedAs(std::move(CheckApplicationHasPermission)))
      .forInterface("com.system.permissions");

  // Запуск сервиса
  connection->enterEventLoop();
}