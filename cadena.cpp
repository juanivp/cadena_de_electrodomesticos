// Una empresa de electrodomésticos cuenta con vendedores en diferentes sucursales. Al finalizar el mes se cuenta con los datos de cada venta ordenados por
// código de vendedor en forma ascendente:

// - Código de vendedor
// - Fecha de venta
// - Producto vendido
// - Monto de la venta
// - Comisión ganada

// Y en forma separada, los datos de cada vendedor:

// - Código de vendedor
// - Nombre
// - Apellido
// - Sucursal (1: Centro, 2: Shopping)

// Los datos ya están cargados en vectores estáticos y que cada vector tiene una variable asociada que indica la cantidad de elementos cargados.

// Se asume que cada vendedor realiza al menos una venta en el mes.

// ---

// ## Se pide:

// **1)** Definir las estructuras de datos necesarias para soportar la solución del problema.

// **2)** Escribir una función que ordene el vector de vendedores por sucursal (ordenamiento burbuja).

// **3)** Escribir una función que busque en el vector de vendedores por código y devuelva la posición en el vector (búsqueda binaria).

// **4)** Escribir una función que genere un nuevo vector con cada vendedor y su total de comisiones del mes, utilizando apareo entre ambos vectores.
// **Importante:** Si el monto de la venta supera los $20.000 y la sucursal es Centro (1), se debe aumentar la comisión en un 15% antes de sumarla al total.

// **5)** Escribir una función que muestre un reporte por sucursal indicando: nombre de la sucursal, cantidad total de ventas y el vendedor con mayor total
// de comisiones (usar corte de control).

#include <iostream>
#include <string>
using namespace std;

struct Vendedor
{
    int codigo_vendedor;
    string nombre;
    string apellido;
    int sucursal;
};

struct Venta
{
    int codigo_vendedor;
    long fecha_venta;
    string producto_vendido;
    float monto_venta;
    float comision_ganada;
};

struct VendedorConTotal
{
    int codigo_vendedor;
    float comision_total;
    int sucursal;
    int cantidad_ventas;
};

