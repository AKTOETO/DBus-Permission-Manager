#ifndef UTILS_H
#define UTILS_H

#include <functional>
#include <string>

namespace Utils {
/**
 * @brief Получение пути файла по dbusid
 *
 * @param dbus_id id процесса в dbus
 * @return std::string путь до исполняемого файла
 */
std::string getFilepath(const std::string &dbus_id);

/**
 * @brief Получение pid, вызвавшего данный метод процесса
 *
 * @param dbus_id id процесса в dbus
 * @return std::string
 */
uint32_t getPid(const std::string &dbus_id);

} // namespace Utils

#endif // !UTILS_H