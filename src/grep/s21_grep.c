#include "s21_grep.h"

#include <errno.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define D_GNU_SOURCE
// void struct_init_zero(options *options) { options = {0}; }

void parser_flags(int argc, char **argv, options *optionsF) {
  if (argc > 2) {
    int i;
    int flagP = 0;
    int flagFP = 0;
    int flagInit = 0;
    for (i = 1; i < argc; i++) {
      if ((argv[i][0] == '-' && flagP != 2)) {
        size_t j;
        for (j = 0; j < strlen(argv[i]); j++) {
          switch (argv[i][j]) {
            case 'e':
              optionsF->opt_e = 1;
              if (flagInit == 1) {
                strcpy(optionsF->text_name[optionsF->countF++],
                       optionsF->templ[--optionsF->countP]);
              }
              flagInit = 2;
              flagP = 2;
              break;
            case 'f':
              optionsF->opt_f = 1;
              if (flagInit == 1) {
                strcpy(optionsF->text_name[optionsF->countF++],
                       optionsF->templ[--optionsF->countP]);
              }
              flagInit = 2;
              flagP = 2;
              flagFP = 1;
              break;
            case 'h':
              optionsF->opt_h = 1;
              break;
            case 'i':
              optionsF->opt_i = REG_ICASE;
              break;
            case 'v':
              optionsF->opt_v = 1;
              break;
            case 's':
              optionsF->opt_s = 1;
              break;
            case 'c':
              optionsF->opt_c = 1;
              break;
            case 'l':
              optionsF->opt_l = 1;
              break;
            case 'n':
              optionsF->opt_n = 1;
              break;
            case 'o':
              optionsF->opt_o = 1;
              break;

            default:
              break;
          }
        }  // for 3
      } else {
        if (!flagInit) {
          strcpy(optionsF->templ[optionsF->countP], argv[i]);
          flagP = 1;
          flagInit = 1;
          optionsF->countP++;
        } else {
          if (flagP == 1) {
            strcpy(optionsF->text_name[optionsF->countF], argv[i]);
            optionsF->countF++;
          }
          if (flagP == 2 && !flagFP) {
            strcpy(optionsF->templ[optionsF->countP], argv[i]);
            flagP = 1;
            optionsF->countP++;
          }
          if (flagP == 2 && flagFP == 1) {
            open_file(argv[i], optionsF);
            flagFP = 0;
            flagP = 1;
            // optionsF->countP++;
          }
        }  // else 2
      }    // else
    }      // for 2
  }        // if
}
void open_file(char *argv, options *optionsF) {
  FILE *file;
  char *str = NULL;
  size_t n, c;
  if ((file = fopen(argv, "r")) != NULL) {
    while ((int)(c = getline(&str, &n, file)) != EOF) {
      //  Replacement '\n' on '\ 0' in end line
      if (str[strlen(str) - 1] == '\n') str[strlen(str) - 1] = '\0';
      strcpy(optionsF->templ[optionsF->countP++], str);
    }
    optionsF->err = 0;
    free(str);
    fclose(file);
  } else {
    if (!optionsF->opt_s) {
      optionsF->err = 1;
      printf("s21_grep: %s: %s\n", argv, strerror(errno));
    }
  }
}
void output(options *optionsF) {
  // We set the priority of the flags
  if (optionsF->opt_l) {
    optionsF->opt_n = 0;
    optionsF->opt_o = 0;
  }
  if (optionsF->opt_c) {
    optionsF->opt_n = 0;
    optionsF->opt_o = 0;
  }
  if (optionsF->opt_v) {
    optionsF->opt_o = 0;
  }
  // We process regular expressions
  regex_t regex;
  int i = 0;
  int success;
  regmatch_t match[1];
  FILE *file;
  int numb_line;
  int flag_match;
  for (i = 0; i < optionsF->countF; i++) {
    char *temp_string = NULL;
    size_t n, c;
    if ((file = fopen(optionsF->text_name[i], "r")) != NULL) {
      numb_line = 0;
      // Read the line behind the line from the file
      int k = 0;
      while ((int)(c = getline(&temp_string, &n, file)) != EOF) {
        // Replacement '\n' on '\ 0' in end line
        if (temp_string[strlen(temp_string) - 1] == '\n')
          temp_string[strlen(temp_string) - 1] = '\0';
        int j;
        int flag = 0;
        flag_match = 0;
        for (j = 0; j < optionsF->countP && flag == 0; j++) {
          if (regcomp(&regex, optionsF->templ[j], optionsF->opt_i) == 0) {
            success = regexec(&regex, temp_string, 1, match, 0);
            if (!success) flag_match = 1;
          }
          regfree(&regex);
        }  // for
        // Flag v
        if (optionsF->opt_v == !flag_match) {
          numb_line++;
          flag = 1;
          if (optionsF->countF > 1 && !optionsF->opt_l && !optionsF->opt_h &&
              !optionsF->opt_c)
            printf("%s:", optionsF->text_name[i]);
          if (optionsF->opt_n) printf("%d:", k + 1);
          if (optionsF->opt_o) {
            for (int o = match[0].rm_so; o < match[0].rm_eo; o++) {
              printf("%c", temp_string[o]);
            }
            printf("\n");
          }
          if (!optionsF->opt_l && !optionsF->opt_c && !optionsF->opt_o)
            printf("%s\n", temp_string);
        }
        k++;
      }  // while
      fclose(file);
      if (optionsF->opt_l || optionsF->opt_c) {
        if (optionsF->opt_c) {
          if (optionsF->opt_l) {
            if (optionsF->countF > 1 && !optionsF->opt_h)
              printf("%s:", optionsF->text_name[i]);
            if (numb_line) printf("%d\n", 1);
            if (!numb_line) printf("%d\n", 0);
          } else {
            if (optionsF->countF > 1 && !optionsF->opt_h)
              printf("%s:", optionsF->text_name[i]);
            printf("%d\n", numb_line);
          }
        }
        if (optionsF->opt_l) {
          if (numb_line) printf("%s\n", optionsF->text_name[i]);
        }
      }
      free(temp_string);
    } else {
      if (!optionsF->opt_s && !optionsF->err)
        printf("s21_grep: %s: %s\n", optionsF->text_name[i], strerror(errno));
    }
  }
}

int main(int argc, char **argv) {
  options optionsF = {0};  // We declare a variable type of flag structure
                           // Initialize the structure of zeros
  if (argc <= 2) {
    printf(
        "usage: s21_grep [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B num] "
        "[-C[num]]\n"
        "[-e pattern] [-f file] [--binary-files=value] [--color=when]\n"
        "[--context[=num]] [--directories=action] [--label] [--line-buffered]\n"
        "[--null] [pattern] [file ...]\n");
  } else {
    parser_flags(argc, argv, &optionsF);
    output(&optionsF);
  }
  return 0;
}
