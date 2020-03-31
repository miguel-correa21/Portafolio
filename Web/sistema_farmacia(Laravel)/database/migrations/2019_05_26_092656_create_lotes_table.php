<?php

use Illuminate\Support\Facades\Schema;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Database\Migrations\Migration;

class CreateLotesTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('lotes', function (Blueprint $table) {
            $table->increments('id');
            $table->string('lote',20)->unique();
            $table->integer('idMedicamento')->unsigned();
            $table->integer('idProveedor')->unsigned();
            $table->string('fechaCaducidad',80);
            $table->float('PrecioCompra');
            $table->integer('cantidad')->unsigned();
            $table->boolean('estado')->default('1');
            $table->timestamps();
            $table->foreign('idMedicamento')->references('id')->on('medicamentos');
            $table->foreign('idProveedor')->references('id')->on('proveedores');
            
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('lotes');
    }
}
