/****************************************************/
/* Archivo: util.h                                  */
/* Implementacion de utilidades del compilador      */
/* Compiladores - ESCOM                             */
/* Miguel e Ivan                                    */
/****************************************************/

#ifndef _UTIL_H_
#define _UTIL_H_

/*
 * Procedimiento printToken imprime un token
* y su lexema al archivo listado.
 */
void printToken( TokenType, const char* );

/*La función newStmtNode crea una nueva sentencia.
  * nodo para la construcción del árbol de sintaxis
 */
TreeNode * newStmtNode(StmtKind);

/* La función newExpNode crea una nueva expresión
  * nodo para la construcción del árbol de sintaxis
 */
TreeNode * newExpNode(ExpKind);

/* La función copyString asigna y realiza una nueva.
  * copia de una cadena existente
 */
char * copyString( char * );

/* procedimiento printTree imprime un árbol de sintaxis al
* archivo de listado usando sangría para indicar subárboles
 */
void printTree( TreeNode * );

#endif
