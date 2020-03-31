package ophiuchuscontrol;

import entidades.Cita;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.ImageIcon;
import javax.swing.JMenuItem;
import javax.swing.JPopupMenu;
import javax.swing.table.TableModel;

public class VistaCitas extends javax.swing.JFrame {
    private Utilidades util;
    private VistaPacientes Antecesor;
    private boolean esMedico;
    private Cita C = new Cita();
    private String id;
    private JMenuItem Eliminar;
    private JPopupMenu pupopMenu = new JPopupMenu();
    //private ImageIcon iconoEditar = new ImageIcon(getClass().getResource("/imagenes/lapiz.png"));     
    private ImageIcon iconoEliminar  = new ImageIcon(getClass().getResource("/imagenes/eliminar.png"));
    
    public VistaCitas(boolean esMedico, String id) {
        initComponents();
        //this.Editar = new JMenuItem("Editar Registro",iconoEditar);
        this.Eliminar = new JMenuItem("Eliminar Cita",iconoEliminar);
        util = new Utilidades();
        this.esMedico = esMedico;
        this.id = id;
        C.setCedula(id);
        ActualizarJTable();
    }
    
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents()
    {

        panel1 = new java.awt.Panel();
        jLabel1 = new javax.swing.JLabel();
        jScrollPane1 = new javax.swing.JScrollPane();
        tablaCitas = new javax.swing.JTable();
        LBuscar = new javax.swing.JLabel();
        txtBusqueda = new javax.swing.JTextField();
        BtnBuscar = new javax.swing.JButton();
        btnRegistroPaciente = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        panel1.setBackground(new java.awt.Color(86, 110, 115));
        panel1.setForeground(new java.awt.Color(0, 204, 204));

        jLabel1.setForeground(new java.awt.Color(240, 240, 240));
        jLabel1.setText("Citas");

        javax.swing.GroupLayout panel1Layout = new javax.swing.GroupLayout(panel1);
        panel1.setLayout(panel1Layout);
        panel1Layout.setHorizontalGroup(
            panel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(panel1Layout.createSequentialGroup()
                .addGap(338, 338, 338)
                .addComponent(jLabel1)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        panel1Layout.setVerticalGroup(
            panel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(panel1Layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jLabel1)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        tablaCitas.setModel(new javax.swing.table.DefaultTableModel(
            new Object [][]
            {
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null}
            },
            new String []
            {
                "Fecha", "CURP", "Doctor", "Costo"
            }
        ));
        tablaCitas.setMaximumSize(new java.awt.Dimension(900, 600));
        tablaCitas.setPreferredSize(new java.awt.Dimension(750, 450));
        tablaCitas.addMouseListener(new java.awt.event.MouseAdapter()
        {
            public void mouseClicked(java.awt.event.MouseEvent evt)
            {
                tablaCitasMouseClicked(evt);
            }
        });
        jScrollPane1.setViewportView(tablaCitas);

        LBuscar.setText("Buscar:");

        txtBusqueda.addActionListener(new java.awt.event.ActionListener()
        {
            public void actionPerformed(java.awt.event.ActionEvent evt)
            {
                txtBusquedaActionPerformed(evt);
            }
        });

        BtnBuscar.setText("Buscar");
        BtnBuscar.addActionListener(new java.awt.event.ActionListener()
        {
            public void actionPerformed(java.awt.event.ActionEvent evt)
            {
                BtnBuscarActionPerformed(evt);
            }
        });

        btnRegistroPaciente.setText("Agregar una nueva cita");
        btnRegistroPaciente.addActionListener(new java.awt.event.ActionListener()
        {
            public void actionPerformed(java.awt.event.ActionEvent evt)
            {
                btnRegistroPacienteActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(24, 24, 24)
                .addComponent(LBuscar)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(txtBusqueda, javax.swing.GroupLayout.PREFERRED_SIZE, 192, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(BtnBuscar)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
            .addComponent(panel1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                        .addComponent(btnRegistroPaciente)
                        .addGap(38, 38, 38))
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                        .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 673, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addContainerGap())))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addComponent(panel1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(14, 14, 14)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(txtBusqueda, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(BtnBuscar)
                    .addComponent(LBuscar))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 235, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(24, 24, 24)
                .addComponent(btnRegistroPaciente))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void BtnBuscarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BtnBuscarActionPerformed
        if(!txtBusqueda.getText().equals("")){
            Conexion conex = new Conexion();
            if(this.esMedico){
                conex.LlenaJTable(tablaCitas,"SELECT PacienteCurp, FechaHora FROM Cita WHERE CedulaProfesional='"+this.id+"' AND PacienteCurp LIKE '"+txtBusqueda.getText()+"%';");
            } else {
                conex.LlenaJTable(tablaCitas,"SELECT PacienteCurp,CedulaProfesional,FechaHora FROM Cita WHERE idEmpleado='"+this.id+"' AND PacienteCurp LIKE '"+txtBusqueda.getText()+"%';");
            }
        } else {
            ActualizarJTable();
        }
    }//GEN-LAST:event_BtnBuscarActionPerformed

    private void btnRegistroPacienteActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnRegistroPacienteActionPerformed
        if(this.esMedico){
            util.SetDialogo(new RegistroCitaMedico(this.id,this));
        } else {
            util.SetDialogo(new RegistroCitaEmpleado(this.id,this));
        }
    }//GEN-LAST:event_btnRegistroPacienteActionPerformed

    private void txtBusquedaActionPerformed(java.awt.event.ActionEvent evt)//GEN-FIRST:event_txtBusquedaActionPerformed
    {//GEN-HEADEREND:event_txtBusquedaActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txtBusquedaActionPerformed

    private void tablaCitasMouseClicked(java.awt.event.MouseEvent evt)//GEN-FIRST:event_tablaCitasMouseClicked
    {//GEN-HEADEREND:event_tablaCitasMouseClicked
       if(!this.esMedico){
        int i = tablaCitas.getSelectedRow();
        TableModel model = tablaCitas.getModel();
        VistaCitas.this.C.setPaciente(model.getValueAt(i, 0).toString());
        VistaCitas.this.C.setFecha(model.getValueAt(i,2).toString());
       }else{
          int i = tablaCitas.getSelectedRow();
          TableModel model = tablaCitas.getModel();
          VistaCitas.this.C.setPaciente(model.getValueAt(i, 0).toString());
          VistaCitas.this.C.setFecha(model.getValueAt(i,1).toString());
       }
       
        Eliminar.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
              boolean respuesta;
              Conexion con = new Conexion();
              String Consulta = "delete from Cita where PacienteCurp = '"+C.getPaciente()+"'AND "
                      + " CedulaProfesional = '"+C.getCedula()+"';";
              
              respuesta = con.EjecutarActualizacion(Consulta);
              if(respuesta){
                  VistaCitas.this.util.LanzaMensaje("Exito", "Registro Eliminado");
              }else{
                  VistaCitas.this.util.LanzaMensaje("Error", "La Cita no se pudo Eliminar");
              }
              ActualizarJTable();
            }
        });
        
        pupopMenu.add(Eliminar);
        //pupopMenu.add(Editar);
        tablaCitas.setComponentPopupMenu(pupopMenu);
    }//GEN-LAST:event_tablaCitasMouseClicked

    public void ActualizarJTable(){
        Conexion conex = new Conexion();
        if(this.esMedico){
            conex.LlenaJTable(tablaCitas,"SELECT PacienteCurp, FechaHora FROM Cita WHERE CedulaProfesional='"+this.id+"';");
        } else {
            conex.LlenaJTable(tablaCitas,"SELECT PacienteCurp,CedulaProfesional,FechaHora FROM Cita WHERE idEmpleado='"+this.id+"';");
        }
    }
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton BtnBuscar;
    private javax.swing.JLabel LBuscar;
    private javax.swing.JButton btnRegistroPaciente;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JScrollPane jScrollPane1;
    private java.awt.Panel panel1;
    private javax.swing.JTable tablaCitas;
    private javax.swing.JTextField txtBusqueda;
    // End of variables declaration//GEN-END:variables
}
