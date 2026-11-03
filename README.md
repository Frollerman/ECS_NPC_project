# NPC Logic Demo (C++17)

Модуль логики NPC на C++: FSM, компонентная архитектура, юнит‑тесты, CI. Спроектирован как отдельный модуль — легко встраивается в Qt‑приложение или игровой сервер.

## Архитектура

- `NpcEntity` — чистые данные (позиция, состояние, параметры).
- `NpcSystem` — логика (`update()`, FSM, движение, проверка дистанции).
- Tick loop в `main` — эмуляция игрока и логирование.

## Покрытие тестами

Тестами закрыты:
- Переходы состояний (Idle → Chase → Attack).
- Движение в состоянии Chase.
- Логика Patrol (диапазон и зацикливание).
- Граничные случаи (игрок убегает/подходит вплотную).

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
npc_demo/
├── CMakeLists.txt
├── src/
│   ├── main.cpp
│   ├── npc_system.cpp
│   ├── npc_system.hpp
│   ├── npc_entity.hpp
│   ├── position.hpp
│   └── state.hpp
└── tests/
    └── npc_test.cpp
```