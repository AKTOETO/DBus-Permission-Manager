#ifndef PERMISSION_CLIENT_H
#define PERMISSION_CLIENT_H

#include "permission.h"

class PermissionsClient : public Permissions {
public:
  PermissionsClient(std::unique_ptr<sdbus::IProxy> proxy);

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
  // Прокси для работы с DBus шиной
  std::unique_ptr<sdbus::IProxy> m_proxy;
};

#endif //! PERMISSION_CLIENT_H