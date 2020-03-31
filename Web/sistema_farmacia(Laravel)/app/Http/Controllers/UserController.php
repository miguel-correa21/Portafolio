<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\DB;
use App\User;
use App\Persona;
use PHPUnit\Framework\MockObject\Stub\Exception;

class UserController extends Controller
{
    public function index(Request $request) 
    {
       if(!$request->ajax())  return redirect('/');
        $buscar = $request->buscar;
        $criterio = $request->criterio;

        if($buscar == '')
        {
            $personas = User::join('personas','users.id','=','personas.id')->join('roles','users.idrol','=','roles.id')->select('personas.id','personas.nombre','personas.tel','personas.email','users.usuario','users.password','users.salario','users.estado','users.idrol','roles.nombre as rol')->orderBy('personas.id','desc')->paginate(3);
        }
        else
        {
            $personas = User::join('personas','users.id','=','personas.id')->join('roles','users.idrol','=','roles.id')->select('personas.id','personas.nombre','personas.tel','personas.email','users.usuario','users.password','users.salario','users.estado','users.idrol','roles.nombre as rol')->where('personas.'.$criterio, 'like', '%'. $buscar.'%')->orderBy('id','desc')->paginate(3);
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
            $user = new User();
            $user->usuario = $request->usuario;
            $user->password = bcrypt($request->password);
            $user->salario = $request->salario;
            $user->estado = '1';
            $user->idrol = $request->idrol;
            $user->id = $persona->id;

            $user->save();

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
            $user = User::findOrFail($request->id);

            $persona =  Persona::findOrFail($user->id);
            $persona->nombre = $request->nombre;
            $persona->email = $request->email;
            $persona->tel = $request->tel;
            $persona->estado = '1';
            $persona->save();

            $user->usuario = $request->usuario;
            $user->password = bcrypt($request->password);
            $user->salario = $request->salario;
            $user->estado = '1';
            $user->id = $persona->id;
            $user->idrol = $request->idrol;

            $user->save();

            DB::commit();
        }catch(Exception $e)
        {
            DB::rollBack();
        };
    }

    public function desactivar(Request $request)
    {
        if(!$request->ajax())  return redirect('/');
        $user = User::findOrFail($request->id);
        $user->estado = '0';
        $user->save();
    }

    public function activar(Request $request)
    {
        if(!$request->ajax())  return redirect('/');
        $user = User::findOrFail($request->id);
        $user->estado = '1';
        $user->save();
    }

}
