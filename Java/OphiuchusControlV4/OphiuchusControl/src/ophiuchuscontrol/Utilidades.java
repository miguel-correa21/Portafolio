package ophiuchuscontrol;

import java.awt.event.*;
import static java.lang.Thread.sleep;
import java.util.*;
import javax.swing.*;

public class Utilidades {

    public Utilidades() {

    }

    /*Recibe como parametro el JTextField a validar, un numero que representa el tipo de
    validacion y otro numero que define los caracteres que se pueden escribir en el JTextField.
    Tipos de validacion:
    0 - Ningun tipo de validacion, solo respeta la longitud maxima
    1 - Solo letras (permite espacios)
    2 - Solo numeros enteros (permite espacios)
    3 - Solo numeros enteros (no permite espacios)
    4 - Solo numeros enteros y letras (no permite espacios)*/
    public void ValidaJTextField(JTextField txt, int TipoValidacion, int LongitudMax) {
        txt.addKeyListener(
                new KeyListener() {
            @Override
            public void keyTyped(KeyEvent e) {
                if (txt.getText().length() == LongitudMax) {
                    e.consume();
                    return;
                }
                char c = e.getKeyChar();
                switch (TipoValidacion) {
                    case 1:
                        if (!(Character.isLetter(c))&&!(Character.isSpaceChar(c))) {
                            e.consume();
                        }
                        break;
                    case 2:
                        if (!(Character.isDigit(c))) {
                            e.consume();
                        }
                        break;
                    case 3:
                        if (!(Character.isDigit(c)) || Character.isSpaceChar(c)) {
                            e.consume();
                        }
                        break;
                    case 4:
                        if (!(Character.isLetter(c)) && !(Character.isDigit(c)) && Character.isSpaceChar(c)) {
                            e.consume();
                        }
                        break;
                    default:
                        break;
                }
            }

            @Override
            public void keyPressed(KeyEvent e) {
            }

            @Override
            public void keyReleased(KeyEvent e) {
            }
        }
        );
    }

    public void ValidaJPasswordField(JPasswordField txt, int LongitudMax) {
        txt.addKeyListener(
                new KeyListener() {
            @Override
            public void keyTyped(KeyEvent e) {
                if (txt.getPassword().length == LongitudMax) {
                    e.consume();
                    return;
                }
            }

            @Override
            public void keyPressed(KeyEvent ke) {

            }

            @Override
            public void keyReleased(KeyEvent ke) {

            }
        }
        );
    }
   
    public void SetDialogo(JFrame formulario){
       JDialog dialogo = new JDialog();
        dialogo.add(formulario.getContentPane());
        dialogo.setModal(true);
        dialogo.setSize(formulario.getSize());
        dialogo.setTitle(formulario.getTitle());
        dialogo.setResizable(false);
        dialogo.setLocationRelativeTo(null);
        dialogo.setVisible(true);
    }
   
    
    public String getPass(JPasswordField p){
        return new String(p.getPassword());
    }
    
    public void LanzaAdvertencia(String titulo, String mensaje){
        JOptionPane.showMessageDialog(null, mensaje, titulo, JOptionPane.WARNING_MESSAGE);
    }
    
    public void LanzaMensaje(String titulo, String mensaje){
        JOptionPane.showMessageDialog(null, mensaje, titulo, JOptionPane.INFORMATION_MESSAGE);
    }
    
    public void reloj(JLabel out) {
        Thread reloj = new Thread() {
            @Override
            public void run() {
                try {
                    Calendar cal;
                    int d,mo,y,s,m,h;
                    for (;;) {
                        cal = new GregorianCalendar();
                        d = cal.get(Calendar.DAY_OF_MONTH);
                        mo = cal.get(Calendar.MONTH)+1;
                        y = cal.get(Calendar.YEAR);
                        s = cal.get(Calendar.SECOND);
                        m = cal.get(Calendar.MINUTE);
                        h = cal.get(Calendar.HOUR_OF_DAY);
                        out.setText("Hora y fecha actuales: "+h + ":" + m + ":" + s + " - " + d + "/" + mo + "/" + y);
                        sleep(1000);
                    }
                } catch (InterruptedException e) {
                    System.out.println("Error al recojer la hora: "+ e);
                }
            }
        };
        reloj.start();
    }
    
    /*public String getFecha(){
        
    }*/
}
