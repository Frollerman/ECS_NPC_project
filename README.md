# ECS_NPC_project

Пет-проект на C++: демонстрация реализации поведения NPC через конечный автомат (FSM) в рамках легковесной ECS-подобной архитектуры.

Проект показывает, как реализовать переходы состояний (`PATROL` → `CHASE` → `ATTACK`) на основе дистанции до игрока, покрыть логику тестами и управлять параметрами через JSON-конфиг.

## Особенности реализации

*   **Конечный автомат (FSM):** NPC имеет 3 состояния:
    *   `PATROL`: патрулирование между точками.
    *   `CHASE`: погоня за игроком при попадании в радиус обнаружения.
    *   `ATTACK`: нанесение урона при сближении; реализован простой таймер кулдауна (1 секунда).
*   **Конфигурация:** параметры (скорости, радиусы, урон) загружаются из `data/npc_config.json`. Предусмотрен конструктор по умолчанию для быстрого запуска и тестов.
*   **Тестирование:** базовые тесты на переходы состояний и загрузку конфига (Google Test).
*   **Сборка:** CMake (версия 3.16+), без внешних зависимостей кроме nlohmann/json (header-only) и Google Test (FetchContent).

## Быстрый старт

### Требования
- C++17 компилятор
- CMake 3.16 или выше
- Интернет (для скачивания Google Test при первой сборке)

---

## Как запустить

### Сборка

```bash
cmake -B build
cmake --build build
```

### Демо

```text
Windows (Debug): build\Debug\npc_demo.exe
Linux/macOS: ./build/npc_demo
```

### Тесты

Реализованы следующие тесты:

DefaultConfigValues: проверка значений по умолчанию.
PatrolToChaseTransition: проверка перехода из PATROL в CHASE при малой дистанции.
ChaseToAttackTransition: проверка перехода из CHASE в ATTACK при сближении.
JsonConfigLoading: проверка загрузки параметров из JSON-файла.

Windows:
```text
ctest -C Debug --output-on-failure
```
или:
```text
build\Debug\npc_tests.exe
```

Linux/macOS:
```text
cd build && ctest --output-on-failure
```

## Структура проекта

```text
ECS_NPC_project/
├── CMakeLists.txt          # Сборка, Google Test, копирование data/
├── README.md               # Эта документация
├── src/
│   ├── main.cpp            # Точка входа, демо-цикл
│   ├── npc_system.hpp      # Объявление NpcSystem, FSM, конфигурации
│   ├── npc_system.cpp      # Реализация FSM и логики
│   ├── position.hpp        # Структура Position
│   └── state.hpp           # Перечисление State (PATROL, CHASE, ATTACK)
├── tests/
│   └── npc_test.cpp        # Тесты на переходы и конфиг
├── data/
│   └── npc_config.json     # Конфигурация NPC
└── third_party/
    └── nlohmann/           
        └── json.hpp        # Библиотека nlohmann/json.hpp (header-only)
```