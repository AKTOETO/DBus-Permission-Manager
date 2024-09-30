#include <iostream>
#include <string>
#include <vector>

#include "time_client.h"

int main() {
  // создадим прокси для подключения к серверной части permissions
  sdbus::ServiceName serviceName{"com.system.time"};
  sdbus::ObjectPath objectPath{"/"};
  auto connection =
      sdbus::createProxy(std::move(serviceName), std::move(objectPath));

  TimeClient client(std::move(connection));

  client.getSystemTime();
  client.getSystemTime();
  client.getSystemTime();
}