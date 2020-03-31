package ophiuchuscontrol;

public class PanelControlAdministrativo extends javax.swing.JFrame {
    private String idEmpleado;
    private Utilidades util;

    public PanelControlAdministrativo(String idEmpleado) {
        initComponents();
        this.setLocationRelativeTo(null);
        this.util = new Utilidades();
        this.idEmpleado = idEmpleado;
        Conexion conex = new Conexion();
        lblBienvenido.setText("Bienvenid@ "+conex.getValor("SELECT Nombre FROM Empleado WHERE idEmpleado='"+idEmpleado+"';"));
        util.reloj(lblReloj);
    }

    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents()
    {

        BtnCita = new javax.swing.JButton();
        BtnPatient = new javax.swing.JButton();
        jScrollPane1 = new javax.swing.JScrollPane();
        jTable1 = new javax.swing.JTable();
        lblBienvenido = new javax.swing.JLabel();
        LblIcon = new javax.swing.JLabel();
        panel1 = new java.awt.Panel();
        jLabel2 = new javax.swing.JLabel();
        lblReloj = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Ophiucus Control");
        setBackground(new java.awt.Color(255, 255, 255));
        setBounds(new java.awt.Rectangle(0, 0, 450, 450));
        setMinimumSize(new java.awt.Dimension(800, 500));
        setType(java.awt.Window.Type.UTILITY);
        getContentPane().setLayout(null);

        BtnCita.setBackground(new java.awt.Color(204, 204, 204));
        BtnCita.setIcon(new javax.swing.ImageIcon(getClass().getResource("/pf_bd/Images/Calendar-icon.png"))); // NOI18N
        BtnCita.setText("Agregar Cita");
        BtnCita.addActionListener(new java.awt.event.ActionListener()
        {
            public void actionPerformed(java.awt.event.ActionEvent evt)
            {
                BtnCitaActionPerformed(evt);
            }
        });
        getContentPane().add(BtnCita);
        BtnCita.setBounds(200, 130, 160, 58);

        BtnPatient.setBackground(new java.awt.Color(204, 204, 204));
        BtnPatient.setIcon(new javax.swing.ImageIcon(getClass().getResource("/pf_bd/Images/People-Patient-Male-icon.png"))); // NOI18N
        BtnPatient.setText("Pacientes");
        BtnPatient.addActionListener(new java.awt.event.ActionListener()
        {
            public void actionPerformed(java.awt.event.ActionEvent evt)
            {
                BtnPatientActionPerformed(evt);
            }
        });
        getContentPane().add(BtnPatient);
        BtnPatient.setBounds(200, 210, 160, 58);

        jTable1.setModel(new javax.swing.table.DefaultTableModel(
            new Object [][]
            {
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
            new String []
            {
                "Hora", "Hoy"
            }
        )
        {
            Class[] types = new Class []
            {
                java.lang.String.class, java.lang.Object.class
            };
            boolean[] canEdit = new boolean []
            {
                false, false
            };

            public Class getColumnClass(int columnIndex)
            {
                return types [columnIndex];
            }

            public boolean isCellEditable(int rowIndex, int columnIndex)
            {
                return canEdit [columnIndex];
            }
        });
        jScrollPane1.setViewportView(jTable1);
        if (jTable1.getColumnModel().getColumnCount() > 0)
        {
            jTable1.getColumnModel().getColumn(0).setResizable(false);
            jTable1.getColumnModel().getColumn(1).setResizable(false);
        }

        getContentPane().add(jScrollPane1);
        jScrollPane1.setBounds(390, 70, 357, 333);

        lblBienvenido.setFont(new java.awt.Font("Calibri", 1, 18)); // NOI18N
        lblBienvenido.setText("Bienvenido ______________");
        getContentPane().add(lblBienvenido);
        lblBienvenido.setBounds(30, 70, 340, 22);

        LblIcon.setIcon(new javax.swing.ImageIcon(getClass().getResource("/pf_bd/Images/Doctor-icon.png"))); // NOI18N
        getContentPane().add(LblIcon);
        LblIcon.setBounds(70, 140, 90, 120);

        panel1.setBackground(new java.awt.Color(86, 101, 115));

        jLabel2.setFont(new java.awt.Font("Berlin Sans FB", 0, 18)); // NOI18N
        jLabel2.setForeground(new java.awt.Color(240, 240, 240));
        jLabel2.setText("OphiucusControl");
        panel1.add(jLabel2);

        getContentPane().add(panel1);
        panel1.setBounds(0, 0, 840, 40);

        lblReloj.setText("------reloj---------");
        getContentPane().add(lblReloj);
        lblReloj.setBounds(460, 40, 240, 30);

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void BtnCitaActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BtnCitaActionPerformed
        util.SetDialogo(new VistaCitas(false, this.idEmpleado));
    }//GEN-LAST:event_BtnCitaActionPerformed

    private void BtnPatientActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BtnPatientActionPerformed

     util.SetDialogo(new VistaPacientes());
    }//GEN-LAST:event_BtnPatientActionPerformed

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton BtnCita;
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
