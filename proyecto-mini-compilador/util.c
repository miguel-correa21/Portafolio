/****************************************************/
/* Archivo: util.c                                  */
/* Implementacion de utilidades del compilador      */
/* Compiladores - ESCOM                             */
/* Miguel e Ivan                                    */
/****************************************************/


#include "globals.h"
#include "util.h"

/* Procedimiento printToken imprime un token
  * y su lexema al archivo listado.
 */
void printToken( TokenType token, const char* tokenString )
{ switch (token)
  { case SI:
    case MIENTRAS:
    case SINO:
    case FIN:
    case REPETIR:
    case HASTA:
    case LEER:
    case ESCRIBIR:
      fprintf(listing,
         "palabra reservada: %s\n",tokenString);
      break;
    case ASIGNAR: fprintf(listing,":=\n"); break;
    case LT: fprintf(listing,"<\n"); break;
    case EQ: fprintf(listing,"=\n"); break;
    case LPAREN: fprintf(listing,"(\n"); break;
    case RPAREN: fprintf(listing,")\n"); break;
    case SEMI: fprintf(listing,";\n"); break;
    case SUMA: fprintf(listing,"+\n"); break;
    case MENOS: fprintf(listing,"-\n"); break;
    case MULT: fprintf(listing,"*\n"); break;
    case DIV: fprintf(listing,"/\n"); break;
    case 0: fprintf(listing,"EOF\n"); break;
    case NUM:
      fprintf(listing,
          "NUM, valor= %s\n",tokenString);
      break;
    case ID:
      fprintf(listing,
          "ID, nombre= %s\n",tokenString);
      break;
    case ERROR:
      fprintf(listing,
          "ERROR: %s\n",tokenString);
      break;
    default: /* nunca deberia pasar */
      fprintf(listing,"token desconocido: %d\n",token);
  }
}

/* La función newStmtNode crea una nueva sentencia.
  * nodo para la construcción del árbol de sintaxis
 */
TreeNode * newStmtNode(StmtKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = StmtK;
    t->kind.stmt = kind;
    t->lineno = lineno;
  }
  return t;
}

/* La función newExpNode crea una nueva expresión
  * nodo para la construcción del árbol de sintaxis
 */
TreeNode * newExpNode(ExpKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = ExpK;
    t->kind.exp = kind;
    t->lineno = lineno;
    t->type = Void;
  }
  return t;
}

/* La función copyString asigna y realiza una nueva.
  * copia de una cadena existente
 */
char * copyString(char * s)
{ int n;
  char * t;
  if (s==NULL) return NULL;
  n = strlen(s)+1;
  t = malloc(n);
  if (t==NULL)
    fprintf(listing,"Fuera de rango error en linea %d\n",lineno);
  else strcpy(t,s);
  return t;
}

/* Variable indentno is used by printTree to
 * store current number of spaces to indent
 */
static int indentno = 0;

/* macros to increase/decrease indentation */
#define INDENT indentno+=2
#define UNINDENT indentno-=2

/* printSpaces indents by printing spaces */
static void printSpaces(void)
{ int i;
  for (i=0;i<indentno;i++)
    fprintf(listing," ");
}

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 */
void printTree( TreeNode * tree )
{ int i;
  INDENT;
  while (tree != NULL) {
    printSpaces();
    if (tree->nodekind==StmtK)
    { switch (tree->kind.stmt) {
        case IfK:
          fprintf(listing,"SI\n");
          break;
        case RepeatK:
          fprintf(listing,"REPETIR\n");
          break;
        case AssignK:
          fprintf(listing,"ASIGNAR A: %s\n",tree->attr.name);
          break;
        case ReadK:
          fprintf(listing,"LEER: %s\n",tree->attr.name);
          break;
        case WriteK:
          fprintf(listing,"ESCRIBIR\n");
          break;
        default:
          fprintf(listing,"ExpNode desconocido\n");
          break;
      }
    }
    else if (tree->nodekind==ExpK)
    { switch (tree->kind.exp) {
        case OpK:
          fprintf(listing,"Op: ");
          printToken(tree->attr.op,"\0");
          break;
        case ConstK:
          fprintf(listing,"Const: %d\n",tree->attr.val);
          break;
        case IdK:
          fprintf(listing,"Id: %s\n",tree->attr.name);
          break;
        default:
          fprintf(listing,"ExpNode desconocido\n");
          break;
      }
    }
    else fprintf(listing,"ExpNode desconocido\n");
    for (i=0;i<MAXCHILDREN;i++)
         printTree(tree->child[i]);
    tree = tree->sibling;
  }
  UNINDENT;
}
