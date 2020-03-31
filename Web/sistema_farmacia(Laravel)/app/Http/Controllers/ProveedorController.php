<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\DB;
use App\Persona;
use App\Proveedor;

class ProveedorController extends Controller
{
    public function index(Request $request) 
    {
       //if(!$request->ajax())  return redirect('/');
        $buscar = $request->buscar;
        $criterio = $request->criterio;

        if($buscar == '')
        {
            $personas = Proveedor::join('personas','proveedores.id','=','personas.id')->select('personas.id','personas.nombre','personas.tel','personas.email','proveedores.tel2','proveedores.rfc','proveedores.estado')->orderBy('personas.id','desc')->paginate(3);
        }
        else
        {
            $personas = Proveedor::join('personas','proveedores.id','=','personas.id')->select('personas.id','personas.nombre','personas.tel','personas.email','proveedores.tel2','proveedores.rfc','proveedores.estado')->where('personas.'.$criterio, 'like', '%'. $buscar.'%')->orderBy('personas.id','desc')->paginate(3);
        }

        return
        [
            'pagination'=>[
                'total' => $personas->total(),
                'current_page' =>$personas->currentPage(),
                'per_page'=> $personas->perPage(),
                'last_page' => $personas->lastPage(),
                'from' => $personas->firstItem(),
                'to'=> $personas->lastItem(),
            ],
            'personas' => $personas
        ];
    }


    public function store(Request $request)
    {
        if(!$request->ajax())  return redirect('/');
        
        try
        {
            DB::beginTransaction();
            $persona = new Persona();
            $persona->nombre = $request->nombre;
            $persona->email = $request->email;
            $persona->tel = $request->tel;
            $persona->estado = '1';
            $persona->save();
            $proveedor = new Proveedor();
            $proveedor->tel2 = $request->tel2;
            $proveedor->rfc = $request->rfc;
            $proveedor->estado = '1';
            $proveedor->id = $persona->id;
            $proveedor->save();


            DB::commit();
        }catch(Exception $e)
        {
            DB::rollBack();
        }
    }

    public function update(Request $request)
    {
        if(!$request->ajax())  return redirect('/');
        
        try
        {
            DB::beginTransaction();
            $proveedor = Proveedor::findOrFail($request->id);

            $persona =  Persona::findOrFail($proveedor->id);
            $persona->nombre = $request->nombre;
            $persona->email = $request->email;
            $persona->tel = $request->tel;
            $persona->estado = '1';
            $persona->save();

            $proveedor->tel2 = $request->tel2;
            $proveedor->rfc = $request->rfc;
            $proveedor->estado = '1';

            $proveedor->save();
            DB::commit();
        }catch(Exception $e)
        {
            DB::rollBack();
        };
    }

    public function desactivar(Request $request)
    {
        if(!$request->ajax())  return redirect('/');
        $proveedor = Proveedor::findOrFail($request->id);
        $proveedor->estado = '0';
        $proveedor->save();
    }

    public function activar(Request $request)
    {
        if(!$request->ajax())  return redirect('/');
        $proveedor = Proveedor::findOrFail($request->id);
        $proveedor->estado = '1';
        $proveedor->save();
    }

    public function selectProveedor(Request $request)
    {
         $proveedores = Proveedor::join('personas','proveedores.id','=','personas.id')->where('proveedores.estado','=','1')->select('proveedores.id as idProveedor','personas.nombre')->orderBy('nombre','asc')->get();

        return ['proveedores' => $proveedores];
    }

}
