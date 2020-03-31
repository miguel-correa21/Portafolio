/****************************************************/
/* Archivo: symtab.c                                */
/* Implementacion de tabla de simbolos              */
/* Compiladores - ESCOM                             */
/* Miguel e Ivan                                    */
/****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

/* SIZE es el tamaño de la tabla hash */
#define SIZE 211

/* SHIFT es el poder de dos utilizados como multiplicador.
en función hash */
#define SHIFT 4

/* la función hash */
static int hash ( char * key )
{ int temp = 0;
  int i = 0;
  while (key[i] != '\0')
  { temp = ((temp << SHIFT) + key[i]) % SIZE;
    ++i;
  }
  return temp;
}

/*La lista de números de línea de la fuente.
* código en el que se hace referencia a una variable
 */
typedef struct LineListRec
   { int lineno;
     struct LineListRec * next;
   } * LineList;

/* El registro en las listas de cubo para
* cada variable, incluido el nombre,
* ubicación de memoria asignada, y
* la lista de números de línea en la que
* Aparece en el código fuente.
 */
typedef struct BucketListRec
   { char * name;
     LineList lines;
     int memloc ; /* ubicación de memoria para la variable */
     struct BucketListRec * next;
   } * BucketList;

/* la tabla hash */
static BucketList hashTable[SIZE];

/*
 * Procedimiento st_insert inserta números de línea y
  * Ubicaciones de memoria en la tabla de símbolos
  * loc = ubicación de la memoria se inserta sólo el
  * primera vez, de lo contrario ignorado
 *
 */
void st_insert( char * name, int lineno, int loc )
{ int h = hash(name);
  BucketList l =  hashTable[h];
  while ((l != NULL) && (strcmp(name,l->name) != 0))
    l = l->next;
  if (l == NULL) /* variable aún no en la tabla */
  { l = (BucketList) malloc(sizeof(struct BucketListRec));
    l->name = name;
    l->lines = (LineList) malloc(sizeof(struct LineListRec));
    l->lines->lineno = lineno;
    l->memloc = loc;
    l->lines->next = NULL;
    l->next = hashTable[h];
    hashTable[h] = l; }
  else /* se encuentra en la tabla, así que simplemente agregue el número de línea */
  { LineList t = l->lines;
    while (t->next != NULL) t = t->next;
    t->next = (LineList) malloc(sizeof(struct LineListRec));
    t->next->lineno = lineno;
    t->next->next = NULL;
  }
} /* st_insert */

/* La función st_lookup devuelve la memoria.
* ubicación de una variable o -1 si no se encuentra
 */
int st_lookup ( char * name )
{ int h = hash(name);
  BucketList l =  hashTable[h];
  while ((l != NULL) && (strcmp(name,l->name) != 0))
    l = l->next;
  if (l == NULL) return -1;
  else return l->memloc;
}

/*
 * Procedimiento printSymTab imprime un formato.
  * Listado de los contenidos de la tabla de símbolos.
  * al archivo de listado
 */
void printSymTab(FILE * listing)
{ int i;
  fprintf(listing,"Variable\tUbicación\tNúmero de linea\n");
  fprintf(listing,"--------\t---------\t---------------\n");
  for (i=0;i<SIZE;++i)
  { if (hashTable[i] != NULL)
    { BucketList l = hashTable[i];
      while (l != NULL)
      { LineList t = l->lines;
        fprintf(listing,"%-14s ",l->name);
        fprintf(listing,"%-8d  ",l->memloc);
        while (t != NULL)
        { fprintf(listing,"%4d ",t->lineno);
          t = t->next;
        }
        fprintf(listing,"\n");
        l = l->next;
      }
    }
  }
} /* printSymTab */