/**
 * @file UtileriasMinterminos.cpp
 * @brief Implementación de utilidades para trabajar con mintérminos en la simplificación de funciones booleanas usando Quine-McCluskey.
 */
#include <bits/stdc++.h>
#include "UtileriasMinterminos.h"
#include "mintermino.h"
using namespace std;

/**
 * @brief Lee los mintérminos desde la entrada estándar.
 * 
 * Solicita al usuario la cantidad de mintérminos, los lee y almacena en un vector. También determina el mintérmino más grande.
 * 
 * @param[out] NUMERO_MINTERMINOS Cantidad total de mintérminos leída.
 * @param[out] minterminos Vector que almacena los mintérminos introducidos.
 * @return int El mintérmino más grande.
 */
int lecturaMinterminos(int &NUMERO_MINTERMINOS, vector<int> &minterminos){
    cout<<"Ingrese la cantidad de minterminos"<<endl;
    cin>>NUMERO_MINTERMINOS;

    int minterminoMaximo = 0;
    cout<<"Ingrese los minterminos:"<<endl;
    for(int i=0; i<NUMERO_MINTERMINOS; i++){
        int minterm;
        cin>>minterm;
        minterminos.push_back(minterm);
        minterminoMaximo = max(minterminoMaximo, minterm);
    }

    sort(minterminos.begin(), minterminos.end());
    return minterminoMaximo;
}


/**
 * @brief Convierte los mintérminos a binario y los clasifica según su cantidad de bits encendidos.
 * 
 * Esta función determina cuántos bits se requieren, convierte los mintérminos a binario y los clasifica 
 * dentro de `clasificacionGlobalMinterminos` por la cantidad de bits en 1.
 * 
 * @param MAXIMO Valor del mintérmino más grande.
 * @param[in] minterminos Vector con los mintérminos numéricos.
 * @param[out] minterminosBinario Vector con representaciones binarias.
 * @param[out] clasificacionGlobalMinterminos Estructura que almacena la clasificación de los mintérminos.
 * @return int Número de bits necesarios para hacer los minterminos.
 */

int formacionMinterminos(int MINTERMINO_MAXIMO, vector<int> &minterminos, vector<string> &minterminosBinario, vector<vector<mintermino>> &clasificacionGlobalMinterminos){
    
    //Mediante el valor más grande, definimos el número de bits que vamos a necesitar
    int NUM_BITS=0;
    while(MINTERMINO_MAXIMO){
        NUM_BITS++;
        MINTERMINO_MAXIMO>>=1;
    }

    //Transformamos los mintérminos a binario y los almacenamos
    for(int i:minterminos){
        bitset<30> mintermToBit(i);
        /**
         * En base al valor mas grande tomamos unicamente los bits necesarios para que queden todos los minterminos
         * con la mínima cantidad de bits posible, para ello de todo el bitset solamente tomamos el segmento
         * que contiene a los bits significativos
         */
        minterminosBinario.push_back(mintermToBit.to_string().substr(((mintermToBit.to_string().size())-NUM_BITS), NUM_BITS));
    }


    int indiceMinterminos=0;
    /**
     * Clasificación de los mintérminos en su forma binaria dependiendo de la cantidad de bits que se encuentren prendidos, estos son 
     * almacenados en la iteracion 0 de la tabla y clasificados en su correspondiente cantidad de bits
    */
    for(string mintermBits:minterminosBinario){
        
        string expresionBool="";
        for(int i=0; i<NUM_BITS; i++){
            expresionBool.push_back((char)('z'-NUM_BITS+(i+1)));
            if(mintermBits[i]=='0') expresionBool.push_back('\'');
        }

        //Declaración mintérmino
        mintermino minterminoInicial;
        minterminoInicial.formaBinaria=mintermBits;
        minterminoInicial.estructuraMintermino=to_string(minterminos[indiceMinterminos++]);
        minterminoInicial.uso=false;
        minterminoInicial.expresionBooleana=expresionBool;

        clasificacionGlobalMinterminos[0].push_back(minterminoInicial);
    }
    return NUM_BITS;
}

