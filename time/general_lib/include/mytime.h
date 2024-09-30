#ifndef TIME_H
#define TIME_H

#include "utils.h"
#include <sdbus-c++/sdbus-c++.h>

class Time {
public:
  Time();

  /**
   * @brief Получаем системное время
   *
   * @return uint64_t время (в миллисекундах)
   */
  virtual uint64_t getSystemTime() = 0;

protected:
  // имя интерфейса
  static constexpr const char *m_interface_name = "com.system.time";
};

#endif //! TIME_H