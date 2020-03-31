package  entidades;

public class Cita{
    private String FechaHora;
    private String PacienteCurp;
    private String Cedula;
    private float Costo;
    private String idEmpleado;
    
    public Cita(){
        
    }
    
    public void setFecha(String Fecha){
        this.FechaHora = Fecha;
    }
    public String getFecha(){
        return this.FechaHora;
    }
    
    public void setPaciente(String Paciente){
        this.PacienteCurp = Paciente;
    }
    public String getPaciente(){
        return this.PacienteCurp;
    }
    
    public void setCedula(String Cedula){
        this.Cedula = Cedula;
    }
    public String getCedula(){
        return this.Cedula;
    }
    
    
    public void setCosto(float costo){
        this.Costo = costo;
    }
    public float getCosto(){
        return this.Costo;
    }
    
    public void setidEmpleado(String id){
        this.idEmpleado = id;
    }
    
}