/**
 * @brief Clasifica los mintérminos en múltiples iteraciones, combinando aquellos que difieren en un solo bit.
 * 
 * Genera nuevas combinaciones de mintérminos a partir de la iteración 1 en adelante, 
 * siguiendo el método de Quine-McCluskey.
 * 
 * @param NUM_BITS Número de bits de los mintérminos.
 * @param[in,out] clasificacionGlobalMinterminos Estructura global que almacena las combinaciones por iteración.
 * @return int Número total de columnas de combinaciones generadas.
 */

int clasificacionMinterminos(int NUM_BITS, vector<vector<mintermino>>&clasificacionGlobalMinterminos){

    int totalColumns=0;
    bool hasElements=true;

    
    //Comparamos todos los minterminos con todos los minterminos dentro de una misma combinacion
    for(int i=0; i<clasificacionGlobalMinterminos.size(); i++){

        if(clasificacionGlobalMinterminos[i].empty()) continue;

        //Cada que logremos hacer una nueva combinación aumentamos el total de combinaciones
        totalColumns++;

        for(int j=0; j<clasificacionGlobalMinterminos[i].size(); j++){

            for(int k=j+1; k<clasificacionGlobalMinterminos[i].size(); k++){

                //Búsqueda de todos los elementos que puedan combinarse
                string posibleCombinacion="";
                int numeroDeCaracteresDiferentes=0;

                for(int l=0; l<NUM_BITS; l++){
                    if(clasificacionGlobalMinterminos[i][j].formaBinaria[l]!=clasificacionGlobalMinterminos[i][k].formaBinaria[l]){
                        numeroDeCaracteresDiferentes++;
                        posibleCombinacion.push_back('_');
                    }else{
                        posibleCombinacion.push_back(clasificacionGlobalMinterminos[i][j].formaBinaria[l]);
                    }
                }
                if(numeroDeCaracteresDiferentes==1){

                    //Creacion del nuevo mintermino combinado
                    mintermino minterminoCombinado;
        
                    //Creacion de la expresion booleana
                    string expresionBool="";
                    for(int l=0; l<NUM_BITS; l++){
                        if(posibleCombinacion[l]=='0') {expresionBool.push_back((char)('z'-NUM_BITS+(l+1))); expresionBool.push_back('\'');}
                        else if(posibleCombinacion[l]=='1') expresionBool.push_back((char)('z'-NUM_BITS+(l+1)));
                    }
        
                    bool minterminoRepetido=false;
                    for(mintermino minterms:clasificacionGlobalMinterminos[i+1]){
                        if(minterms.formaBinaria==posibleCombinacion){
                            clasificacionGlobalMinterminos[i][j].uso=true;
                            clasificacionGlobalMinterminos[i][k].uso=true;
                            minterminoRepetido=true;
                        }
                    }

                    if(minterminoRepetido) continue;

                    //Llenado de datos en el dato de tipo mintermino con los datos recabados
                    minterminoCombinado.formaBinaria=posibleCombinacion;
                    minterminoCombinado.estructuraMintermino=clasificacionGlobalMinterminos[i][j].estructuraMintermino+","+clasificacionGlobalMinterminos[i][k].estructuraMintermino;
                    minterminoCombinado.uso=false;
                    minterminoCombinado.expresionBooleana=expresionBool;
        
                    clasificacionGlobalMinterminos[i+1].push_back(minterminoCombinado);
        
                    //actualizacion de los estados de los minterminos usados
                    clasificacionGlobalMinterminos[i][j].uso=true;
                    clasificacionGlobalMinterminos[i][k].uso=true;
                }
            }
        }
    }

    return totalColumns;
}

/**
 * @brief Imprime la tabla de combinaciones y retorna los mintérminos que no fueron usados.
 * 
 * Imprime una tabla donde se listan todas las combinaciones realizadas en cada iteración.
 * Los mintérminos que no pudieron combinarse más son marcados con un `*`.
 * 
 * @param NUMERO_COLUMNAS Total de columnas, cantidad de combinaciones realizadas.
 * @param NUM_BITS Número de bits de cada mintérmino.
 * @param[in] clasificacionGlobalMinterminos Estructura global con todos los mintérminos clasificados.
 * @return vector<mintermino> Lista de mintérminos no utilizados, los implicantes primos.
 */

