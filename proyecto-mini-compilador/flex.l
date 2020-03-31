/****************************************************/
/* Archivo: flex.l                                  */
/* Especificacion lex                               */
/* Compiladores - ESCOM                             */
/* Miguel e Ivan                                    */
/****************************************************/
%{
#include "globals.h"
#include "util.h"
#include "scan.h"
#include "bison.tab.h"
/* Lexema del identificador o palabra reservada */
char tokenString[MAXTOKENLEN+1];
%}

digit           [0-9]
number          {digit}+
letter          [a-zA-Z]
identifier      {letter}+
newline         \n
whitespace      [ \t]+

%%

"si"            {return SI;}
"entonces"      {return MIENTRAS;}
"sino"          {return SINO;}
"fin"           {return FIN;}
"repetir"       {return REPETIR;}
"hasta"         {return HASTA;}
"leer"          {return LEER;}
"escribir"      {return ESCRIBIR;}
":="            {return ASIGNAR;}
"="             {return EQ;}
"<"             {return LT;}
"+"             {return SUMA;}
"-"             {return MENOS;}
"*"             {return MULT;}
"/"             {return DIV;}
"("             {return LPAREN;}
")"             {return RPAREN;}
";"             {return SEMI;}
{number}        {return NUM;}
{identifier}    {return ID;}
{newline}       {lineno++;}
{whitespace}    {/* salta espacio en blanco */}
"{"             { char c;
                  do
                  { c = input();
                    if (c == '\n') lineno++;
                  } while (c != '}');
                }
.               {return ERROR;}

%%



typedef enum
   { START,INASSIGN,INCOMMENT,INNUM,INID,DONE }
   StateType;

/* lexema de identificador o palabra reservada */
char tokenString[MAXTOKENLEN+1];

/* BUFLEN = longitud del buffer de entrada para
    líneas de código fuente */
#define BUFLEN 256

static char lineBuf[BUFLEN]; /* mantiene la línea actual*/
static int linepos = 0; /* posición actual en LineBuf */
static int bufsize = 0; /* tamaño actual de la cadena de búfer */
static int EOF_flag = FALSE; /* corrige el comportamiento de ungetNextChar en EOF */


static int getNextChar(void)
{ if (!(linepos < bufsize))
  { lineno++;
    if (fgets(lineBuf,BUFLEN-1,source))
    { if (EchoSource) fprintf(listing,"%4d: %s",lineno,lineBuf);
      bufsize = strlen(lineBuf);
      linepos = 0;
      return lineBuf[linepos++];
    }
    else
    { EOF_flag = TRUE;
      return EOF;
    }
  }
  else return lineBuf[linepos++];
}

/* ungetNextChar hace un seguimiento de un personaje
    en lineaBuf */
static void ungetNextChar(void)
{ if (!EOF_flag) linepos-- ;}

/* tabla de búsqueda de palabras reservadas */
static struct
    { char* str;
      TokenType tok;
    } reservedWords[MAXRESERVED]
   = {{"si",SI},{"entonces",MIENTRAS},{"sino",SINO},{"fin",FIN},
      {"repetir",REPETIR},{"hasta",HASTA},{"leer",LEER},
      {"escribir",ESCRIBIR}};

/* buscar un identificador para ver si es una palabra reservada * /
/ * utiliza la búsqueda lineal */
static TokenType reservedLookup (char * s)
{ int i;
  for (i=0;i<MAXRESERVED;i++)
    if (!strcmp(s,reservedWords[i].str))
      return reservedWords[i].tok;
  return ID;
}

/****************************************/
/* La función principal del escáner.  */
/****************************************/
/* La función getToken devuelve el
  * siguiente token en el archivo fuente
 */
TokenType getToken(void)
{  /* índice para almacenar en tokenString*/
   int tokenStringIndex = 0;
   /* mantiene el token actual para ser devuelto */
   TokenType currentToken;
   /* estado actual - siempre comienza en START */
   StateType state = START;
   /* bandera para indicar guardar en tokenString*/
   int save;
   while (state != DONE)
   { int c = getNextChar();
     save = TRUE;
     switch (state)
     { case START:
         if (isdigit(c))
           state = INNUM;
         else if (isalpha(c))
           state = INID;
         else if (c == ':')
           state = INASSIGN;
         else if ((c == ' ') || (c == '\t') || (c == '\n'))
           save = FALSE;
         else if (c == '{')
         { save = FALSE;
           state = INCOMMENT;
         }
         else
         { state = DONE;
           switch (c)
           { case EOF:
               save = FALSE;
               currentToken = 0;
               break;
             case '=':
               currentToken = EQ;
               break;
             case '<':
               currentToken = LT;
               break;
             case '+':
               currentToken = SUMA;
               break;
             case '-':
               currentToken = MENOS;
               break;
             case '*':
               currentToken = MULT;
               break;
             case '/':
               currentToken = DIV;
               break;
             case '(':
               currentToken = LPAREN;
               break;
             case ')':
               currentToken = RPAREN;
               break;
             case ';':
               currentToken = SEMI;
               break;
             default:
               currentToken = ERROR;
               break;
           }
         }
         break;
       case INCOMMENT:
         save = FALSE;
         if (c == EOF)
         { state = DONE;
           currentToken = 0;
         }
         else if (c == '}') state = START;
         break;
       case INASSIGN:
         state = DONE;
         if (c == '=')
           currentToken = ASIGNAR;
         else
         { /* copia de seguridad en la entrada */
           ungetNextChar();
           save = FALSE;
           currentToken = ERROR;
         }
         break;
       case INNUM:
         if (!isdigit(c))
         { /* copia de seguridad en la entrada*/
           ungetNextChar();
           save = FALSE;
           state = DONE;
           currentToken = NUM;
         }
         break;
       case INID:
         if (!isalpha(c))
         { /* copia de seguridad en la entrada */
           ungetNextChar();
           save = FALSE;
           state = DONE;
           currentToken = ID;
         }
         break;
       case DONE:
       default: /* nunca debería suceder */
         fprintf(listing,"Error del escáner: estado= %d\n",state);
         state = DONE;
         currentToken = ERROR;
         break;
     }
     if ((save) && (tokenStringIndex <= MAXTOKENLEN))
       tokenString[tokenStringIndex++] = (char) c;
     if (state == DONE)
     { tokenString[tokenStringIndex] = '\0';
       if (currentToken == ID)
         currentToken = reservedLookup(tokenString);
     }
   }
   if (TraceScan) {
     fprintf(listing,"\t%d: ",lineno);
     printToken(currentToken,tokenString);
   }
   return currentToken;
} /* end getToken */

