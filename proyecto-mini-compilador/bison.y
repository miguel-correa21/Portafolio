/****************************************************/
/* Archivo: byson.y                                 */
/* Definicion de gramatica del compilador BISON     */
/* Compiladores - ESCOM                             */
/* Miguel e Ivan                                    */
/****************************************************/

%{
#define YYPARSER // Distinge la salida Bison de otros archivos de codigo

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"
#include "cgen.h"
#include "analyze.h"

#define YYSTYPE TreeNode *
static char * savedName; // Para su uso en asignaciones
static int savedLineNo; // Idem
static TreeNode * savedTree; // Almacena el arbol sintatico para un retorno posterior

%}
%token SI MIENTRAS SINO FIN REPETIR HASTA LEER ESCRIBIR
%token ID NUM
%token ASIGNAR EQ LT SUMA MENOS MULT DIV LPAREN RPAREN SEMI
%token ERROR 

%% // Gramatica para compilador

program     : stmt_seq
                 { savedTree = $1; }
            ;
stmt_seq    : stmt_seq SEMI stmt
                { YYSTYPE t = $1;
                    if (t != NULL)
                    { while (t->sibling != NULL)
                        t = t->sibling;
                      t->sibling = $3;
                      $$ = $1;}
                      else $$ = $3;
                }
            | stmt  { $$ = $1; }
            ;
stmt        : if_stmt { $$ = $1; }
            | repeat_stmt { $$ = $1; }
            | assign_stmt { $$ = $1; }
            | read_stmt { $$ = $1; }
            | write_stmt { $$ = $1; }
            | error { $$ = NULL; }
            ;
if_stmt     : SI exp MIENTRAS stmt_seq FIN
                { $$ = newStmtNode(IfK);
                  $$->child[0] = $2;
                  $$->child[1] = $4;
                }
			| SI exp MIENTRAS stmt_seq HASTA exp
				{
					$$ = newStmtNode(RepeatK);
					$$->child[0] = $2;
					$$->child[1] = $4;
					$$->child[2] = $6;
				}
            ;
repeat_stmt : REPETIR stmt_seq HASTA exp
                {  $$ = newStmtNode(RepeatK);
                   $$->child[0] = $2;
                   $$->child[1] = $4;
                }
            ;
assign_stmt : ID { savedName = copyString(tokenString);
                   savedLineNo = lineno; }
              ASIGNAR exp
                 { $$ = newStmtNode(AssignK);
                   $$->child[0] = $4;
                   $$->attr.name = savedName;
                   $$->lineno = savedLineNo;
                 }
            ;
read_stmt   : LEER ID
                 { $$ = newStmtNode(ReadK);
                   $$->attr.name =
                     copyString(tokenString);
                 }
            ;
write_stmt  : ESCRIBIR exp
                 { $$ = newStmtNode(WriteK);
                   $$->child[0] = $2;
                 }
exp         : simple_exp LT simple_exp
                 { $$ = newStmtNode(OpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->attr.op = LT;
                 }
            | simple_exp EQ simple_exp
                 { $$ = newStmtNode(OpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->attr.op = EQ;
                 }
            | simple_exp { $$ = $1; }
            ;
simple_exp  : simple_exp SUMA term
                 { $$ = newExpNode(OpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->attr.op = SUMA;
                 }
            | simple_exp MENOS term
                 { $$ = newExpNode(OpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->attr.op = MENOS;
                 }
            | term { $$ = $1; }
            ;
term        : term MULT factor
                 { $$ = newExpNode(OpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->attr.op = MULT;
                 }
            | term DIV factor
                 { $$ = newExpNode(OpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->attr.op = DIV;
                 }
            | factor { $$ = $1; }
            ;
factor      : LPAREN exp RPAREN
                 { $$ = $2; }
            | NUM
                 { $$ = newExpNode(ConstK);
                   $$->attr.val = atoi(tokenString);
                 }
            | ID { $$ = newExpNode(IdK);
                   $$->attr.name =
                         copyString(tokenString);
                 }
            | error { $$ = NULL; }
            ;

%%

int yyerror(char * message)
{ fprintf(listing, "Error de sintaxis en la linea %d: %s\n",lineno,message);
  fprintf(listing, "Token actual: ");
  Error = TRUE;
  return 0;
}

/* yylex llama a getToken para hacer la salida Bison
 * compatible con versiones mas antiguas del analizador lexico TINY
 */

//int yylex(void)
//{ return getToken(); }

//TreeNode * parse(void)
//{ yyparse();
// return savedTree;
//}

/* set NO_PARSE to TRUE to get a scanner-only compiler */
#define NO_PARSE FALSE 
/* set NO_ANALYZE to TRUE to get a parser-only compiler */
#define NO_ANALYZE FALSE 

/* set NO_CODE to TRUE to get a compiler that does not
 * generate code
 */
#define NO_CODE FALSE

//#if NO_PARSE
//#else
//#if !NO_ANALYZE
//#if !NO_CODE
//#endif
//#endif
//#endif

/* allocate global variables */
int lineno = 0;
FILE * source;
FILE * listing;
FILE * code;

/* allocate and set tracing flags */
int EchoSource = FALSE;
int TraceScan = FALSE;
int TraceParse = FALSE;
int TraceAnalyze = FALSE;
int TraceCode = FALSE;

int Error = FALSE;

int main( int argc, char * argv[] )
{ TreeNode * syntaxTree;
  char pgm[120]; /* source code file name */
  if (argc != 2)
    { fprintf(stderr,"Usar: %s <filename>\n",argv[0]);
      exit(1);
    }
  strcpy(pgm,argv[1]) ;
  if (strchr (pgm, '.') == NULL)
     strcat(pgm,".escom");
  source = fopen(pgm,"r");
  if (source==NULL)
  { fprintf(stderr,"Archivo %s no encontrado\n",pgm);
    exit(1);
  }
  listing = stdout; /* send listing to screen */
  fprintf(listing,"\nCOMPILACION: %s\n",pgm);
#if NO_PARSE
  while (getToken()!= 0);
#else
  syntaxTree = parse();
  if (TraceParse) {
    fprintf(listing,"\nArbol sintactico:\n");
    printTree(syntaxTree);
  }
#if !NO_ANALYZE
  if (! Error)
  { if (TraceAnalyze) fprintf(listing,"\nConstruyendo tabla de simbolos...\n");
    buildSymtab(syntaxTree);
    if (TraceAnalyze) fprintf(listing,"\nVerificando tipos...\n");
    typeCheck(syntaxTree);
    if (TraceAnalyze) fprintf(listing,"\nVerificacion de tipos finalizada\n");
  }
#if !NO_CODE
  if (! Error)
  { 
	char * codefile;
    int fnlen = strcspn(pgm,".");
    codefile = (char *) calloc(fnlen+4, sizeof(char));
    strncpy(codefile,pgm,fnlen);
    strcat(codefile,".scm");
    code = fopen(codefile,"w");
    if (code == NULL)
    { printf("No se puede abrir el archivo %s\n",codefile);
      exit(1);
    }
    codeGen(syntaxTree,codefile);
    fclose(code);
  }
#endif
#endif
#endif
  fclose(source);
  return 0;
}
