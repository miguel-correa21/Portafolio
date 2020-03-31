/****************************************************/
/* Archivo: scan.h                                  */
/* Implementacion de interfaz scanner               */
/* Compiladores - ESCOM                             */
/* Miguel e Ivan                                    */
/****************************************************/

#ifndef _SCAN_H_
#define _SCAN_H_

/* MAXTOKENLEN es el tamaño máximo de un token */
#define MAXTOKENLEN 40

/* tokenString array almacena el lexema de cada token */
extern char tokenString[MAXTOKENLEN+1];

/* La función getToken devuelve el
  * siguiente token en el archivo fuente
 */
TokenType getToken(void);

#endif