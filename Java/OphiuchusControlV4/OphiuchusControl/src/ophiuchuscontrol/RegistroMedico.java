package ophiuchuscontrol;

public class RegistroMedico extends javax.swing.JFrame {

    private Utilidades util;

    public RegistroMedico() {
        initComponents();
        this.setLocationRelativeTo(null);
        //inicio validaciones
        util = new Utilidades();
        util.ValidaJTextField(txtCedula, 4, 8);
        util.ValidaJTextField(txtNombre, 1, 30);
        util.ValidaJTextField(txtApMat, 1, 30);
        util.ValidaJTextField(txtApPat, 1, 30);
        util.ValidaJTextField(txtTelefono, 0, 15);
        util.ValidaJTextField(txtCorreo, 4, 35);
        util.ValidaJPasswordField(passwordMedico, 25);
        util.ValidaJPasswordField(passwordMedicoVerifica, 25);
        //fin validaciones
    }

    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jButton4 = new javax.swing.JButton();
        jRadioButton1 = new javax.swing.JRadioButton();
        jPanel1 = new javax.swing.JPanel();
        jLabel1 = new javax.swing.JLabel();
        btnRegistrar = new javax.swing.JButton();
        jLabel2 = new javax.swing.JLabel();
        jLabel3 = new javax.swing.JLabel();
        jLabel4 = new javax.swing.JLabel();
        jLabel5 = new javax.swing.JLabel();
        jLabel6 = new javax.swing.JLabel();
        jLabel7 = new javax.swing.JLabel();
        jLabel8 = new javax.swing.JLabel();
        txtNombre = new javax.swing.JTextField();
        txtApPat = new javax.swing.JTextField();
        txtApMat = new javax.swing.JTextField();
        txtCorreo = new javax.swing.JTextField();
        jLabel9 = new javax.swing.JLabel();
        jLabel10 = new javax.swing.JLabel();
        txtTelefono = new javax.swing.JTextField();
        txtCedula = new javax.swing.JTextField();
        passwordMedico = new javax.swing.JPasswordField();
        passwordMedicoVerifica = new javax.swing.JPasswordField();

        jButton4.setText("jButton4");

        jRadioButton1.setText("jRadioButton1");

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setMinimumSize(new java.awt.Dimension(500, 350));
        setResizable(false);
        getContentPane().setLayout(new org.netbeans.lib.awtextra.AbsoluteLayout());

        jPanel1.setBackground(new java.awt.Color(86, 101, 115));
        jPanel1.setForeground(new java.awt.Color(50, 198, 182));

        jLabel1.setFont(new java.awt.Font("Silom", 0, 12)); // NOI18N
        jLabel1.setForeground(new java.awt.Color(255, 255, 255));
        jLabel1.setText("Registro - Nuevo Médico");

        javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(jPanel1);
        jPanel1.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jLabel1)
                .addContainerGap(354, Short.MAX_VALUE))
        );
        jPanel1Layout.setVerticalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addComponent(jLabel1, javax.swing.GroupLayout.PREFERRED_SIZE, 29, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(0, 1, Short.MAX_VALUE))
        );

        getContentPane().add(jPanel1, new org.netbeans.lib.awtextra.AbsoluteConstraints(0, 0, 500, 30));

        btnRegistrar.setText("Registrar");
        btnRegistrar.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnRegistrarActionPerformed(evt);
            }
        });
        getContentPane().add(btnRegistrar, new org.netbeans.lib.awtextra.AbsoluteConstraints(10, 206, 124, -1));

        jLabel2.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagenes/medical-29_icon-icons.com_73943-min-150x150.png"))); // NOI18N
        getContentPane().add(jLabel2, new org.netbeans.lib.awtextra.AbsoluteConstraints(0, 50, 134, -1));

        jLabel3.setText("Nombre (s):");
        getContentPane().add(jLabel3, new org.netbeans.lib.awtextra.AbsoluteConstraints(152, 45, -1, -1));

        jLabel4.setText("Apellido Paterno:");
        getContentPane().add(jLabel4, new org.netbeans.lib.awtextra.AbsoluteConstraints(152, 77, -1, -1));

        jLabel5.setText("Apellido Materno:");
        getContentPane().add(jLabel5, new org.netbeans.lib.awtextra.AbsoluteConstraints(152, 109, -1, -1));

        jLabel6.setText("Telefono:");
        getContentPane().add(jLabel6, new org.netbeans.lib.awtextra.AbsoluteConstraints(152, 175, -1, -1));

        jLabel7.setText("Correo Electronico:");
        getContentPane().add(jLabel7, new org.netbeans.lib.awtextra.AbsoluteConstraints(152, 141, -1, -1));

        jLabel8.setText("Password:");
        getContentPane().add(jLabel8, new org.netbeans.lib.awtextra.AbsoluteConstraints(152, 231, -1, -1));
        getContentPane().add(txtNombre, new org.netbeans.lib.awtextra.AbsoluteConstraints(280, 40, 192, -1));
        getContentPane().add(txtApPat, new org.netbeans.lib.awtextra.AbsoluteConstraints(280, 72, 192, -1));
        getContentPane().add(txtApMat, new org.netbeans.lib.awtextra.AbsoluteConstraints(280, 104, 192, -1));
        getContentPane().add(txtCorreo, new org.netbeans.lib.awtextra.AbsoluteConstraints(280, 136, 192, -1));

        jLabel9.setText("Cedula Profesional:");
        getContentPane().add(jLabel9, new org.netbeans.lib.awtextra.AbsoluteConstraints(152, 203, -1, -1));

        jLabel10.setText("Verificar Password:");
        getContentPane().add(jLabel10, new org.netbeans.lib.awtextra.AbsoluteConstraints(152, 258, -1, -1));
        getContentPane().add(txtTelefono, new org.netbeans.lib.awtextra.AbsoluteConstraints(280, 165, 192, -1));
        getContentPane().add(txtCedula, new org.netbeans.lib.awtextra.AbsoluteConstraints(280, 193, 192, -1));
        getContentPane().add(passwordMedico, new org.netbeans.lib.awtextra.AbsoluteConstraints(280, 221, 192, -1));
        getContentPane().add(passwordMedicoVerifica, new org.netbeans.lib.awtextra.AbsoluteConstraints(280, 253, 192, -1));

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void btnRegistrarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnRegistrarActionPerformed
        if (util.getPass(passwordMedico).equals(util.getPass(passwordMedicoVerifica))) {
            entidades.Medico med = new entidades.Medico(txtCedula.getText(), txtNombre.getText(), txtApPat.getText(), txtApMat.getText(), txtCorreo.getText(), txtTelefono.getText(), util.getPass(passwordMedico));
            if (med.ObligatoriosNoNulosCortos()) {
                Conexion conex = new Conexion();
                if (conex.ExisteEnBD("SELECT * FROM Medico WHERE CedulaProfesional = '" + med.getCedula() + "';")) {
                    util.LanzaAdvertencia("Campos Invalidos", "El medico con la cedula profesional que usted intenta registrar ya existe.");
                } else {
                    if (conex.EjecutarActualizacion("INSERT INTO Medico VALUES ('" + med.getCedula() + "','" + med.getNombre() + "','" + med.getApPat() + "','" + med.getApMat() + "','" + med.getTel() + "','" + med.getEmail() + "','" + med.getPass() + "');")) {
                        util.LanzaMensaje("Operacion exitosa", "Medico agregado con exito!");
                        this.dispose();
                    } else {
                        util.LanzaAdvertencia("Campos Invalidos", "Algo salio mal, verifica tu conexion a la BD.");
                    }
                }
            } else {
                util.LanzaAdvertencia("Campos Invalidos", "Uno o mas campos  obligatorios estan vacios o son demasiado cortos, porfavor intente de nuevo.");
            }
        } else {
            util.LanzaAdvertencia("Campos Invalidos", "Las contraseñas no coinciden, porfavor intente de nuevo.");
        }
    }//GEN-LAST:event_btnRegistrarActionPerformed

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton btnRegistrar;
    private javax.swing.JButton jButton4;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel10;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel jLabel5;
    private javax.swing.JLabel jLabel6;
    private javax.swing.JLabel jLabel7;
    private javax.swing.JLabel jLabel8;
    private javax.swing.JLabel jLabel9;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JRadioButton jRadioButton1;
    private javax.swing.JPasswordField passwordMedico;
    private javax.swing.JPasswordField passwordMedicoVerifica;
    private javax.swing.JTextField txtApMat;
    private javax.swing.JTextField txtApPat;
    private javax.swing.JTextField txtCedula;
    private javax.swing.JTextField txtCorreo;
    private javax.swing.JTextField txtNombre;
    private javax.swing.JTextField txtTelefono;
    // End of variables declaration//GEN-END:variables
}