vector<mintermino> impresionTablaMinterminosTotales(int NUMERO_COLUMNAS, int NUM_BITS, vector<vector<mintermino>>&clasificacionGlobalMinterminos){

    //construccion de la tabla, los datos de los if dependen del numero de datos, a su vez, almacenando los 
    //elementos que no hayan sido usados durante las combinaciones mediante una pila
    vector<mintermino> minterminosNoUsados;
    bool element;

    cout<<"\n====================================================================================================\n\n    Tabla de combinaciones\n"<<endl;
    for(int i=0; i<50; i++){
        
        element=false;

        for(int j=0; j<50; j++){
            if(i==0){
                if(j==0) cout<<setw(4)<<left<<""<<setw(20+NUM_BITS)<<left<<"Minterminos";
                else if(!clasificacionGlobalMinterminos[j].empty()){string combinacionN="Combinacion "+to_string(j); cout<<setw(20+NUM_BITS)<<left<<combinacionN;}
                continue;
            }
            if(clasificacionGlobalMinterminos[j].empty()) break;
            if(i-1>=clasificacionGlobalMinterminos[j].size()) continue;

            if(j==0) cout<<setw(4)<<left<<"";

            mintermino minterm=clasificacionGlobalMinterminos[j][i-1];
            string mparenthesis="";
            element=true;
            
            if(!minterm.uso) {mparenthesis.push_back('*'); minterminosNoUsados.push_back(minterm);}

            mparenthesis+="m("+minterm.estructuraMintermino+") -> "+minterm.formaBinaria;
            cout<<setw(20+NUM_BITS)<<left<<mparenthesis;
            
        }
        if(element || i==0) cout<<endl;
    }
    cout<<"\n    * : Elementos no utilizados durante las combinaciones\n\n===================================================================================================="<<endl;
    return minterminosNoUsados;
}

/**
 * @brief Imprime la tabla de cobertura de los mintérminos no utilizados.
 * 
 * Esta tabla muestra las combinaciones que están relacionadas con cada uno de los mintérminos originales, 
 * usando una 'X' para marcar las coincidencias. Al mismo tiempo, se genera una matriz que guarda esta información, 
 * la cual será utilizada más adelante para simplificar la función booleana.
 * 
 * @param[in] minterminosNoUsados Vector de mintérminos que no se usaron en las combinaciones anteriores.
 * @param[out] tablaExpresionesFinales Matriz de cobertura booleana: filas(implicantes), columnas(mintérminos).
 * @param[in] minterminos Vector con los mintérminos originales de entrada.
 */

