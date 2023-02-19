#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_
#include <stdio.h>
typedef struct {
  int opt_n;
  int opt_b;
  int opt_v;
  int opt_e;
  int opt_s;
  int opt_t;
  int cr;
  int line;
  FILE *filename;
} options;

void struct_init_zero(options *options);  // обнуляет структуру
void output(options *options,
            char **argv);  // вывод текста на экран, получает указатель на
                           // структуру и имя файла
void write_in_file(char *filename);  // заполняет файл невидимыми символами
char **parser_flags(int argc, char **argv,
                    options *optionsF);  // парсер флагов apple

// char opt_s(char c, options *optionsF);

// -n (GNU: --number)
// нумерует все выходные строки начиная с 1

// -b (GNU: --number-nonblank)
// нумерует только непустые строки отменяет -n (CR-перевод каретки)

// -v отображает непечатные символы
// Отображение непечатных символов. Упpавляющие символы выводятся
// в виде ^X (CRTL+X), символ DEL (восьмеричное 0177) как ^?.
// Символы не входящие в стандаpтный ASCII-набоp
// (напpимеp, символы киppилицы с набоpом стаpших pазpядов)
// выводятся как «M-x», где x — опpеделяемый младшими семи битами символ.

// -e включат в себя и -v (GNU only: -E то же самое, но без применения -v)
// также отображает символы конца строки как $ (визуализация символа пеpевода
// стpоки).

// -s (GNU: --squeeze-blank)
// сжимает несколько смежных пустых строк
// Пpи наличии идущих подpяд пустых стpок выводить только одну

// -t предполагает и -v (GNU: -T то же самое, но без применения -v)
// также отображает табы как ^I
#endif  //  SRC_CAT_S21_CAT_H_
