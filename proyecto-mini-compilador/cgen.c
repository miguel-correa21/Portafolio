/****************************************************/
/* Archivo: cgen.c                                  */
/* Implementacion de generador de codigo            */
/* Compiladores - ESCOM                             */
/* Miguel e Ivan                                    */
/****************************************************/

#include "globals.h"
#include "bison.tab.h"
#include "symtab.h"
#include "code.h"
#include "cgen.h"

/* tmpOffset es el desplazamiento de la memoria para las temperaturas
    Se decrementa cada vez que una temperatura es
    almacenado, e increminado cuando cargado de nuevo
*/
static int tmpOffset = 0;

/* Prototipo para generador interno de código recursivo. */
static void cGen (TreeNode * tree);

/* Procedimiento genStmt genera código en un nodo de declaración */
static void genStmt( TreeNode * tree)
{ TreeNode * p1, * p2, * p3;
  int savedLoc1,savedLoc2,currentLoc;
  int loc;
  switch (tree->kind.stmt) {

      case IfK :
         if (TraceCode) emitComment("-> if") ;
         p1 = tree->child[0] ;
         p2 = tree->child[1] ;
         p3 = tree->child[2] ;
         /* generar código para expresión de prueba */
         cGen(p1);
         savedLoc1 = emitSkip(1) ;
         emitComment("SI: salto a SINO comienza aqui");
         /* recurse on then part */
         cGen(p2);
         savedLoc2 = emitSkip(1) ;
         emitComment("SI, salto al final");
         currentLoc = emitSkip(0) ;
         emitBackup(savedLoc1) ;
         emitRM_Abs("JEQ",ac,currentLoc,"SI, salto a SINO");
         emitRestore() ;
          /* repetir en otra parte */
         cGen(p3);
         currentLoc = emitSkip(0) ;
         emitBackup(savedLoc2) ;
         emitRM_Abs("LDA",pc,currentLoc,"Salto al final") ;
         emitRestore() ;
         if (TraceCode)  emitComment("<- SI") ;
         break; /* if_k */

      case RepeatK:
         if (TraceCode) emitComment("-> Repetir") ;
         p1 = tree->child[0] ;
         p2 = tree->child[1] ;
         savedLoc1 = emitSkip(0);
         emitComment("Repetir: regreso despues del salto");
          /* generar código para el cuerpo */
         cGen(p1);
         /* generar código para prueba */
         cGen(p2);
         emitRM_Abs("JEQ",ac,savedLoc1,"Repetir: salto de regreso");
         if (TraceCode)  emitComment("<- Repetir") ;
         break; /* repeat */

      case AssignK:
         if (TraceCode) emitComment("-> Asignar") ;
         /* generate code for rhs */
         cGen(tree->child[0]);
         /* now store value */
         loc = st_lookup(tree->attr.name);
         emitRM("ST",ac,loc,gp,"Asignar valor guardado");
         if (TraceCode)  emitComment("<- Asignar") ;
         break; /* assign_k */

      case ReadK:
         emitRO("IN",ac,0,0,"Leer valor");
         loc = st_lookup(tree->attr.name);
         emitRM("ST",ac,loc,gp,"Leer valor guardado");
         break;
      case WriteK:
          /* generar codigo para expresion escribir */
         cGen(tree->child[0]);
         /* now output it */
         emitRO("SALIDA",ac,0,0,"Escribir ac");
         break;
      default:
         break;
    }
} /* genStmt */

/* Procedimiento genExp genera código en un nodo de expresión */
static void genExp( TreeNode * tree)
{ int loc;
  TreeNode * p1, * p2;
  switch (tree->kind.exp) {

    case ConstK :
      if (TraceCode) emitComment("-> Constante") ;
      /* código gen para cargar constante entero usando CC */
      emitRM("LDC",ac,tree->attr.val,0,"Cargar constante");
      if (TraceCode)  emitComment("<- Constante") ;
      break; /* ConstK */
    
    case IdK :
      if (TraceCode) emitComment("-> Id") ;
      loc = st_lookup(tree->attr.name);
      emitRM("LD",ac,loc,gp,"load id value");
      if (TraceCode)  emitComment("<- Id") ;
      break; /* IdK */

    case OpK :
         if (TraceCode) emitComment("-> Op") ;
         p1 = tree->child[0];
         p2 = tree->child[1];
          /* código gen para ac = izquierda arg */
         cGen(p1);
          /* código gen para empujar operando izquierda */
         emitRM("ST",ac,tmpOffset--,mp,"op: poner a izquierdo");
          /* código gen para ac = operando derecho */
         cGen(p2);
          /* ahora carga el operando izquierdo */
         emitRM("LD",ac1,++tmpOffset,mp,"op: cargar a izquierdo");
         switch (tree->attr.op) {
            case SUMA :
               emitRO("SUMA",ac,ac1,ac,"op +");
               break;
            case MENOS :
               emitRO("SUB",ac,ac1,ac,"op -");
               break;
            case MULT :
               emitRO("MUL",ac,ac1,ac,"op *");
               break;
            case DIV :
               emitRO("DIV",ac,ac1,ac,"op /");
               break;
            case LT :
               emitRO("SUB",ac,ac1,ac,"op <") ;
               emitRM("JLT",ac,2,pc,"br Si verdadero") ;
               emitRM("LDC",ac,0,ac,"Caso falso") ;
               emitRM("LDA",pc,1,pc,"Salto incondicional") ;
               emitRM("LDC",ac,1,ac,"Caso verdadero") ;
               break;
            case EQ :
               emitRO("SUB",ac,ac1,ac,"op ==");
               emitRM("JEQ",ac,2,pc,"br Si verdadero");
               emitRM("LDC",ac,0,ac,"Caso falso") ;
               emitRM("LDA",pc,1,pc,"Salto incondicional") ;
               emitRM("LDC",ac,1,ac,"Caso Verdadero") ;
               break;
            default:
               emitComment("BUG: Operador desconocido");
               break;
         } /* case op */
         if (TraceCode)  emitComment("<- Op") ;
         break; /* OpK */

    default:
      break;
  }
} /* genExp */

/* Pprocedimiento cGen código generado recursivamente por *
 * árbol transversal
 */
static void cGen( TreeNode * tree)
{ if (tree != NULL)
  { switch (tree->nodekind) {
      case StmtK:
        genStmt(tree);
        break;
      case ExpK:
        genExp(tree);
        break;
      default:
        break;
    }
    cGen(tree->sibling);
  }
}

/**********************************************/
/* La función principal del generador de código.*/
/**********************************************/
/* Procedimiento codeGen genera código a un código
  * Archivo por recorrido del árbol de sintaxis. los
  * segundo parámetro (archivo de código) es el nombre del archivo
  * del archivo de código, y se utiliza para imprimir el
  * Nombre del archivo como comentario en el archivo de código.
 */
void codeGen(TreeNode * syntaxTree, char * codefile)
{  char * s = malloc(strlen(codefile)+7);
   strcpy(s,"Archivo : ");
   strcat(s,codefile);
   emitComment("Compilacion exitosa ");
   emitComment(s);
   /* generate standard prelude */
   emitComment("Standard prelude:");
   emitRM("LD",mp,0,ac,"cargada maxaddress de la ubicacion 0");
   emitRM("ST",ac,0,ac,"limpiar localizacion");
   emitComment("Fin del ciclo estandar.");
   /* generate code for TINY program */
   cGen(syntaxTree);
   /* finish */
   emitComment("Fin de la ejecucion.");
   emitRO("DETENER",0,0,0,"");
}
