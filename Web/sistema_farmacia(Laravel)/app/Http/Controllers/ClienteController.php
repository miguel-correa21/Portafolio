<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Cliente;

class ClienteController extends Controller
{
    public function index(Request $request) 
    {
        if(!$request->ajax())  return redirect('/');
        $buscar = $request->buscar;
        $criterio = $request->criterio;

        if($buscar == '')
        {
            $clientes = Cliente::orderBy('id','desc')->paginate(3);
        }
        else
        {
            $clientes = Cliente::where($criterio, 'like', '%'. $buscar.'%')->orderBy('id','desc')->paginate(3);
        }

        return
        [
            'pagination'=>[
                'total' => $clientes->total(),
                'current_page' =>$clientes->currentPage(),
                'per_page'=> $clientes->perPage(),
                'last_page' => $clientes->lastPage(),
                'from' => $clientes->firstItem(),
                'to'=> $clientes->lastItem(),
            ],
            'clientes' => $clientes
        ];
    }

    
    public function store(Request $request)
    {
        if(!$request->ajax())  return redirect('/');
        $cliente = new Cliente();
        $cliente->nombre = $request->nombre;
        $cliente->ApellidoPaterno = $request->ApellidoPaterno;
        $cliente->ApellidoMaterno = $request->ApellidoMaterno;
        $cliente->Email = $request->Email;
        $cliente->tel = $request->tel;
        $cliente->estado = '1';
        $cliente->save();
    }

    public function update(Request $request)
    {
        if(!$request->ajax())  return redirect('/');
        $cliente = Cliente::findOrFail($request->id);
        $cliente->nombre = $request->nombre;
        $cliente->ApellidoPaterno = $request->ApellidoPaterno;
        $cliente->ApellidoMaterno = $request->ApellidoMaterno;
        $cliente->Email = $request->Email;
        $cliente->tel = $request->tel;
        $cliente->estado = '1';
        $cliente->save();
    }

    public function desactivar(Request $request)
    {
        if(!$request->ajax())  return redirect('/');
        $cliente = Cliente::findOrFail($request->id);
        $cliente->estado = '0';
        $cliente->save();
    }

    public function activar(Request $request)
    {
        if(!$request->ajax())  return redirect('/');
        $cliente = Cliente::findOrFail($request->id);
        $cliente->estado = '1';
        $cliente->save();
    }

}
