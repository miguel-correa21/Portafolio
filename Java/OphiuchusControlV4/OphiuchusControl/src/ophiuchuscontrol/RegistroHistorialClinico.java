package ophiuchuscontrol;

import java.io.File;
import javax.swing.JFileChooser;
import javax.swing.JFrame;

public class RegistroHistorialClinico extends javax.swing.JFrame {

    private String CedulaProfesional;
    private Utilidades util;
    private VistaHistorialClinico Antecesor;

    public RegistroHistorialClinico(String CedulaProfesional, VistaHistorialClinico Antecesor) {
        initComponents();
        this.setLocationRelativeTo(null);
        util = new Utilidades();
        //inicio validaciones
        util.ValidaJTextField(txtNombre, 0, 30);
        //fin validaciones
        this.CedulaProfesional = CedulaProfesional;
        this.Antecesor = Antecesor;
        Conexion conex = new Conexion();
        conex.LlenaComboBox(txtPaciente,"SELECT Curp FROM Paciente;");
    }

    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jButton4 = new javax.swing.JButton();
        jMenuBar1 = new javax.swing.JMenuBar();
        jMenu1 = new javax.swing.JMenu();
        jMenu2 = new javax.swing.JMenu();
        jPanel1 = new javax.swing.JPanel();
        jLabel1 = new javax.swing.JLabel();
        jLabel11 = new javax.swing.JLabel();
        jLabel3 = new javax.swing.JLabel();
        jLabel5 = new javax.swing.JLabel();
        jLabel6 = new javax.swing.JLabel();
        txtNombre = new javax.swing.JTextField();
        txtPath = new javax.swing.JTextField();
        btnSubir = new javax.swing.JButton();
        btnGuardar = new javax.swing.JButton();
        txtPaciente = new javax.swing.JComboBox<>();
        jLabel4 = new javax.swing.JLabel();

        jButton4.setText("jButton4");

        jMenu1.setText("File");
        jMenuBar1.add(jMenu1);

        jMenu2.setText("Edit");
        jMenuBar1.add(jMenu2);

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setMaximumSize(new java.awt.Dimension(350, 350));
        setMinimumSize(new java.awt.Dimension(358, 300));
        setResizable(false);
        getContentPane().setLayout(new org.netbeans.lib.awtextra.AbsoluteLayout());

        jPanel1.setBackground(new java.awt.Color(86, 101, 115));
        jPanel1.setForeground(new java.awt.Color(50, 198, 182));

        jLabel1.setFont(new java.awt.Font("Silom", 0, 12)); // NOI18N
        jLabel1.setForeground(new java.awt.Color(255, 255, 255));
        jLabel1.setText("Historiales clinicos");

        javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(jPanel1);
        jPanel1.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addGap(34, 34, 34)
                .addComponent(jLabel1)
                .addContainerGap(221, Short.MAX_VALUE))
        );
        jPanel1Layout.setVerticalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanel1Layout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(jLabel1, javax.swing.GroupLayout.PREFERRED_SIZE, 16, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap())
        );

        getContentPane().add(jPanel1, new org.netbeans.lib.awtextra.AbsoluteConstraints(0, 0, 360, -1));

        jLabel11.setFont(new java.awt.Font("Lucida Grande", 1, 13)); // NOI18N
        jLabel11.setText("Agregar nuevo historial clinico");
        getContentPane().add(jLabel11, new org.netbeans.lib.awtextra.AbsoluteConstraints(70, 60, -1, -1));

        jLabel3.setText("Curp (paciente):");
        getContentPane().add(jLabel3, new org.netbeans.lib.awtextra.AbsoluteConstraints(40, 140, -1, -1));

        jLabel5.setText("  Nombre: ");
        getContentPane().add(jLabel5, new org.netbeans.lib.awtextra.AbsoluteConstraints(60, 100, 70, -1));

        jLabel6.setText(" Archivo:");
        getContentPane().add(jLabel6, new org.netbeans.lib.awtextra.AbsoluteConstraints(30, 180, 60, -1));
        getContentPane().add(txtNombre, new org.netbeans.lib.awtextra.AbsoluteConstraints(140, 100, 180, -1));

        txtPath.setEditable(false);
        getContentPane().add(txtPath, new org.netbeans.lib.awtextra.AbsoluteConstraints(90, 180, 130, -1));

        btnSubir.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagenes/if_new10_216291 (1).png"))); // NOI18N
        btnSubir.setText("Subir ");
        btnSubir.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnSubirActionPerformed(evt);
            }
        });
        getContentPane().add(btnSubir, new org.netbeans.lib.awtextra.AbsoluteConstraints(230, 180, 90, -1));

        btnGuardar.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagenes/if_save_2561379.png"))); // NOI18N
        btnGuardar.setText("Guardar");
        btnGuardar.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnGuardarActionPerformed(evt);
            }
        });
        getContentPane().add(btnGuardar, new org.netbeans.lib.awtextra.AbsoluteConstraints(30, 220, 290, -1));

        getContentPane().add(txtPaciente, new org.netbeans.lib.awtextra.AbsoluteConstraints(140, 140, 180, -1));

        jLabel4.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagenes/if_new-24_103173 (1).png"))); // NOI18N
        getContentPane().add(jLabel4, new org.netbeans.lib.awtextra.AbsoluteConstraints(20, 50, 40, 40));

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void btnGuardarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnGuardarActionPerformed
        entidades.HistorialClinico HC = new entidades.HistorialClinico(CedulaProfesional, txtPaciente.getSelectedItem().toString(), txtNombre.getText(), txtPath.getText());
        if (HC.ObligatoriosNoNulosCortos()) {
            Conexion conex = new Conexion();
            if (!conex.ExisteEnBD("SELECT * FROM HistorialClinico WHERE CedulaProfesional='" + HC.getCedulaProfesional() + "' AND PacienteCurp='" + HC.getPacienteCurp() + "' AND Nombre='" + HC.getNombre() + "';")) {
                if (conex.EjecutarActualizacion("INSERT INTO HistorialClinico VALUES('" + HC.getCedulaProfesional() + "','" + HC.getPacienteCurp() + "','" + HC.getNombre() + "','" + HC.getRutaArchivo() + "');")) {
                    util.LanzaMensaje("Historial clinico guardado", "Historial clinico guardado con exito.");
                    Antecesor.ActualizarJTable();
                    dispose();
                }
            } else {
                util.LanzaAdvertencia("Campos duplicados", "Ya existe un historial clinico con ese nombre para el paciente con Curp " + HC.getPacienteCurp() + ", porfavor intente de nuevo con un nombre diferente.");
            }
        } else {
            util.LanzaAdvertencia("Campos Invalidos", "Uno o mas campos  obligatorios estan vacios o son demasiado cortos, porfavor intente de nuevo.");
        }
    }//GEN-LAST:event_btnGuardarActionPerformed

    private void btnSubirActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnSubirActionPerformed
        JFileChooser fc = new JFileChooser();
        int seleccion = fc.showOpenDialog(this);
        if (seleccion == JFileChooser.APPROVE_OPTION) {
            File fichero = fc.getSelectedFile();
            txtPath.setText(fichero.getAbsolutePath());
        }
    }//GEN-LAST:event_btnSubirActionPerformed

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton btnGuardar;
    private javax.swing.JButton btnSubir;
    private javax.swing.JButton jButton4;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel11;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel jLabel5;
    private javax.swing.JLabel jLabel6;
    private javax.swing.JMenu jMenu1;
    private javax.swing.JMenu jMenu2;
    private javax.swing.JMenuBar jMenuBar1;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JTextField txtNombre;
    private javax.swing.JComboBox<String> txtPaciente;
    private javax.swing.JTextField txtPath;
    // End of variables declaration//GEN-END:variables
}
