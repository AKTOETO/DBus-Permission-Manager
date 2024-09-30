#include "permission_server.h"
#include "db.h"
#include "utils.h"
#include <iostream>
#include <unistd.h>

PermissionsServer::PermissionsServer(std::unique_ptr<sdbus::IObject> object)
    : Permissions(), m_db("file.db"), m_object(std::move(object)) {
  // Регистрация методов
  m_object
      ->addVTable(sdbus::registerMethod("RequestPermission")
                      .implementedAs(
                          std::move([this](Permissions::PermissionType type) {
                            requestPermission(type);
                          }))
                      .withInputParamNames("Permissions"),

                  sdbus::registerMethod("CheckApplicationHasPermission")
                      .implementedAs(std::move(
                          [this](std::string str, PermissionType perm) -> bool {
                            return this->checkApplicationHasPermission(str,
                                                                       perm);
                          }))
                      .withInputParamNames("filepath", "Permissions")
                      .withOutputParamNames("access"))
      .forInterface(m_interface_name);
}

void PermissionsServer::requestPermissionWOError(PermissionType perm) {

  // try {
  std::string filepath =
      Utils::getFilepath(m_object->getCurrentlyProcessedMessage().getSender());

  std::cout << "Запрошенынй тип доступа: " << int32_t(perm)
            << " для файла: " << filepath << std::endl;

  /*
    Сохраняем в бд запрос приложения о праве доступа
  */
  { m_db.savePermissionRequest(filepath, perm); }

  // } catch (const sdbus::Error &e) {
  //   std::cerr << "Ошибка: " << e.getName() << ":" << e.getMessage()
  //             << std::endl;
  // } catch (const std::exception &e) {
  //   std::cerr << "Ошибка: " << e.what() << std::endl;
  // }
}

bool PermissionsServer::checkApplicationHasPermissionWOError(
    std::string str, PermissionType perm) {
  // результат запроса: если права есть = 1, если нет = 0
  bool result = 0;

  // try {

  std::cout << "Запрос права доступа: " << int32_t(perm)
            << " у приложения: " << str << std::endl;

  /*
   * Обращаемся к бд и узнаем, есть ли у приложения str права perm
   */
  result = m_db.hasPermission(str, int(perm));

  // } catch (const sdbus::Error &e) {
  //   std::cerr << "Ошибка: " << e.getName() << ":" << e.getMessage()
  //             << std::endl;
  // } catch (const std::exception &e) {
  //   std::cerr << "Ошибка: " << e.what() << std::endl;
  // }

  // возвращаем результат запроса
  return result;
}