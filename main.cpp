/**
 * @file main.cpp
 * @brief Implementación principal del método de Quine-McCluskey para simplificación de funciones booleanas.
 * 
 * Ejemplo de entrada sugerido:
 * ```
 * 0 4 8 5 12 11 7 15
 * ```
 * 
 * @note COMPILACIÓN:
 * Asegúrate de tener todos los archivos del proyecto en una misma carpeta (como se encuentra en GitHub).
 * 
 * Para compilar:
 * ```
 * g++ main.cpp UtileriasMinterminos.cpp -o programa
 * ./programa
 * ```
 * 
 * @author 
 * @date Junio de 2025
 */

#include <bits/stdc++.h>
#include <iomanip>
#include "UtileriasMinterminos.h"
#include "mintermino.h"

using namespace std;
typedef long long ll;

/**
 * @brief Punto de entrada principal del programa.
 * 
 * Lee mintérminos desde entrada, los clasifica, genera las combinaciones de Quine-McCluskey
 * e imprime la tabla de implicantes primos con su cobertura.
 * 
 * @return int 0 si la ejecución fue exitosa.
 */
int main() {

    /**
     * @brief Vector que almacena la clasificación de los mintérminos, en la primera pocisión es el número de bits encendidos que tiene el mintermino
     *el par exterior en su primera posicion tiene otro par con la información del número en bits y en la segunda pocisión tenemos el número 
     *del cual surgió el número binario.
     * 
     * @note Estructura: [iteracionDeLaTabla][minterminosAlmacenados]
     * 
     * IMPORTANTE: A partir de la iteracion 1, los minterminos seran clasificados de forma creciente con referencia
     * a la cantidad de bits encendidos sobre el cual se generó la combinación.
     */
    vector<vector<mintermino>> clasificacionGlobalMinterminos(50);

    vector<int> minterminos;  vector<string> minterminosBinario;
    int NUMERO_MINTERMINOS;


    // Lectura de datos y retorno del mintérmino mas grande
    const int MINTERMINO_MAXIMO=lecturaMinterminos(NUMERO_MINTERMINOS, minterminos);

    // Formación de los mintérminos completos.
    const int NUM_BITS=formacionMinterminos(MINTERMINO_MAXIMO, minterminos, minterminosBinario, clasificacionGlobalMinterminos);

    // Llenado de la tabla ClasificacionGlobalMinterminos
    const int NUMERO_COLUMNAS=clasificacionMinterminos(NUM_BITS, clasificacionGlobalMinterminos);

    // Impresion de la tabla con las combinaciones generadas.
    vector<mintermino> minterminosNoUsados=impresionTablaMinterminosTotales(NUMERO_COLUMNAS, NUM_BITS, clasificacionGlobalMinterminos);


    /**
     * @brief Tabla que representa la cobertura de los mintérminos por los implicantes primos.
     * 
     * 1 representa una X, 0 representa un espacio vacio
     * 
     * tablaExpresionesFinales[i][j] = 1 si el implicante i cubre el mintérmino j
     */

    // Métrica de la construcción de la tabla
    const int NUM_MINTERMINOS_FINAL=minterminosNoUsados.size(); 
    vector<vector<int>> tablaExpresionesFinales(NUM_MINTERMINOS_FINAL+1, vector<int>(NUMERO_MINTERMINOS));    //1 representa una X, 0 representa un espacio vacio.


    //Impresion de la tabla final
    impresionTablaMinterminosFinal(minterminosNoUsados, tablaExpresionesFinales, minterminos);
    

    //Simplificación de la tabla final para obtener la expresión más simple
    vector<int> indices = simplificacionTablaFinal(tablaExpresionesFinales, NUMERO_MINTERMINOS, minterminosNoUsados);

    //Impresion de la expresión booleana final
    cout<<"\n====================================================================================================    \n\n    Expresion booleana final:";
    cout<<"  ";
    for(int i=0; i<indices.size(); i++){
        cout<<minterminosNoUsados[indices[i]].expresionBooleana;
        if(i!=indices.size()-1) cout<<" + ";
    }
    cout<<" \n"<<endl;
    return 0;

}

