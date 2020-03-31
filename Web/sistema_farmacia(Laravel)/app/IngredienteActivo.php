<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class IngredienteActivo extends Model
{
    protected $table = '_ingrediente_activo';
    protected $fillable =['nombre','cantidad'];

    public function medicamentos()
    {
        return $this->hasMany('App\Medicamento');
    }
}
