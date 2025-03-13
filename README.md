# Проект Визуализации Куба

Этот проект представляет собой 3D-визуализацию кубика Рубика с использованием OpenGL. Он позволяет пользователям взаимодействовать с кубом через клавиатуру и мышь, предоставляя визуальное представление вращений и манипуляций с кубом.

## Возможности

- 3D-рендеринг кубика Рубика с использованием OpenGL.
- Интерактивное управление для вращения куба и его граней.
- Обновления и анимации в реальном времени.
- Настраиваемый размер куба и цвета граней.

## Необходимые компоненты

Для запуска этого проекта необходимо установить следующие компоненты:

- OpenGL
- GLUT (OpenGL Utility Toolkit)
- GLEW (OpenGL Extension Wrangler Library)

## Установка и настройка

1. **Клонируйте репозиторий:**

   ```bash
   git clone <repository-url>
   cd Cube
   ```

2. **Соберите проект:**

   Убедитесь, что у вас установлен компилятор C++ и необходимые библиотеки OpenGL. Затем скомпилируйте проект с помощью команды:

   ```bash
   g++ Cube.cpp -o Cube -lGL -lGLU -lglut -lGLEW
   ```

3. **Запустите приложение:**

   Выполните скомпилированный файл:

   ```bash
   ./Cube
   ```

## Использование

- **Управление с клавиатуры:**
  - `F5`: Непрерывное вращение куба.
  - Стрелки: Вращение куба в разных направлениях.
  - `Home`/`End`: Приближение/отдаление.
  - `F1`: Сброс куба в начальное состояние.
  - Цифры (`0` до `5`): Вращение определенных граней куба.

- **Управление мышью:**
  - Правая кнопка: Переключение таймера для автоматических вращений.

## Структура кода

- `Element.h`: Определяет структуру `Element`, представляющую каждый маленький кубик в кубике Рубика.
- `Cube.h`: Содержит класс `Cube`, который управляет общей структурой куба и операциями.
- `Cube.cpp`: Реализует основную логику для рендеринга и взаимодействия с кубом.

## Вклад

Будем рады вашему вкладу! Пожалуйста, форкните репозиторий и отправьте pull request для любых улучшений или исправлений ошибок.

## Лицензия

Этот проект лицензирован под лицензией MIT. Подробности смотрите в файле `LICENSE`.

## Благодарности

- OpenGL и GLUT за предоставление графической платформы.
- Любые другие библиотеки или ресурсы, использованные в проекте.
