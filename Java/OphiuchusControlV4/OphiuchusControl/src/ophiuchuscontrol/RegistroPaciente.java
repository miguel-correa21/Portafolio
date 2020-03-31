package ophiuchuscontrol;

public class RegistroPaciente extends javax.swing.JFrame {
    Utilidades util;
    VistaPacientes Antecesor;

    public RegistroPaciente(VistaPacientes Antecesor) {
        initComponents();
        this.setLocationRelativeTo(null);
        util = new Utilidades();
        this.Antecesor = Antecesor;
        //validaciones
        util.ValidaJTextField(txtNombre, 1, 30);
        util.ValidaJTextField(txtApMat, 1, 30);
        util.ValidaJTextField(txtApPat, 1, 30);
        util.ValidaJTextField(txtTelefono, 0, 15);
        util.ValidaJTextField(txtCorreo, 4, 35);
        util.ValidaJTextField(txtCURP, 4, 18);
        //fin validaciones
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
        txtCURP = new javax.swing.JTextField();
        txtCorreo = new javax.swing.JTextField();
        txtTelefono = new javax.swing.JTextField();

        jButton4.setText("jButton4");

        jMenu1.setText("File");
        jMenuBar1.add(jMenu1);

        jMenu2.setText("Edit");
        jMenuBar1.add(jMenu2);

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setMinimumSize(new java.awt.Dimension(500, 300));
        setResizable(false);
        getContentPane().setLayout(new org.netbeans.lib.awtextra.AbsoluteLayout());

        jPanel1.setBackground(new java.awt.Color(86, 101, 115));
        jPanel1.setForeground(new java.awt.Color(50, 198, 182));

        jLabel1.setFont(new java.awt.Font("Silom", 0, 12)); // NOI18N
        jLabel1.setForeground(new java.awt.Color(255, 255, 255));
        jLabel1.setText("Registro - Nuevo Paciente");

        javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(jPanel1);
        jPanel1.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addGap(34, 34, 34)
                .addComponent(jLabel1)
                .addContainerGap(323, Short.MAX_VALUE))
        );
        jPanel1Layout.setVerticalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jLabel1, javax.swing.GroupLayout.DEFAULT_SIZE, 30, Short.MAX_VALUE)
        );

        getContentPane().add(jPanel1, new org.netbeans.lib.awtextra.AbsoluteConstraints(0, 0, 500, 30));

        btnRegistrar.setText("Registrar");
        btnRegistrar.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnRegistrarActionPerformed(evt);
            }
        });
        getContentPane().add(btnRegistrar, new org.netbeans.lib.awtextra.AbsoluteConstraints(20, 210, 117, -1));

        jLabel2.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagenes/Patient_Female_icon-icons.com_75052.png"))); // NOI18N
        getContentPane().add(jLabel2, new org.netbeans.lib.awtextra.AbsoluteConstraints(20, 60, 115, 137));

        jLabel3.setText("Nombre (s):");
        getContentPane().add(jLabel3, new org.netbeans.lib.awtextra.AbsoluteConstraints(167, 51, -1, -1));

        jLabel4.setText("Apellido Paterno:");
        getContentPane().add(jLabel4, new org.netbeans.lib.awtextra.AbsoluteConstraints(167, 83, -1, -1));

        jLabel5.setText("Apellido Materno:");
        getContentPane().add(jLabel5, new org.netbeans.lib.awtextra.AbsoluteConstraints(167, 115, -1, -1));

        jLabel6.setText("Telefono:");
        getContentPane().add(jLabel6, new org.netbeans.lib.awtextra.AbsoluteConstraints(170, 180, 61, -1));

        jLabel7.setText("CURP:");
        getContentPane().add(jLabel7, new org.netbeans.lib.awtextra.AbsoluteConstraints(167, 147, -1, -1));

        jLabel8.setText("    Correo Electronico:");
        getContentPane().add(jLabel8, new org.netbeans.lib.awtextra.AbsoluteConstraints(150, 210, 150, 30));
        getContentPane().add(txtNombre, new org.netbeans.lib.awtextra.AbsoluteConstraints(298, 46, 192, -1));
        getContentPane().add(txtApPat, new org.netbeans.lib.awtextra.AbsoluteConstraints(298, 78, 192, -1));
        getContentPane().add(txtApMat, new org.netbeans.lib.awtextra.AbsoluteConstraints(298, 110, 192, -1));
        getContentPane().add(txtCURP, new org.netbeans.lib.awtextra.AbsoluteConstraints(298, 142, 192, -1));
        getContentPane().add(txtCorreo, new org.netbeans.lib.awtextra.AbsoluteConstraints(300, 220, 192, -1));
        getContentPane().add(txtTelefono, new org.netbeans.lib.awtextra.AbsoluteConstraints(300, 180, 192, -1));

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void btnRegistrarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnRegistrarActionPerformed
        entidades.Paciente pac = new entidades.Paciente(txtCURP.getText(), txtNombre.getText(), txtApPat.getText(), txtApMat.getText(), txtCorreo.getText(), txtTelefono.getText());
        if (pac.ObligatoriosNoNulosCortos()) {
            Conexion conex = new Conexion();
            if (conex.ExisteEnBD("SELECT * FROM Paciente WHERE Curp = '" + pac.getCurp()+ "';")) {
                util.LanzaAdvertencia("Campos Invalidos", "El paciente con la curp que usted intenta registrar ya existe.");
            } else {
                if (conex.EjecutarActualizacion("INSERT INTO Paciente VALUES ('" + pac.getCurp() + "','" + pac.getNombre() + "','" + pac.getApPat() + "','" + pac.getApMat() + "','" + pac.getTel() + "','" + pac.getEmail() + "');")) {
                    util.LanzaMensaje("Operacion exitosa", "Paciente agregado con exito!");
                    Antecesor.ActualizarJTable();
                    this.dispose();
                } else {
                    util.LanzaAdvertencia("Campos Invalidos", "Algo salio mal, verifica tu conexion a la BD.");
                }
            }
        } else {
            util.LanzaAdvertencia("Campos Invalidos", "Uno o mas campos  obligatorios estan vacios o son demasiado cortos, porfavor intente de nuevo.");
        }
    }//GEN-LAST:event_btnRegistrarActionPerformed

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton btnRegistrar;
    private javax.swing.JButton jButton4;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel jLabel5;
    private javax.swing.JLabel jLabel6;
    private javax.swing.JLabel jLabel7;
    private javax.swing.JLabel jLabel8;
    private javax.swing.JMenu jMenu1;
    private javax.swing.JMenu jMenu2;
    private javax.swing.JMenuBar jMenuBar1;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JTextField txtApMat;
    private javax.swing.JTextField txtApPat;
    private javax.swing.JTextField txtCURP;
    private javax.swing.JTextField txtCorreo;
    private javax.swing.JTextField txtNombre;
    private javax.swing.JTextField txtTelefono;
    // End of variables declaration//GEN-END:variables
}
