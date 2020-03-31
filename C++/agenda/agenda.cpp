#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#define ARCHIVO "Contactos.dat"

using namespace std;

struct contacto
{
    char nombre[30];
    char ApellidoPaterno[30];
    char ApellidoMaterno[30];
    char Telefono[30];
    int Edad;
    char Correo[50];
};
/**************************FUNCIONES DEL PROGRAMA************/
bool GuardarContacto(contacto c);
contacto LeerContacto();
bool ExisteContacto(char nombre[], char correo[]);
contacto BuscarContacto(char nombre[], char correo[]);
void MostrarContacto(contacto c);
void ListarContatos();
void EliminarContacto(char nombre[], char correo[]);
void ActualizarContacto(char nombre[], char correo[]);
/***************************************************************/

/**********************Funciones para Menus*********************/
void MenuIngresar();
void MenuBuscar();
void MenuListado();
void MenuEliminar();
void MenuActualizar();
/***************************************************************/
int main()
{
    int opcion;
    do
    {
        system("clear");
        cout << "\t\t\t\tAGENDA" << endl;
        cout << "\t\t\tIngresar contacto............[1]" << endl;
        cout << "\t\t\tBuscar contacto..............[2]" << endl;
        cout << "\t\t\tVer contactos................[3]" << endl;
        cout << "\t\t\tEliminar contacto............[4]" << endl;
        cout << "\t\t\tActualizar contacto..........[5]" << endl;
        cout << "\t\t\tSALIR........................[6]" << endl;
        cout << "\t\t\tIngrese Una opcion ->:";
        cin >> opcion;
        cin.ignore();
        switch (opcion)
        {
        case 1:
            system("clear");
            MenuIngresar();
            break;
        case 2:
            system("clear");
            MenuBuscar();
            break;
        case 3:
            system("clear");
            MenuListado();
            break;
        case 4:
            system("clear");
            MenuEliminar();
            break;
        case 5:
            system("clear");
            MenuActualizar();
            break;
        case 6:
            break;
        default:
            cout << "\t\t\t Opcion incorrecta" << endl;
        }
        getchar();

    } while (opcion != 6);
    return 0;
}

bool GuardarContacto(contacto c)
{
    bool respuesta;
    ofstream salida;
    salida.open(ARCHIVO, ios::binary | ios::app);
    if (salida.good())
    {
        salida.write((char *)&c, sizeof(contacto));
        salida.close();
        respuesta = true;
    }
    else
    {
        cout << "\t\t\t¡¡¡¡El archivo esta dañado!!!!";
        respuesta = false;
        salida.close();
    }
    return respuesta;
}

contacto LeerContacto()
{
    contacto c;
    cout << "\t\t\t           Nombre: ";
    cin.getline(c.nombre, 30);
    cout << "\t\t\t Apellido Paterno: ";
    cin.getline(c.ApellidoPaterno, 30);
    cout << "\t\t\t Apellido Materno: ";
    cin.getline(c.ApellidoMaterno, 30);
    cout << "\t\t\t         Telefono: ";
    cin.getline(c.Telefono, 30);
    cout << "\t\t\t             Edad: ";
    cin >> c.Edad;
    cin.ignore();
    cout << "\t\t\t            Correo: ";
    cin.getline(c.Correo, 50);

    return c;
}

bool ExisteContacto(char nombre[], char correo[])
{
    bool existe;
    contacto c;
    ifstream entrada;
    entrada.open(ARCHIVO, ios::binary);
    if (entrada.good())
    {
        while (entrada.read((char *)&c, sizeof(contacto)))
        {
            //string comparation
            if (strcmp(nombre, c.nombre) == 0 && strcmp(correo, c.Correo) == 0)
            {
                entrada.close();
                return true;
            }
            else
                continue;
        }
        existe = false;
    }
    else
    {
        existe = false;
    }
    entrada.close();
    return existe;
}

contacto BuscarContacto(char nombre[], char correo[])
{
    contacto c;
    ifstream entrada;
    entrada.open(ARCHIVO, ios::binary);
    if (ExisteContacto(nombre, correo))
    {
        while (entrada.read((char *)&c, sizeof(contacto)))
        {
            //string comparation
            if (strcmp(nombre, c.nombre) == 0 && strcmp(correo, c.Correo) == 0)
            {
                entrada.close();
                return c;
            }
        }
    }
    else
    {
        cout << "\t\t\tEl contacto con nombre "
             << nombre << "y con correo " << correo << "no existe"
             << endl;
    }
    entrada.close();
    return c;
}
void MostrarContacto(contacto c)
{
    cout << endl;
    cout << "\t\t\t           Nombre: " << c.nombre << endl;
    cout << "\t\t\t Apellido Paterno: " << c.ApellidoPaterno << endl;
    cout << "\t\t\t Apellido Materno: " << c.ApellidoMaterno << endl;
    cout << "\t\t\t         Teléfono: " << c.Telefono << endl;
    cout << "\t\t\t             Edad: " << c.Edad << endl;
    cout << "\t\t\t           Correo: " << c.Correo << endl;
    cout << endl;
}
void ListarContatos()
{
    ifstream entrada;
    entrada.open(ARCHIVO, ios::binary);
    contacto c;
    if (entrada.good())
    {
        while (entrada.read((char *)&c, sizeof(contacto)))
        {
            MostrarContacto(c);
        }
    }
    else
    {
        cout << "ha ocurrido un error al intentar abrir el archivo"
             << endl;
    }
    entrada.close();
}

