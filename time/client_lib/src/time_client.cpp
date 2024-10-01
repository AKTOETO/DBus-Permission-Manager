#include "time_client.h"
#include <iostream>

TimeClient::TimeClient(std::unique_ptr<sdbus::IProxy> proxy)
    : m_proxy(std::move(proxy)) {}

uint64_t TimeClient::getSystemTime() {
  // системное время в миллисекундах
  uint64_t time;

  // получаем системное время
  m_proxy->callMethod("GetSystemTime")
      .onInterface(m_interface_name)
      .storeResultsTo(time);
  return time;
}