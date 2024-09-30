#ifndef PERMISSION_SERVER_H
#define PERMISSION_SERVER_H

#include "mytime.h"

class TimeServer : public Time {
public:
  TimeServer(std::unique_ptr<sdbus::IObject> object);

  /**
   * @brief Получаем системное время
   *
   * @return uint64_t время (в миллисекундах)
   */
  virtual uint64_t getSystemTime() override;

private:

  // Объект на DBus шине
  std::unique_ptr<sdbus::IObject> m_object;
};

#endif // !PERMISSION_SERVER_H