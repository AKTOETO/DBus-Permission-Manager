# DBus permission manager

## Описание
### Концепция
В популярных мобильных ОС присутствует динамическое управление разрешениями. Один из способов его реализации - централизованный
сервис, у которого стороннее приложение может запросить какое-либо разрешение, а другой сервис может узнать, запрашивало ли приложение,
которое к нему обращается, определенный вид разрешения.

### Необходимо

1. Реализовать DBus сервис с именем com.system.permissions на сессионной шине с использованием языка C++, который имеет 2
метода:
- `void RequestPermission(permissionEnumCode: int)`
Который получает путь до исполняемого файла, вызвавшего данный метод, по dbus имени клиента и сохраняет в базу данных SQLite информацию о том, что данный исполняемый файла запросил заданное
разрешение. В случае ошибки метод должен возвращать DBus ошибку с человекочитаемым сообщением.
- `bool CheckApplicationHasPermission(applicationExecPath: String, permissionEnumCode: int)`
Который проверяет имеется ли у приложение с заданным путем до исполняемого файла заданное разрешение. В случае
ошибки метод должен возвращать DBus ошибку с человекочитаемым сообщением.

    **Перечисление разрешений:**
`enum Permissions { SystemTime = 0 }`

    **Пример использования:**
- `gdbus send -e -d com.system.permissions -o / -m com.system.permissions.RequestPermission 0`
- `gdbus send -e -d com.system.permissions -o / -m com.system.permissions.CheckApplicationHasPermission /usr/bin/com.example.example 0`
2. Реализовать DBus сервис `com.system.time` на сессионной шине с использованием языка C++, который имеет 1 метод:
- `uint64 GetSystemTime()`
Который возврашает `timestamp` текущего системного времени. Однако перед этим, он получает путь до исполняемого файла,
вызвавшего данный метод, по dbus имени клиента и проверяет при помощи DBus сервиса com.
`system.permissions`, имеет ли данный исполняемый файл разрешение `SystemTime`. В случае если исполняемый файл не
имеет разрешения `SystemTime`, должна возвращаться ошибка `UnauthorizedAccess` с человекочитаемым сообщением. В
случае любой другой ошибки должна возвращаться обычная ошибка с человекочитаемым сообщением.
- Пример использования:
`gdbus send -e -d com.system.time -o / -m com.system.time.GetSystemTime`
3. Реализовать приложение с использованием языка C++, которое:
- Пробует запросить у сервиса `com.system.time` текущее время и в случае ошибки `UnauthorizedAccess` запрашивает
разрешение `SystemTime` у сервиса `com.system.permissions`, после чего пытается повторить запрос текущего времени.
- После получения `timestamp`a текущего времени, выводит его на экран в человекочитемом виде.

### Установка

**1. Вариант установки с использованием скриптов**

1. Склонировать репозиторий и перейти в папку с репозиторием:
```
git clone https://github.com/AKTOETO/DBus-Permission-Manager.git
cd DBus-Permission-Manager/
```
2. Выдать права на исполнение трем скриптам
```
chmod +x initial-conf.sh compile-debug.sh compile-release.sh 
```
3. Запустить скрипт `initial-conf.sh` для начальной настройки репозитория (установки cmake и conan; создание профиля в conan; загрузки нужных библиотек через conan; создание папки `build` для бинарников). 
> Если запустить `initial-conf.sh` без параметров, то проект будет конфигурироваться под тип сборки `Release` (от этого будет зависеть следующий запускаемый скрипт). Если нужна конкретная сборка (всего типа два: `Debug`; `Release`), то нужно передать тип сборки в скрипт.
```
./initial-conf.sh
```
4. Запускаем скрипт `compile-release.sh`, который сконфигурирует проект через `cmake` в соответствии с текущим типом сборки (на предыдущем шаге говорилось про тип сборки) и скомпилирует все необходимые таргеты.
```
./compile-release.sh
```
> Если нужен тип сборки `Debug`, то вызываем скрипт `compile-debug.sh`
5. Запускаем необходмые файлы из соответствующей папки:
```
./build/Release/bin/permission_server ...
```

Полный набор команд:
```
https://github.com/AKTOETO/DBus-Permission-Manager.git
chmod +x initial-conf.sh compile-debug.sh compile-release.sh 
./initial-conf.sh
./compile-release.sh
./build/Release/bin/permissions
```

> После сборки появится директория `build/<Тип сборки>/bin/`, где находятся необходимые исполняемые файлы.

**2. Вариант установки вручную**




---

### Тестирование
Заместо команды 
```
gdbus send -e -d com.system.permissions -o / -m com.system.permissions.RequestPermission 0
```
будет использована
```
gdbus call -e -d com.system.permissions -o / -m com.system.permissions.RequestPermission 0
```

#### Пример использования:
![](doc/RequestPermission.png)

А также заместо
```
gdbus send -e -d com.system.permissions -o / -m com.system.permissions.CheckApplicationHasPermission
/usr/bin/com.example.example 0
```
будет использована
```
gdbus call -e -d com.system.permissions -o / -m com.system.permissions.CheckApplicationHasPermission path/to/exe 0
```
#### Пример использования:
![](doc/CheckApplicationHasPermission.png)

### Источники информации
[Здесь инфа по dbus](https://github.com/Kistler-Group/sdbus-cpp/blob/master/docs/using-sdbus-c++.md)

---

### Использование
#### Первое задание
Необходимо запустить Файл `build/<Тип сборки>/bin/permission_server`, который выполнит подключение к DBus шине и зарегистрирует там необходимые функции. Также создастся файл с базой данных под названием `build/<Тип сборки>/bin/file.db`, в котором будут храниться приложения и их уровни доступа.
После чего можно использовать команды из пункта [Тестирование](#тестирование), либо же запустить приложение `build/<Тип сборки>/bin/permission_client`, в котором есть возможность протестировать две реализованные в первом задании команды.