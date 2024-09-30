#ifndef UTILS_H
#define UTILS_H

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

/**
 * @brief Получить текущее время
 *
 * @return uint64_t время (в миллисекундах)
 */
uint64_t getCurrentTime();

} // namespace Utils

#endif // !UTILS_H