package ophiuchuscontrol;

public class PanelControlMedico extends javax.swing.JFrame {
    private String CedulaProfesional;
    private Utilidades util;

    public PanelControlMedico(String CedulaProfesional) {
        initComponents();
        this.setLocationRelativeTo(null);
        this.util = new Utilidades();
        this.CedulaProfesional = CedulaProfesional;
        Conexion conex = new Conexion();
        lblBienvenido.setText("Bienvenid@ "+conex.getValor("SELECT Nombre FROM Medico WHERE CedulaProfesional='"+CedulaProfesional+"';"));
        util.reloj(lblReloj);
    }
    
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        BtnCita = new javax.swing.JButton();
        BtnHistory = new javax.swing.JButton();
        BtnAdmon = new javax.swing.JButton();
        jScrollPane1 = new javax.swing.JScrollPane();
        jTable1 = new javax.swing.JTable();
        lblBienvenido = new javax.swing.JLabel();
        LblIcon = new javax.swing.JLabel();
        panel1 = new java.awt.Panel();
        jLabel2 = new javax.swing.JLabel();
        BtnPatient = new javax.swing.JButton();
        lblReloj = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Ophiucus Control");
        setBackground(new java.awt.Color(255, 255, 255));
        setMinimumSize(new java.awt.Dimension(800, 400));
        setType(java.awt.Window.Type.UTILITY);
        getContentPane().setLayout(new org.netbeans.lib.awtextra.AbsoluteLayout());

        BtnCita.setBackground(new java.awt.Color(204, 204, 204));
        BtnCita.setIcon(new javax.swing.ImageIcon(getClass().getResource("/pf_bd/Images/Calendar-icon.png"))); // NOI18N
        BtnCita.setText("Administrar Citas");
        BtnCita.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BtnCitaActionPerformed(evt);
            }
        });
        getContentPane().add(BtnCita, new org.netbeans.lib.awtextra.AbsoluteConstraints(150, 110, 190, 58));

        BtnHistory.setBackground(new java.awt.Color(204, 204, 204));
        BtnHistory.setIcon(new javax.swing.ImageIcon(getClass().getResource("/pf_bd/Images/folder-subfolder-icon.png"))); // NOI18N
        BtnHistory.setText("Historial Clínico");
        BtnHistory.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BtnHistoryActionPerformed(evt);
            }
        });
        getContentPane().add(BtnHistory, new org.netbeans.lib.awtextra.AbsoluteConstraints(150, 180, 190, 58));

        BtnAdmon.setBackground(new java.awt.Color(204, 204, 204));
        BtnAdmon.setIcon(new javax.swing.ImageIcon(getClass().getResource("/pf_bd/Images/Doctor-icon (1).png"))); // NOI18N
        BtnAdmon.setText("Gestionar Permisos");
        BtnAdmon.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BtnAdmonActionPerformed(evt);
            }
        });
        getContentPane().add(BtnAdmon, new org.netbeans.lib.awtextra.AbsoluteConstraints(150, 320, 190, 58));

        jTable1.setModel(new javax.swing.table.DefaultTableModel(
            new Object [][] {
                {"12:00", null},
                {"12:20", null},
                {"12:40", null},
                {"13:00", null},
                {"13:20", null},
                {"13:40", null},
                {"14:00", null},
                {"14:20", null},
                {"14:40", null},
                {"15:00", null},
                {"15:20", null},
                {"15:40", null},
                {"16:00", null},
                {"16:20", null},
                {"16:40", null},
                {"17:00", null},
                {"17:20", null},
                {"17:40", null},
                {"18:00", null}
            },
            new String [] {
                "Hora", "Hoy"
            }
        ) {
            Class[] types = new Class [] {
                java.lang.String.class, java.lang.Object.class
            };
            boolean[] canEdit = new boolean [] {
                false, false
            };

            public Class getColumnClass(int columnIndex) {
                return types [columnIndex];
            }

            public boolean isCellEditable(int rowIndex, int columnIndex) {
                return canEdit [columnIndex];
            }
        });
        jScrollPane1.setViewportView(jTable1);
        if (jTable1.getColumnModel().getColumnCount() > 0) {
            jTable1.getColumnModel().getColumn(0).setResizable(false);
            jTable1.getColumnModel().getColumn(1).setResizable(false);
        }

        getContentPane().add(jScrollPane1, new org.netbeans.lib.awtextra.AbsoluteConstraints(380, 70, 357, 333));

        lblBienvenido.setFont(new java.awt.Font("Calibri", 1, 18)); // NOI18N
        lblBienvenido.setText("Bienvenido ______________");
        getContentPane().add(lblBienvenido, new org.netbeans.lib.awtextra.AbsoluteConstraints(40, 70, -1, -1));

        LblIcon.setIcon(new javax.swing.ImageIcon(getClass().getResource("/pf_bd/Images/People-Doctor-Male-icon_2.png"))); // NOI18N
        getContentPane().add(LblIcon, new org.netbeans.lib.awtextra.AbsoluteConstraints(40, 120, -1, -1));

        panel1.setBackground(new java.awt.Color(86, 101, 115));

        jLabel2.setFont(new java.awt.Font("Berlin Sans FB", 0, 18)); // NOI18N
        jLabel2.setForeground(new java.awt.Color(240, 240, 240));
        jLabel2.setText("OphiucusControl");
        panel1.add(jLabel2);

        getContentPane().add(panel1, new org.netbeans.lib.awtextra.AbsoluteConstraints(0, 0, 800, 40));

        BtnPatient.setBackground(new java.awt.Color(204, 204, 204));
        BtnPatient.setIcon(new javax.swing.ImageIcon(getClass().getResource("/pf_bd/Images/People-Patient-Male-icon.png"))); // NOI18N
        BtnPatient.setText("Pacientes");
        BtnPatient.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BtnPatientActionPerformed(evt);
            }
        });
        getContentPane().add(BtnPatient, new org.netbeans.lib.awtextra.AbsoluteConstraints(150, 250, 190, 58));

        lblReloj.setText("------reloj---------");
        getContentPane().add(lblReloj, new org.netbeans.lib.awtextra.AbsoluteConstraints(470, 46, 260, 20));

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void BtnCitaActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BtnCitaActionPerformed
        util.SetDialogo(new VistaCitas(true, CedulaProfesional));
    }//GEN-LAST:event_BtnCitaActionPerformed

    private void BtnHistoryActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BtnHistoryActionPerformed
        util.SetDialogo(new VistaHistorialClinico(CedulaProfesional));
    }//GEN-LAST:event_BtnHistoryActionPerformed

    private void BtnPatientActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BtnPatientActionPerformed
        util.SetDialogo(new VistaPacientes());
    }//GEN-LAST:event_BtnPatientActionPerformed

    private void BtnAdmonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BtnAdmonActionPerformed
        util.SetDialogo(new VistaPermisos(CedulaProfesional));
    }//GEN-LAST:event_BtnAdmonActionPerformed

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton BtnAdmon;
    private javax.swing.JButton BtnCita;
    private javax.swing.JButton BtnHistory;
    private javax.swing.JButton BtnPatient;
    private javax.swing.JLabel LblIcon;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JTable jTable1;
    private javax.swing.JLabel lblBienvenido;
    private javax.swing.JLabel lblReloj;
    private java.awt.Panel panel1;
    // End of variables declaration//GEN-END:variables
}
