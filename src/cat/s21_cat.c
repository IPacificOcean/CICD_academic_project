#include "s21_cat.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

void struct_init_zero(options *options) {
  options->opt_n = 0;
  options->opt_b = 0;
  options->opt_v = 0;
  options->opt_e = 0;
  options->opt_s = 0;
  options->opt_t = 0;
}

void output(options *options, char **argv) {
  while (*argv != NULL) {
    if ((options->filename = fopen(*argv++, "r")) == NULL) {
      printf("%s\n", strerror(errno));
    } else {
      char c;
      options->line = 1;    // counter of lines
      options->cr = 0;      // counter \n
      int smb_one_line = 0; // flag of first line smb's
      int l = 1;            // cycle Counter
      while ((c = fgetc(options->filename)) != EOF) {
        if (c == '\n' && options->line == 1 && !smb_one_line)
          options->cr++;
        if (options->opt_s) {
          if (c == '\n' && options->cr >= 2)
            continue;
        }
        if (options->opt_b) {
          options->opt_n = 0;
          if (c != '\n' && (options->cr || l == 1)) {
            printf("%6d\t", l++);
          }
        }
        if (options->opt_n) {
          if (l++ == 1 || options->cr) {
            printf("%6d\t", options->line);
          }
        }
        if (options->opt_t) {
          if (c == '\t') {
            printf("^");
            c += 64;
          }
        }
        if (options->opt_e) {
          if (c == '\n') {
            printf("$");
          }
        }
        if (options->opt_v) {
          if (c < 0) {
            printf("M-");
            c += 128;
          }
          if (c < 32 && c != '\t' && c != '\n') {
            printf("^");
            c += 64;
          }
          if (c == 127) {
            printf("^");
            c -= 64;
          }
        }
        printf("%c", c);
        options->line += (c == '\n') ? 1 : 0;
        options->cr += (c == '\n') ? 1 : 0;
        if (c != '\n')
          options->cr = 0;
        smb_one_line = (options->line == 1 && c != '\n') ? 1 : 0;
      } /// while 2
      fclose(options->filename);
    } // else
  }   // while 1
}

char **parser_flags(int argc, char **argv, options *optionsF) {
  int i = 1;
  // if (argc == i || (strlen(argv[i]) == 1 && argv[i][0] == '-')) {
  //     // exit in stdin

  //     } else {
  if (argc > i) {
    size_t j;
    int is_text = 0;
    while (argv[i]) {
      if (is_text == 0) {
        if (argv[i][0] == '-' && argv[i][1] != '-') {
          for (j = 1; j < strlen(argv[i]); j++) {
            switch (argv[i][j]) {
            case 's':
              optionsF->opt_s = 1;
              break;
            case 'b':
              optionsF->opt_b = 1;
              break;
            case 'n':
              optionsF->opt_n = 1;
              break;
            case 'e':
              optionsF->opt_e = 1;
              optionsF->opt_v = 1;
              break;
            case 't':
              optionsF->opt_t = 1;
              optionsF->opt_v = 1;
              break;
            case 'v':
              optionsF->opt_v = 1;
              break;
            case 'E':
              optionsF->opt_e = 1;
              break;
            case 'T':
              optionsF->opt_t = 1;
              break;
            default:
              printf("\ns21_cat: illegal option -- %c\nusage: cat [-benstuv] "
                     "[file ...]",
                     argv[i][j]);
              break;
            } // swith
          }   // for
        } else if (strcmp(argv[i], "--number") == 0) {
          optionsF->opt_n = 1;

        } else if (strcmp(argv[i], "--number-nonblank") == 0) {
          optionsF->opt_b = 1;

        } else if (strcmp(argv[i], "--squeeze-blank") == 0) {
          optionsF->opt_s = 1;

        } else {
          is_text++;
        } // if 2
      }   // if 1
      if (is_text)
        break;
      i++;
    } // main while argv
  }   // if argc
  //    } // 1 else
  return &argv[i];
}

// void write_in_file(char *filename){
//   FILE * file;
//   printf("%s\n", filename);
//   if ((file = fopen(filename, "w")) == NULL){
//        printf("%s", strerror(errno));
//         // perror("Error occured while opening data.txt");
//         // exit(0)
//   } else {
//       int i = 256;
//       while (i--) {
//          fprintf(file,"\tThis iqwers invisible smb N%d  %c \n", i, i);
//       }
//       fclose(file);
//   }
// }

int main(int argc, char **argv) {
  // char *fileS = "simbols.txt";
  options optionsF; // We declare a variable type of flag structure
  // write_in_file(fileS);
  struct_init_zero(&optionsF); // Initialize the structure of zeros
  char **filename = parser_flags(argc, argv, &optionsF);
  output(&optionsF, filename); // output of text files on the screen

  return 0;
}
