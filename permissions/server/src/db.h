#ifndef DB_H
#define DB_H

#include "permission.h"
#include <iostream>
#include <sqlite3.h>

class DataBase {
public:
  DataBase(std::string filepath);
  ~DataBase();

  // Функция для сохранения запроса в базу данных
  void savePermissionRequest(std::string path,
                             Permissions::PermissionType type);

  // Спрашиваем: есть ли права у приложения?
  bool hasPermission(const std::string &executablePath, int permission);

private:
  // база данных
  sqlite3 *m_db;
};

#endif // !DB_H