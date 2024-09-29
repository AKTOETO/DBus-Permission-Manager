#include "permission_server.h"
#include <iostream>
#include <unistd.h>

Permissions::Permissions() {
  // Создаем DBus шину
  sdbus::ServiceName serviceName{"com.system.permissions"};
  m_connection = sdbus::createSessionBusConnection(serviceName);

  // Создаем DBus объект
  sdbus::ObjectPath objectPath{"/"};
  m_object = sdbus::createObject(*m_connection, std::move(objectPath));

  // обертка для запроса прав
  auto requestPerm = [this](Permissions::PermissionType type) {
    auto msg = getObject()->getCurrentlyProcessedMessage();
    auto name = getFilepath(msg.getSender());
    std::cout << "Имя вызывающего файла: " << name << "\n";

    requestPermission(name, type);
  };

  // Регистрация методов
  m_object
      ->addVTable(sdbus::registerMethod("RequestPermission")
                      .implementedAs(std::move(requestPerm))
                      .withInputParamNames("Permissions"),

                  sdbus::registerMethod("CheckApplicationHasPermission")
                      .implementedAs(std::move(
                          [this](std::string str, PermissionType perm) -> bool {
                            return this->checkApplicationHasPermission(str,
                                                                       perm);
                          }))
                      .withInputParamNames("filepath", "Permissions")
                      .withOutputParamNames("access"))
      .forInterface("com.system.permissions");
}

void Permissions::requestPermission(std::string str, PermissionType perm) {

  std::cout << "Запрошенынй тип доступа: " << int32_t(perm)
            << " для файла: " << str << std::endl;

  /*
    Сохраняем в бд запрос приложения о праве доступа
  */

  // возвращаем пустой ответ
  return;
}

bool Permissions::checkApplicationHasPermission(std::string str,
                                                PermissionType perm) {
  std::cout << "Запрос права доступа: " << int32_t(perm)
            << " у приложения: " << str << std::endl;

  /*
   * Обращаемся к бд и узнаем, есть ли у приложения str права perm
   */

  // результат запроса: если права есть = 1, если нет = 0
  bool result = 0;

  // возвращаем результат запроса
  return result;
}

void Permissions::run() {
  // Запуск сервиса
  m_connection->enterEventLoop();
}

const std::unique_ptr<sdbus::IObject> &Permissions::getObject() {
  return m_object;
}

std::string Permissions::getFilepath(const std::string &dbus_id) {

  // формирование фалового пути по pid
  char exe[150];
  sprintf(exe, "/proc/%d/exe", getPid(dbus_id));

  // Проверяем, существует ли файл
  if (access(exe, F_OK) == -1) {
    throw sdbus::Error(sdbus::Error::Name{"com.system.permissions.Error.PID"},
                       "Процесс с таким pid не найден");
  }

  // Читаем символическую ссылку
  ssize_t len = readlink(exe, exe, sizeof(exe) - 1);
  if (len == -1) {
    throw sdbus::Error(sdbus::Error::Name{"com.system.permissions.Error.LINK"},
                       "Ошибка при чтении символической ссылки");
  }
  exe[len] = '\0';

  return std::string(exe);
}

uint32_t Permissions::getPid(const std::string &dbus_id) {
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

  std::cout << "pid: " << pid << "\n";
  return pid;
}
