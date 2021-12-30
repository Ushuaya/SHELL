//
//  tree.h
//  
//
//  Created by Ivan on 28.11.2020.
//


#include <stdio.h>
#include "syn.h"
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>

//char ** list;


enum type_of_next{
    NXT, AND, OR   // виды связей соседних команд в списке команд
};

enum type_of_graph
{
    BEGIN,
    CONV,
    CONV1,
    IN,
    OUT,
    OUT_APP,
    IN1,
    OUT1,
    BACKGRND,
    POINTCOMMA, 
    END,
    IN_END,
    CIDIOT,
    AND_CMD,
    OR_CMD,
    NULL_CMD
};

struct cmd_inf {
    char ** argv; // список из имени команды и аргументов
    char *infile; // переназначенный файл стандартного ввода
    char *outfile; // переназначенный файл стандартного вывода
    int append;
    int backgrnd; // =1, если команда подлежит выполнению в фоновом режиме
    struct cmd_inf* psubcmd; // команды для запуска в дочернем shell
    struct cmd_inf* pipe; // следующая команда после "|"
    struct cmd_inf* next; // следующая после ";" (или после "&")
    enum type_of_next type;// связь со следующей командой через ; или && или ||
};


char** plex; /* указатель текущей лексемы, начальное значение передается через параметр
 //функции build_tree(), список list – это массив указателей на лексемы-строки */
typedef struct cmd_inf * tree;
tree make_cmd(); /* создает дерево из одного элемента, обнуляет все поля */
void make_bgrnd(tree t); /* устанавливает поле backgrnd=1 во всех командах конвейера t */
//add_arg(); /* добавляет очередной элемент в массив argv текущей команды */
 /* предыдущая команда, лучше назвать ее prev_cmd, тоже локальная */

typedef struct cmd_inf * tree;
typedef struct cmd_inf node;

void print_tree(tree, int);
tree build_tree(char **);
void clear_tree(tree );