void burbujeo_sucursal(Vendedor arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j].sucursal > arr[j + 1].sucursal)
            {
                // Intercambiar
                Vendedor temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void mostrar_vector_vendedor(Vendedor arr[], int cant)
{
    for (int i = 0; i < cant; i++)
    {
        cout << "Vendedor: " << arr[i].codigo_vendedor << endl;
        cout << "Sucursal: " << arr[i].sucursal << endl;
    }
}

void mostrar_vector_resultado(VendedorConTotal arr[], int cant)
{
    for (int i = 0; i < cant; i++)
    {
        cout << "Vendedor: " << arr[i].codigo_vendedor << endl;
        cout << "Comision total ganada: " << arr[i].comision_total << endl;
    }
}

int busquedaBinaria(Vendedor arr[], int cant, int valor)
{
    int inicio = 0;
    int fin = cant - 1;
    int posicion = -1; // Inicializar posición como no encontrada

    while (inicio <= fin)
    {
        int medio = inicio + (fin - inicio) / 2;

        if (arr[medio].codigo_vendedor == valor)
        {
            posicion = medio; // Lo encontró
        }

        if (arr[medio].codigo_vendedor > valor)
        {
            fin = medio - 1; // Buscar en la mitad izquierda
        }
        else
        {
            inicio = medio + 1; // Buscar en la mitad derecha
        }
    }

    return posicion; // No lo encontró
}

// **4)** Escribir una función que genere un nuevo vector con cada vendedor y su total de comisiones del mes, utilizando apareo entre ambos vectores.
// **Importante:** Si el monto de la venta supera los $20.000 y la sucursal es Centro (1), se debe aumentar la comisión en un 15% antes de sumarla al total.

void apareo(Vendedor vecA[], int cant_vendedores, Venta vecB[], int cant_ventas, VendedorConTotal vecC[], int &k)
{
    int i = 0;
    int j = 0;
    k = 0;
    long key;
    float acumulador_comisiones;
    int cantidad_ventas;

    while (i < cant_vendedores)
    {
        vecC[k].sucursal = vecA[i].sucursal;
        vecC[k].codigo_vendedor = vecA[i].codigo_vendedor;

        key = vecA[i].codigo_vendedor;
        acumulador_comisiones = 0;
        cantidad_ventas = 0;

        while (j < cant_ventas && key == vecB[j].codigo_vendedor)
        {
            if (vecA[i].sucursal == 1 && vecB[j].monto_venta > 20000)
            {
                acumulador_comisiones += vecB[j].comision_ganada + (vecB[j].comision_ganada*0.15);
                
            } else{
                acumulador_comisiones += vecB[j].comision_ganada;
            }
            j++;
            cantidad_ventas++;
        }
        i++;
        vecC[k].comision_total = acumulador_comisiones;
        vecC[k].cantidad_ventas = cantidad_ventas;
        k++;
    }

}

// **5)** Escribir una función que muestre un reporte por sucursal indicando: nombre de la sucursal, cantidad total de ventas y el vendedor con mayor total de comisiones (usar corte de control).

void listarPresentismo(Venta vec[], int n)
{

    //i: recorre todo el vector.

    //ausentes: contador de faltas por empleado.

    //key: guarda el legajo actual.

    int i = 0;
    int ausentes = 0;
    int key;

    cout << "=== REPORTE DE FALTAS POR ALUMNO ===" << endl;
    cout << "------------------------------------" << endl;

    // El primer ciclo es el que recorre el lote completo
    while (i < n)
    {
        // Guardo el valor del legajo actual como clave
        // Esto permite agrupar los registros por legajo
        key = vec[i].legajo;

        // Inicializo contador de ausentes para este legajo
        ausentes = 0;

        // El segundo ciclo se mantiene por el sublote, mientras sea el mismo
        // legajo y aun no se haya acabado el vector
        //Este bucle procesa el sublote, es decir, todos los registros que tienen el mismo legajo.
        while (i < n && key == vec[i].legajo)
        {
            //se agrega el i<n para evitar el desbordamiento 

            // Cuento si es un registro de ausente
            if (!vec[i].presente)
            {
                ausentes++;
            }
            i++; // Avanza a la siguiente posicion
        }

        // Mostramos resultados por cada sublote (legajo)
        cout << "Legajo: " << key << " - Faltas: " << ausentes << endl;
    }

    cout << "------------------------------------" << endl;
    cout << "Fin del reporte" << endl;
}

// Variables globales con datos precargados
const int MAX_VENDEDORES = 100;
const int MAX_VENTAS = 500;
const int MAX_RESULTADO = 100;

int main()
{
    // Vector de vendedores (ordenado por código ascendente)
    Vendedor vendedores[MAX_VENDEDORES] = {
        {101, "Juan", "Perez", 1},
        {103, "Ana", "Lopez", 1},
        {105, "Carlos", "Ruiz", 2},
        {107, "Maria", "Garcia", 2},
        {109, "Luis", "Martinez", 1}};
    int cantVendedores = 5;

    // Vector de ventas (ordenado por código de vendedor ascendente)
    Venta ventas[MAX_VENTAS] = {
        {101, 15032024, "Heladera", 15000.0, 450.0},
        {101, 16032024, "Microondas", 25000.0, 750.0},
        {101, 18032024, "Lavarropas", 30000.0, 900.0},
        {103, 17032024, "Televisor", 18000.0, 540.0},
        {103, 20032024, "Aire Acond.", 22000.0, 660.0},
        {105, 19032024, "Cocina", 12000.0, 360.0},
        {105, 21032024, "Freezer", 16000.0, 480.0},
        {105, 22032024, "Lavavajillas", 28000.0, 840.0},
        {107, 23032024, "Heladera", 35000.0, 1050.0},
        {107, 25032024, "Televisor", 40000.0, 1200.0},
        {109, 26032024, "Microondas", 8000.0, 240.0},
        {109, 28032024, "Cocina", 45000.0, 1350.0}};
    int cantVentas = 12;

    int codigo_buscado = 107;
    int indice_codigo_buscado = busquedaBinaria(vendedores, cantVendedores, codigo_buscado);

    if (indice_codigo_buscado != -1)
    {
        cout << "El codigo de vendedor " << codigo_buscado << " se encuentra en la posicion " << indice_codigo_buscado << endl;
    }
    else
    {
        cout << "El codigo de vendedor " << codigo_buscado << " no se encuentra en el listado." << endl;
    }

    // burbujeo_sucursal(vendedores, cantVendedores);
    mostrar_vector_vendedor(vendedores, cantVendedores);

    // Vector resultado del apareo
    VendedorConTotal resultado[MAX_RESULTADO];
    int cantResultado = 0;

    apareo(vendedores, cantVendedores, ventas, cantVentas, resultado, cantResultado);
    mostrar_vector_resultado(resultado, cantResultado);

    cout << "holsfjasf";

    return 0;
}