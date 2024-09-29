#include "utils.h"

#include <sdbus-c++/sdbus-c++.h>
#include <unistd.h>

namespace Utils {
std::string getFilepath(const std::string &dbus_id) {

  // формирование фалового пути по pid
  char exe[150];
  sprintf(exe, "/proc/%d/exe", getPid(dbus_id));

  // Проверяем, существует ли файл
  if (access(exe, F_OK) == -1) {
    throw sdbus::Error(sdbus::Error::Name{"com.system.permissions.Error.PID"},
                       "Процесс с таким pid не найден");
  }

  // Читаем символическую ссылку
  char buf[150];
  ssize_t len = readlink(exe, buf, sizeof(exe) - 1);
  if (len == -1) {
    throw sdbus::Error(sdbus::Error::Name{"com.system.permissions.Error.LINK"},
                       "Ошибка при чтении символической ссылки");
  }
  buf[len] = '\0';

  return std::string(buf);
}

uint32_t getPid(const std::string &dbus_id) {
  // Получаем D-Bus соединение
  sdbus::ServiceName serviceName{"org.freedesktop.DBus"};
  sdbus::ObjectPath objectPath{"/org/freedesktop/DBus"};
  auto connection = sdbus::createProxy(serviceName, objectPath);

  uint32_t pid;
  // Получаем pid процесса, отправившего запрос
  connection->callMethod("GetConnectionUnixProcessID")
      .onInterface("org.freedesktop.DBus")
      .withArguments(dbus_id)
      .storeResultsTo(pid);
  return pid;
}
} // namespace Utils
