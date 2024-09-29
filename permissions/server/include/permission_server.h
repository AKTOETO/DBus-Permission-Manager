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
   * @brief Заправшиваем права доступа
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

  /**
   * @brief Получение пути файла по dbusid
   *
   * @param dbus_id строка, полученная из getSender()
   * @return std::string путь до исполняемого файла
   */
  std::string getFilepath(const std::string& dbus_id);

    /**
     * @brief Получение pid, вызвавшего данный метод процесса
     * 
     * @param dbus_id строка, полученная из getSender()
     * @return std::string 
     */
  uint32_t getPid(const std::string &dbus_id);

private:

  // соединение с DBus шиной
  std::unique_ptr<sdbus::IConnection> m_connection;

  // Объект на DBus шине
  std::unique_ptr<sdbus::IObject> m_object;
};

#endif // !PERMISSION_SERVER_H