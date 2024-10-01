#include "utils.h"

#include <iomanip>
#include <sdbus-c++/sdbus-c++.h>
#include <unistd.h>

namespace Utils {
std::string getFilepath(const std::string &dbus_id) {

  // формирование фалового пути по pid
  char exe[150];
  sprintf(exe, "/proc/%d/exe", getPid(dbus_id));

  // Проверяем, существует ли файл
  if (access(exe, F_OK) == -1) {
    throw std::runtime_error("Процесс с таким pid не найден");
  }

  // Читаем символическую ссылку
  char buf[150];
  ssize_t len = readlink(exe, buf, sizeof(exe) - 1);
  if (len == -1) {
    throw std::runtime_error(
        "Ошибка при чтении символической ссылки. Возможно нет такого пути.");
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

void printTime(std::ostream &out, uint64_t time) {
  // начало отсчета времени
  std::chrono::system_clock::time_point tp =
      std::chrono::system_clock::from_time_t(0);

  // Добавляем миллисекунды к начальному моменту
  tp += std::chrono::milliseconds(time);

  // Преобразуем в time_t
  time_t tt = std::chrono::system_clock::to_time_t(tp);

  // Форматируем в строку
  std::tm *tm = localtime(&tt);

  // Формат: год-месяц-день часы:минуты:секунды
  out << std::put_time(tm, "%Y-%m-%d %H:%M:%S\n");
}

std::unique_ptr<sdbus::IProxy> createProxy(std::string service_name,
                                           std::string object_path) {
  // создадим прокси для подключения к серверной части permissions
  sdbus::ServiceName serviceName{service_name};
  sdbus::ObjectPath objectPath{object_path};
  return sdbus::createProxy(std::move(serviceName), std::move(objectPath));
}
} // namespace Utils
