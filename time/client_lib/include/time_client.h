#ifndef PERMISSION_CLIENT_H
#define PERMISSION_CLIENT_H

#include "mytime.h"

class TimeClient : public Time {
public:
  TimeClient(std::unique_ptr<sdbus::IProxy> proxy);

  /**
   * @brief Получаем системное время
   *
   * @return uint64_t время (в миллисекундах)
   */
  virtual uint64_t getSystemTime() override;

private:
  // Прокси для работы с DBus шиной
  std::unique_ptr<sdbus::IProxy> m_proxy;
};

#endif //! PERMISSION_CLIENT_H