<template>
<main class="main">
        <!-- Breadcrumb -->
        <ol class="breadcrumb">
            <li class="breadcrumb-item"><a href="/">Escritorio</a></li>
        </ol>
        <div class="container-fluid">
            <!-- Ejemplo de tabla Listado -->
            <div class="card">
                <div class="card-header">
                    <i class="fa fa-align-justify"></i> Usuarios 
                    <button type="button" @click="abrirModal('persona','registrar')" class="btn btn-secondary" >
                        <i class="icon-plus"></i>&nbsp;Nuevo
                    </button>
                </div>
                <div class="card-body">
                    <div class="form-group row">
                        <div class="col-md-6">
                            <div class="input-group">
                                <select class="form-control col-md-3" v-model="criterio">
                                    <option value="nombre">Nombre</option>
                                    <option value="email">Email</option>
                                </select>
                                <input type="text" v-model="buscar" @keyup.enter="listarPersona(1,buscar,criterio)" class="form-control" placeholder="Texto a buscar">
                                <button type="submit" @click="listarPersona(1,buscar,criterio)" class="btn btn-primary"><i class="fa fa-search"></i> Buscar</button>
                            </div>
                        </div>
                    </div>
                    <table class="table table-bordered table-striped table-sm">
                        <thead>
                            <tr>
                                <th>Opciones</th>
                                <th>Nombre</th>
                                <th>Email</th>
                                <th>Telefono </th>
                                <th>Usuario</th>
                                <th>Rol</th>
                                <th>Salario</th>
                                <th>Estado</th>
                            </tr>
                        </thead>
                        <tbody>
                            <tr v-for="persona in arrayPersona" :key="persona.id">
                                <td>
                                    <button type="button" @click="abrirModal('persona','actualizar',persona)" class="btn btn-warning btn-sm" >
                                        <i class="icon-pencil"></i>
                                    </button> &nbsp;
                                    <template v-if="persona.estado">
                                        <button type="button" class="btn btn-danger btn-sm" @click="desactivarPersona(persona.id)">
                                            <i class="icon-trash"></i>
                                        </button>
                                    </template>
                                    <template v-else>
                                        <button type="button" class="btn btn-info btn-sm" @click="activarPersona(persona.id)">
                                            <i class="icon-check"></i>
                                        </button>
                                    </template>
                                </td>
                                <td v-text="persona.nombre"></td>
                                <td v-text="persona.email"></td>
                                <td v-text="persona.tel"></td>
                                <td v-text="persona.usuario"></td>
                                <td v-text="persona.rol"></td>
                                <td v-text="persona.salario"></td>
                                <td>
                                    <div v-if="persona.estado">
                                    <span class="badge badge-success">Activo</span>
                                    </div>
                                    <div v-else>
                                    <span class="badge badge-danger">Desactivado</span>
                                    </div>
                                </td>
                            </tr>
                            
                        </tbody>
                    </table>
                    <nav>
                        <ul class="pagination">
                            <li class="page-item" v-if="pagination.current_page > 1">
                                <a class="page-link" href="#" @click="cambiarPagina(pagination.current_page - 1,buscar,criterio)">Ant</a>
                            </li>
                            <li class="page-item" v-for="page in pagesNumber" :key="page" :class="[page == isActived ? 'active' : '']">
                                <a class="page-link" href="#" @click.prevent="cambiarPagina(page,buscar,criterio)" v-text="page"></a>
                            </li>
                            <li class="page-item" v-if="pagination.current_page < pagination.last_page">
                                <a class="page-link" href="#" @click="cambiarPagina(pagination.current_page + 1,buscar,criterio)">Sig</a>
                            </li>
                        </ul>
                    </nav>
                </div>
            </div>
            <!-- Fin ejemplo de tabla Listado -->
        </div>
        <!--Inicio del modal agregar/actualizar-->
        <div class="modal fade" tabindex="-1" :class="{'mostrar':modal}"  role="dialog" aria-labelledby="myModalLabel" style="display: none;" aria-hidden="true">
            <div class="modal-dialog modal-primary modal-lg" role="document">
                <div class="modal-content">
                    <div class="modal-header">
                        <h4 class="modal-title" v-text="tituloModal"></h4>
                        <button type="button" class="close" @click="cerrarModal()" aria-label="Close">
                            <span aria-hidden="true">×</span>
                        </button>
                    </div>
                    <div class="modal-body">
                        <form action="" method="post" enctype="multipart/form-data" class="form-horizontal" scrolling="yes">
                            <div class="form-group row">
                                <label class="col-md-3 form-control-label" for="text-input">Nombre</label>
                                <div class="col-md-9">
                                    <input type="text" v-model="nombre" class="form-control" placeholder="Nombre completo">
                                </div>
                            </div>
                            <div class="form-group row">
                                <label class="col-md-3 form-control-label" for="email-input">Email</label>
                                <div class="col-md-9">
                                    <input type="email" v-model="email" class="form-control" >
                                </div>
                            </div>
                            <div class="form-group row">
                                <label class="col-md-3 form-control-label" for="text-input">Télefono</label>
                                <div class="col-md-9">
                                    <input  v-model="tel" class="form-control" >
                                </div>
                            </div>
                            <div class="form-group row">
                                <label class="col-md-3 form-control-label" for="text-input">Usuario</label>
                                <div class="col-md-9">
                                    <input type="email" v-model="usuario" class="form-control" placeholder="Nombre de usuario">
                                </div>
                            </div>
                            <div class="form-group row">
                                <label class="col-md-3 form-control-label" for="text-input">Password</label>
                                <div class="col-md-9">
                                    <input type="email" v-model="password" class="form-control" placeholder="password de acceso">
                                </div>
                            </div>
                            <div class="form-group row">
                                <label class="col-md-3 form-control-label" for="number-input">Salario</label>
                                <div class="col-md-9">
                                    <input type="number" v-model="salario" class="form-control">
                                </div>
                            </div>
                            <div class="form-group row">
                                <label class="col-md-3 form-control-label" for="text-input">Rol</label>
                                <div class="col-md-9">
                                    <select class="form-control" v-model="idrol">
                                        <option value="0">Seleccione un Rol</option>
                                        <option v-for="rol in arrayRol" :key="rol.id" :value="rol.id" v-text="rol.nombre"> 

                                        </option>
                                    </select>
                                </div>
                            </div>
                            <div v-show="errorPersona" class="form-group row div-error">
                                <div class="text-center text-error">
                                    <div v-for="error in errorMostrarMsjPersona" :key="error" v-text="error">

                                    </div>
                                </div>
                            </div>
                        </form>
                    </div>
                    <div class="modal-footer">
                        <button type="button" class="btn btn-secondary" @click="cerrarModal()">Cerrar</button>
                        <button type="button" v-if = "tipoAccion==1" class="btn btn-primary" @click="registrarPersona()">Guardar</button>
                        <button type="button" v-if = "tipoAccion==2" @click="actualizarPersona()" class="btn btn-primary">Actualizar</button>
                    </div>
                </div>
                <!-- /.modal-content -->
            </div>
            <!-- /.modal-dialog -->
        </div>
    </main>
