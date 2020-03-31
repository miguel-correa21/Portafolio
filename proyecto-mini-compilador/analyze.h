/****************************************************/
/* Archivo: analyze.h                               */
/* Implementacion de analizador semantico           */
/* Compiladores - ESCOM                             */
/* Miguel e Ivan                                    */
/****************************************************/


#ifndef _ANALYZE_H_
#define _ANALYZE_H_

/* La función buildSymtab construye el símbolo
  * tabla por preorder recorrido del árbol de sintaxis
 */
void buildSymtab(TreeNode *);

/* Procedimiento typeCheck realiza verificación de tipo
  * por un recorrido de árbol de sintaxis de orden posterior
 */
void typeCheck(TreeNode *);

#endif
