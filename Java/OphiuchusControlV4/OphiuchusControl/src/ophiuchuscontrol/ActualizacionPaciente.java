package ophiuchuscontrol;

import entidades.Paciente;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JFrame;

public class ActualizacionPaciente extends javax.swing.JFrame {
    
    private Utilidades util;
    private Conexion con = new Conexion();
  //  private VistaPacientes vp;
    
    public ActualizacionPaciente() {
        initComponents();
        this.util = new Utilidades();
//        vp = new VistaPacientes();
        //this.setLocationRelativeTo(null);
    }
    
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents()
    {

        jButton4 = new javax.swing.JButton();
        jMenuBar1 = new javax.swing.JMenuBar();
        jMenu1 = new javax.swing.JMenu();
        jMenu2 = new javax.swing.JMenu();
        jPanel1 = new javax.swing.JPanel();
        jLabel1 = new javax.swing.JLabel();
        jButton1 = new javax.swing.JButton();
        jLabel2 = new javax.swing.JLabel();
        jLabel3 = new javax.swing.JLabel();
        jLabel4 = new javax.swing.JLabel();
        jLabel5 = new javax.swing.JLabel();
        jLabel6 = new javax.swing.JLabel();
        jLabel7 = new javax.swing.JLabel();
        jLabel8 = new javax.swing.JLabel();
        txtNombre = new javax.swing.JTextField();
        txtApPaterno = new javax.swing.JTextField();
        txtApMaterno = new javax.swing.JTextField();
        txtCURP = new javax.swing.JTextField();
        txtTel = new javax.swing.JTextField();
        txtEmail = new javax.swing.JTextField();

        jButton4.setText("jButton4");

        jMenu1.setText("File");
        jMenuBar1.add(jMenu1);

        jMenu2.setText("Edit");
        jMenuBar1.add(jMenu2);

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setResizable(false);
        getContentPane().setLayout(new org.netbeans.lib.awtextra.AbsoluteLayout());

        jPanel1.setBackground(new java.awt.Color(86, 101, 115));
        jPanel1.setForeground(new java.awt.Color(50, 198, 182));

        jLabel1.setFont(new java.awt.Font("Silom", 0, 12)); // NOI18N
        jLabel1.setForeground(new java.awt.Color(255, 255, 255));
        jLabel1.setText("Datos Perfil - Paciente");

        javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(jPanel1);
        jPanel1.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addGap(34, 34, 34)
                .addComponent(jLabel1)
                .addContainerGap(320, Short.MAX_VALUE))
        );
        jPanel1Layout.setVerticalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanel1Layout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(jLabel1, javax.swing.GroupLayout.PREFERRED_SIZE, 16, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap())
        );

        getContentPane().add(jPanel1, new org.netbeans.lib.awtextra.AbsoluteConstraints(0, 0, 500, -1));

        jButton1.setText("Actualizar");
        jButton1.addMouseListener(new java.awt.event.MouseAdapter()
        {
            public void mouseClicked(java.awt.event.MouseEvent evt)
            {
                jButton1MouseClicked(evt);
            }
        });
        jButton1.addActionListener(new java.awt.event.ActionListener()
        {
            public void actionPerformed(java.awt.event.ActionEvent evt)
            {
                jButton1ActionPerformed(evt);
            }
        });
        getContentPane().add(jButton1, new org.netbeans.lib.awtextra.AbsoluteConstraints(20, 210, 117, -1));

        jLabel2.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagenes/Patient_Female_icon-icons.com_75052.png"))); // NOI18N
        getContentPane().add(jLabel2, new org.netbeans.lib.awtextra.AbsoluteConstraints(20, 60, 115, 137));

        jLabel3.setText("Nombre (s):");
        getContentPane().add(jLabel3, new org.netbeans.lib.awtextra.AbsoluteConstraints(167, 51, -1, -1));

        jLabel4.setText("Apellido Paterno:");
        getContentPane().add(jLabel4, new org.netbeans.lib.awtextra.AbsoluteConstraints(167, 83, -1, -1));

        jLabel5.setText("Apellido Materno:");
        getContentPane().add(jLabel5, new org.netbeans.lib.awtextra.AbsoluteConstraints(167, 115, -1, -1));

        jLabel6.setText("  Telefono:");
        getContentPane().add(jLabel6, new org.netbeans.lib.awtextra.AbsoluteConstraints(160, 180, 70, -1));

        jLabel7.setText("CURP:");
        getContentPane().add(jLabel7, new org.netbeans.lib.awtextra.AbsoluteConstraints(167, 147, -1, -1));

        jLabel8.setText("    Correo Electronico:");
        getContentPane().add(jLabel8, new org.netbeans.lib.awtextra.AbsoluteConstraints(150, 200, 150, 30));

        txtNombre.setBackground(new java.awt.Color(238, 238, 238));
        txtNombre.addActionListener(new java.awt.event.ActionListener()
        {
            public void actionPerformed(java.awt.event.ActionEvent evt)
            {
                txtNombreActionPerformed(evt);
            }
        });
        getContentPane().add(txtNombre, new org.netbeans.lib.awtextra.AbsoluteConstraints(300, 46, 190, -1));

        txtApPaterno.setBackground(new java.awt.Color(238, 238, 238));
        getContentPane().add(txtApPaterno, new org.netbeans.lib.awtextra.AbsoluteConstraints(300, 78, 190, -1));

        txtApMaterno.setBackground(new java.awt.Color(238, 238, 238));
        getContentPane().add(txtApMaterno, new org.netbeans.lib.awtextra.AbsoluteConstraints(300, 110, 190, -1));

        txtCURP.setBackground(new java.awt.Color(238, 238, 238));
        txtCURP.addActionListener(new java.awt.event.ActionListener()
        {
            public void actionPerformed(java.awt.event.ActionEvent evt)
            {
                txtCURPActionPerformed(evt);
            }
        });
        getContentPane().add(txtCURP, new org.netbeans.lib.awtextra.AbsoluteConstraints(300, 142, 190, -1));
        getContentPane().add(txtTel, new org.netbeans.lib.awtextra.AbsoluteConstraints(300, 170, 190, -1));
        getContentPane().add(txtEmail, new org.netbeans.lib.awtextra.AbsoluteConstraints(300, 200, 190, -1));

        pack();
    }// </editor-fold>//GEN-END:initComponents

    public void LlenarCampos(Paciente p){
        txtNombre.setText(p.getNombre());
        txtApPaterno.setText(p.getApPat());
        txtApMaterno.setText(p.getApMat());
        txtCURP.setText(p.getCurp());
        txtTel.setText(p.getTel());
        txtEmail.setText(p.getEmail());
    }
    private void jButton1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton1ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_jButton1ActionPerformed

    private void txtNombreActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txtNombreActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txtNombreActionPerformed

    private void txtCURPActionPerformed(java.awt.event.ActionEvent evt)//GEN-FIRST:event_txtCURPActionPerformed
    {//GEN-HEADEREND:event_txtCURPActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txtCURPActionPerformed

    private void jButton1MouseClicked(java.awt.event.MouseEvent evt)//GEN-FIRST:event_jButton1MouseClicked
    {//GEN-HEADEREND:event_jButton1MouseClicked
        String consulta = "update Paciente set Nombre='"+txtNombre.getText()+"',"
                + " ApellidoParteno='"+txtApPaterno.getText()+"', "
                + " ApellidoMaterno='"+txtApMaterno.getText()+"',"
                + " Telefono='"+txtTel.getText()+"',"
                + " Email='"+txtEmail.getText()+"' where Curp='"+txtCURP.getText()+"';";
        con.EjecutarActualizacion(consulta);
        util.LanzaMensaje("Opearción Exitosa","Actualización Realizada");
    }//GEN-LAST:event_jButton1MouseClicked

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton jButton1;
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
    private javax.swing.JTextField txtApMaterno;
    private javax.swing.JTextField txtApPaterno;
    private javax.swing.JTextField txtCURP;
    private javax.swing.JTextField txtEmail;
    private javax.swing.JTextField txtNombre;
    private javax.swing.JTextField txtTel;
    // End of variables declaration//GEN-END:variables
}
