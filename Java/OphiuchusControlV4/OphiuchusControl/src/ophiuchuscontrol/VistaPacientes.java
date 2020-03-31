package ophiuchuscontrol;

import entidades.Paciente;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.ImageIcon;
import javax.swing.JMenuItem;
import javax.swing.JPopupMenu;
import javax.swing.table.TableModel;

public class VistaPacientes extends javax.swing.JFrame {
    private Utilidades util ;
    public Paciente p = new Paciente();
    private ImageIcon iconoEditar = new ImageIcon(getClass().getResource("/imagenes/lapiz.png"));     
    private ImageIcon iconoEliminar  = new ImageIcon(getClass().getResource("/imagenes/eliminar.png"));
    private JMenuItem Editar = new JMenuItem("Editar Registro",iconoEditar);
    private JMenuItem Eliminar = new JMenuItem("Eliminar Registro",iconoEliminar);
    private JPopupMenu pupopMenu = new JPopupMenu();
    private ActualizacionPaciente ap;
    
    public VistaPacientes() {
        initComponents();
        this.util = new Utilidades();
        ActualizarJTable();
    }

    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents()
    {

        panel1 = new java.awt.Panel();
        jLabel1 = new javax.swing.JLabel();
        jScrollPane1 = new javax.swing.JScrollPane();
        tablaPaciente = new javax.swing.JTable();
        txtBusqueda = new javax.swing.JTextField();
        LBuscar = new javax.swing.JLabel();
        btnBuscar = new javax.swing.JButton();
        btnRegistro = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setName("Pacientes"); // NOI18N

        panel1.setBackground(new java.awt.Color(86, 110, 115));
        panel1.setForeground(new java.awt.Color(0, 204, 204));

        jLabel1.setForeground(new java.awt.Color(240, 240, 240));
        jLabel1.setText("Pacientes");

        javax.swing.GroupLayout panel1Layout = new javax.swing.GroupLayout(panel1);
        panel1.setLayout(panel1Layout);
        panel1Layout.setHorizontalGroup(
            panel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, panel1Layout.createSequentialGroup()
                .addContainerGap(452, Short.MAX_VALUE)
                .addComponent(jLabel1)
                .addGap(447, 447, 447))
        );
        panel1Layout.setVerticalGroup(
            panel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(panel1Layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jLabel1)
                .addContainerGap(15, Short.MAX_VALUE))
        );

        tablaPaciente.setModel(new javax.swing.table.DefaultTableModel(
            new Object [][]
            {
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null}
            },
            new String []
            {
                "CURP", "Nombre", "Doctor", "Archivo"
            }
        ));
        tablaPaciente.addMouseListener(new java.awt.event.MouseAdapter()
        {
            public void mouseClicked(java.awt.event.MouseEvent evt)
            {
                tablaPacienteMouseClicked(evt);
            }
        });
        jScrollPane1.setViewportView(tablaPaciente);

        LBuscar.setText("Buscar:");

        btnBuscar.setText("Buscar");
        btnBuscar.addActionListener(new java.awt.event.ActionListener()
        {
            public void actionPerformed(java.awt.event.ActionEvent evt)
            {
                btnBuscarActionPerformed(evt);
            }
        });

        btnRegistro.setText("Agregar nuevo paciente");
        btnRegistro.addActionListener(new java.awt.event.ActionListener()
        {
            public void actionPerformed(java.awt.event.ActionEvent evt)
            {
                btnRegistroActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(panel1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(LBuscar)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(txtBusqueda, javax.swing.GroupLayout.PREFERRED_SIZE, 203, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(btnBuscar)
                        .addGap(0, 0, Short.MAX_VALUE))
                    .addComponent(jScrollPane1))
                .addContainerGap())
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(btnRegistro)
                .addGap(23, 23, 23))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addComponent(panel1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(LBuscar)
                    .addComponent(txtBusqueda, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(btnBuscar))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 229, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(btnRegistro)
                .addContainerGap(15, Short.MAX_VALUE))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void btnRegistroActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnRegistroActionPerformed
        util.SetDialogo(new RegistroPaciente(this));
    }//GEN-LAST:event_btnRegistroActionPerformed

    private void btnBuscarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnBuscarActionPerformed
        if(!txtBusqueda.getText().equals("")){
            Conexion conex = new Conexion();
            conex.LlenaJTable(tablaPaciente,"SELECT * FROM Paciente WHERE Curp LIKE '"+txtBusqueda.getText()+"%';");
        } else {
            ActualizarJTable();
        }
    }//GEN-LAST:event_btnBuscarActionPerformed

    private void tablaPacienteMouseClicked(java.awt.event.MouseEvent evt)//GEN-FIRST:event_tablaPacienteMouseClicked
    {//GEN-HEADEREND:event_tablaPacienteMouseClicked
        int i = tablaPaciente.getSelectedRow();
        TableModel model = tablaPaciente.getModel();
        VistaPacientes.this.p.setCurp(model.getValueAt(i,0).toString());
        VistaPacientes.this.p.setNombre(model.getValueAt(i, 1).toString());
        VistaPacientes.this.p.setApPat(model.getValueAt(i,2).toString());
        VistaPacientes.this.p.setApMat(model.getValueAt(i,3).toString());
        VistaPacientes.this.p.setTel(model.getValueAt(i,4).toString());
        VistaPacientes.this.p.setEmail(model.getValueAt(i,5).toString());
        Editar.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
               
                ap = new ActualizacionPaciente();
                ap.LlenarCampos(VistaPacientes.this.p);
                util.SetDialogo(ap);
                ActualizarJTable();
            }
        });  
        Eliminar.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
              boolean respuesta;
              Conexion con = new Conexion();
              
              String Consulta = "delete from Paciente where Curp = '"+p.getCurp()+"';";
              respuesta = con.EjecutarActualizacion(Consulta);
              if(respuesta){
                  VistaPacientes.this.util.LanzaMensaje("Exito", "Registro Eliminado");
              }else{
                  VistaPacientes.this.util.LanzaMensaje("Error", "El Registro no se pudo Eliminar");
              }
              ActualizarJTable();
            }
        });
        
        pupopMenu.add(Eliminar);
        pupopMenu.add(Editar);
        tablaPaciente.setComponentPopupMenu(pupopMenu);
        
    }//GEN-LAST:event_tablaPacienteMouseClicked

    public void ActualizarJTable(){
        Conexion conex = new Conexion();
        conex.LlenaJTable(tablaPaciente,"SELECT * FROM Paciente;");
    }
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JLabel LBuscar;
    private javax.swing.JButton btnBuscar;
    private javax.swing.JButton btnRegistro;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JScrollPane jScrollPane1;
    private java.awt.Panel panel1;
    private javax.swing.JTable tablaPaciente;
    private javax.swing.JTextField txtBusqueda;
    // End of variables declaration//GEN-END:variables
}
