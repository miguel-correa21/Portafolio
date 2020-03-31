<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Medicamento extends Model
{
    protected $fillable = 
    [
        'idIngredienteActivo',
        'nombre',
        'advertencia',
        'viaAdmin',
        'presentacion',
        'estado'
    ];

    public function ingredienteActivo()
    {
        return $this->belongsTo(App\IngredienteActivo);
    }

    public function lotes()
    {
        return $this->hasMany('App\Lote');
    }
}
