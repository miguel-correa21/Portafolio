package ophiuchuscontrol;

import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

public class OphiuchusControl {
    public static void main(String[] args) {
        setTema();
        Login frmLogin = new Login();
        frmLogin.setVisible(true);
    }
    private static void setTema(){
        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (ClassNotFoundException | IllegalAccessException | InstantiationException | UnsupportedLookAndFeelException e) {
        }
    }
}
