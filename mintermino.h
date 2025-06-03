/**
 * @file mintermino.h
 * @brief Definición de la estructura de datos para representar un mintérmino en la simplificación booleana.
 * 
 * Esta estructura encapsula toda la información necesaria para representar y manipular mintérminos dentro del
 * método de Quine-McCluskey, incluyendo su forma binaria, su origen numérico y su forma algebraica.
 */

#ifndef MINTERMINO_H
#define MINTERMINO_H

#include <string>

/**
 * @struct mintermino
 * @brief Representa un mintérmino utilizado en la simplificación de funciones booleanas.
 * 
 * Contiene información binaria, su representación en forma booleana, y un flag que indica si ya fue usado en combinaciones.
 */
struct mintermino {
    /**
     * @brief Representación binaria del mintérmino.
     */
    std::string formaBinaria;

    /**
     * @brief Lista de los índices de mintérminos que forman este término.
     */
    std::string estructuraMintermino;

    /**
     * @brief Expresión booleana correspondiente.
     */
    std::string expresionBooleana;

    /**
     * @brief Marca si el mintérmino ya fue utilizado en alguna combinación.
     */
    bool uso;
};

#endif 
