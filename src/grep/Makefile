.PHONY: all s21_grep.c
override CFLAGS += -Wall -Wextra -Werror -std=c11 -g -D_GNU_SOURCE
CC=gcc
EXE=s21_grep
RUN=$(EXE) -e while -e void s21_grep.c Makefile -n -v -c -f s21_pattern.txt
all: s21_grep

s21_grep: s21_grep.c
	$(CC) $(CFLAGS) $^ -o s21_grep
	mkdir compiled-code && mv s21_grep compiled-code/s21_grep

rebuild:
	make clean; make

clean:
	rm -rf compiled-code test-results
test:
	-mkdir test-results
	bash s21_grep_test.sh

check:
	clang-format  -i  s21_grep.c 
	clang-format  -n -Werror s21_grep.c
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config s21_grep.c s21_grep.h

ifeq ($(shell uname -s), Darwin)
	CK_FORK=no leaks --atExit -- ./compiled-code/$(RUN)
endif
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./compiled-code/$(RUN)
