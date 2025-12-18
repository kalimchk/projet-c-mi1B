#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>

int is_usine_line(char *line);
int parse_usine_line(char *line, char **id_usine, float *capacite_Mm3);

#endif
