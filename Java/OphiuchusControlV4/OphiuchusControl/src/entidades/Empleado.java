package entidades;

public class Empleado {

    private String idEmp;
    private String Nombre;
    private String ApPat;
    private String ApMat;
    private String Puesto;
    private String Tel;
    private String Pass;

    public Empleado(String idEmp, String Nombre, String ApPat, String ApMat, String Puesto, String Tel, String Pass) {
        this.idEmp = idEmp;
        this.Nombre = Nombre;
        this.ApPat = ApPat;
        this.ApMat = ApMat;
        this.Puesto = Puesto;
        this.Tel = Tel;
        this.Pass = Pass;
    }
    
    public boolean ObligatoriosNoNulosCortos(){
        if(idEmp.isEmpty()||Nombre.isEmpty()||ApPat.isEmpty()||ApMat.isEmpty()||Pass.isEmpty()||Puesto.isEmpty()){
            return false;
        }
        return true;
    }

    public String getIdEmp() {
        return idEmp;
    }

    public void setIdEmp(String idEmp) {
        this.idEmp = idEmp;
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

    public String getPuesto() {
        return Puesto;
    }

    public void setPuesto(String Puesto) {
        this.Puesto = Puesto;
    }

    public String getTel() {
        return Tel;
    }

    public void setTel(String Tel) {
        this.Tel = Tel;
    }

    public String getPass() {
        return Pass;
    }

    public void setPass(String Pass) {
        this.Pass = Pass;
    }

}
