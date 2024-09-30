#include "permission.h"
#include <iostream>

// Permissions::Permissions(sdbus::ServiceName service_name,
//                          sdbus::ObjectPath object_path)
//     : m_service_name(service_name), m_object_path(object_path) {}

Permissions::Permissions() {}

void Permissions::requestPermission(PermissionType perm) {
  // try {
  checkPermission(perm);
  requestPermissionWOError(perm);
  /*} catch (const sdbus::Error &e) {
    std::cerr << "Ошибка: " << e.getName() << ":" << e.getMessage()
              << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Ошибка: " << e.what() << std::endl;
  }*/
}

bool Permissions::checkApplicationHasPermission(std::string str,
                                                PermissionType perm) {
  bool result = 0;
  // try {
  checkPermission(perm);
  result = checkApplicationHasPermissionWOError(str, perm);
  // } catch (const sdbus::Error &e) {
  //   std::cerr << "Ошибка: " << e.getName() << ":" << e.getMessage()
  //             << std::endl;
  // } catch (const std::exception &e) {
  //   std::cerr << "Ошибка: " << e.what() << std::endl;
  // }
  return result;
}

void Permissions::checkPermission(PermissionType perm) {
  // если права больше допустимого, выбрасываем ошибку
  if (int32_t(perm) > int32_t(PermissionType::MaxType) || int32_t(perm) < 0) {
    std::string err{m_interface_name};
    err += ".Error.PermissionType";
    std::string err_msg{
        "Недопустимое значение типа доступа. Должно быть в границах [0,"};
    err_msg += std::to_string(int32_t(PermissionType::MaxType) - 1);
    err_msg += "]";
    throw sdbus::Error(sdbus::Error::Name{err}, err_msg);
  }
}
