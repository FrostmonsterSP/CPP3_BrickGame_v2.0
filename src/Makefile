PROJECT_NAME:=s21_brick_game
PROJECT_VER:=2.0

# Компилятор и флаги
CC=gcc
CXX=g++
AR=ar rcs
RM=rm -rf
GCOVR=gcovr
DOXYGEN=doxygen/doxygen
PIPE=>/dev/null 2>&1
G=@

# Папки
OBJ_DIR=objects
TOBJ_DIR=objects/test
LIB_DIR=libs
TEST_DIR=tests
REPORT_DIR=report
BIN_DIR=bin
HTML_DOC_DIR=doc/html
GUI_DIR=gui/desktop/snake

# Исходные файлы
MAIN_SRCS=main.cpp
GUI_SRCS=$(wildcard $(GUI_DIR)/*.cpp)
TEST_SRCS=$(wildcard $(TEST_DIR)/*.cpp)

# Объектные файлы
MAIN_OBJ=$(patsubst %.cpp, $(OBJ_DIR)/%.o, $(MAIN_SRCS))
GUI_OBJS=$(patsubst $(GUI_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(GUI_SRCS))

# Объектные файлы тестов
TGUI_OBJS=$(patsubst $(GUI_DIR)/%.cpp, $(TOBJ_DIR)/%.o, $(GUI_SRCS))

# Исполняемый файл и библиотеки
EXEC=$(PROJECT_NAME)
LIB_TETRIS=$(LIB_DIR)/libtetris.a
LIB_DIR_LINK=-L$(LIB_DIR)
DISTFILE=$(PROJECT_NAME)-$(PROJECT_VER).tar.gz

# Документация
HTML_DOC=$(HTML_DOC_DIR)/index.html
GCOV_REPORT=$(REPORT_DIR)/coverage.html

CFLAGS+=-std=c++17 `pkg-config --cflags gtkmm-4.0` -Ilibs -g -fPIC
CPPLIBS=`pkg-config --libs gtkmm-4.0` -ltetris
TEST_LIBS=-lcheck -ltetris -lgcov -lm -lsubunit
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
OPEN_CMD=open
endif

ifeq ($(shell uname),Linux)
OPEN_CMD=xdg-open
ADD_LDFLAGS=-lm -lsubunit
endif

ifeq ($(DEBUG), 1)
G=
PIPE=
endif

ifneq ($(DOXYPATH),)
DOXYGEN=$(DOXYPATH)
endif

.PHONY: test

# Правило по умолчанию
all: test install

# Создание директорий для объектных файлов, библиотек и исполняемого файла
$(OBJ_DIR):
	@if test ! -d $(OBJ_DIR); then printf "${PURPLE}${BOLD}=>${RESET}${PURPLE} Создание каталога сборки${RESET}\n"; mkdir -p $(OBJ_DIR); fi

$(LIB_DIR):
	@if test ! -d $(LIB_DIR); then printf "${PURPLE}${BOLD}=>${RESET}${PURPLE} Создание каталога библиотек${RESET}\n"; mkdir -p $(LIB_DIR); fi

$(REPORT_DIR):
	@if test ! -d $(REPORT_DIR); then printf "${PURPLE}${BOLD}=>${RESET}${PURPLE} Создание каталога отчёта${RESET}\n"; mkdir -p $(REPORT_DIR); fi

$(TOBJ_DIR):
	@if test ! -d $(TOBJ_DIR); then printf "${PURPLE}${BOLD}=>${RESET}${PURPLE} Создание каталога сборки тестов${RESET}\n"; mkdir -p $(TOBJ_DIR); fi

$(BIN_DIR):
	@if test ! -d $(BIN_DIR); then printf "${PURPLE}${BOLD}=>${RESET}${PURPLE} Создание каталога исполняемого файла${RESET}\n"; mkdir -p $(BIN_DIR); fi

# Сборка исполняемого файла
$(EXEC): get-libs $(OBJ_DIR) $(MAIN_OBJ) $(GUI_OBJS)
	@printf "${BLUE}${BOLD}=>${RESET}${BLUE} Сборка исполняемого файла $@${RESET}\n"
	$(G)$(CXX) $(CFLAGS) -o $@ $(MAIN_OBJ) $(GUI_OBJS) $(LIB_DIR_LINK) $(CPPLIBS)

# Сборка тестов
test: $(TOBJ_DIR) 
	@printf "${BLUE}${BOLD}=>${RESET}${BLUE} Сборка тестов${RESET}\n"
	$(G)$(CXX) $(CFLAGS) $(COV_FLAGS) -o $@ $(TEST_OBJS) $(TGUI_OBJS) $(LIB_DIR_LINK) $(TEST_LIBS)
	@printf "${YELLOW}${BOLD}=>${RESET}${YELLOW} Запуск тестов${RESET}\n"
	$(G)./$@

# Создание статической библиотеки движка
# $(LIB_TETRIS): $(BRICK_OBJS)
# 	@printf "${BLUE}${BOLD}=>${RESET}${BLUE} Сборка статической библиотеки движка $(notdir $@)${RESET}\n"
# 	$(G)$(AR) $@ $^

# Компиляция объектных файлов
# Main
$(OBJ_DIR)/%.o: %.cpp
	@printf "${BLUE}${BOLD}=>${RESET}${BLUE} Компиляция $(notdir $<)${RESET}\n"
	$(G)$(CXX) $(CFLAGS) -c $< -o $@

# Gui
$(GUI_OBJS): $(GUI_SRCS)
	@printf "${BLUE}${BOLD}=>${RESET}${BLUE} Компиляция $(notdir $<)${RESET}\n"
	$(G)$(CXX) $(CFLAGS) -c $< -o $@

# Компиляция тестов
$(TOBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	@printf "${BLUE}${BOLD}=>${RESET}${BLUE} Компиляция тестов $(notdir $<)${RESET}\n"
	$(G)$(CXX) $(CFLAGS) -c $< -o $@

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
# 	@if test -d $(TOBJ_DIR); then printf "${PURPLE}${BOLD}=>${RESET}${PURPLE} Удаление каталога сборки тестов${RESET}\n"; $(RM) $(TOBJ_DIR); fi

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
	$(G)$(GCOVR) --html-details $(GCOV_REPORT) --html-theme github.dark-blue $(PIPE)

# Генерация отчёта о покрытии тестов
gcov_report: test $(GCOV_REPORT)
	@printf "${GREEN}${BOLD}=>${RESET}${GREEN} Открытие отчёта о покрытии тестов${RESET}\n"
	$(G)$(OPEN_CMD) $(GCOV_REPORT)

build: $(EXEC)

get-libs:
	$(G)if test ! -f $(LIB_TETRIS); then printf "${YELLOW}${BOLD}=>${RESET}${YELLOW} Получение библиотек${RESET}\n"; fi
	$(G)chmod +x get-libs.sh
	$(G)./get-libs.sh

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