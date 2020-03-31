/****************************************************/
/* Archivo: code.h                                  */
/* Implementacion de emision de utiidades           */
/* Compiladores - ESCOM                             */
/* Miguel e Ivan                                    */
/****************************************************/

#ifndef _CODE_H_
#define _CODE_H_

/* pc = contador de programa  */
#define  pc 7

/* mp = "puntero de memoria" puntos
  * a la parte superior de la memoria (para almacenamiento temporal)
 */
#define  mp 6

/* gp = "puntero global" puntos
  * al fondo de la memoria para (global)
  * almacenamiento variable
 */
#define gp 5

/* acumulador */
#define  ac 0

/* 2nd acumulador */
#define  ac1 1

/* utilidades de emisión de código */

/* Procedimiento emitComment imprime una línea de comentario.
  * con el comentario c en el archivo de código
 */
void emitComment( char * c );

/* Procedimiento emitRO emite un registro solo
  * Instrucción de TM
  * op = el opcode
  * r = registro objetivo
  * s = 1er registro fuente
  * t = 2do registro fuente
  * c = un comentario que se imprimirá si TraceCode es VERDADERO
 */
void emitRO( char *op, int r, int s, int t, char *c);

/* Procedimiento emitRM emite un registro a memoria
  * Instrucción de TM
  * op = el opcode
  * r = registro objetivo
  * d = el desplazamiento
  * s = el registro base
  * c = un comentario que se imprimirá si TraceCode es VERDADERO
 */
void emitRM( char * op, int r, int d, int s, char *c);

/* La función emitSkip omite el código "howMany"
  * Ubicaciones para posterior backpatch. También
  * devuelve la posición del código actual
 */
int emitSkip( int howMany);

/* Procedimiento emitBackup respalda hasta
  * loc = una ubicación previamente omitida
 */
void emitBackup( int loc);

/* Procedimiento emitRestore restaura la corriente
  * Posición del código al más alto anteriormente.
  * posición no emitida
 */
void emitRestore(void);

/* Procedimiento emitRM_Abs convierte una referencia absoluta
  * a una referencia relativa al PC al emitir un
  * Instrucción de registro a memoria TM
  * op = el opcode
  * r = registro objetivo
  * a = la ubicación absoluta en la memoria
  * c = un comentario que se imprimirá si TraceCode es VERDADERO
 */
void emitRM_Abs( char *op, int r, int a, char * c);

#endif