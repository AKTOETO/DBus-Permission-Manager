#ifndef PERMISSION_SERVER_H
#define PERMISSION_SERVER_H

#include <sdbus-c++/sdbus-c++.h>

class Permissions {
public:
  /**
   * @brief Права доступа
   *
   */
  enum class PermissionType : int32_t { SystemTime = 0 };

  Permissions();

  /**
   * @brief Запуск сервера
   *
   */
  void run();

private:
  /**
   * @brief Запрашиваем права доступа
   *
   * @param perm код доступа
   */
  void requestPermission(PermissionType perm);

  /**
   * @brief Проверяем: есть ли право доступа perm у приложения str
   *
   * @param str путь к приложению
   * @param perm код доступа
   * @return true доступ есть \n
   * @return false доступа нет
   */
  bool checkApplicationHasPermission(std::string str, PermissionType perm);

private:
  // соединение с DBus шиной
  std::unique_ptr<sdbus::IConnection> m_connection;

  // Объект на DBus шине
  std::unique_ptr<sdbus::IObject> m_object;
};

#endif // !PERMISSION_SERVER_H