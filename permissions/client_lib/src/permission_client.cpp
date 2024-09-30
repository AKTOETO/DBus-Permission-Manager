#include "permission_client.h"

#include <iostream>

PermissionsClient::PermissionsClient(std::unique_ptr<sdbus::IProxy> proxy)
    : m_proxy(std::move(proxy)) {}

void PermissionsClient::requestPermissionWOError(PermissionType perm) {
  try {
    m_proxy->callMethod("RequestPermission")
        .onInterface(m_interface_name)
        .withArguments(perm);
    std::cout << "Отправлен запрос на получение прав: " << int32_t(perm)
              << "\n";
  } catch (const sdbus::Error &e) {
    std::cerr << "Ошибка: " << e.getName() << ":" << e.getMessage()
              << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Ошибка: " << e.what() << std::endl;
  }
}

bool PermissionsClient::checkApplicationHasPermissionWOError(
    std::string str, PermissionType perm) {
  bool result = 0;
  try {
    m_proxy->callMethod("CheckApplicationHasPermission")
        .onInterface(m_interface_name)
        .withArguments(str, perm)
        .storeResultsTo(result);
    std::cout << "Получен ответ от сервера на запрос "
                 "CheckApplicationHasPermission: "
              << std::boolalpha << result << "\n";
  } catch (const sdbus::Error &er) {
    std::cerr << "Ошибка: " << er.getName() << ":" << er.getMessage()
              << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Ошибка: " << e.what() << std::endl;
  }
  return result;
}
