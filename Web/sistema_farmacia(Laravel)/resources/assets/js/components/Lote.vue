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
                    <i class="fa fa-align-justify"></i> Lotes
                    <button type="button" @click="abrirModal('lote','registrar')" class="btn btn-secondary" >
                        <i class="icon-plus"></i>&nbsp;Nuevo
                    </button>
                </div>
                <div class="card-body">
                    <div class="form-group row">
                        <div class="col-md-6">
                            <div class="input-group">
                                <select class="form-control col-md-3" v-model="criterio">
                                    <option value="lote">Lote</option>
                                    <option value="nombre">Medicamento</option>
                                </select>
                                <input type="text" v-model="buscar" @keyup.enter="listarLote(1,buscar,criterio)" class="form-control" placeholder="Texto a buscar">
                                <button type="submit" @click="listarLote(1,buscar,criterio)" class="btn btn-primary"><i class="fa fa-search"></i> Buscar</button>
                            </div>
                        </div>
                    </div>
                    <table class="table table-bordered table-striped table-sm">
                        <thead>
                            <tr>
                                <th>Opciones</th>
                                <th>Lote</th>
                                <th>Medicamento</th>
                                <th>Proveedor</th>
                                <th>Fecha de Caducidad</th>
                                <th>Precio de Lote</th>
                                <th>Cantidad</th>
                                <th>Estado</th>
                            </tr>
                        </thead>
                        <tbody>
                            <tr v-for="lote in arrayLote" :key="lote.id">
                                <td>
                                    <button type="button" @click="abrirModal('lote','actualizar',lote)" class="btn btn-warning btn-sm" >
                                        <i class="icon-pencil"></i>
                                    </button> &nbsp;
                                    <template v-if="lote.estado">
                                        <button type="button" class="btn btn-danger btn-sm" @click="desactivarLote(lote.id)">
                                            <i class="icon-trash"></i>
                                        </button>
                                    </template>
                                    <template v-else>
                                        <button type="button" class="btn btn-info btn-sm" @click="activarLote(lote.id)">
                                            <i class="icon-check"></i>
                                        </button>
                                    </template>
                                </td>
                                <td v-text="lote.lote"></td>
                                <td v-text="lote.nombre"></td>
                                <td v-text="lote.proveedor"></td>
                                <td v-text="lote.fechaCaducidad"></td>
                                <td v-text="'$'+lote.PrecioCompra"></td>
                                <td v-text="lote.cantidad"></td>
                                <td>
                                    <div v-if="lote.estado">
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
                                <label class="col-md-3 form-control-label" for="text-input">Lote</label>
                                <div class="col-md-9">
                                    <input type="text" v-model="lote" class="form-control" >
                                </div>
                            </div>
                            <div class="form-group row">
                                <label class="col-md-3 form-control-label" for="text-input">Medicamento</label>
                                <div class="col-md-9">
                                    <select class="form-control" v-model="idMedicamento">
                                        <option value="0" disabled>Seleccione un Medicamento</option>
                                        <option v-for="medicamento in arrayMedicamento" :key="medicamento.id" :value="medicamento.id" v-text="medicamento.nombre"></option>
                                    </select>                                    
                                </div>
                            </div>
                            <div class="form-group row">
                                <label class="col-md-3 form-control-label" for="text-input">Proveedor</label>
                                <div class="col-md-9">
                                    <select class="form-control" v-model="idProveedor">
                                        <option value="0" disabled>Seleccione un proveedor</option>
                                        <option v-for="proveedor in arrayProveedor" :key="proveedor.id" :value="proveedor.idProveedor" v-text="proveedor.nombre"></option>
                                    </select>                                    
                                </div>
                            </div>
                            <div class="form-group row">
                                <label class="col-md-3 form-control-label" for="text-input">Fecha de Caducidad</label>
                                <div class="col-md-9">
                                    <input type="date" v-model="fechaCaducidad" class="form-control" >
                                </div>
                            </div>
                            <div class="form-group row">
                                <label class="col-md-3 form-control-label" for="text-input">Precio de Lote</label>
                                <div class="col-md-9">
                                    <input type="number" v-model="PrecioCompra" class="form-control" >
                                </div>
                            </div>
                            <div class="form-group row">
                                <label class="col-md-3 form-control-label" for="text-input">Cantidad</label>
                                <div class="col-md-9">
                                    <input type="number" v-model="cantidad" class="form-control" >
                                </div>
                            </div>
                            <div v-show="errorLote" class="form-group row div-error">
                                <div class="text-center text-error">
                                    <div v-for="error in errorMostrarMsjLote" :key="error" v-text="error">

                                    </div>
                                </div>
                            </div>
                        </form>
                    </div>
                    <div class="modal-footer">
                        <button type="button" class="btn btn-secondary" @click="cerrarModal()">Cerrar</button>
                        <button type="button" v-if = "tipoAccion==1" class="btn btn-primary" @click="registrarLote()">Guardar</button>
                        <button type="button" v-if = "tipoAccion==2" @click="actualizarLote()" class="btn btn-primary">Actualizar</button>
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
            lote_id:0,
            idMedicamento:0,
            nombre: '',
            proveedor: '',
            idProveedor: 0,
            lote : '',
            fechaCaducidad: '',
            PrecioCompra: 0.0,
            cantidad: 0,
            arrayLote : [],
            arrayMedicamento: [],
            arrayProveedor: [],
            modal : 0,
            tituloModal : '',
            tipoAccion : 0,
            errorLote : 0,
            errorMostrarMsjLote: [],
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
            buscar : '',
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
        listarLote(page,buscar,criterio)
        {
            let me = this;
            var url = '/lote?page=' + page + '&buscar='+ buscar + '&criterio=' + criterio;
            axios.get(url).then(function(response)
            {
               var respuesta = response.data;
               me.arrayLote = respuesta.lotes.data;
               me.pagination = respuesta.pagination;
            }).catch(function(error)
            {
                console.log(error);
            })
        },
        selectMedicamento()
        {
            let me = this;
            var url = '/medicamento/selectMedicamento';
            axios.get(url).then(function(response)
            {
                var respuesta = response.data;
                me.arrayMedicamento = respuesta.medicamentos;
            }).catch(function(error)
            {
                console.log(error);
            })
        },
        selectProveedor()
        {
               let me = this;
            var url = '/proveedor/selectProveedor';
            axios.get(url).then(function(response)
            {
                var respuesta = response.data;
                me.arrayProveedor = respuesta.proveedores;
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
            me.listarLote(page,buscar,criterio);
        },
        registrarLote()
        {
            //si hay un error
            if(this.validarLote())
            {
                return;
            }
            let me = this;
            axios.post('/lote/registrar',
            {
                'lote' : this.lote,
                'idMedicamento' :this.idMedicamento,
                'fechaCaducidad' :this.fechaCaducidad,
                'PrecioCompra' :this.PrecioCompra,
                'idProveedor':this.idProveedor,
                'cantidad' :this.cantidad
            }).then(function(response)
            {
                me.cerrarModal();
                me.listarLote(1,'','nombre');
            }).catch(function(error)
            {
                console.log(error);
            });
        },
        actualizarLote()
        {

            //si hay un error
           if(this.validarLote())
            {
                
                return;
            }
            let me = this;
            axios.put('/lote/actualizar',
            {
                'lote' : this.lote,
                'idMedicamento' :this.idMedicamento,
                'fechaCaducidad' :this.fechaCaducidad,
                'PrecioCompra' :this.PrecioCompra,
                'idProveedor':this.idProveedor,
                'cantidad' :this.cantidad,
                'id':this.lote_id
            }).then(function(response)
            {
                me.cerrarModal();
                me.listarLote(1,'','nombre');
            }).catch(function(error)
            {
                console.log(error);
            });
        },
        desactivarLote(id)
        {
            const swalWithBootstrapButtons = Swal.mixin({
            customClass: {
                confirmButton: 'btn btn-success',
                cancelButton: 'btn btn-danger'
            },
            buttonsStyling: false,
            })

            swalWithBootstrapButtons.fire({
            title: '¿Estás seguro de desactivar este Lote?',
            text: "No se podrá revertir",
            type: 'warning',
            showCancelButton: true,
            confirmButtonText: 'Si Desactivalo!',
            cancelButtonText: 'No, cancelar!',
            reverseButtons: true
            }).then((result) => {
            if (result.value) {
                let me = this;
                axios.put('/lote/desactivar',
                {
                    'id':id
                }).then(function(response)
                {
                    me.listarLote(1,'','nombre');
                    swalWithBootstrapButtons.fire(
                        'Desactivado!',
                        'El Lote ha sido desactivado.',
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
        activarLote(id)
        {
            const swalWithBootstrapButtons = Swal.mixin({
            customClass: {
                confirmButton: 'btn btn-success',
                cancelButton: 'btn btn-danger'
            },
            buttonsStyling: false,
            })

            swalWithBootstrapButtons.fire({
            title: '¿Estás seguro de activar este Lote?',
            text: "No se podrá revertir",
            type: 'warning',
            showCancelButton: true,
            confirmButtonText: 'Si Activar!',
            cancelButtonText: 'No, cancelar!',
            reverseButtons: true
            }).then((result) => {
            if (result.value) {
                let me = this;
                axios.put('/lote/activar',
                {
                    'id':id
                }).then(function(response)
                {
                    me.listarLote(1,'','nombre');
                    swalWithBootstrapButtons.fire(
                        'Activado!',
                        'El medicamento ha sido activado.',
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
        validarLote()
        {
            this.errorLote = 0;
            this.errorMostrarMsjLote = [];
            
            if(this.idMedicamento==0) this.errorMostrarMsjLote.push("El medicamento del lote no puede estar vacio");
            if(!this.lote) this.errorMostrarMsjLote.push("El Lote  no puede estar vacio");
            if(!this.PrecioCompra) this.errorMostrarMsjLote.push("La advertencia del medicamento no puede estar vacio");
            if(!this.cantidad) this.errorMostrarMsjLote.push("La cantidad del lote no puede estar vacio");
            if(!this.idProveedor) this.errorMostrarMsjLote.push("Se debe de seleccionar un proveedor");

            if(!this.fechaCaducidad) this.errorMostrarMsjLote.push("La fecha de caducidad no puede estar vacio");


            if(this.errorMostrarMsjLote.length) this.errorLote = 1;
            return this.errorLote;
        },
        cerrarModal()
        {
            this.modal = 0;
            this.tituloModal = '';
            this.lote= '';
            this.idMedicamento = 0;
            this.idProveedor = 0;
            this.fechaCaducidad = '';
            this.PrecioCompra = 0.0;
            this.cantidad = 0;
            this.errorLote=0;
        },
        abrirModal(modelo,accion, data = [])
        {
            switch(modelo)
            {
                case "lote":
                {
                    switch(accion)
                    {
                        case 'registrar':
                        {
                            this.modal = 1;
                            this.tituloModal = 'Registrar Lote';
                            this.tipoAccion = 1;
                            this.idMedicamento = 0;
                            this.idProveedor = 0;
                            this.lote = '';
                            this.fechaCaducidad = '';
                            this.PrecioCompra = 0.0;
                            this.cantidad = 0;
                            break;
                        }
                        case 'actualizar':
                        {
                            this.modal=1;
                            this.tituloModal="Actualizar Lote";
                            this.tipoAccion=2;
                            this.lote_id= data['id'];
                            this.lote = data['lote'];
                            this.idMedicamento=data['idMedicamento'];
                            this.idProveedor=data['idProveedor'];
                            this.fechaCaducidad = data['fechaCaducidad'];
                            this.PrecioCompra = data['PrecioCompra'];
                            this.cantidad = data['cantidad'];
                            break;
                        }
                    }
                }    
            }
            this.selectMedicamento();
            this.selectProveedor();
        }
    },
    mounted() {
        this.listarLote(1,this.buscar,this.criterio);
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