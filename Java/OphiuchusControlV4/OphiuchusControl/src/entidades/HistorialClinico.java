package entidades;

public class HistorialClinico {
    private String CedulaProfesional;
    private String PacienteCurp;
    private String Nombre;
    private String RutaArchivo;

    public HistorialClinico(String CedulaProfesional, String PacienteCurp, String Nombre, String RutaArchivo) {
        this.CedulaProfesional = CedulaProfesional;
        this.PacienteCurp = PacienteCurp;
        this.Nombre = Nombre;
        this.RutaArchivo = RutaArchivo;
    }
    public HistorialClinico(){}
    
    public boolean ObligatoriosNoNulosCortos(){
        if(CedulaProfesional.isEmpty()||PacienteCurp.isEmpty()||Nombre.isEmpty()||RutaArchivo.isEmpty()){
            return false;
        }
        return true;
    }

    public String getCedulaProfesional() {
        return CedulaProfesional;
    }

    public void setCedulaProfesional(String CedulaProfesional) {
        this.CedulaProfesional = CedulaProfesional;
    }

    public String getPacienteCurp() {
        return PacienteCurp;
    }

    public void setPacienteCurp(String PacienteCurp) {
        this.PacienteCurp = PacienteCurp;
    }

    public String getNombre() {
        return Nombre;
    }

    public void setNombre(String Nombre) {
        this.Nombre = Nombre;
    }

    public String getRutaArchivo() {
        return RutaArchivo;
    }

    public void setRutaArchivo(String RutaArchivo) {
        this.RutaArchivo = RutaArchivo;
    }
    
}
