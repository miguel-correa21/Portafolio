<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Proveedor extends Model
{
    protected $table = 'proveedores';
    protected $fillable = ['tel2','rfc','estado'];

    public $timestamps = false;

    public function persona()
    {
        return $this->belongsTo('All\Persona');
    }

    public function lotes()
    {
        return $this->hasMany('App\Lote');
    }
}
