package ophiuchuscontrol;

import java.sql.*;
import java.util.*;
import javax.swing.*;
import javax.swing.table.DefaultTableModel;

public class Conexion {
    private Utilidades util;
    private Connection conn;
    private String driver, user, url, password;

    //Sobrecargados
    public Conexion(){
        /*this.driver = "com.mysql.jdbc.Driver";
        this.user = "root";
        this.url = "jdbc:mysql://localhost:3306/consultorio?useSSL=false";
        this.password = "";*///conexion aburrida en local
        //conexion pro
        this.driver = "com.mysql.jdbc.Driver";
        this.user = "ArbolitoSempai97";
        this.password = "637bARrq)]2(";
        //configurar servidor remoto desde el host usar %
        this.url = "jdbc:mysql://nibblux.com/OphiuchusControlDB?useSSL=false";
    }
    
    //637bARrq)]2(

    //retorna verdadero si pudo hacer la insercion
    public boolean EjecutarActualizacion(String consulta) {
        boolean r = true;
        try {
            CreaConexion();
            Statement sentencia = conn.createStatement();
            sentencia.executeUpdate(consulta);
            System.out.println("Actualizacion de la BD ejecutada con exito!");
            CierraConexion();
        } catch (SQLException e) {
            System.out.println("Error en la consula.\nError: " + e);
            r = false;
        } catch (ClassNotFoundException s) {
            System.out.println("Imposible conectar. \nError: " + s);
            r = false;
        }
        return r;
    }

    //retorna las tuplas resultado de la consulta
    public ResultSet EjecutarConsulta(String consulta) {
        ResultSet r;
        try {
            CreaConexion();
            Statement sentencia = conn.createStatement();
            r = sentencia.executeQuery(consulta);
            System.out.println("Consulta ejecutada con exito!");
            //CierraConexion(); //Por alguna razon no funciona aqui
        } catch (SQLException e) {
            System.out.println("Error en la consula.\nError: " + e);
            r = null;
        } catch (ClassNotFoundException s) {
            System.out.println("Imposible conectar. \nError: " + s);
            r = null;
        }
        return r;
    }

    //Llena un JTable con todas las tuplas generadas de la consulta
    public void LlenaJTable(JTable tbl, String consulta) {
        ResultSet rs = EjecutarConsulta(consulta);
        try {
            ResultSetMetaData metaData = rs.getMetaData();
            Vector<String> columnNames = new Vector<>();
            int columnCount = metaData.getColumnCount();
            for (int column = 1; column <= columnCount; column++) {
                columnNames.add(metaData.getColumnName(column));
            }
            Vector<Vector<Object>> data = new Vector<>();
            while (rs.next()) {
                Vector<Object> vector = new Vector<>();
                for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                    vector.add(rs.getObject(columnIndex));
                }
                data.add(vector);
            }
            tbl.setModel(new DefaultTableModel(data, columnNames));
            CierraConexion();
        } catch (SQLException ex) {
            System.out.println("Error al cargar modelo al JTable " + tbl.getName() + ".\nError: " + ex);
        }
    }
    //llena un combobox con los resultados de la consulta dada
    //(arrojar una sola columna en la consulta para que funcione correctamente)
    public void LlenaComboBox(JComboBox cmb, String consulta) {
        ResultSet rs = EjecutarConsulta(consulta);
        try {
            while (rs.next()) {
                cmb.addItem(rs.getObject(1));
            }
            cmb.setSelectedIndex(0);
            CierraConexion();
        } catch (SQLException ex) {
            System.out.println("Error al obtener los datos de la BD.\nError: " + ex);
        }
    }

    //Si la consulta genera mas de una tupla retorna true, de lo contrario false
    public boolean ExisteEnBD(String consulta) {
        ResultSet rs = EjecutarConsulta(consulta);
        try {
            if (rs.next()) {
                CierraConexion();
                return true;
            }
            CierraConexion();
        } catch (SQLException ex) {
            System.out.println("Error al obtener los datos de la BD.\nError: " + ex);
        }
        return false;
    }

    //Retorna el valor de la primera o unica tupla
    public String getValor(String consulta) {
        ResultSet rs = EjecutarConsulta(consulta);
        String c = "";
        try {
            if (rs.next()) {
                c += rs.getObject(1);
            }
            CierraConexion();
        } catch (SQLException ex) {
            System.out.println("Error al obtener los datos de la BD.\nError: " + ex);
        }
        return c;
    }

    private void CreaConexion() throws SQLException, ClassNotFoundException {
        Class.forName(driver);
        conn = DriverManager.getConnection(url, user, password);
    }

    private void CierraConexion() throws SQLException {
        conn.close();
        System.out.println("Conexion terminada.");
    }
}
