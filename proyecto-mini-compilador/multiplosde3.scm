  0:     LD  6,0(0) 
  1:     ST  0,0(0) 
  2:     IN  0,0,0 
  3:     ST  0,0(5) 
  4:     IN  0,0,0 
  5:     ST  0,1(5) 
  6:     IN  0,0,0 
  7:     ST  0,2(5) 
  8:     LD  0,0(5) 
  9:     ST  0,3(5) 
 10:     LD  0,3(5) 
 11:     ST  0,0(6) 
 12:    LDC  0,1(0) 
 13:     LD  1,0(6) 
 14:   SUMA  0,1,0 
 15:     ST  0,3(5) 
 16:     LD  0,3(5) 
 17:     ST  0,0(6) 
 18:     LD  0,2(5) 
 19:     LD  1,0(6) 
 20:    DIV  0,1,0 
 21:     ST  0,4(5) 
 22:     LD  0,3(5) 
 23:     ST  0,0(6) 
 24:     LD  0,4(5) 
 25:     ST  0,-1(6) 
 26:     LD  0,2(5) 
 27:     LD  1,-1(6) 
 28:    MUL  0,1,0 
 29:     LD  1,0(6) 
 30:    SUB  0,1,0 
 31:     ST  0,5(5) 
 32:     LD  0,1(5) 
 33:     ST  0,0(6) 
 34:     LD  0,3(5) 
 35:     LD  1,0(6) 
 36:    SUB  0,1,0 
 37:     ST  0,6(5) 
 38:    LDC  0,0(0) 
 39:     ST  0,0(6) 
 40:     LD  0,5(5) 
 41:     LD  1,0(6) 
 42:    SUB  0,1,0 
 43:    JEQ  0,2(7) 
 44:    LDC  0,0(0) 
 45:    LDA  7,1(7) 
 46:    LDC  0,1(0) 
 48:     LD  0,3(5) 
 49:  SALIDA  0,0,0 
 47:    JEQ  0,3(7) 
 50:    LDA  7,0(7) 
 51:     LD  0,6(5) 
 52:     ST  0,0(6) 
 53:    LDC  0,0(0) 
 54:     LD  1,0(6) 
 55:    SUB  0,1,0 
 56:    JEQ  0,2(7) 
 57:    LDC  0,0(0) 
 58:    LDA  7,1(7) 
 59:    LDC  0,1(0) 
 60:    JEQ  0,-51(7) 
 61:  DETENER  0,0,0 
