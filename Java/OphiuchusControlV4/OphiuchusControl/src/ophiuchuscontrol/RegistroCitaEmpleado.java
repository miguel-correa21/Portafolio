package ophiuchuscontrol;

public final class RegistroCitaEmpleado extends javax.swing.JFrame {
    private String idUser;
    private Utilidades util;
    private VistaCitas Antecesor;
    
    public RegistroCitaEmpleado(String idUser, VistaCitas Antecesor) {
        initComponents();
        this.setLocationRelativeTo(null);
        this.idUser = idUser;
        this.util = new Utilidades();
        this.Antecesor = Antecesor;
        Conexion conex = new Conexion();
        conex.LlenaComboBox(cmbPaciente,"SELECT Curp FROM Paciente;");
        conex.LlenaComboBox(cmbMedico, "SELECT CedulaProfesional FROM Medico;");
    }

    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents()
    {

        panel1 = new java.awt.Panel();
        jLabel2 = new javax.swing.JLabel();
        BtnCanc = new javax.swing.JButton();
        jLabel1 = new javax.swing.JLabel();
        cbbday = new javax.swing.JComboBox<>();
        cbbmonth = new javax.swing.JComboBox<>();
        cbbyear = new javax.swing.JComboBox<>();
        jLabel3 = new javax.swing.JLabel();
        jLabel4 = new javax.swing.JLabel();
        jLabel5 = new javax.swing.JLabel();
        jLabel6 = new javax.swing.JLabel();
        jLabel7 = new javax.swing.JLabel();
        cmbPaciente = new javax.swing.JComboBox<>();
        calendario = new com.toedter.calendar.JCalendar();
        jLabel8 = new javax.swing.JLabel();
        jLabel9 = new javax.swing.JLabel();
        cbbhour = new javax.swing.JComboBox<>();
        cmbMedico = new javax.swing.JComboBox<>();
        jLabel10 = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Ophiucus Control");
        setBackground(new java.awt.Color(255, 255, 255));
        setBounds(new java.awt.Rectangle(0, 0, 450, 450));
        setMinimumSize(new java.awt.Dimension(720, 450));
        setType(java.awt.Window.Type.UTILITY);
        getContentPane().setLayout(null);

        panel1.setBackground(new java.awt.Color(86, 101, 115));

        jLabel2.setFont(new java.awt.Font("Berlin Sans FB", 0, 18)); // NOI18N
        jLabel2.setForeground(new java.awt.Color(240, 240, 240));
        jLabel2.setText("Agregar Cita");
        panel1.add(jLabel2);

        getContentPane().add(panel1);
        panel1.setBounds(0, 0, 730, 40);

        BtnCanc.setBackground(new java.awt.Color(204, 204, 204));
        BtnCanc.setIcon(new javax.swing.ImageIcon(getClass().getResource("/pf_bd/Images/Time-Tear-Off-Calendar-icon (1).png"))); // NOI18N
        BtnCanc.setText("Confirmar");
        BtnCanc.addActionListener(new java.awt.event.ActionListener()
        {
            public void actionPerformed(java.awt.event.ActionEvent evt)
            {
                BtnCancActionPerformed(evt);
            }
        });
        getContentPane().add(BtnCanc);
        BtnCanc.setBounds(100, 350, 170, 40);

        jLabel1.setText("Seleccione la fecha en que quiere agregar la cita:");
        getContentPane().add(jLabel1);
        jLabel1.setBounds(20, 240, 290, 30);

        cbbday.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31" }));
        getContentPane().add(cbbday);
        cbbday.setBounds(100, 300, 50, 30);
        cbbday.getAccessibleContext().setAccessibleName("");

        cbbmonth.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", " " }));
        cbbmonth.setDebugGraphicsOptions(javax.swing.DebugGraphics.NONE_OPTION);
        cbbmonth.setEditor(null);
        getContentPane().add(cbbmonth);
        cbbmonth.setBounds(160, 300, 50, 30);

        cbbyear.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "2018", "2019", "2020", "2021", "2022", "2023", "2024", "2025" }));
        getContentPane().add(cbbyear);
        cbbyear.setBounds(220, 300, 70, 30);

        jLabel3.setFont(new java.awt.Font("Tahoma", 1, 14)); // NOI18N
        jLabel3.setIcon(new javax.swing.ImageIcon(getClass().getResource("/pf_bd/Images/Calendar-icon.png"))); // NOI18N
        jLabel3.setText("Agregar Nueva Cita");
        getContentPane().add(jLabel3);
        jLabel3.setBounds(20, 50, 280, 40);

        jLabel4.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jLabel4.setText("Año");
        getContentPane().add(jLabel4);
        jLabel4.setBounds(230, 280, 34, 15);

        jLabel5.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jLabel5.setText("Hora:");
        getContentPane().add(jLabel5);
        jLabel5.setBounds(30, 280, 34, 15);

        jLabel6.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jLabel6.setText("Mes");
        getContentPane().add(jLabel6);
        jLabel6.setBounds(160, 280, 34, 15);

        jLabel7.setText("Medico que atendera:");
        getContentPane().add(jLabel7);
        jLabel7.setBounds(30, 170, 180, 20);

        getContentPane().add(cmbPaciente);
        cmbPaciente.setBounds(30, 130, 220, 30);

        calendario.addMouseListener(new java.awt.event.MouseAdapter()
        {
            public void mouseClicked(java.awt.event.MouseEvent evt)
            {
                calendarioMouseClicked(evt);
            }
        });
        getContentPane().add(calendario);
        calendario.setBounds(320, 90, 370, 210);

        jLabel8.setText("Verifique su fecha aquí:");
        getContentPane().add(jLabel8);
        jLabel8.setBounds(320, 50, 200, 40);

        jLabel9.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jLabel9.setText("Día");
        getContentPane().add(jLabel9);
        jLabel9.setBounds(100, 280, 34, 15);

        cbbhour.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "06:00", "06:30", "07:00", "07:30", "08:00", "08:30", "09:00", "09:30", "10:00", "10:30", "11:00", "11:30", "12:00", "12:30", "13:00", "13:30", "14:00", "14:30", "15:00", "15:30", "16:00", "16:30", "17:00", "17:30", "18:00", "18:30", "19:00", "19:30", "20:00", "20:30", "21:00", "21:30", "22:00", "22:30" }));
        getContentPane().add(cbbhour);
        cbbhour.setBounds(30, 300, 60, 30);

        getContentPane().add(cmbMedico);
        cmbMedico.setBounds(30, 190, 220, 30);

        jLabel10.setText("Paciente a citar:");
        getContentPane().add(jLabel10);
        jLabel10.setBounds(30, 100, 180, 20);

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void BtnCancActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BtnCancActionPerformed
        String fecha = cbbyear.getSelectedItem().toString() + "-" + cbbmonth.getSelectedItem().toString() + "-" + cbbday.getSelectedItem().toString() + " " + cbbhour.getSelectedItem().toString();
        Conexion conex = new Conexion();
        if(!conex.ExisteEnBD("select * from Cita where FechaHora='"+fecha+"' and CedulaProfesional='"+cmbMedico.getSelectedItem().toString()+"';")){
            if(conex.EjecutarActualizacion("insert into Cita values('"+fecha+"','"+cmbPaciente.getSelectedItem().toString()+"','"+cmbMedico.getSelectedItem().toString()+"',NULL,'"+idUser+"');")){
                util.LanzaMensaje("Cita creada", "Cita creada con exito");
                Antecesor.ActualizarJTable();
            }
        } else {
            util.LanzaAdvertencia("Horario no disponible", "El horario en el que usted intenta registrar la cita ya se encuentra ocupado, porfavor intente de nuevo con otra fecha.");
        }
    }//GEN-LAST:event_BtnCancActionPerformed

    private void calendarioMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_calendarioMouseClicked
        
    }//GEN-LAST:event_calendarioMouseClicked

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton BtnCanc;
    private com.toedter.calendar.JCalendar calendario;
    private javax.swing.JComboBox<String> cbbday;
    private javax.swing.JComboBox<String> cbbhour;
    private javax.swing.JComboBox<String> cbbmonth;
    private javax.swing.JComboBox<String> cbbyear;
    private javax.swing.JComboBox<String> cmbMedico;
    private javax.swing.JComboBox<String> cmbPaciente;
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
    private java.awt.Panel panel1;
    // End of variables declaration//GEN-END:variables
}
