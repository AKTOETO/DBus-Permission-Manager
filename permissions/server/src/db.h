#ifndef DB_H
#define DB_H

#include "permission.h"
#include <iostream>
#include <sqlite3.h>

class DataBase {
public:
  /**
   * @brief Создание объекта базы данных
   *
   * @param filepath путь к базе данных
   * @param drop_table нужно ли сбросить базу данных (удаляет ее содержимое,
   * если бд раньше существовала)
   */
  DataBase(std::string filepath, bool drop_table = 0);
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