void impresionTablaMinterminosFinal(vector<mintermino> &minterminosNoUsados, vector<vector<int>> &tablaExpresionesFinales, vector<int> &minterminos){

    const int NUMERO_MINTERMINOS=minterminos.size();
    const int NUM_MINTERMINOS_FINAL=minterminosNoUsados.size();
    
    //Impresion de la tabla final con los minterminos no utilizados de la forma vista en clase
    cout<<"\n    Tabla inicial formacion de minterminos no utilizados   \n"<<endl;

    //Formación del encabezado de la tabla (variable)
    for(int i=0; i<NUMERO_MINTERMINOS; i++){
        tablaExpresionesFinales[0][i]=minterminos[i];
    }

    //Construcción del encabezado de la tabla (imagen)
    for(int i=-1; i<=NUMERO_MINTERMINOS; i++){
        if(i==-1) {cout<<setw(4)<<left<<""<<setw(15)<<left<<"Mintermino"; continue;}
        if(i==NUMERO_MINTERMINOS) {cout<<setw(18)<<left<<"Expresion booleana"<<endl; continue;}
        cout<<setw(4)<<left<<minterminos[i];
    }

    for(int j=1; j<=NUM_MINTERMINOS_FINAL; j++){
        
        mintermino minterm=minterminosNoUsados[j-1];
        unordered_map<int,int> minterminosInt;

        string numStr="";
        for(int i=0; i<=minterm.estructuraMintermino.size(); i++){
            if(i==minterm.estructuraMintermino.size()){
                int numInt=stoi(numStr);
                minterminosInt[numInt]=1;
                continue;
            }
            if(minterm.estructuraMintermino[i]==','){
                int numInt=stoi(numStr);
                minterminosInt[numInt]=1;
                numStr="";
                continue;
            }
            numStr.push_back(minterm.estructuraMintermino[i]);
        }

        for(int i=-1; i<=NUMERO_MINTERMINOS; i++){
            if(i==-1){
                string mparenthesis="m("+minterm.estructuraMintermino+")";
                cout<<setw(4)<<left<<""<<setw(15)<<left<<mparenthesis;
                continue;
            }
            if(i==NUMERO_MINTERMINOS){
                cout<<setw(18)<<left<<minterm.expresionBooleana<<endl;
                continue;
            }

            //si tiene elementos se expresa como un 1, si está vacio se expresa como un 0
            if(minterminosInt[minterminos[i]]==1){
                cout<<setw(4)<<left<<"X";
                tablaExpresionesFinales[j][i]=1;
            }else {
                cout<<setw(4)<<left<<"";
                tablaExpresionesFinales[j][i]=0;
            }
        }
    } 
}

/**
 * @brief Al seleccionar los implicantes primos esenciales, produce la simplificación final.
 * 
 * Primero encuentra los mintérminos cubiertos por una sola fila que son los implicantes esenciales y 
 * utiliza un enfoque iterativo que selecciona los implicantes que cubren la mayor cantidad de mintérminos pendientes hasta completar la cobertura total.
 * Para obtener el conjunto mínimo de implicantes que cubren toda la función.
 * 
 * @param[in,out] tablaExpresionesFinales Matriz de cobertura booleana.
 * @param[in] NUMERO_MINTERMINOS Número total de mintérminos que deben ser cubiertos.
 * @param[in] minterminosNoUsados Vector con los implicantes candidatos.
 * @return std::vector<int> Índices de los implicantes seleccionados.
 */

vector<int> simplificacionTablaFinal(vector<vector<int>>&tablaExpresionesFinales, const int NUMERO_MINTERMINOS, vector<mintermino>&minterminosNoUsados){
    
    //Vector que nos indica los minterminos que aún no son expresados
    vector<bool> minterminosExpresados(NUMERO_MINTERMINOS, false);
    vector<int> indicesMinterminosMinimos;
    int numeroMinterminosExpresados=0;
    const int NUMERO_MINTERMINOS_FINALES=tablaExpresionesFinales.size();
    
    
    set<int> minterminosUnicos;
    //Descarte de los mintérminos únicos (solo son expresados por una expresion booleana)
    for(int i=0; i<NUMERO_MINTERMINOS; i++){
        
        int numXsEnColumna=0;
        int row=0;
        
        for(int j=1; j<NUMERO_MINTERMINOS_FINALES; j++){
            if(tablaExpresionesFinales[j][i]==1){
                numXsEnColumna++;
                row=j;
            }
        }
        
        if(numXsEnColumna==1){
            minterminosUnicos.insert(row);
        }
    }
    
    while(!minterminosUnicos.empty()){
        int row=*minterminosUnicos.begin();
        minterminosUnicos.erase(row);
        
        //almacenaje de los indices con los mintérminos escenciales
        indicesMinterminosMinimos.push_back(row-1);
        //Impresion datos actualizada
        numeroMinterminosExpresados+=actualizacionImpresionTabla(tablaExpresionesFinales, row, minterminosExpresados, minterminosNoUsados);
        
        if(numeroMinterminosExpresados==NUMERO_MINTERMINOS){
            return indicesMinterminosMinimos;
        }
    }


    //Descarte final realizado por cantidad máxima de elementos únicos por mintermino hasta cubrir todos los minterminos
    while(numeroMinterminosExpresados<NUMERO_MINTERMINOS){
        int rowMaxMinterminos=1, numMaxMinterminos=0;
        
        for(int i=1; i<tablaExpresionesFinales.size(); i++){
            
            int numMinterminosUnicos=0;

            for(int j=0; j<tablaExpresionesFinales[0].size(); j++){
                if(tablaExpresionesFinales[i][j]==1 && !minterminosExpresados[j]) numMinterminosUnicos++;
            }
            if(numMinterminosUnicos>numMaxMinterminos){
                numMaxMinterminos=numMinterminosUnicos;
                rowMaxMinterminos=i;
            }
        }

        indicesMinterminosMinimos.push_back(rowMaxMinterminos-1);
        numeroMinterminosExpresados+=actualizacionImpresionTabla(tablaExpresionesFinales, rowMaxMinterminos, minterminosExpresados, minterminosNoUsados);
    }
    return indicesMinterminosMinimos;
}

