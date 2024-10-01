#include "permission_server.h"
#include "db.h"
#include "db_config.h"
#include "utils.h"
#include <iostream>
#include <unistd.h>

PermissionsServer::PermissionsServer(std::unique_ptr<sdbus::IObject> object,
                                     bool drop_table)
    : Permissions(), m_db(DATABASE_PATH, drop_table),
      m_object(std::move(object)) {
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

void PermissionsServer::requestPermission(PermissionType perm) {
  // проверка границ прав доступа
  Permissions::checkPermission(perm);

  std::string filepath =
      Utils::getFilepath(m_object->getCurrentlyProcessedMessage().getSender());

  std::cout << "requestPermission: " << int32_t(perm) << " : " << filepath
            << std::endl;

  //Сохраняем в бд запрос приложения о праве доступа
  m_db.savePermissionRequest(filepath, perm);
}

bool PermissionsServer::checkApplicationHasPermission(std::string str,
                                                      PermissionType perm) {
  // проверка границ прав доступа
  Permissions::checkPermission(perm);

  // результат запроса: если права есть = 1, если нет = 0
  bool result = 0;

  std::cout << "checkApplicationHasPermission: " << int32_t(perm) << " : "
            << str << std::endl;

  // Обращаемся к бд и узнаем, есть ли у приложения str права perm
  result = m_db.hasPermission(str, int32_t(perm));

  // возвращаем результат запроса
  return result;
}