void EliminarContacto(char nombre[], char correo[])
{
    ofstream temporal;
    ifstream entrada;
    entrada.open(ARCHIVO, ios::binary);
    temporal.open("temp.dat", ios::binary);
    contacto c;
    if (ExisteContacto(nombre, correo))
    {
        if (entrada.good())
        {
            while (entrada.read((char *)&c, sizeof(contacto)))
            {
                if (strcmp(nombre, c.nombre) != 0 || strcmp(correo, c.Correo) != 0)
                {
                    temporal.write((char *)&c, sizeof(contacto));
                }
            }
        }
        else
        {
            cout << "\t\t\thubo algun error al abrir el archivo"
                 << endl;
        }
        entrada.close();
        temporal.close();
        remove(ARCHIVO);
        rename("temp.dat", ARCHIVO);
        cout << "\t\t\tArchivo eliminado" << endl;
    }
    else
    {
        cout << "\t\t\tEl contacto no existe" << endl;
    }
    temporal.close();
}
void ActualizarContacto(char nombre[], char correo[])
{
    ifstream entrada;
    ofstream temporal;
    entrada.open(ARCHIVO, ios::binary);
    temporal.open("temp.dat", ios::binary);
    contacto c;
    if (entrada.good())
    {
        while (entrada.read((char *)&c, sizeof(contacto)))
        {
            if (strcmp(nombre, c.nombre) == 0 || strcmp(correo, c.Correo) == 0)
            {
                contacto actualizado = LeerContacto();
                temporal.write((char *)&actualizado, sizeof(contacto));
            }
            else
            {
                temporal.write((char *)&c, sizeof(contacto));
            }
        }
        entrada.close();
        temporal.close();
        remove(ARCHIVO);
        rename("temp.dat", ARCHIVO);
    }
    else
    {
        cout << "\t\t\tHubo un error al intentar abrir el archivo"
             << endl;
    }
}
void MenuIngresar()
{
    cout << "\t\t\tINGRESAR NUEVO CONTACTO " << endl;
    contacto nuevo = LeerContacto();
    if (ExisteContacto(nuevo.nombre, nuevo.Correo))
    {
        cout << "\t\t\tCONTACTO YA: EXISTENTE" << endl;
    }
    else
    {
        GuardarContacto(nuevo);
        cout << "\t\t\tCONTACTO AGREGADO CON EXITO" << endl;
    }
}
void MenuBuscar()
{
    cout << "\t\t\t BUSCAR CONTACTO" << endl;
    char nombre[30];
    char correo[50];
    cout << "\t\t\tIngrese el nombre y el correo del contaco a buscar" << endl;
    cout << "\t\t\tNombre: ";
    cin.getline(nombre, 30);
    cout << "\t\t\tCorreo: ";
    cin.getline(correo, 50);
    if (ExisteContacto(nombre, correo))
    {
        contacto buscado = BuscarContacto(nombre, correo);
        MostrarContacto(buscado);
    }
    else
    {
        cout << "\t\t\t No se encuentro el contacto" << endl;
    }
}
void MenuListado()
{
    cout << "\t\t\t\tLISTA DE CONTACTOS" << endl;
    ListarContatos();
}
void MenuEliminar()
{
    cout << "\t\t\t ELIMINAR CONTACTO" << endl;
    char nombre[30];
    char correo[50];
    int opcion;
    cout << "\t\t\tIngrese el nombre y el correo del contaco a eliminar" << endl;
    cout << "\t\t\tNombre: ";
    cin.getline(nombre, 30);
    cout << "\t\t\tCorreo: ";
    cin.getline(correo, 50);
    if (ExisteContacto(nombre, correo))
    {
        cout << "\t\t\t¿Seguro de eliminar el contacto?" << endl;
        contacto eliminar = BuscarContacto(nombre, correo);
        MostrarContacto(eliminar);
        do
        {
            cout << "\t\t\t SI[1]... NO[2]" << ends;
            cin >> opcion;
            cin.ignore();
            switch (opcion)
            {
            case 1:
                EliminarContacto(nombre, correo);
                cout << "\t\t\t Contacto eliminado con exito"
                     << endl;
                break;
            case 2:
                break;
            default:
                cout << "\t\t\tOPCION INCORRECTA" << endl;
            }
        } while (opcion != 1 && opcion != 2);
    }
    else
    {
        cout << "\t\t\tEL CONTACTO NO EXISTE" << endl;
    }
}
void MenuActualizar()
{
    cout << "\t\t\t ACTUALIZAR CONTACTO" << endl;
    char nombre[30];
    char correo[50];
    int opcion;
    cout << "\t\t\tIngrese el nombre y el correo del contaco a actualizar" << endl;
    cout << "\t\t\tNombre: ";
    cin.getline(nombre, 30);
    cout << "\t\t\tCorreo: ";
    cin.getline(correo, 50);
    if (ExisteContacto(nombre, correo))
    {
        contacto actualizar = BuscarContacto(nombre, correo);
        cout << "\t\t\tRegistro a modificar" << endl;
        MostrarContacto(actualizar);
        ActualizarContacto(nombre, correo);
        cout << "\t\t\t SE ACTUALIZO EL REGISTRO" << endl;
    }
    else
    {
        cout << "\t\t\t NO EXISTE EL CONTACTO " << endl;
    }
}
