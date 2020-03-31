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
                    <i class="fa fa-align-justify"></i> Clientes
                    <button type="button" @click="abrirModal('cliente','registrar')" class="btn btn-secondary" >
                        <i class="icon-plus"></i>&nbsp;Nuevo
                    </button>
                </div>
                <div class="card-body">
                    <div class="form-group row">
                        <div class="col-md-6">
                            <div class="input-group">
                                <select class="form-control col-md-3" v-model="criterio">
                                    <option value="nombre">Nombre</option>
                                    <option value="ApellidoPaterno">Apellido Paterno</option>
                                    <option value="ApellidoMaterno">Apellido Materno</option>
                                </select>
                                <input type="text" v-model="buscar" @keyup.enter="listarCliente(1,buscar,criterio)" class="form-control" placeholder="Texto a buscar">
                                <button type="submit" @click="listarCliente(1,buscar,criterio)" class="btn btn-primary"><i class="fa fa-search"></i> Buscar</button>
                            </div>
                        </div>
                    </div>
                    <table class="table table-bordered table-striped table-sm">
                        <thead>
                            <tr>
                                <th>Opciones</th>
                                <th>Nombre</th>
                                <th>Apellido Paterno</th>
                                <th>Apellido Materno</th>
                                <th>Email</th>
                                <th>Telefono </th>
                                <th>Estado</th>
                            </tr>
                        </thead>
                        <tbody>
                            <tr v-for="cliente in arrayCliente" :key="cliente.id">
                                <td>
                                    <button type="button" @click="abrirModal('cliente','actualizar',cliente)" class="btn btn-warning btn-sm" >
                                        <i class="icon-pencil"></i>
                                    </button> &nbsp;
                                    <template v-if="cliente.estado">
                                        <button type="button" class="btn btn-danger btn-sm" @click="desactivarCliente(cliente.id)">
                                            <i class="icon-trash"></i>
                                        </button>
                                    </template>
                                    <template v-else>
                                        <button type="button" class="btn btn-info btn-sm" @click="activarCliente(cliente.id)">
                                            <i class="icon-check"></i>
                                        </button>
                                    </template>
                                </td>
                                <td v-text="cliente.nombre"></td>
                                <td v-text="cliente.ApellidoPaterno"></td>
                                <td v-text="cliente.ApellidoMaterno"></td>
                                <td v-text="cliente.Email"></td>
                                <td v-text="cliente.tel"></td>
                                <td>
                                    <div v-if="cliente.estado">
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
                        <form action="" method="post" enctype="multipart/form-data" class="form-horizontal">
                            <div class="form-group row">
                                <label class="col-md-3 form-control-label" for="text-input">Nombre</label>
                                <div class="col-md-9">
                                    <input type="text" v-model="nombre" class="form-control" placeholder="Nombre de cliente">
                                </div>
                            </div>
                            <div class="form-group row">
                                <label class="col-md-3 form-control-label" for="email-input">Apellido Paterno</label>
                                <div class="col-md-9">
                                    <input type="email" v-model="ApellidoPaterno" class="form-control" >
                                </div>
                            </div>
                            <div class="form-group row">
                                <label class="col-md-3 form-control-label" for="email-input">Apellido Materno</label>
                                <div class="col-md-9">
                                    <input type="email" v-model="ApellidoMaterno" class="form-control" >
                                </div>
                            </div>
                            <div class="form-group row">
                                <label class="col-md-3 form-control-label" for="email-input">Email</label>
                                <div class="col-md-9">
                                    <input type="email" v-model="Email" class="form-control" >
                                </div>
                            </div>
                            <div class="form-group row">
                                <label class="col-md-3 form-control-label" for="email-input">Télefono</label>
                                <div class="col-md-9">
                                    <input type="email" v-model="tel" class="form-control" >
                                </div>
                            </div>
                            <div v-show="errorCliente" class="form-group row div-error">
                                <div class="text-center text-error">
                                    <div v-for="error in errorMostrarMsjCliente" :key="error" v-text="error">

                                    </div>
                                </div>
                            </div>
                        </form>
                    </div>
                    <div class="modal-footer">
                        <button type="button" class="btn btn-secondary" @click="cerrarModal()">Cerrar</button>
                        <button type="button" v-if = "tipoAccion==1" class="btn btn-primary" @click="registrarCliente()">Guardar</button>
                        <button type="button" v-if = "tipoAccion==2" @click="actualizarCliente()" class="btn btn-primary">Actualizar</button>
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
            cliente_id:0,
            nombre : '',
            ApellidoPaterno : '',
            ApellidoMaterno : '',
            Email : '',
            tel : '',
            arrayCliente : [],
            modal : 0,
            tituloModal : '',
            tipoAccion : 0,
            errorCliente : 0,
            errorMostrarMsjCliente: [],
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
        listarCliente(page,buscar,criterio)
        {
            let me = this;
            var url = '/cliente?page=' + page + '&buscar='+ buscar + '&criterio=' + criterio;
            axios.get(url).then(function(response)
            {
                var respuesta = response.data;
                me.arrayCliente = respuesta.clientes.data;
                me.pagination = respuesta.pagination;
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
            me.listarCliente(page,buscar,criterio);
        },
        registrarCliente()
        {
            //si hay un error
            if(this.validarCliente())
            {
                return;
            }
            let me = this;
            axios.post('/cliente/registrar',
            {
                'nombre':this.nombre,
                'ApellidoPaterno':this.ApellidoPaterno,
                'ApellidoMaterno':this.ApellidoMaterno,
                'Email':this.Email,
                'tel':this.tel
            }).then(function(response)
            {
                me.cerrarModal();
                me.listarCliente(1,'','nombre');
            }).catch(function(error)
            {
                console.log(error);
            });
        },
        actualizarCliente()
        {
            //si hay un error
            if(this.validarCliente())
            {
                return;
            }
            let me = this;
            axios.put('/cliente/actualizar',
            {
                'nombre':this.nombre,
                'ApellidoPaterno':this.ApellidoPaterno,
                'ApellidoMaterno':this.ApellidoMaterno,
                'Email':this.Email,
                'tel':this.tel,
                'id':this.cliente_id
            }).then(function(response)
            {
                me.cerrarModal();
                me.listarCliente(1,'','nombre');
            }).catch(function(error)
            {
                console.log(error);
            });
        },
        desactivarCliente(id)
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
            confirmButtonText: 'Si borralo!',
            cancelButtonText: 'No, cancelar!',
            reverseButtons: true
            }).then((result) => {
            if (result.value) {
                let me = this;
                axios.put('/cliente/desactivar',
                {
                    'id':id
                }).then(function(response)
                {
                    me.listarCliente(1,'','nombre');
                    swalWithBootstrapButtons.fire(
                        'Desactivado!',
                        'Tu cliente ha sido desactivado.',
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
        activarCliente(id)
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
                axios.put('/cliente/activar',
                {
                    'id':id
                }).then(function(response)
                {
                    me.listarCliente(1,'','nombre');
                    swalWithBootstrapButtons.fire(
                        'Activado!',
                        'Tu cliente ha sido activado.',
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
        validarCliente()
        {
            this.errorCliente = 0;
            this.errorMostrarMsjCliente = [];
            
            if(!this.nombre) this.errorMostrarMsjCliente.push("El nombre de cliente no puede ser vacio");
            if(!this.ApellidoPaterno) this.errorMostrarMsjCliente.push("El Apellido Paterno del cliente no puede se vacio");
            if(!this.ApellidoMaterno) this.errorMostrarMsjCliente.push("El Apellido Materno del cliente no puede se vacio");

            if(this.errorMostrarMsjCliente.length) this.errorCliente = 1;
            return this.errorCliente;
        },
        cerrarModal()
        {
            this.modal = 0;
            this.tituloModal = '';
            this.nombre = '';
            this.ApellidoPaterno = '';
            this.ApellidoMaterno = '';
            this.Email = '';
            this.tel = '';
        },
        abrirModal(modelo,accion, data = [])
        {
            switch(modelo)
            {
                case "cliente":
                {
                    switch(accion)
                    {
                        case 'registrar':
                        {
                            this.modal = 1;
                            this.tituloModal = 'Registrar Cliente';
                            this.tipoAccion = 1;
                            this.nombre = '';
                            this.ApellidoPaterno = '';
                            this.ApellidoMaterno = '';
                            this.Email = '';
                            this.tel = '';
                            break;
                        }
                        case 'actualizar':
                        {
                            this.modal=1;
                            this.tituloModal="Actualizar cliente";
                            this.tipoAccion=2;
                            this.cliente_id = data['id'];
                            this.nombre = data['nombre'];
                            this.ApellidoPaterno = data['ApellidoPaterno'];
                            this.ApellidoMaterno = data['ApellidoMaterno'];
                            this.Email = data['Email'];
                            this.tel = data['tel'];
                            break;
                        }
                    }
                }    
            }
        }
    },
    mounted() {
        this.listarCliente(1,this.buscar,this.criterio);
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