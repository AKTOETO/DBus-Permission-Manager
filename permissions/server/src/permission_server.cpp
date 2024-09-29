#include "permission_server.h"
#include "utils.h"
#include <iostream>
#include <unistd.h>

PermissionsServer::PermissionsServer(std::unique_ptr<sdbus::IObject> object)
    : Permissions(), m_object(std::move(object)) {
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
      .forInterface("com.system.permissions");
}

void PermissionsServer::requestPermission(PermissionType perm) {

  std::string filepath =
      Utils::getFilepath(m_object->getCurrentlyProcessedMessage().getSender());

  std::cout << "Запрошенынй тип доступа: " << int32_t(perm)
            << " для файла: " << filepath << std::endl;

  /*
    Сохраняем в бд запрос приложения о праве доступа
  */
}

bool PermissionsServer::checkApplicationHasPermission(std::string str,
                                                      PermissionType perm) {
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