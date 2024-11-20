PROJECT_NAME:=s21_brick_game
PROJECT_VER:=2.0

# Компилятор и флаги
CC:=gcc
CXX:=g++
AR:=ar rcs
RM:=rm -rf
DOXYGEN:=doxygen/doxygen
PIPE=>/dev/null 2>&1
G=@

# Папки
OBJ_DIR=objects
LIB_DIR=libs
TEST_DIR=tests
REPORT_DIR=report
BIN_DIR=bin
HTML_DOC_DIR=doc/html
GUI_DIR=gui/desktop/snake

# Объектные файлы
MAIN_OBJ:=$(patsubst %.cc, $(OBJ_DIR)/%.o, main.cc)
GUI_OBJS:=$(patsubst $(GUI_DIR)/%.cc, $(OBJ_DIR)/%.o, $(wildcard $(GUI_DIR)/*.cc)) $(OBJ_DIR)/gresources.c.o

# Объектные файлы тестов
TOBJ_OBJS:=$(patsubst $(GUI_DIR)/%.cc, $(OBJ_DIR)/%.o, $(wildcard $(GUI_DIR)/*.cc))

# Исполняемый файл и библиотеки
EXEC=$(PROJECT_NAME)
LIB_TETRIS=$(LIB_DIR)/libtetris.a
LIB_SNAKE=$(LIB_DIR)/libsnake.a
DISTFILE=$(PROJECT_NAME)-$(PROJECT_VER).$(shell uname -m).tar.gz

# Документация
HTML_DOC=$(HTML_DOC_DIR)/index.html
GCOV_REPORT=$(REPORT_DIR)/coverage.html

COMPILE_FLAGS:=-Wall -Werror -Wextra -Wpedantic -Ilibs -Iheaders -fPIC
CXXFLAGS:=$(CXXFLAGS) -std=c++17 $(COMPILE_FLAGS) `pkg-config --cflags gtkmm-4.0`
# DEBUG:=
CXXLIBS:=`pkg-config --libs gtkmm-4.0`
TEST_LIBS=-l
COV_FLAGS=-fprofile-arcs -ftest-coverage

# Цвета для вывода в консоль
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
PURPLE=\033[0;35m
BOLD=\033[1m
RESET=\033[0m

ifeq ($(shell uname),Darwin)
OPEN_CMD:=open
endif

ifeq ($(shell uname),Linux)
OPEN_CMD:=xdg-open
endif

ifeq ($(DEBUG), 1)
G=
PIPE=
endif

ifneq ($(DOXYPATH),)
DOXYGEN=$(DOXYPATH)
endif

.PHONY: test install rebuild resources dvi dist

# Правило по умолчанию
all: install

# Создание директорий для объектных файлов, библиотек и исполняемого файла
$(OBJ_DIR):
	@if test ! -d $(OBJ_DIR); then printf "${PURPLE}${BOLD}=>${RESET}${PURPLE} Создание каталога сборки${RESET}\n"; mkdir -p $(OBJ_DIR); fi

$(LIB_DIR):
	@if test ! -d $(LIB_DIR); then printf "${PURPLE}${BOLD}=>${RESET}${PURPLE} Создание каталога библиотек${RESET}\n"; mkdir -p $(LIB_DIR); fi

$(REPORT_DIR):
	@if test ! -d $(REPORT_DIR); then printf "${PURPLE}${BOLD}=>${RESET}${PURPLE} Создание каталога отчёта${RESET}\n"; mkdir -p $(REPORT_DIR); fi

$(BIN_DIR):
	@if test ! -d $(BIN_DIR); then printf "${PURPLE}${BOLD}=>${RESET}${PURPLE} Создание каталога исполняемого файла${RESET}\n"; mkdir -p $(BIN_DIR); fi

# Сборка исполняемого файла
$(EXEC): $(OBJ_DIR) check_deps $(OBJ_DIR)/gresources.c.o $(MAIN_OBJ) $(GUI_OBJS)
	@printf "${BLUE}${BOLD}=>${RESET}${BLUE} Сборка исполняемого файла $@${RESET}\n"
	$(G)$(CXX) $(CXXFLAGS) -o $@ $(MAIN_OBJ) $(GUI_OBJS) -L$(LIB_DIR) $(CXXLIBS)

# Сборка ресурсов Gtk4
$(OBJ_DIR)/gresources.c.o:
	@printf "${BLUE}${BOLD}=>${RESET}${BLUE} Сборка ресурсов Gtk4${RESET}\n"
	$(G)glib-compile-resources --generate-source --target=$(GUI_DIR)/gresources.c $(GUI_DIR)/gresources.xml --sourcedir $(GUI_DIR)
	$(G)$(CC) $(COMPILE_FLAGS) `pkg-config --cflags glib-2.0` -c $(GUI_DIR)/gresources.c -o $(OBJ_DIR)/gresources.c.o

# Сборка тестов
test: $(OBJ_DIR) 
	@printf "${BLUE}${BOLD}=>${RESET}${BLUE} Сборка тестов${RESET}\n"
	$(G)$(CXX) $(CXXFLAGS) $(COV_FLAGS) -o $@ $(TEST_OBJS) $(TGUI_OBJS) -L$(LIB_DIR) $(TEST_LIBS)
	@printf "${YELLOW}${BOLD}=>${RESET}${YELLOW} Запуск тестов${RESET}\n"
	$(G)./$@

# Создание статической библиотеки движка
# $(LIB_TETRIS): $(BRICK_OBJS)
# 	@printf "${BLUE}${BOLD}=>${RESET}${BLUE} Сборка статической библиотеки движка $(notdir $@)${RESET}\n"
# 	$(G)$(AR) $@ $^

# Компиляция объектных файлов
# Main
$(OBJ_DIR)/%.o: %.cc
	@printf "${BLUE}${BOLD}=>${RESET}${BLUE} Компиляция $(notdir $<)${RESET}\n"
	$(G)$(CXX) $(CXXFLAGS) -c $< -o $@

# Gui
$(OBJ_DIR)/%.o: $(GUI_DIR)/%.cc
	@printf "${BLUE}${BOLD}=>${RESET}${BLUE} Компиляция $(notdir $<)${RESET}\n"
	$(G)$(CXX) $(CXXFLAGS) -c $< -o $@

# Компиляция тестов
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cc
	@printf "${BLUE}${BOLD}=>${RESET}${BLUE} Компиляция тестов $(notdir $<)${RESET}\n"
	$(G)$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка отчёта о покрытии тестов
clean-report:
	@if test -d $(REPORT_DIR); then printf "${PURPLE}${BOLD}=>${RESET}${PURPLE} Удаление отчёта о покрытии тестов${RESET}\n"; $(RM) $(REPORT_DIR); fi

# Очистка документации
clean-doc:
	@if test -d $(HTML_DOC_DIR); then printf "${PURPLE}${BOLD}=>${RESET}${PURPLE} Удаление html документации${RESET}\n"; $(RM) $(HTML_DOC_DIR); fi

# Очистка тестов
# clean-test: clean-test-obj clean-test-lib
# 	@if test -f test; then printf "${PURPLE}${BOLD}=>${RESET}${PURPLE} Удаление тестового файла${RESET}\n"; $(RM) test; fi

# clean-test-obj:
# 	@if test -d $(OBJ_DIR); then printf "${PURPLE}${BOLD}=>${RESET}${PURPLE} Удаление каталога сборки тестов${RESET}\n"; $(RM) $(OBJ_DIR); fi

# clean-test-lib:
# 	@if test -f $(TLIB_TETRIS); then printf "${PURPLE}${BOLD}=>${RESET}${PURPLE} Удаление тестовой статической библиотеки движка${RESET}\n"; $(RM) $(TLIB_TETRIS); fi

# Очистка исполняемого файла
clean-exec:
	@if test -f $(EXEC); then printf "${PURPLE}${BOLD}=>${RESET}${PURPLE} Удаление исполняемого файла${RESET}\n"; $(RM) $(EXEC); fi

# Очистка каталога установки
clean-bin:
	@if test -d $(BIN_DIR); then printf "${PURPLE}${BOLD}=>${RESET}${PURPLE} Удаление каталога установки${RESET}\n"; $(RM) $(BIN_DIR); fi

# Очистка библиотек
clean-lib:
	@if test -d $(LIB_DIR); then printf "${PURPLE}${BOLD}=>${RESET}${PURPLE} Удаление каталога библиотек${RESET}\n"; $(RM) $(LIB_DIR); fi

# Очистка объектных файлов
clean-obj:
	@if test -d $(OBJ_DIR); then printf "${PURPLE}${BOLD}=>${RESET}${PURPLE} Удаление каталога сборки${RESET}\n"; $(RM) $(OBJ_DIR); fi

# Очистка старого архива:
clean-dist:
	@if test -f "$(DISTFILE)"; then printf "${PURPLE}${BOLD}=>${RESET}${PURPLE} Удаление старого архива $(DISTFILE)${RESET}\n"; $(RM) $(DISTFILE); fi

clean: clean-obj clean-bin clean-exec

# Пересборка
rebuild: clean all

# Удаление установленного исполняемого файла
uninstall: clean-bin clean-lib

$(GCOV_REPORT): $(REPORT_DIR)
	@printf "${YELLOW}${BOLD}=>${RESET}${YELLOW} Генерация отчёта о покрытии тестов${RESET}\n"
	$(G)gcovr --html-details $(GCOV_REPORT) --html-theme github.dark-blue $(PIPE)

# Генерация отчёта о покрытии тестов
gcov_report: test $(GCOV_REPORT)
	@printf "${GREEN}${BOLD}=>${RESET}${GREEN} Открытие отчёта о покрытии тестов${RESET}\n"
	$(G)$(OPEN_CMD) $(GCOV_REPORT)

build: $(EXEC)

# Цель install
install: $(BIN_DIR) build
	@printf "${YELLOW}${BOLD}=>${RESET}${YELLOW} Установка исполняемого файла${RESET}\n"
	$(G)mv $(EXEC) $(BIN_DIR)
	@printf "${YELLOW}${BOLD}=>${RESET}${YELLOW} Установка завершена${RESET}\n"

# Генерация документации
$(HTML_DOC):
	@if test ! -d $(HTML_DOC_DIR); then printf "${YELLOW}${BOLD}=>${RESET}${YELLOW} Генерация документации${RESET}\n" ; fi
	@if test ! -d $(HTML_DOC_DIR); then $(DOXYGEN) $(PIPE); fi;

dvi: $(HTML_DOC)
	@printf "${GREEN}${BOLD}=>${RESET}${GREEN} Открытие html документации${RESET}\n"
	$(G)$(OPEN_CMD) $(HTML_DOC)

# Создание tar архива
dist: clean-dist install $(HTML_DOC)
	@printf "${YELLOW}${BOLD}=>${RESET}${YELLOW} Создание архива $(DISTFILE)${RESET}\n"
	$(G)tar -czf $(DISTFILE) bin doc Makefile README.md libs headers tests gui brick_game

# Полная чистка
purge: clean uninstall clean-report clean-doc clean-dist 

# Полная сборка (все цели)
everything: all $(GCOV_REPORT) $(HTML_DOC) dist

# Полная пересборка
rebuild-all: purge everything

# Проверка зависимостей
check_deps: check_gtkmm check_gtest check_gcovr get-libs

check_gtkmm:
	@printf "${GREEN}${BOLD}=>${RESET}${GREEN} Проверка зависимостей${RESET}\n"
	$(G)pkg-config --exists gtkmm-4.0 || (printf "${RED}${BOLD}=>${RESET}${RED} Ошибка: Необходим gtkmm-4.0. Установите его.${RESET}\n"; exit 1)

get-libs:
	$(G)test -f $(LIB_TETRIS) || (printf "${YELLOW}${BOLD}=>${RESET}${YELLOW} Получение библиотек${RESET}\n"; chmod +x get-libs.sh; ./get-libs.sh)

check_gtest:
	$(G)pkg-config --exists gtest || (printf "${RED}${BOLD}=>${RESET}${RED} Ошибка: Необходим gtest. Установите его${RESET}\n"; exit 1)

check_gcovr:
	$(G)which gcovr &> /dev/null || (printf "${RED}${BOLD}=>${RESET} Ошибка: Необходим gcovr. Установите его из pip${RESET}\n"; exit 1)
	$(G)test $(shell gcovr --version | grep -oe '[0-9]\.[0-9]' | sed -e 's/\.//g') -gt 74 || (printf "${RED}${BOLD}=>${RESET}${RED} Ошибка: Необходим gcovr версии не ниже 7.4. Установите его из pip${RESET}\n"; exit 1)
