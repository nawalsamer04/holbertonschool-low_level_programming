/* main.h */
#ifndef MAIN_H
#define MAIN_H

int **alloc_grid(int width, int height);
int _putchar(char c); /* required by project checker */
void free_grid(int **grid, int height);
char *argstostr(int ac, char **av);
#endif /* MAIN_H */

