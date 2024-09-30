#ifndef PERMISSION_SERVER_H
#define PERMISSION_SERVER_H

#include "permission.h"
#include "db.h"

class PermissionsServer : public Permissions {
public:
  PermissionsServer(std::unique_ptr<sdbus::IObject> object);

  /**
   * @brief Запрашиваем права доступа
   *
   * @param perm код доступа
   */
  virtual void requestPermissionWOError(PermissionType perm) override;

  /**
   * @brief Проверяем: есть ли право доступа perm у приложения str
   *
   * @param str путь к приложению
   * @param perm код доступа
   * @return true доступ есть \n
   * @return false доступа нет
   */
  virtual bool
  checkApplicationHasPermissionWOError(std::string str,
                                       PermissionType perm) override;

private:
  // База даных
  DataBase m_db;

  // Объект на DBus шине
  std::unique_ptr<sdbus::IObject> m_object;
};

#endif // !PERMISSION_SERVER_H