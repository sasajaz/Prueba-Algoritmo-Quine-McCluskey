/**
 * @file UtileriasMinterminos.h
 * @brief Declaraciones de funciones auxiliares para el manejo de mintérminos en la simplificación booleana.
 * 
 * Este archivo contiene las funciones necesarias para leer los mintérminos, covertirlos a binario,
 * clasificarlos y combinarlos con el método de Quine-McCluskey e imprimiendo la tabla resultante.
 * 
 * Se usan estructuras de datos que hacen más fácil trabajar paso a paso con mintérminos, agrupándolos según cuántos bits tienen en uno.
 */

#ifndef UTILERIAS_MINTERMINOS_H
#define UTILERIAS_MINTERMINOS_H

#include <vector>
#include <string>
#include "mintermino.h"

/**
 * @brief Funcion mediante la cual leemos los diferentes minterminos que se ingresen en el sistema
 * 
 * Esta función solicita al usuario la cantidad de mintérminos y luego los valores individuales.
 * También identifica el valor más grande, útil para determinar el número de bits necesarios.
 *
 * @param[out] NUMERO_MINTERMINOS Valor por referencia para almacenar el número total de minterminos
 * @param[out] minterminos Almacenamiento de los diferentes minterminos que se ingresen
 * @return int valor del mintérmino más grande localizado, útil para la construcción de los mintérminos binarios
 */
int lecturaMinterminos(int&, std::vector<int>&);

/**
 * @brief Convierte mintérminos a binario y los organiza en estructuras para futuras combinaciones.
 * 
 * Formación de los demás elementos necesarios para definir los mintérminos iniciales como lo es el propio mintérmino
 * en su forma binaria, el mintérmino representado con variables XYZ, y definiendo que aún no se han usado.
 * 
 * @param MAXIMO Elemento más grande que se encontro en la lectura de minterminos.
 * @param[in] minterminos Vector con los mintérminos almacenados anteriormente.
 * @param[out] minterminosBinario Vector que almacenará los mintérminos en su forma binaria.
 * @param[out] clasificacionGlobalMinterminos Vector que almacenará toda la información para las combinaciones posteriores
 * de los mintérminos, contieniendo TODA la información necesaria.
 * @return Retorna el número de bits con los cuales se formaron los minterminos binarios
 */

int formacionMinterminos(int, std::vector<int>&, std::vector<std::string>& , std::vector<std::vector<mintermino>>&);

/**
 * @brief Realiza las combinaciones entre mintérminos según el método de Quine-McCluskey.
 * 
 * Llenado completo de la tabla de clasificaciónG global de los mintérminos, generando todas las posibles combinaciones 
 * y almacenandolas
 * 
 * @param NUM_BITS Cantidad de bits que se necesitaron para el mintérmino más grande
 * @param[in,out] clasificacionGlobalMinterminos Vector referencia en el que almacenaremos toda la información
 * @return Devuelve el número total de columnas que se generaron al hacer todas las posibles combinaciones
 */

int clasificacionMinterminos(int, std::vector<std::vector<mintermino>>&);

/**
 * @brief Imprime la tabla de combinaciones y devuelve los mintérminos no utilizados.
 * 
 * Funcion mediante la cual vamos a imprimir en la terminal toda la información generada en las combinaciones.
 * 
 * @param NUMERO_COLUMNAS Número total de columnas con combinaciones
 * @param NUM_BITS Número total de bits que se utilizaron para crear las expresiones booleanas
 * @param[in] clasificacionGlobalMinterminos Tabla con la información de las combinaciones realizadas en otra función.
 * @return Retorna un vector con todos los minterminos que no se utilizaron en la construcción de las combinaciones.
 */
std::vector<mintermino> impresionTablaMinterminosTotales(const int, const int, std::vector<std::vector<mintermino>>&);

/**
 * @brief Imprime la tabla final de cobertura booleana.
 * Función sobre la cual organizamos, almacenamos e imprimimos los diferentes mintérminos que no hayan
 * sido utilizados durante las combinaciones de mintérminos, incluyendo su estilo en mintérmino, la posicion
 * de las X dentro de la tabla y su forma como espresion booleana.
 * @param minterminosNoUsados Vector que almacena los mintérminos no utilizados
 * @param tablaExpresionesFinales Matriz que almacena la tabla con los mintérminos finales y la posición de las X
 * @param minterminos Vector con los mintérminos totales
 */
void impresionTablaMinterminosFinal(std::vector<mintermino>&, std::vector<std::vector<int>>&, std::vector<int>&);

/**
 * @brief Simplifica la tabla final para obtener la expresión booleana más simple.
 * Función en la que imprimimos todas las simplificaciónes de la tabla final, de forma que mantengamos solamente
 * las expresiones booleanas escenciales
 * @param tablaExpresionesFinales Matriz con la información de la tabla final
 * @param NUMERO_MINTERMINOS Cantidad de minterminos a procesar
 * @param minterminosNoUsados Vector con los elementos que no se hayan combinado
 * @return Retorna una lista con los indices asociados a los mintérminos escenciales
 */
std::vector<int> simplificacionTablaFinal(std::vector<std::vector<int>>&, const int, std::vector<mintermino>&);


/**
 * @brief Actualiza la tabla de cobertura eliminando mintérminos cubiertos por un implicante
 * 
 * Función en la cual actualizamos la tanla de expresiones finales, dando como entrada las coordenadas del punto
 * sobre el cual comenzaremos la simplificación
 * 
 * @param tablaExpresionesFinales Tabla sobre la cual se hará la actualización
 * @param row Fila en la que se encuentra el punto inicial para la eliminación de los elementos
 * @param minterminosExpresados Vector que almacena los elementos ya procesados
 * @return Retorna el número de mintérminos que lograron ser expresados por la combinación
 */
int actualizacionImpresionTabla(std::vector<std::vector<int>>&, int, std::vector<bool>&, std::vector<mintermino>&);
#endif


