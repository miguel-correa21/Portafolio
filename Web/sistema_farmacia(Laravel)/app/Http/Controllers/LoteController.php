<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Lote;

class LoteController extends Controller
{
    public function index(Request $request) 
    {
        if(!$request->ajax())  return redirect('/');
        $buscar = $request->buscar;
        $criterio = $request->criterio;

        if($buscar == '')
        {
            $lotes = Lote::join('medicamentos','lotes.idMedicamento','=','medicamentos.id')->join('proveedores','lotes.idProveedor','=','proveedores.id')->join('personas','proveedores.id','=','personas.id')->select('lotes.id','lotes.lote','lotes.idMedicamento','lotes.fechaCaducidad','lotes.PrecioCompra','lotes.cantidad','lotes.estado','medicamentos.nombre','lotes.idProveedor','personas.nombre as proveedor')->orderBy('lotes.id','desc')->paginate(3);
        }
        else
        {
            if($criterio == 'nombre')
            {
                $lotes = Lote::join('medicamentos','lotes.idMedicamento','=','medicamentos.id')->join('proveedores','lotes.idProveedor','=','proveedores.id')->join('personas','proveedores.id','=','personas.id')->select('lotes.id','lotes.lote','lotes.idMedicamento','lotes.fechaCaducidad','lotes.PrecioCompra','lotes.cantidad','lotes.estado','medicamentos.nombre','lotes.idProveedor','personas.nombre as proveedor')->where('medicamentos.'.$criterio, 'like', '%'. $buscar. '%')->orderBy('lotes.id','desc')->paginate(3);
            }
            else
            {
                $lotes = Lote::join('medicamentos','lotes.idMedicamento','=','medicamentos.id')->join('proveedores','lotes.idProveedor','=','proveedores.id')->join('personas','proveedores.id','=','personas.id')->select('lotes.id','lotes.lote','lotes.idMedicamento','lotes.fechaCaducidad','lotes.PrecioCompra','lotes.cantidad','lotes.estado','medicamentos.nombre','lotes.idProveedor','personas.nombre as proveedor')->where('lotes.'.$criterio, 'like', '%'. $buscar. '%')->orderBy('lotes.id','desc')->paginate(3);

            }
        }

        return
        [
            'pagination'=>[
                'total' => $lotes->total(),
                'current_page' =>$lotes->currentPage(),
                'per_page'=> $lotes->perPage(),
                'last_page' => $lotes->lastPage(),
                'from' => $lotes->firstItem(),
                'to'=> $lotes->lastItem(),
            ],
            'lotes' => $lotes
        ];
    }

    
    public function store(Request $request)
    {
        if(!$request->ajax())  return redirect('/');
        $lote = new Lote();
        $lote->lote = $request->lote;
        $lote->idMedicamento = $request->idMedicamento;
        $lote->fechaCaducidad = $request->fechaCaducidad;
        $lote->idProveedor = $request->idProveedor;
        $lote->PrecioCompra = $request->PrecioCompra;
        $lote->cantidad = $request->cantidad;
        $lote->estado = '1';
        $lote->save();
    }

    public function update(Request $request)
    {
        //if(!$request->ajax())  return redirect('/');
        $lote = Lote::findOrFail($request->id);
        $lote->lote = $request->lote;
        $lote->idMedicamento = $request->idMedicamento;
        $lote->fechaCaducidad = $request->fechaCaducidad;
        $lote->idProveedor = $request->idProveedor;
        $lote->PrecioCompra = $request->PrecioCompra;
        $lote->cantidad = $request->cantidad;
        $lote->estado = '1';
        $lote->save();
    }

    public function desactivar(Request $request)
    {
        if(!$request->ajax())  return redirect('/');
        $lote = Lote::findOrFail($request->id);
        $lote->estado = '0';
        $lote->save();
    }

    public function activar(Request $request)
    {
        if(!$request->ajax())  return redirect('/');
        $lote = Lote::findOrFail($request->id);
        $lote->estado = '1';
        $lote->save();
    }

}
