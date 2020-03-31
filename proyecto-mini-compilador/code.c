/****************************************************/
/* Archivo: code.c                                  */
/* Implementacion de emision de utiidades           */
/* Compiladores - ESCOM                             */
/* Miguel e Ivan                                    */
/****************************************************/
#include "globals.h"
#include "code.h"
#include "bison.tab.h"

/* Número de ubicación de  para la emisión de instrucciones actuales */
static int emitLoc = 0 ;

/* La ubicación más alta emitida hasta el momento
    Para uso en conjunto con emitSkip,
    emitBackup, y emitRestore */
static int highEmitLoc = 0;

/* Procedimiento emitComment imprime una línea de comentario.
  * con el comentario c en el archivo de código
 */
void emitComment( char * c )
{ if (TraceCode) fprintf(code,"* %s\n",c);}

/* Procedimiento emitRO emite un registro solo
  * Instrucción de TM
  * op = el opcode
  * r = registro objetivo
  * s = 1er registro fuente
  * t = 2do registro fuente
  * c = un comentario que se imprimirá si TraceCode es VERDADERO
 */
void emitRO( char *op, int r, int s, int t, char *c)
{ fprintf(code,"%3d:  %5s  %d,%d,%d ",emitLoc++,op,r,s,t);
  if (TraceCode) fprintf(code,"\t%s",c) ;
  fprintf(code,"\n") ;
  if (highEmitLoc < emitLoc) highEmitLoc = emitLoc ;
} /* emitRO */

/* Procedimiento emitRM emite un registro a memoria
  * Instrucción de TM
  * op = el opcode
  * r = registro objetivo
  * d = el desplazamiento
  * s = el registro base
  * c = un comentario que se imprimirá si TraceCode es VERDADERO
 */
void emitRM( char * op, int r, int d, int s, char *c)
{ fprintf(code,"%3d:  %5s  %d,%d(%d) ",emitLoc++,op,r,d,s);
  if (TraceCode) fprintf(code,"\t%s",c) ;
  fprintf(code,"\n") ;
  if (highEmitLoc < emitLoc)  highEmitLoc = emitLoc ;
} /* emitRM */

/* La función emitSkip omite el código "howMany"
  * Ubicaciones para posterior backpatch. También
  * devuelve la posición del código actual
 */
int emitSkip( int howMany)
{  int i = emitLoc;
   emitLoc += howMany ;
   if (highEmitLoc < emitLoc)  highEmitLoc = emitLoc ;
   return i;
} /* emitSkip */

/* Procedimiento emitBackup respalda hasta
  * loc = una ubicación previamente omitida
 */
void emitBackup( int loc)
{ if (loc > highEmitLoc) emitComment("BUG in emitBackup");
  emitLoc = loc ;
} /* emitBackup */

/* Procedimiento emitRestore restaura la corriente
  * Posición del código al más alto anteriormente.
  * posición no emitida
 */
void emitRestore(void)
{ emitLoc = highEmitLoc;}

/* Procedimiento emitRM_Abs convierte una referencia absoluta
  * a una referencia relativa al PC al emitir un
  * Instrucción de registro a memoria TM
  * op = el opcode
  * r = registro objetivo
  * a = la ubicación absoluta en la memoria
  * c = un comentario que se imprimirá si TraceCode es VERDADERO
 */
void emitRM_Abs( char *op, int r, int a, char * c)
{ fprintf(code,"%3d:  %5s  %d,%d(%d) ",
               emitLoc,op,r,a-(emitLoc+1),pc);
  ++emitLoc ;
  if (TraceCode) fprintf(code,"\t%s",c) ;
  fprintf(code,"\n") ;
  if (highEmitLoc < emitLoc) highEmitLoc = emitLoc ;
} /* emitRM_Abs */