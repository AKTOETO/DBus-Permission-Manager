#ifndef PERMISSION_H
#define PERMISSION_H

#include "utils.h"
#include <sdbus-c++/sdbus-c++.h>

class Permissions {
public:
  /**
   * @brief Права доступа
   *
   */
  enum class PermissionType : int32_t { SystemTime = 0, MaxType };

  Permissions();

  /**
   * @brief Запрашивание прав доступа, без обработки ошибок
   *
   * @param perm код доступа
   */
  virtual void requestPermission(PermissionType perm) = 0;

  /**
   * @brief Проверяем: есть ли право доступа perm у приложения str
   *
   *
   * @param str путь к приложению
   * @param perm код доступа
   * @return true доступ есть
   * @return false доступа нет
   */
  virtual bool checkApplicationHasPermission(std::string str, PermissionType perm) = 0;

protected:
  // Обработка введенного типа доступа
  void checkPermission(PermissionType perm);

protected:
  // имя интерфейса
  static constexpr const char *m_interface_name = "com.system.permissions";
};

#endif //! PERMISSION_H