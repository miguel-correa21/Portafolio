<?php
use Symfony\Component\HttpKernel\Fragment\RoutableFragmentRenderer;
use PhpParser\Node\Expr\FuncCall;

//use Symfony\Component\Routing\Route;

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/
Route::group(['middleware'=>['guest']],function()
{
    Route::get('/',"Auth\LoginController@showLoginForm");
    Route::post('/login', 'Auth\LoginController@login')->name('login');
});

Route::group(['middleware'=>['auth']],function()
{
    Route::post('/logout','Auth\LoginController@logout')->name('logout');

    Route::get('/main', function () 
    {
        return view("contenido/contenido");
    })->name('main');

    Route::group(['middleware'=>['Dueño']],function()
    {
        Route::get('/medicamento','MedicamentoController@index');
        Route::post('/medicamento/registrar','MedicamentoController@store');
        Route::put('/medicamento/actualizar','MedicamentoController@update');
        Route::put('/medicamento/desactivar','MedicamentoController@desactivar');
        Route::put('/medicamento/activar','MedicamentoController@activar');
        Route::get('/IngredienteActivo/selectIngrediente','IngredienteActivoController@selectIngrediente');

        Route::get('/rol','RolController@index');
        Route::get('/rol/selectRol','RolController@selectRol');
    
        Route::get('/user','UserController@index');
        Route::post('/user/registrar','UserController@store');
        Route::put('/user/actualizar','UserController@update');
        Route::put('/user/desactivar','UserController@desactivar');
        Route::put('/user/activar','UserController@activar');

        Route::get('/proveedor','ProveedorController@index');
        Route::post('/proveedor/registrar','ProveedorController@store');
        Route::put('/proveedor/actualizar','ProveedorController@update');
        Route::put('/proveedor/desactivar','ProveedorController@desactivar');
        Route::put('/proveedor/activar','ProveedorController@activar');

    });


    Route::group(['middleware'=>['Cajero']],function()
    {
        Route::get('/cliente','ClienteController@index');
        Route::post('/cliente/registrar','ClienteController@store');
        Route::put('/cliente/actualizar','ClienteController@update');
        Route::put('/cliente/desactivar','ClienteController@desactivar');
        Route::put('/cliente/activar','ClienteController@activar');

        Route::get('/medicamento','MedicamentoController@index');
        Route::get('/medicamento/selectMedicamento','MedicamentoController@selectMedicamento');
        Route::get('/proveedor/selectProveedor','ProveedorController@selectProveedor');

        Route::get('/lote','LoteController@index');
        Route::post('/lote/registrar','LoteController@store');
        Route::put('/lote/actualizar','LoteController@update');
        Route::put('/lote/desactivar','LoteController@desactivar');
        Route::put('/lote/activar','LoteController@activar');
    });

    
    Route::group(['middleware'=>['Supervisor']],function()
    {
        Route::get('/medicamento','MedicamentoController@index');
        Route::get('/rol','RolController@index');
        Route::get('/rol/selectRol','RolController@selectRol');
    
        Route::get('/user','UserController@index');
        Route::post('/user/registrar','UserController@store');
        Route::put('/user/actualizar','UserController@update');

    });

});

//Route::get('/home', 'HomeController@index')->name('home');


