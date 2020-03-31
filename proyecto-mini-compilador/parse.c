/****************************************************/
/* Archivo: parse.c                                 */
/* Implementacion de parser                         */
/* Compiladores - ESCOM                             */
/* Miguel e Ivan                                    */
/****************************************************/
#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"
#include "bison.tab.h"

static TokenType token; /* holds current token */

/* function prototypes for recursive calls */
static TreeNode * stmt_sequence(void);
static TreeNode * statement(void);
static TreeNode * if_stmt(void);
static TreeNode * repeat_stmt(void);
static TreeNode * assign_stmt(void);
static TreeNode * read_stmt(void);
static TreeNode * write_stmt(void);
static TreeNode * exp(void);
static TreeNode * simple_exp(void);
static TreeNode * term(void);
static TreeNode * factor(void);

static void syntaxError(char * message)
{ fprintf(listing,"\n>>> ");
  fprintf(listing,"Error de sintaxis en la linea %d: %s",lineno,message);
  Error = TRUE;
}

static void match(TokenType expected)
{ if (token == expected) token = getToken();
  else {
    syntaxError("Token desconocido-> ");
    printToken(token,tokenString);
    fprintf(listing,"      ");
  }
}

TreeNode * stmt_sequence(void)
{ TreeNode * t = statement();
  TreeNode * p = t;
  while ((token!=0) && (token!=FIN) &&
         (token!=SINO) && (token!=HASTA))
  { TreeNode * q;
    match(SEMI);
    q = statement();
    if (q!=NULL) {
      if (t==NULL) t = p = q;
      else /* p no puede ser NULL */
      { p->sibling = q;
        p = q;
      }
    }
  }
  return t;
}

TreeNode * statement(void)
{ TreeNode * t = NULL;
  switch (token) {
    case SI : t = if_stmt(); break;
    case REPETIR : t = repeat_stmt(); break;
    case ID : t = assign_stmt(); break;
    case LEER : t = read_stmt(); break;
    case ESCRIBIR : t = write_stmt(); break;
    default : syntaxError("token desconocido-> ");
              printToken(token,tokenString);
              token = getToken();
              break;
  } /* end case */
  return t;
}

TreeNode * if_stmt(void)
{ TreeNode * t = newStmtNode(IfK);
  match(SI);
  if (t!=NULL) t->child[0] = exp();
  match(MIENTRAS);
  if (t!=NULL) t->child[1] = stmt_sequence();
  if (token==SINO) {
    match(SINO);
    if (t!=NULL) t->child[2] = stmt_sequence();
  }
  match(FIN);
  return t;
}

TreeNode * repeat_stmt(void)
{ TreeNode * t = newStmtNode(RepeatK);
  match(REPETIR);
  if (t!=NULL) t->child[0] = stmt_sequence();
  match(HASTA);
  if (t!=NULL) t->child[1] = exp();
  return t;
}

TreeNode * assign_stmt(void)
{ TreeNode * t = newStmtNode(AssignK);
  if ((t!=NULL) && (token==ID))
    t->attr.name = copyString(tokenString);
  match(ID);
  match(ASIGNAR);
  if (t!=NULL) t->child[0] = exp();
  return t;
}

TreeNode * read_stmt(void)
{ TreeNode * t = newStmtNode(ReadK);
  match(LEER);
  if ((t!=NULL) && (token==ID))
    t->attr.name = copyString(tokenString);
  match(ID);
  return t;
}

TreeNode * write_stmt(void)
{ TreeNode * t = newStmtNode(WriteK);
  match(ESCRIBIR);
  if (t!=NULL) t->child[0] = exp();
  return t;
}

TreeNode * exp(void)
{ TreeNode * t = simple_exp();
  if ((token==LT)||(token==EQ)) {
    TreeNode * p = newExpNode(OpK);
    if (p!=NULL) {
      p->child[0] = t;
      p->attr.op = token;
      t = p;
    }
    match(token);
    if (t!=NULL)
      t->child[1] = simple_exp();
  }
  return t;
}

TreeNode * simple_exp(void)
{ TreeNode * t = term();
  while ((token==SUMA)||(token==MENOS))
  { TreeNode * p = newExpNode(OpK);
    if (p!=NULL) {
      p->child[0] = t;
      p->attr.op = token;
      t = p;
      match(token);
      t->child[1] = term();
    }
  }
  return t;
}

TreeNode * term(void)
{ TreeNode * t = factor();
  while ((token==MULT)||(token==DIV))
  { TreeNode * p = newExpNode(OpK);
    if (p!=NULL) {
      p->child[0] = t;
      p->attr.op = token;
      t = p;
      match(token);
      p->child[1] = factor();
    }
  }
  return t;
}

TreeNode * factor(void)
{ TreeNode * t = NULL;
  switch (token) {
    case NUM :
      t = newExpNode(ConstK);
      if ((t!=NULL) && (token==NUM))
        t->attr.val = atoi(tokenString);
      match(NUM);
      break;
    case ID :
      t = newExpNode(IdK);
      if ((t!=NULL) && (token==ID))
        t->attr.name = copyString(tokenString);
      match(ID);
      break;
    case LPAREN :
      match(LPAREN);
      t = exp();
      match(RPAREN);
      break;
    default:
      syntaxError("token inesperado-> ");
      printToken(token,tokenString);
      token = getToken();
      break;
    }
  return t;
}

/****************************************/
/* la función primaria del analizador   */
/****************************************/
/* la función primaria del analizador
 */
TreeNode * parse(void)
{ TreeNode * t;
  token = getToken();
  t = stmt_sequence();
  if (token!=0)
    syntaxError("El codigo termina antes que el archivo\n");
  return t;
}
