#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_
#include <stdio.h>

typedef struct {
  int opt_e;
  int opt_f;
  int opt_i;
  int opt_v;
  int opt_c;
  int opt_l;
  int opt_n;
  int opt_h;
  int opt_s;
  int opt_o;
  char templ[100][1024];
  char text_name[100][1024];
  int countP;
  int countF;
  int err;
} options;

// void struct_init_zero(options *options);  // обнуляет структуру
void output(options *optionsF);  // вывод текста на экран, получает указатель на
                                 // структуру и имя файла
void parser_flags(int argc, char **argv,
                  options *optionsF);  // парсер флагов apple
void open_file(char *argv, options *optionsF);

// gcc -Wall -Wextra -std=c11 s21_grep.c -g  -o s21_grep

// -e Шаблон

// -i Игнорирует различия регистра.

// -v Инвертирует смысл поиска соответствий.

// -c Выводит только количество совпадающих строк.

// -l Выводит только совпадающие файлы.

// -n Предваряет каждую строку вывода номером строки из файла ввода.

// -h Выводит совпадающие строки, не предваряя их именами файлов.

// -s Подавляет сообщения об ошибках о несуществующих или нечитаемых файлах.

// -f file Получает регулярные выражения из файла.

// -o Печатает только совпадающие (непустые) части совпавшей строки.

#endif  //  SRC_GREP_S21_GREP_H_
