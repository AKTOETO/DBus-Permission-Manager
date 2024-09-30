#ifndef PERMISSION_SERVER_H
#define PERMISSION_SERVER_H

#include "db.h"
#include "permission.h"

class PermissionsServer : public Permissions {
public:
  /**
   * @brief Создаем новый объект для взаимодействия с сервисом прав доступа
   *
   * @param object DBus объект
   * @param drop_table нужно ли сбросить базу данных
   */
  PermissionsServer(std::unique_ptr<sdbus::IObject> object,
                    bool drop_table = 0);

  /**
   * @brief Запрашиваем права доступа
   *
   * @param perm код доступа
   */
  virtual void requestPermission(PermissionType perm) override;

  /**
   * @brief Проверяем: есть ли право доступа perm у приложения str
   *
   * @param str путь к приложению
   * @param perm код доступа
   * @return true доступ есть \n
   * @return false доступа нет
   */
  virtual bool checkApplicationHasPermission(std::string str,
                                             PermissionType perm) override;

private:
  // База даных
  DataBase m_db;

  // Объект на DBus шине
  std::unique_ptr<sdbus::IObject> m_object;
};

#endif // !PERMISSION_SERVER_H