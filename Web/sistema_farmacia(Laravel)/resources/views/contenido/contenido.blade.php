@extends('principal')
@section('contenido')

@if(Auth::check())
            @if(Auth::user()->idrol == 2)
                <template v-if="menu==0">
                    <escritorio></escritorio>
                </template>
                <template v-if="menu==1">
                    <medicamento></medicamento>
                </template>
                <template v-if="menu==3">
                    <lote></lote>
                </template>
                <template v-if="menu==5">
                    <cliente></cliente>
                </template>

            @elseif(Auth::user()->idrol == 1)
                <template v-if="menu==0">
                    <escritorio></escritorio>
                </template>
                <template v-if="menu==1">
                        <medicamento></medicamento>
                </template>
                <template v-if="menu==6">
                    <user></user>
                </template>

            @elseif(Auth::user()->idrol == 4)
                <template v-if="menu==0">
                    <escritorio></escritorio>
                </template>

                <template v-if="menu==1">
                    <medicamento></medicamento>
                </template>

                <template v-if="menu==3">
                    <lote></lote>
                </template>

                <template v-if="menu==4">
                    <proveedor></proveedor>
                </template>

                <template v-if="menu==5">
                    <cliente></cliente>
                </template>

                <template v-if="menu==6">
                    <user></user>
                </template>

            @else 


            @endif

@endif
@endsection