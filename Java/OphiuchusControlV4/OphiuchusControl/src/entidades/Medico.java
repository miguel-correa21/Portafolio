package entidades;

public class Medico {

    private String Cedula;
    private String Nombre;
    private String ApPat;
    private String ApMat;
    private String Email;
    private String Tel;
    private String Pass;

    public Medico(String Cedula, String Nombre, String ApPat, String ApMat, String Email, String Tel, String Pass) {
        this.Cedula = Cedula;
        this.Nombre = Nombre;
        this.ApPat = ApPat;
        this.ApMat = ApMat;
        this.Email = Email;
        this.Tel = Tel;
        this.Pass = Pass;
    }
    
    public boolean ObligatoriosNoNulosCortos(){
        if(Cedula.isEmpty()||Nombre.isEmpty()||ApPat.isEmpty()||ApMat.isEmpty()||Pass.isEmpty()){
            return false;
        }
        return true;
    }

    public String getCedula() {
        return Cedula;
    }

    public void setCedula(String Cedula) {
        this.Cedula = Cedula;
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
        if(this.Email.isEmpty()){
            this.Email = null;
        }
    }

    public String getTel() {
        return Tel;
    }

    public void setTel(String Tel) {
        this.Tel = Tel;
        if(this.Tel.isEmpty()){
            this.Tel = null;
        }
    }

    public String getPass() {
        return Pass;
    }

    public void setPass(String Pass) {
        this.Pass = Pass;
    }
}
