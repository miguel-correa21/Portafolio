/****************************************************/
/* Archivo: globals.h                               */
/* Implementacion de elementos globales             */
/* Compiladores - ESCOM                             */
/* Miguel e Ivan                                    */
/****************************************************/

/* Los tipos globales y variables para el compilador
 * deben aparecer antes que otros archivos "include"*/

#ifndef  _GLOBALS_H_
#define  _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef YYPARSER
#include "bison.tab.h"
//#define ENDFILE 0
#endif


#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif


/* MAXRESERVED = el numero de palabras reservadas */
#define MAXRESERVED 8

typedef int TokenType;

extern FILE *source; //archivo de texto de codigo fuente
 extern  FILE *listing; //archivo de texto de salida de listado
 extern FILE *code; //archivo de texto de codigo para el simulador TM

 extern int lineno; //numero de linea fuente para el listado

/************************************************
 * arbol sintactico para el analisis sintantico
 */

typedef enum {StmtK, ExpK } NodeKind;
typedef enum {IfK, RepeatK, AssignK, ReadK, WriteK } StmtKind;
typedef enum {OpK, ConstK, IdK } ExpKind;

//ExpType es utilizado para verificacion de tipo
typedef enum {Void, Integer, Boolean } ExpType;

#define MAXCHILDREN 3

typedef struct treeNode {
    struct treeNode *child[MAXCHILDREN];
    struct treeNode *sibling;
    int lineno;
    NodeKind nodekind;
    union {
        StmtKind stmt;
        ExpKind exp;
    } kind;
    union {
        TokenType op;
        int val;
        char *name;
    } attr;
    ExpType type; //Para verificacion de tipo de expresiones
} TreeNode;


/************************************************
 * Marcas para rastreo
 */
/* EchoSource = tRUE cuasa que el programa fuente se
 * replique en el archivo de listado con numeros de
 * linea durante el analisis sintactico*/
extern int EchoSource;

/* TraceScan = TRUE causa que la informacion de token
 * sea impresa al archivo de listado a medida que cada
 * token sea reconocido por el analizador lexico */
extern int TraceScan;

/* TraceParse = TRUE causa que el arbol sintatico sea
 * impreso en el archivo del listado en forma linealizada
 * utilizando sangrias para los hijos */
extern int TraceParse;

/* TraceAnalize = TRUE causa que la tabla de simbolos
 * inserte y busque para informalo en el archivo de
 * listado*/
extern int TraceAnalyze;

/* TraceCode = TRUE cuasa que se escriban comentarios
 * al archivo de codigo TM a medida que se genera el
 * codigo*/
extern int TraceCode;

/* Error = TRUE evita pasos adicionales si se presenta un error */
extern  int Error;
#endif
