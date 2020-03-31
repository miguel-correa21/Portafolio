<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\IngredienteActivo;

class IngredienteActivoController extends Controller
{
   public function selectIngrediente(Request $request)
   {
       if(!$request->ajax()) return redirect('/');

        $ingredientes = IngredienteActivo::select('id','nombre','cantidad')->orderBy('nombre','asc')->get();

        return ['ingredientes_activos' => $ingredientes];
   } 
}