</template>

<script>
export default {
    data()
    {
        return{
            persona_id:0,
            nombre : '',
            email : '',
            tel : '',
            usuario: '',
            salario: 0.0,
            password: '',
            idrol: 0,
            arrayPersona : [],
            arrayRol : [],
            modal : 0,
            tituloModal : '',
            tipoAccion : 0,
            errorPersona : 0,
            errorMostrarMsjPersona: [],
            pagination: {
                'total': 0,
                'current_page':0,
                'per_page':0,
                'last_page':0,
                'from':0,
                'to':0
            },
            offset: 3,
            criterio: 'nombre',
            buscar : ''
        }
    },
    computed:
    {
        isActived: function()
        {
            return this.pagination.current_page;
        },
        pagesNumber: function()
        {
            if(!this.pagination.to)
            {
                return[];
            }
            
            var from = this.pagination.current_page - this.offset;
            if(from < 1)
            {
                from = 1;
            }

            var to = from + (this.offset*2);
            if(to >= this.pagination.last_page)
            {
                to = this.pagination.last_page;
            }

            var pagesArray = [];
            while(from <= to)
            {
                pagesArray.push(from);
                from++;
            }
            return pagesArray;
        }
    },
    methods:
    {
        listarPersona(page,buscar,criterio)
        {
            let me = this;
            var url = '/user?page=' + page + '&buscar='+ buscar + '&criterio=' + criterio;
            axios.get(url).then(function(response)
            {
                var respuesta = response.data;
                me.arrayPersona = respuesta.personas.data;
                me.pagination = respuesta.pagination;
            }).catch(function(error)
            {
                console.log(error);
            })
        },
        selectRol()
        {
             let me = this;
            var url = '/rol/selectRol';
            axios.get(url).then(function(response)
            {
                var respuesta = response.data;
                me.arrayRol = respuesta.roles;
            }).catch(function(error)
            {
                console.log(error);
            })
        },
        cambiarPagina(page,buscar,criterio)
        {
            let me = this;
            //actualiza la página actual
            me.pagination.current_page = page;
            me.listarPersona(page,buscar,criterio);
        },
        registrarPersona()
        {
            //si hay un error
            if(this.validarPersona())
            {
                return;
            }
            let me = this;
            axios.post('/user/registrar',
            {
                'nombre':this.nombre,
                'email':this.email,
                'tel':this.tel,
                'usuario':this.usuario,
                'password':this.password,
                'salario':this.salario,
                'idrol':this.idrol
            }).then(function(response)
            {
                me.cerrarModal();
                me.listarPersona(1,'','nombre');
            }).catch(function(error)
            {
                console.log(error);
            });
        },
        actualizarPersona()
        {
            //si hay un error
            if(this.validarPersona())
            {
                return;
            }
            let me = this;
            axios.put('/user/actualizar',
            {
                'nombre':this.nombre,
                'email':this.email,
                'tel':this.tel,
                'usuario':this.usuario,
                'password':this.password,
                'salario':this.salario,
                'idrol':this.idrol,
                'id':this.persona_id
            }).then(function(response)
            {
                me.cerrarModal();
                me.listarPersona(1,'','nombre');
            }).catch(function(error)
            {
                console.log(error);
            });
        },
        desactivarPersona(id)
        {
            const swalWithBootstrapButtons = Swal.mixin({
            customClass: {
                confirmButton: 'btn btn-success',
                cancelButton: 'btn btn-danger'
            },
            buttonsStyling: false,
            })

            swalWithBootstrapButtons.fire({
            title: '¿Estás seguro?',
            text: " se podrá revertir",
            type: 'warning',
            showCancelButton: true,
            confirmButtonText: 'Si Desactivalo!',
            cancelButtonText: 'No, cancelar!',
            reverseButtons: true
            }).then((result) => {
            if (result.value) {
                let me = this;
                axios.put('/proveedor/desactivar',
                {
                    'id':id
                }).then(function(response)
                {
                    me.listarPersona(1,'','nombre');
                    swalWithBootstrapButtons.fire(
                        'Desactivado!',
                        'Tu proveedor ha sido desactivado.',
                        'succes'
                        )
                }).catch(function(error)
                {
                    console.log(error);
                });
             
            } else if (
                // Read more about handling dismissals
                result.dismiss === Swal.DismissReason.cancel
            ) {
            }
        })
        },
        activarPersona(id)
        {
            const swalWithBootstrapButtons = Swal.mixin({
            customClass: {
                confirmButton: 'btn btn-success',
                cancelButton: 'btn btn-danger'
            },
            buttonsStyling: false,
            })

            swalWithBootstrapButtons.fire({
            title: '¿Estás seguro?',
            text: "No se podrá revertir",
            type: 'warning',
            showCancelButton: true,
            confirmButtonText: 'Si Activar!',
            cancelButtonText: 'No, cancelar!',
            reverseButtons: true
            }).then((result) => {
            if (result.value) {
                let me = this;
                axios.put('/proveedor/activar',
                {
                    'id':id
                }).then(function(response)
                {
                    me.listarPersona(1,'','nombre');
                    swalWithBootstrapButtons.fire(
                        'Activado!',
                        'Tu proveedor ha sido activado.',
                        'succes'
                        )
                }).catch(function(error)
                {
                    console.log(error);
                });
             
            } else if (
                // Read more about handling dismissals
                result.dismiss === Swal.DismissReason.cancel
            ) {
            }
        })
        },
        validarPersona()
        {
            this.errorPersona = 0;
            this.errorMostrarMsjPersona = [];
            
            if(!this.nombre) this.errorMostrarMsjPersona.push("El nombre del Usuario no puede ser vacio");
            if(!this.email) this.errorMostrarMsjPersona.push("El email del Usuario no puede se vacio");
            if(!this.tel) this.errorMostrarMsjPersona.push("El télefono del Usuario no puede se vacio");
            if(!this.usuario) this.errorMostrarMsjPersona.push("El Usuario del Usuario no puede se vacio");
            if(!this.password) this.errorMostrarMsjPersona.push("El Password del Usuario no puede se vacio");
            if(!this.salario) this.errorMostrarMsjPersona.push("El Salario del Usuario no puede se vacio");
            //if(typeof(salario) != Number) this.errorMostrarMsjPersona.push("El salario debe de ser un número");
            if(this.idrol == 0) this.errorMostrarMsjPersona.push("Se debe de seleccionar un rol para el usuario");
            if(this.errorMostrarMsjPersona.length) this.errorPersona = 1;
            return this.errorPersona;
        },
        cerrarModal()
        {
            this.modal = 0;
            this.tituloModal = '';
            this.nombre = '';
            this.email = '';
            this.tel = '';
            this.salario = 0.0;
            this.usuario = '';
            this.password = '';
            this.errorPersona=0;
            this.idrol = 0;
        },
        abrirModal(modelo,accion, data = [])
        {
            this.selectRol();
            switch(modelo)
            {
                case "persona":
                {
                    switch(accion)
                    {
                        case 'registrar':
                        {
                            this.modal = 1;
                            this.tituloModal = 'Registrar Usuario';
                            this.tipoAccion = 1;
                            this.nombre = '';
                            this.email = '';
                            this.tel = '';
                            this.usuario = '';
                            this.password = '';
                            this.salario = 0.0;
                            this.idrol = 0;

                            break;
                        }
                        case 'actualizar':
                        {
                            this.modal=1;
                            this.tituloModal="Actualizar Usuario";
                            this.tipoAccion=2;
                            this.persona_id = data['id'];
                            this.nombre = data['nombre'];
                            this.email = data['email'];
                            this.tel = data['tel'];
                            this.salario = data['salario'];
                            this.password = data['password'];
                            this.usuario = data['usuario'];
                            this.idrol = data['idrol'];
                            break;
                        }
                    }
                }    
            }
        }
    },
    mounted() {
        this.listarPersona(1,this.buscar,this.criterio);
    }
}
</script>
<style>
.modal-content
{
    width: 100% !important;
    position: absolute !important;
}
.mostrar
{
    display: list-item !important;
    opacity: 1 !important;
    position: absolute !important;
    background-color: #3c29297a !important;
}
.div-error
{
    display: flex;
    justify-content: center;
}
.text-error
{
    color: red !important;
    font-weight: bold;
}
</style>