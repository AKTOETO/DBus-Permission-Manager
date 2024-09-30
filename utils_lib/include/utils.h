#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <memory>
#include <sdbus-c++/sdbus-c++.h>

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
 * @brief Печать времени в поток out
 * 
 * @param out поток вывода для времени
 * @param time время (в миллисекундах)
 */
void printTime(std::ostream& out, uint64_t time);

/**
 * @brief Фабрика по созданию прокси для подключения к сервисам
 *
 * @param service_name имя сервиса
 * @param object_path путь
 * @return std::unique_ptr<sdbus::IProxy> прокси к сервису
 */
std::unique_ptr<sdbus::IProxy> createProxy(std::string service_name,
                                           std::string object_path = "/");

} // namespace Utils

#endif // !UTILS_H