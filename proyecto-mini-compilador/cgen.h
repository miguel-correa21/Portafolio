/****************************************************/
/* Archivo: cgen.h                                  */
/* Implementacion de generador de codigo            */
/* Compiladores - ESCOM                             */
/* Miguel e Ivan                                    */
/****************************************************/

#ifndef _CGEN_H_
#define _CGEN_H_

/* Procedimiento codeGen genera código a un código
  * Archivo por recorrido del árbol de sintaxis. los
  * segundo parámetro (archivo de código) es el nombre del archivo
  * del archivo de código, y se utiliza para imprimir el
  * Nombre del archivo como comentario en el archivo de código.
 */
void codeGen(TreeNode * syntaxTree, char * codefile);

#endif
