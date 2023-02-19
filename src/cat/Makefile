.PHONY: all s21_cat.c
override CFLAGS += -Wall -Wextra -Werror -std=c11 -g
CC=gcc
EXE=s21_cat
RUN=$(EXE) -e -n -s -b -t -v s21_cat.c s21_cat.h
all: s21_cat

s21_cat: s21_cat.c
	$(CC) $(CFLAGS) $^ -o $(EXE)

rebuild:
	make clean; make s21_cat

clean:
	rm s21_cat a.out *.cfg log.txt
test:
	ls -la
	bash s21_cat_test.sh

check:
	clang-format  -i  s21_cat.c 
	clang-format  -n -Werror s21_cat.c

deploy:
	mv s21_cat /home/gitlab-runner
	mv /home/gitlab-runner/s21_cat /home/gitlab-runner/builds/Ls8mhqtm/0/students/DO6_CICD.ID_356283/qyburnbo_student.21_school.ru/DO6_CICD-0/src/cat

ifeq ($(shell uname -s), Darwin)
	CK_FORK=no leaks --atExit -- ./$(RUN)
else
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./$(RUN)
endif