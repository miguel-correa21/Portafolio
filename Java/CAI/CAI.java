import java.util.Random;
import javax.swing.JOptionPane;
import cai.*;
//importo el paquete donde tengo las clases menu y Aritmetica
public class CAI 
{
    private static String signo;
    private static int entero1;
    private static int entero2;
    private static int opcion;
    private static int dificultad;
    private static int rango;
    private static int respuesta;
    private static double resultado;
    private static String mensaje;
    private static double contador;

    public static void setParametros()
    {
        menu.MostrarMenu();
        opcion = menu.getOpcion();
        dificultad = menu.setDificultad();
        
        if(dificultad == 1)
            rango = 10;
    
        if(dificultad == 2)
            rango = 100;
        
        if(dificultad == 3)
            rango = 1000;
    }
    public void ejecutar()
    {
        setParametros();
        String entrada;
        double usuario;
        String operacion;
        String mensaje2;
        Random numeros = new Random();
        double promedio;
        String despedida;
        
        for(int i  = 0; i < 10;i++)
        {
            entero1 = 1 + numeros.nextInt(rango);
            entero2 = 1 + numeros.nextInt(rango);
            Operar(entero1,entero2);

            mensaje2 = String.format("%d %s %d",entero1,signo,entero2);
            entrada = JOptionPane.showInputDialog(mensaje2
                    +"\nIntroduzca su respuesta:\n");

            if(signo != "/"){usuario = Integer.parseInt(entrada);}
            else
            {
                usuario = Math.round(Double.parseDouble(entrada)*100d)/100d;
                resultado = Math.round((resultado*100d))/100d;
            }

            if(usuario == resultado)
            {
                respuesta(true);
                JOptionPane.showMessageDialog(null,mensaje);
            }

            else
            {
                respuesta(false);
                JOptionPane.showMessageDialog(null,mensaje);
                JOptionPane.showMessageDialog(null,"el resultado es:"+resultado);
            }
            
        }

        promedio = (contador/10)*100;
        if(promedio >= 75.00)
        {
            despedida = 
                "Lo hiciste muy bien ya estas listo para el siguiente nivel";
            JOptionPane.showMessageDialog(null,despedida);
        }
        else
        {
            despedida = 
                "Necesitas prácticar más, acude a tutorias con tu profesor";
            JOptionPane.showMessageDialog(null,despedida);
        }
        
    }

    public static void Operar(int c ,int d)
    {
        switch(opcion)
        {
            case 1:
                 resultado =  Aritmetica.Multiplicar(c,d);
                 signo = "x";
                 break;
            case 2:
                 resultado =  Aritmetica.Dividir((double)c,(double)d);
                 signo =  "/";
                 break;
            case 3:
                 resultado =  Aritmetica.Restar(c,d);
                 signo = "-";
                 break;
            case 4:
                 resultado =  Aritmetica.Sumar(c,d);                 
                 signo =   "+";
                 break;
       }
    }

    public static void respuesta(boolean correcto)
    {
        Random entrada = new Random();
        if(correcto)
        {
            contador++;
            respuesta = entrada.nextInt(4);
            switch(respuesta)
            {
                case 0:
                    mensaje = "!Muy bien sigue asi¡";
                    break;
                case 1:
                    mensaje = "!Correcto¡, bien hecho";
                    break;
                case 2:
                    mensaje = "!!!!Perfecto¡¡¡¡";
                    break;
                case 3:
                    mensaje = "Excelente lo estas haciendo bien";
                    break; 
            }
        }
        else
        {
            respuesta = entrada.nextInt(4);
            switch(respuesta)
            {
                case 0:
                    mensaje = "No. Por favor intenta de nuevo";
                    break;
                case 1:
                    mensaje = "Incorrecto intentelo de nuevo";
                    break;
                case 2:
                    mensaje = "Mal, pero no te !rindas¡";
                    break;
                case 3:
                    mensaje = "No. Sigue intentandolo";
                    break; 
            }
        }
    }
}
