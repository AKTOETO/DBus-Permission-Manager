#include <iostream>
#include <sstream>
#include <unistd.h>

#include "permission_client.h"
#include "time_server.h"
#include "utils.h"

TimeServer::TimeServer(std::unique_ptr<sdbus::IObject> object)
    : Time(), m_object(std::move(object)) {
  m_object
      ->addVTable(sdbus::registerMethod("GetSystemTime")
                      .implementedAs(std::move([this]() -> uint64_t {
                        auto num = getSystemTime();
                        return num;
                      }))
                      .withOutputParamNames("timestamp"))
      .forInterface(m_interface_name);
}

uint64_t TimeServer::getSystemTime() {
  // Получение пути до файла, который вызвал этот метод
  std::string filepath =
      Utils::getFilepath(m_object->getCurrentlyProcessedMessage().getSender());

  // Проверка прав через сервис permissions
  sdbus::ServiceName name{"com.system.permissions"};
  sdbus::ObjectPath path{"/"};
  auto proxy = sdbus::createProxy(std::move(name), std::move(path));

  // создаем клиент для взаимодействия с permissions
  PermissionsClient client(std::move(proxy));

  // получение прав доступа у файла
  bool result = client.checkApplicationHasPermission(
      filepath, Permissions::PermissionType::SystemTime);

  // если прав нет
  if (!result) {
    std::stringstream name;
    name << m_interface_name << ".Error.UnauthorizedAccess";
    std::stringstream desc;
    desc << " Файл: " << filepath << " не имеет прав: "
         << int32_t(Permissions::PermissionType::SystemTime);
    throw sdbus::Error(sdbus::Error::Name{name.str()}, desc.str());
  }

  // Если есть права, получаем текущее время
  return getCurrentTime();
}

uint64_t TimeServer::getCurrentTime() {
  // получаем текущее время
  auto now = std::chrono::system_clock::now().time_since_epoch();

  // преобразуем это все в миллисекунды
  return std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
}
