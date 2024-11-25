/**
 * @file engine.h
 * @brief Библиотека для управления игровым процессом
 *
 * @details Библиотека engine.h предназначена для управления игровым процессом.
 * Она содержит функции для инициализации игры, старта, паузы, изменения
 * направления, изменения скорости, сброса, касания, заполнения строки, очистки
 * заполненных строк, изменения направления, изменения скорости, выхода, а также
 * вспомогательные функции, которые используются этими функциями.
 *
 * @dotfile engine_graph.dot
 * - `State0`: Начальное состояние
 * - `StateInit`: Инициализированное состояние (например, экран выбора настроек
 * перед игрой)
 * - `StateAction`: Состояние обработки действий пользователя
 * - `StateShift`: Состояние сдвига фигуры
 * - `StateIdle`: Бездействие (игра на паузе)
 * - `StateSpawn`: Появление новой фигуры
 */
#ifndef ENGINE_H
#define ENGINE_H
// NOLINTBEGIN

/**
 * @brief Состояния игры
 *
 * Определяет различные состояния, в которых может находиться игра.
 */
typedef enum {
  State0,       ///< Начальное состояние (неинициализировано)
  StateInit,    ///< Инициализация игры
  StateIdle,    ///< Ожидание действий пользователя
  StateSpawn,   ///< Спавн новой фигуры
  StateAction,  ///< Действия игрока
  StateShift,   ///< Сдвиг фигуры
} GameState_t;

/**
 * @brief Действия пользователя
 *
 * Определяет возможные действия пользователя во время игры.
 */
typedef enum {
  Start,      ///< Начать игру
  Pause,      ///< Поставить игру на паузу
  Terminate,  ///< Завершить игру
  Left,       ///< Сдвиг фигуры влево
  Right,      ///< Сдвиг фигуры вправо
  Up,         ///< Поворот фигуры
  Down,       ///< Ускорение падения фигуры
  Action,     ///< Специальное действие (например, моментальное падение)
} UserAction_t;

/**
 * @brief События игры
 *
 * Определяет возможные события, которые происходят в игре.
 */
typedef enum {
  EventInit,       ///< Событие инициализации игры
  EventIdle,       ///< Событие ожидания
  EventStart,      ///< Событие старта игры
  EventPause,      ///< Событие паузы
  EventTerminate,  ///< Событие завершения игры
  EventLeft,       ///< Событие сдвига влево
  EventRight,      ///< Событие сдвига вправо
  EventDown,       ///< Событие ускоренного падения
  EventUp,         ///< Событие поворота фигуры
  EventAction,     ///< Событие специального действия
  EventTick,       ///< Событие тика таймера
  EventTouchdown,  ///< Событие касания дна или другой фигуры
  EventPlaceFree,  ///< Событие свободного места для фигуры
} GameEvent_t;

/**
 * @brief Повороты фигур
 *
 * Определяет возможные повороты фигуры.
 */
typedef enum {
  R0,    ///< Поворот на 0 градусов
  R90,   ///< Поворот на 90 градусов
  R180,  ///< Поворот на 180 градусов
  R270   ///< Поворот на 270 градусов
} Rotation_t;

/**
 * @brief Типы фигур тетромино
 *
 * Определяет возможные типы фигур, используемых в игре.
 */
typedef enum {
  IFig,  ///< Фигура I
  JFig,  ///< Фигура J
  LFig,  ///< Фигура L
  OFig,  ///< Фигура O
  SFig,  ///< Фигура S
  TFig,  ///< Фигура T
  ZFig   ///< Фигура Z
} FigType_t;

/**
 * @brief Структура, содержащая информацию об игре
 *
 * Содержит текущее состояние игрового поля, уровень, очки и другую информацию.
 */
typedef struct {
  int field[FIELD_HEIGHT][FIELD_WIDTH];  ///< Игровое поле
  int **next;                            ///< Указатель на следующую фигуру
  int score;                             ///< Текущие очки
  int high_score;                        ///< Рекорд
  int level;                             ///< Текущий уровень
  int speed;                             ///< Текущая скорость игры
  GameState_t state;                     ///< Текущее состояние игры
} GameInfo_t;

/**
 * @brief Структура, описывающая фигуру тетромино
 *
 * Содержит параметры фигуры, такие как координаты, тип, поворот и границы.
 */
typedef struct {
  int x;                             ///< Координата X фигуры
  int y;                             ///< Координата Y фигуры
  int left_edge;                     ///< Левая граница фигуры
  int right_edge;                    ///< Правая граница фигуры
  int rows_next_line[FIGURE_WIDTH];  ///< Информация о следующей строке для
                                     ///< фигуры
  FigType_t type;                    ///< Тип фигуры
  Rotation_t rotation;               ///< Текущий поворот фигуры
} Figure_t;

/**
 * @brief Обработка ввода пользователя
 *
 * Функция принимает действие пользователя и генерирует соответствующее игровое
 * событие. В зависимости от переданного действия вызывается соответствующая
 * функция для обработки событий, таких как начало игры, пауза, сдвиги фигур и
 * другие.
 *
 * @param action Действие пользователя, которое нужно обработать.
 */
void userInput(UserAction_t action);

/**
 * @brief Обновление текущего состояния игры
 *
 * Функция обновляет текущее состояние игры в зависимости от игрового состояния
 * и событий. Если состояние игры требует генерации нового события (например,
 * тик таймера или касание фигуры дна), оно обрабатывается. Если таймер доходит
 * до нуля, генерируется событие тика. Возвращает указатель на обновлённое
 * состояние игры.
 *
 * @return const GameInfo_t* Указатель на структуру с текущей информацией о
 * состоянии игры.
 */
const GameInfo_t *updateCurrentState(void);
// NOLINTEND
#endif  // ENGINE_H
