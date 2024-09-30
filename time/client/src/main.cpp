#include <iostream>
#include <string>
#include <vector>

#include "time_client.h"

int main() {
  // создадим прокси для подключения к серверной части permissions
  TimeClient client(std::move(Utils::createProxy("com.system.time")));

  client.getSystemTime();
  client.getSystemTime();
  client.getSystemTime();
}