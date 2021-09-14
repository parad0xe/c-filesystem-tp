#ifndef TP_UTILS_H
#define TP_UTILS_H

int len(char* str);
char* format(char* str, ...);
void echo(char* str, ...);
char** explode(char* data, int data_size, char delimiter);
void free_explode(char** tokens);
char* to_string(int n);

#endif //TP_UTILS_H