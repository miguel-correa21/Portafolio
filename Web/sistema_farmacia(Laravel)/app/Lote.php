<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Lote extends Model
{
    protected $fillable = ['idMedicamento','lote','fechaCaducidad','PrecioCompra','cantidad','estado'];

    public function medicamento()
    {
        return $this->belongsTo('App\Medicamento');
    }
}
