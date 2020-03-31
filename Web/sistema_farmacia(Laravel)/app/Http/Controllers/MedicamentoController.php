<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Medicamento;

class MedicamentoController extends Controller
{
    public function index(Request $request) 
    {
        //if(!$request->ajax())  return redirect('/');
        $buscar = $request->buscar;
        $criterio = $request->criterio;

        if($buscar == '')
        {
            $medicamentos = Medicamento::join('_ingrediente_activo','medicamentos.idIngredienteActivo','=','_ingrediente_activo.id')->select('medicamentos.id','medicamentos.idIngredienteActivo','medicamentos.advertencia','medicamentos.viaAdmin','medicamentos.presentacion','medicamentos.nombre','_ingrediente_activo.nombre as nombre_ingrediente','_ingrediente_activo.cantidad','medicamentos.estado')->
            orderBy('medicamentos.id','desc')->paginate(3);
        }
        else
        {
            if($criterio == "nombre_ingrediente")
            {
                $medicamentos = Medicamento::join('_ingrediente_activo','medicamentos.idIngredienteActivo','=','_ingrediente_activo.id')->select('medicamentos.id','medicamentos.idIngredienteActivo','medicamentos.advertencia','medicamentos.viaAdmin','medicamentos.presentacion','medicamentos.nombre','_ingrediente_activo.nombre as nombre_ingrediente', '_ingrediente_activo.cantidad','medicamentos.estado')->where('_ingrediente_activo.nombre', 'like', '%'. $buscar.'%')
                ->orderBy('medicamentos.id','desc')->paginate(3);
            }
            else
            {
                $medicamentos = Medicamento::join('_ingrediente_activo','medicamentos.idIngredienteActivo','=','_ingrediente_activo.id')->select('medicamentos.id','medicamentos.idIngredienteActivo','medicamentos.advertencia','medicamentos.viaAdmin','medicamentos.presentacion','medicamentos.nombre','_ingrediente_activo.nombre as nombre_ingrediente', '_ingrediente_activo.cantidad','medicamentos.estado')->where('medicamentos.' .$criterio, 'like', '%'. $buscar.'%')
                ->orderBy('medicamentos.id','desc')->paginate(3);
            }
        }

        return
        [
            'pagination'=>[
                'total' => $medicamentos->total(),
                'current_page' =>$medicamentos->currentPage(),
                'per_page'=> $medicamentos->perPage(),
                'last_page' => $medicamentos->lastPage(),
                'from' => $medicamentos->firstItem(),
                'to'=> $medicamentos->lastItem(),
            ],
            'medicamentos' => $medicamentos
        ];
    }
    
    public function store(Request $request)
    {
        if(!$request->ajax())  return redirect('/');
        $medicamento = new Medicamento();
        $medicamento->idIngredienteActivo = $request->idIngredienteActivo;
        $medicamento->nombre = $request->nombre;
        $medicamento->advertencia = $request->advertencia;
        $medicamento->viaAdmin = $request->viaAdmin;
        $medicamento->presentacion = $request->presentacion;
        $medicamento->estado = '1';
        $medicamento->save();
    }

    public function update(Request $request)
    {
        if(!$request->ajax())  return redirect('/');
        $medicamento =Medicamento::findOrFail($request->id);
        $medicamento->idIngredienteActivo = $request->idIngredienteActivo;
        $medicamento->nombre = $request->nombre;
        $medicamento->advertencia = $request->advertencia;
        $medicamento->viaAdmin = $request->viaAdmin;
        $medicamento->presentacion = $request->presentacion;
        $medicamento->estado = '1';
        $medicamento->save();
    }//


    public function desactivar(Request $request)
    {
        if(!$request->ajax())  return redirect('/');
        $medicamento = Medicamento::findOrFail($request->id);
        $medicamento->estado = '0';
        $medicamento->save();
    }

    public function activar(Request $request)
    {
        if(!$request->ajax())  return redirect('/');
        $medicamento = Medicamento::findOrFail($request->id);
        $medicamento->estado = '1';
        $medicamento->save();
    }

    public function selectMedicamento(Request $request)
    {
        $medicamentos = Medicamento::where('estado','=','1')->select('id','nombre')->orderBy('nombre','asc')->get();

        return ['medicamentos' => $medicamentos];
    }
}
