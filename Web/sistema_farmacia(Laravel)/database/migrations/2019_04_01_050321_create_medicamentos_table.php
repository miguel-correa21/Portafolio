<?php

use Illuminate\Support\Facades\Schema;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Database\Migrations\Migration;

class CreateMedicamentosTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('medicamentos', function (Blueprint $table) {
            $table->increments('id');
            $table->integer('idIngredienteActivo')->unsigned();
            $table->string('nombre',45);
            $table->string('advertencia',200);
            $table->string('viaAdmin',30);
            $table->string('presentacion',30);
            $table->boolean('estado')->default(1);
            $table->timestamps();

            $table->foreign('idIngredienteActivo')->references('id')->on('_ingrediente_activo');
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('medicamentos');
    }
}
