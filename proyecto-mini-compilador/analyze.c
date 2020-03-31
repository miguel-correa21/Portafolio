/****************************************************/
/* Archivo: analyze.c                               */
/* Implementacion de analizador semantico           */
/* Compiladores - ESCOM                             */
/* Miguel e Ivan                                    */
/****************************************************/

#include "globals.h"
#include "symtab.h"
#include "analyze.h"
#include "bison.tab.h"

/*contador para ubicaciones de memoria variable  */
static int location = 0;

/*
 * El procedimiento transversal es un genérico recursivo.
  * Rutina transversal del árbol de sintaxis:
  * aplica preProc en preorder y postproc
  * en orden posterior al árbol apuntado por t
 */
static void traverse( TreeNode * t,
               void (* preProc) (TreeNode *),
               void (* postProc) (TreeNode *) )
{ if (t != NULL)
  { preProc(t);
    { int i;
      for (i=0; i < MAXCHILDREN; i++)
        traverse(t->child[i],preProc,postProc);
    }
    postProc(t);
    traverse(t->sibling,preProc,postProc);
  }
}

/*
 * nullProc es un procedimiento de no hacer nada para
* generar solo preorden o solo postorder
* travesías de travesía
 */
static void nullProc(TreeNode * t)
{ if (t==NULL) return;
  else return;
}

/*
Procedimiento insertNode inserta
  * identificadores almacenados en t en
  * la tabla de símbolos
 */
static void insertNode( TreeNode * t)
{ switch (t->nodekind)
  { case StmtK:
      switch (t->kind.stmt)
      { case AssignK:
        case ReadK:
          if (st_lookup(t->attr.name) == -1)
              /*aún no en la tabla, así que trate como nueva definición */
            st_insert(t->attr.name,t->lineno,location++);
          else
              /* ya en la tabla, así que ignora la ubicación,
                añadir el número de línea de uso solamente */
              st_insert(t->attr.name,t->lineno,0);
          break;
        default:
          break;
      }
      break;
    case ExpK:
      switch (t->kind.exp)
      { case IdK:
          if (st_lookup(t->attr.name) == -1)
              /* aún no en la tabla, así que trate como nueva definición */
            st_insert(t->attr.name,t->lineno,location++);
          else
         /*ya en la tabla, así que ignora la ubicación,
                     añadir el número de línea de uso solamente */
            st_insert(t->attr.name,t->lineno,0);
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}

/*
 * La función buildSymtab construye el símbolo
 * tabla por preorder recorrido del árbol de sintaxis
 */
void buildSymtab(TreeNode * syntaxTree)
{ traverse(syntaxTree,insertNode,nullProc);
  if (TraceAnalyze)
  { fprintf(listing,"\nTabla de simbolos:\n\n");
    printSymTab(listing);
  }
}

static void typeError(TreeNode * t, char * message)
{ fprintf(listing,"Error en la linea %d: %s\n",t->lineno,message);
  Error = TRUE;
}

/* Procedimiento checkNode realiza
* comprobación de tipo en un solo nodo de árbol
 */
static void checkNode(TreeNode * t)
{ switch (t->nodekind)
  { case ExpK:
      switch (t->kind.exp)
      { case OpK:
          if ((t->child[0]->type != Integer) ||
              (t->child[1]->type != Integer))
            typeError(t,"Operacion aplicada a un no entero");
          if ((t->attr.op == EQ) || (t->attr.op == LT))
            t->type = Boolean;
          else
            t->type = Integer;
          break;
        case ConstK:
        case IdK:
          t->type = Integer;
          break;
        default:
          break;
      }
      break;
    case StmtK:
      switch (t->kind.stmt)
      { case IfK:
          if (t->child[0]->type == Integer)
            typeError(t->child[0],"si no es boleano");
          break;
        case AssignK:
          if (t->child[0]->type != Integer)
            typeError(t->child[0],"asignacion a un valor no entero");
          break;
        case WriteK:
          if (t->child[0]->type != Integer)
            typeError(t->child[0],"escribir en un valor no entero");
          break;
        case RepeatK:
          if (t->child[1]->type == Integer)
            typeError(t->child[1],"valor para repetir no es booleano");
          break;
        default:
          break;
      }
      break;
    default:
      break;

  }
}

/*
 * Procedimiento typeCheck realiza verificación de tipo
* por un recorrido de árbol de sintaxis de orden posterior
 */
void typeCheck(TreeNode * syntaxTree)
{ traverse(syntaxTree,nullProc,checkNode);
}