/**
 * @brief Actualiza la matriz de cobertura eliminando los mintérminos ya cubiertos por un implicante, e imprime la tabla actualizada con los cambios.
 * 
 * Los minterminos cubiertos por cada fila dada son descartados y marcadks como (`-1`). Los espacios representan no cobertura,mientras que X es cobertura. 
 * Finalmente `#` para celda descartada.
 * 
 * @param[in,out] tablaExpresionesFinales Matriz de cobertura actual.
 * @param[in] row Índice de la fila seleccionada para cubrir.
 * @param[in,out] minterminosExpresados Vector que indica qué mintérminos ya están cubiertos.
 * @param[in] minterminosNoUsados Vector de implicantes candidatos.
 * @return int Número de mintérminos cubiertos por esta fila.
 */
int actualizacionImpresionTabla(vector<vector<int>>&tablaExpresionesFinales, int row, vector<bool>&minterminosExpresados, vector<mintermino>&minterminosNoUsados){

    int totalMinterminosExpresados=0;
    // Recorrido de toda la fila, haciendo los descartes que serán expresados con un -1
    for(int i=0; i<tablaExpresionesFinales[row].size(); i++){
        
        if(tablaExpresionesFinales[row][i]==1){
            
            minterminosExpresados[i]=true;
            totalMinterminosExpresados++;
            
            //recorrido hacia arriba 
            int pointer=row;
            while(pointer>0){
                tablaExpresionesFinales[pointer][i]=-1;
                pointer--;
            }
            
            //recorrido hacia abajo
            pointer=row;
            while(pointer<tablaExpresionesFinales.size()){
                tablaExpresionesFinales[pointer][i]=-1;
                pointer++;
            }
        }
        tablaExpresionesFinales[row][i]=-1;
    }

    //impresion tabla
    cout<<"\n====================================================================================================    \n\n    Simplificacion fila "<<row<<"\n"<<endl;
    
    //Construcción del encabezado de la tabla (imagen)
    cout<<setw(4)<<left<<""<<setw(15)<<left<<"Mintermino";

    for(int i=0; i<tablaExpresionesFinales[0].size(); i++){
        cout<<setw(4)<<left<<tablaExpresionesFinales[0][i];
    }

    cout<<setw(18)<<left<<"Expresion booleana"<<endl;


    for(int j=1; j<tablaExpresionesFinales.size(); j++){

        string mparenthesis="m("+minterminosNoUsados[j-1].estructuraMintermino+")";
        cout<<setw(4)<<left<<""<<setw(15)<<left<<mparenthesis;

        for(int i=0; i<tablaExpresionesFinales[0].size(); i++){

            //Impresion de los caracteres dependiendo su naturaleza
            //1: Elemento con X
            //0: Elemento vacio
            //-1: Elemento descartado
            if(tablaExpresionesFinales[j][i]==-1){
                cout<<setw(4)<<left<<"#";
            }else if(tablaExpresionesFinales[j][i]==0){
                cout<<setw(4)<<left<<"";
            }else{
                cout<<setw(4)<<left<<"X";
            }
        }

        cout<<setw(18)<<left<<minterminosNoUsados[j-1].expresionBooleana<<endl;
    } 

    return totalMinterminosExpresados;
}







