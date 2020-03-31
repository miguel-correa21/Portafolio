/****************************************************/
/* Archivo: symtab.h                                */
/* Implementacion de tabla de simbolos              */
/* Compiladores - ESCOM                             */
/* Miguel e Ivan                                    */
/****************************************************/


#ifndef _SYMTAB_H_
#define _SYMTAB_H_

/* Procedimiento st_insert inserta números de línea y
  * Ubicaciones de memoria en la tabla de símbolos
  * loc = ubicación de la memoria se inserta sólo el
  * primera vez, de lo contrario ignorado
 */
void st_insert( char * name, int lineno, int loc );

/* La función st_lookup devuelve la memoria.
  * ubicación de una variable o -1 si no se encuentra
 */
int st_lookup ( char * name );

/* Procedimiento printSymTab imprime un formato.
  * Listado de los contenidos de la tabla de símbolos.
  * al archivo de listado
 */
void printSymTab(FILE * listing);

#endif
