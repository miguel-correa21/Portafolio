package entidades;

public class Paciente {
    
    private String Curp;   
    private String Nombre;
    private String ApPat;
    private String ApMat;
    private String Email;
    private String  Tel;

    public Paciente(String Curp, String Nombre, String ApPat, String ApMat, String Email, String Tel) {
        this.Curp = Curp;
        this.Nombre = Nombre;
        this.ApPat = ApPat;
        this.ApMat = ApMat;
        this.Email = Email;
        this.Tel = Tel;
    }
    
    public Paciente(){
        
    }
    
    public boolean ObligatoriosNoNulosCortos(){
        if(Curp.isEmpty()||Nombre.isEmpty()||ApPat.isEmpty()||ApMat.isEmpty()){
            return false;
        }
        return true;
    }

    public String getCurp() {
        return Curp;
    }

    public void setCurp(String Curp) {
        this.Curp = Curp;
    }

    public String getNombre() {
        return Nombre;
    }

    public void setNombre(String Nombre) {
        this.Nombre = Nombre;
    }

    public String getApPat() {
        return ApPat;
    }

    public void setApPat(String ApPat) {
        this.ApPat = ApPat;
    }

    public String getApMat() {
        return ApMat;
    }

    public void setApMat(String ApMat) {
        this.ApMat = ApMat;
    }

    public String getEmail() {
        return Email;
    }

    public void setEmail(String Email) {
        this.Email = Email;
    }

    public String getTel() {
        return Tel;
    }

    public void setTel(String Tel) {
        this.Tel = Tel;
    }
    
}
