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
                    <i class="fa fa-align-justify"></i> Medicamentos
                    <button type="button" @click="abrirModal('medicamento','registrar')" class="btn btn-secondary" >
                        <i class="icon-plus"></i>&nbsp;Nuevo
                    </button>
                </div>
                <div class="card-body">
                    <div class="form-group row">
                        <div class="col-md-6">
                            <div class="input-group">
                                <select class="form-control col-md-3" v-model="criterio">
                                    <option value="nombre">Nombre</option>
                                    <option value="nombre_ingrediente">Ingrediente activo</option>
                                </select>
                                <input type="text" v-model="buscar" @keyup.enter="listarMedicamento(1,buscar,criterio)" class="form-control" placeholder="Texto a buscar">
                                <button type="submit" @click="listarMedicamento(1,buscar,criterio)" class="btn btn-primary"><i class="fa fa-search"></i> Buscar</button>
                            </div>
                        </div>
                    </div>
                    <table class="table table-bordered table-striped table-sm">
                        <thead>
                            <tr>
                                <th>Opciones</th>
                                <th>Nombre</th>
                                <th>Advertencia</th>
                                <th>Via de Administración</th>
                                <th>Presentación</th>
                                <th>Ingrediente Activo</th>
                                <th>Estado</th>
                            </tr>
                        </thead>
                        <tbody>
                            <tr v-for="medicamento in arrayMedicamento" :key="medicamento.id">
                                <td>
                                    <button type="button" @click="abrirModal('medicamento','actualizar',medicamento)" class="btn btn-warning btn-sm" >
                                        <i class="icon-pencil"></i>
                                    </button> &nbsp;
                                    <template v-if="medicamento.estado">
                                        <button type="button" class="btn btn-danger btn-sm" @click="desactivarMedicamento(medicamento.id)">
                                            <i class="icon-trash"></i>
                                        </button>
                                    </template>
                                    <template v-else>
                                        <button type="button" class="btn btn-info btn-sm" @click="activarMedicamento(medicamento.id)">
                                            <i class="icon-check"></i>
                                        </button>
                                    </template>
                                </td>
                                <td v-text="medicamento.nombre"></td>
                                <td v-text="medicamento.advertencia"></td>
                                <td v-text="medicamento.viaAdmin"></td>
                                <td v-text="medicamento.presentacion"></td>
                                <td v-text="medicamento.nombre_ingrediente + ' ' + medicamento.cantidad"></td>
                                <td>
                                    <div v-if="medicamento.estado">
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
                                    <input type="text" v-model="nombre" class="form-control" placeholder="Nombre de Medicamento">
                                </div>
                            </div>
                            <div class="form-group row">
                                <label class="col-md-3 form-control-label" for="text-input">Ingrediente Activo</label>
                                <div class="col-md-9">
                                    <select class="form-control" v-model="idIngredienteActivo">
                                        <option value="0" disabled>Seleccione</option>
                                        <option v-for="ingrediente in arrayIngredientes" :key="ingrediente" :value="ingrediente.id" v-text="ingrediente.nombre + ' ' + ingrediente.cantidad"></option>
                                    </select>                                    
                                </div>
                            </div>
                            <div class="form-group row">
                                <label class="col-md-3 form-control-label" for="text-input">Advertencia</label>
                                <div class="col-md-9">
                                    <input type="email" v-model="advertencia" class="form-control" >
                                </div>
                            </div>
                            <div class="form-group row">
                                <label class="col-md-3 form-control-label" for="text-input">Via de Administración</label>
                                <div class="col-md-9">
                                    <select class="form-control" v-model="viaAdmin">
                                        <option value="Oral">Oral</option>
                                        <option value="Rectal">Rectal</option>
                                        <option value="Intramuscular">Intramuscular</option>
                                        <option value="Intravenosa">Intravenosa</option>
                                        <option value="Subcutánea">Subcutánea</option>
                                        <option value="Inhalatoria">Inhalatoria</option>
                                        <option value="Transdérmica">Transdérmica</option>
                                        <option value="Nasal">Nasal</option>
                                        <option value="Oftálmica">Oftálmica</option>
                                        <option value="Ótica">Ótica</option>
                                        <option value="Tópica">Tópica</option>
                                        <option value="Vaginal">Vaginal</option>
                                    </select>
                                </div>
                            </div>
                            <div class="form-group row">
                                <label class="col-md-3 form-control-label" for="text-input">Presentacion</label>
                                <div class="col-md-9">
                                    <select class="form-control" v-model="presentacion">
                                        <option value="Tabletas">Tabletas</option>
                                        <option value="Polvo">Polvo</option>
                                        <option value="Cápsulas">Cápsulas</option>
                                        <option value="Píldoras">Píldoras</option>
                                        <option value="Grageas">Grageas</option>
                                        <option value="Supositorios">Supositorios</option>
                                        <option value="Óvulos">Óvulos</option>
                                        <option value="Pomada">Pomada</option>
                                        <option value="Cremas">Cremas</option>
                                        <option value="Solucion">Solucion</option>
                                        <option value="Jarabe">Jarabe</option>
                                        <option value="Colirio">Colirio</option>
                                        <option value="Locion">Locion</option>
                                        <option value="Linimento">Linimento</option>
                                        <option value="Elixir">Elixir</option>
                                        <option value="Enema">Enema</option>
                                        <option value="Inhalacion">Inhalacion</option>
                                        <option value="Aerosol">Aerosol</option>
                                    </select>
                                </div>
                            </div>
                            <div v-show="errorMedicamento" class="form-group row div-error">
                                <div class="text-center text-error">
                                    <div v-for="error in errorMostrarMsjMedicamento" :key="error" v-text="error">

                                    </div>
                                </div>
                            </div>
                        </form>
                    </div>
                    <div class="modal-footer">
                        <button type="button" class="btn btn-secondary" @click="cerrarModal()">Cerrar</button>
                        <button type="button" v-if = "tipoAccion==1" class="btn btn-primary" @click="registrarMedicamento()">Guardar</button>
                        <button type="button" v-if = "tipoAccion==2" @click="actualizarMedicamento()" class="btn btn-primary">Actualizar</button>
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
            medicamento_id:0,
            idIngredienteActivo:0,
            nombre_ingrediente: '',
            nombre : '',
            advertencia: '',
            viaAdmin: '',
            presentacion: '',
            arrayMedicamento : [],
            modal : 0,
            tituloModal : '',
            tipoAccion : 0,
            errorMedicamento : 0,
            errorMostrarMsjMedicamento: [],
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
            arrayIngredientes: []
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
        listarMedicamento(page,buscar,criterio)
        {
            let me = this;
            var url = '/medicamento?page=' + page + '&buscar='+ buscar + '&criterio=' + criterio;
            axios.get(url).then(function(response)
            {
               var respuesta = response.data;
               me.arrayMedicamento = respuesta.medicamentos.data;
               me.pagination = respuesta.pagination;
            }).catch(function(error)
            {
                console.log(error);
            })
        },
        selectIngrediente()
        {
            let me = this;
            var url = '/IngredienteActivo/selectIngrediente';
            axios.get(url).then(function(response)
            {
                var respuesta = response.data;
                me.arrayIngredientes = respuesta.ingredientes_activos;
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
            me.listarMedicamento(page,buscar,criterio);
        },
        registrarMedicamento()
        {
            //si hay un error
            if(this.validarMedicamento())
            {
                return;
            }
            let me = this;
            axios.post('/medicamento/registrar',
            {
                'nombre' : this.nombre,
                'idIngredienteActivo' :this.idIngredienteActivo,
                'advertencia' :this.advertencia,
                'viaAdmin' :this.viaAdmin,
                'presentacion' :this.presentacion
            }).then(function(response)
            {
                me.cerrarModal();
                me.listarMedicamento(1,'','nombre');
            }).catch(function(error)
            {
                console.log(error);
            });
        },
        actualizarMedicamento()
        {
            //si hay un error
            if(this.validarMedicamento())
            {
                return;
            }
            let me = this;
            axios.put('/medicamento/actualizar',
            {
                'nombre' : this.nombre,
                'idIngredienteActivo' :this.idIngredienteActivo,
                'advertencia' :this.advertencia,
                'viaAdmin' :this.viaAdmin,
                'presentacion' :this.presentacion,
                'id':this.medicamento_id
            }).then(function(response)
            {
                me.cerrarModal();
                me.listarMedicamento(1,'','nombre');
            }).catch(function(error)
            {
                console.log(error);
            });
        },
        desactivarMedicamento(id)
        {
            const swalWithBootstrapButtons = Swal.mixin({
            customClass: {
                confirmButton: 'btn btn-success',
                cancelButton: 'btn btn-danger'
            },
            buttonsStyling: false,
            })

            swalWithBootstrapButtons.fire({
            title: '¿Estás seguro de desactivar este Medicamento?',
            text: "No se podrá revertir",
            type: 'warning',
            showCancelButton: true,
            confirmButtonText: 'Si Desactivalo!',
            cancelButtonText: 'No, cancelar!',
            reverseButtons: true
            }).then((result) => {
            if (result.value) {
                let me = this;
                axios.put('/medicamento/desactivar',
                {
                    'id':id
                }).then(function(response)
                {
                    me.listarMedicamento(1,'','nombre');
                    swalWithBootstrapButtons.fire(
                        'Desactivado!',
                        'El medicamento ha sido desactivado.',
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
        activarMedicamento(id)
        {
            const swalWithBootstrapButtons = Swal.mixin({
            customClass: {
                confirmButton: 'btn btn-success',
                cancelButton: 'btn btn-danger'
            },
            buttonsStyling: false,
            })

            swalWithBootstrapButtons.fire({
            title: '¿Estás seguro de activar este medicamento?',
            text: "No se podrá revertir",
            type: 'warning',
            showCancelButton: true,
            confirmButtonText: 'Si Activar!',
            cancelButtonText: 'No, cancelar!',
            reverseButtons: true
            }).then((result) => {
            if (result.value) {
                let me = this;
                axios.put('/medicamento/activar',
                {
                    'id':id
                }).then(function(response)
                {
                    me.listarMedicamento(1,'','nombre');
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
        validarMedicamento()
        {
            this.errorMedicamento = 0;
            this.errorMostrarMsjMedicamento = [];
            
            if(this.idIngredienteActivo==0) this.errorMostrarMsjMedicamento.push("El ingrediente activo del medicamento no puede estar vacio");
            if(!this.nombre) this.errorMostrarMsjMedicamento.push("El nombre del medicamento no puede estar vacio");
            if(!this.advertencia) this.errorMostrarMsjMedicamento.push("La advertencia del medicamento no puede estar vacio");
            if(!this.presentacion) this.errorMostrarMsjMedicamento.push("La presentacion del medicamento no puede estar vacio");

            if(!this.viaAdmin) this.errorMostrarMsjMedicamento.push("La Via de administración del medicamento no puede estar vacio");


            if(this.errorMostrarMsjMedicamento.length) this.errorMedicamento = 1;
            return this.errorMedicamento;
        },
        cerrarModal()
        {
            this.modal = 0;
            this.tituloModal = '';
            this.nombre = '';
            this.idIngredienteActivo = 0;
            this.advertencia = '';
            this.viaAdmin = '';
            this.presentacion = '';
            this.errorMedicamento=0;
        },
        abrirModal(modelo,accion, data = [])
        {
            switch(modelo)
            {
                case "medicamento":
                {
                    switch(accion)
                    {
                        case 'registrar':
                        {
                            this.modal = 1;
                            this.tituloModal = 'Registrar Medicamento';
                            this.tipoAccion = 1;
                            this.nombre = '';
                            this.idIngredienteActivo = 0;
                            this.advertencia = '';
                            this.viaAdmin = '';
                            this.presentacion = '';
                            break;
                        }
                        case 'actualizar':
                        {
                            this.modal=1;
                            this.tituloModal="Actualizar Medicamento";
                            this.tipoAccion=2;
                            this.medicamento_id = data['id'];
                            this.idIngredienteActivo=data['idIngredienteActivo'];
                            this.nombre = data['nombre'];
                            this.advertencia = data['advertencia'];
                            this.viaAdmin = data['viaAdmin'];
                            this.presentacion = data['presentacion'];
                            break;
                        }
                    }
                }    

            }
            this.selectIngrediente();
        }
    },
    mounted() {
        this.listarMedicamento(1,this.buscar,this.criterio);
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