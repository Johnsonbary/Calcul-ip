#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void affichage_classe(char**, int *, char *);
void masque_reseau(int, char **);
void affichage_subnet(char *, char *, char **);
void affichage_broadcast(char*, int, char**, char*);
void number_div(int*);
void decoupage_reseau(int, char*, char*, int, char*, char*, char);
void traitement();
char *affichage();