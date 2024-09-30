#include "permission.h"
#include <iostream>

Permissions::Permissions() {}

// void Permissions::requestPermission(PermissionType perm) {
//   checkPermission(perm);
//   requestPermissionWOError(perm);
// }

// bool Permissions::checkApplicationHasPermission(std::string str,
//                                                 PermissionType perm) {
//   bool result = 0;
//   checkPermission(perm);
//   result = checkApplicationHasPermissionWOError(str, perm);
//   return result;
// }

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
