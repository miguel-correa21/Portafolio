package cai;
import javax.swing.JOptionPane;

public class menu
{
    public static String m = "[1]Multiplicacion";
    public static String d = "[2]División";
    public static String r = "[3]Resta";
    public static String s = "[4]Suma";
    
    public static int  opcion;

    public static int getOpcion(){ return opcion; }
      
    public static void MostrarMenu()
    {
        do
        {    
            String mensaje = String.format("%s\n%s\n%s\n%s\nIngrese una opción[1-4]:"
                ,m,d,r,s);       
        
            String op = 
                JOptionPane.showInputDialog(mensaje);
    
             opcion = Integer.parseInt(op);

        }while(opcion < 0 && opcion >4);
    }
    public static int setDificultad()
    {
        String dif = 
            JOptionPane.showInputDialog("Escoje una dificultad:"
                    +"[1] Fácil [2] Medio [3] Dificil");
       return Integer.parseInt(dif);
    }
}
