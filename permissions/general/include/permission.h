#ifndef PERMISSION_H
#define PERMISSION_H

#include <sdbus-c++/sdbus-c++.h>

class Permissions {
public:
  /**
   * @brief Права доступа
   *
   */
  enum class PermissionType : int32_t { SystemTime = 0 };

  //   Permissions(sdbus::ServiceName service_name =
  //                   sdbus::ServiceName{"com.system.permissions"},
  //               sdbus::ObjectPath object_path = sdbus::ObjectPath{"/"});
  Permissions();

protected:
  /**
   * @brief Заправшиваем права доступа
   *
   * @param perm код доступа
   */
  virtual void requestPermission(PermissionType perm) = 0;

  /**
   * @brief Проверяем: есть ли право доступа perm у приложения str
   *
   * @param str путь к приложению
   * @param perm код доступа
   * @return true доступ есть \n
   * @return false доступа нет
   */
  virtual bool checkApplicationHasPermission(std::string str,
                                             PermissionType perm) = 0;

protected:
  // так не получится, потому что в клиенте используется прокси, а на сервере
  // конектион
  // соединение с DBus шиной
  // std::unique_ptr<sdbus::IConnection> m_connection;

  // Объект на DBus шине
  // std::unique_ptr<sdbus::IObject> m_object;

  // sdbus::ServiceName m_service_name;
  // sdbus::ObjectPath m_object_path;

  // имя интерфейса
  static constexpr const char *m_interface_name = "com.system.permissions";
};

#endif //! PERMISSION_H