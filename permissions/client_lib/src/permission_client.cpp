#include "permission_client.h"

#include <iostream>

PermissionsClient::PermissionsClient(std::unique_ptr<sdbus::IProxy> proxy)
    : m_proxy(std::move(proxy)) {}

void PermissionsClient::requestPermission(PermissionType perm) {
  m_proxy->callMethod("RequestPermission")
      .onInterface(m_interface_name)
      .withArguments(perm);
  //std::cout << "Отправлен запрос на получение прав: " << int32_t(perm) << "\n";
}

bool PermissionsClient::checkApplicationHasPermission(std::string str,
                                                      PermissionType perm) {
  bool result = 0;
  m_proxy->callMethod("CheckApplicationHasPermission")
      .onInterface(m_interface_name)
      .withArguments(str, perm)
      .storeResultsTo(result);
  // std::cout << "Получен ответ от сервера на запрос "
  //              "CheckApplicationHasPermission: "
  //           << std::boolalpha << result << "\n";
  return result;
}
