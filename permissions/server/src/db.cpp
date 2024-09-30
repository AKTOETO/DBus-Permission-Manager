#include "db.h"

#include <sstream>

DataBase::DataBase(std::string filepath) {

  // Открываем файл с бд
  int rc = sqlite3_open(filepath.c_str(), &m_db);
  if (rc) {
    std::stringstream sstr;
    sstr << "Невозможно открыть базу данных: " << sqlite3_errmsg(m_db);
    throw std::runtime_error(sstr.str());
  }

  // Создаем таблицу если она еще не существует
  std::string sql = "CREATE TABLE IF NOT EXISTS permissions ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "executable_path TEXT,"
                    "permission INTEGER)";
  rc = sqlite3_exec(m_db, sql.c_str(), nullptr, nullptr, nullptr);
  if (rc != SQLITE_OK) {

    std::stringstream sstr;
    sstr << "SQL ошибка: " << sqlite3_errmsg(m_db);
    throw std::runtime_error(sstr.str());
  }
}

DataBase::~DataBase() { sqlite3_close(m_db); }

void DataBase::savePermissionRequest(std::string path,
                                     Permissions::PermissionType type) {
  // Подготовка SQL запроса
  std::string sql =
      "INSERT INTO permissions (executable_path, permission) VALUES (?, ?)";
  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(m_db, sql.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    // sqlite3_close(m_db);
    std::stringstream sstr;
    sstr << "Невозможно подготовить запрос: " << sqlite3_errmsg(m_db);
    throw std::runtime_error(sstr.str());
  }

  // Привязка параметров к запросу
  sqlite3_bind_text(stmt, 1, path.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_int(stmt, 2, static_cast<int32_t>(type));

  // Выполнение запроса
  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE) {
    sqlite3_finalize(stmt);
    std::stringstream sstr;
    sstr << "Невозможно выполнить запрос: " << sqlite3_errmsg(m_db);
    throw std::runtime_error(sstr.str());
  }

  // Закрытие ресурсов
  sqlite3_finalize(stmt);
}

bool DataBase::hasPermission(const std::string &executablePath,
                             int permission) {
  std::string sql = "SELECT COUNT(*) FROM permissions WHERE executable_path=? "
                    "AND permission=?";
  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(m_db, sql.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    std::stringstream sstr;
    sstr << "SQL ошибка: " << sqlite3_errmsg(m_db);
    throw std::runtime_error(sstr.str());
  }

  sqlite3_bind_text(stmt, 1, executablePath.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_int(stmt, 2, permission);

  rc = sqlite3_step(stmt);
  if (rc != SQLITE_ROW) {
    std::stringstream sstr;
    sqlite3_finalize(stmt);
    sstr << "SQL ошибка: " << sqlite3_errmsg(m_db);
    throw std::runtime_error(sstr.str());
  }

  int count = sqlite3_column_int(stmt, 0);
  sqlite3_finalize(stmt);
  return count > 0;
}
