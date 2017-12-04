/************************************************************************
 *
 *      Archivo:  tablero.cpp
 *        Autor:  Alfredo Orozco de la Paz
 *        Fecha:  25 de Febrero del 2015
 *   Compilador:  GNU GCC++ 
 *
 *  Descripción:
 * 
 *      Implementación de los métodos de la clase "tablero"      
 *      
 ************************************************************************/
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "tablero.h"



/**
 * Constructor de la clase tablero.
 * 
 * Inicializa un tablero de tamaño numReynas con una
 * posición inicial y calcula la máxima energía del
 * tablero.
 * 
 * @param numReynas 
 *          Numero de reinas del tablero.
 * 
 */
tablero::tablero(int numReinas) {
    
    _energiaMax=0;
        
    if(numReinas>MAX_REYNAS)
        _nReynas=MAX_REYNAS;
    else
    if(numReinas<MIN_REYNAS)
        _nReynas=MIN_REYNAS;
    else        
        _nReynas=numReinas;
    
    _tablero = new columna[_nReynas];
    
    for(byte i=0; i<_nReynas;i++){
        _tablero[i] = 0x80000000;
        _energiaMax += i;
    }
    
    srand(time(NULL));
}

/**
 * 
 * @param orig
 */
tablero::tablero(const tablero& orig) {
}

/**
 * Destructor de la clase tablero.
 * 
 * Libera la memoria reservada para el tablero.
 */
tablero::~tablero() {
    
    delete _tablero;
}

/**
 * Operador =
 * 
 * Copia el tablero "tab" en el tablero de esta clase.
 * 
 * @param tab
 *          Tablero a asignar.
 * @return 
 *          Devuelve el tablero "this" con el mismo contenido
 *          que "tab".    
 * 
 */
tablero& tablero::operator =(const tablero& tab){
    
    if(this != &tab)
    {
        this->_nReynas=tab._nReynas;
        delete (this->_tablero);
        _energiaMax=0;
        this->_tablero=new columna[_nReynas];
        for(int i=0;i<_nReynas;i++){
            this->_tablero[i]=tab._tablero[i];
            _energiaMax += i;
        }
    }
    return *this;
}

/**
 * revuelveTablero()
 * 
 * Revuelve el tablero moviendo todas las reinas
 * a una posición aleatoria.
 */
void tablero::revuelveTablero(){
   
    for(byte i=0; i<_nReynas;i++)
        mueveReinaAleatoria(i);
}

/**
 * mueveReinaAleatoria(uint8_t col)
 * 
 * Mueve una reina de una columna a otra posición aleatoria.
 * 
 * @param col
 *          Columna de la que se desea mover la reina.
 *          si no se indica la columna de la que se moverá la
 *          reina, seleccina una culmna aleatoria a mover.
 */
void tablero::mueveReinaAleatoria(uint8_t col){
    
    if(col<0 || col >=_nReynas)
        col=rand()%_nReynas;
    
    columna nueva=_tablero[col];
    while(nueva == _tablero[col])
        nueva = 0x80000000 >> rand()%_nReynas;
    _tablero[col]=nueva;
    
}

/**
 * comparaEnergias(tablero& tab)
 * 
 * Compara la energía de este tablero con la de otro tablero.
 * 
 * @param tab
 *          Tablero con el que se va a compara la energía.
 * @return 
 *          Devuelve 1 si la energía de este tablero es mayor
 *          que la de "tab", -1 si es menor y 0 si las energas
 *          son iguales.
 */
int tablero::comparaEnergias(tablero& tab){
    
    int resultado;    
    
    resultado=getDeltaEnergias(tab);
    
    if(resultado>0)
        return 1;
    else
        if(resultado<0)
            return -1;
    
    return resultado;    
}

/**
 * imprimeTablero(ostream& myCout)
 * 
 * Imprime el tablero el la salida especificada.
 * 
 * @param mycout
 *          Stream de salida.
 */
void tablero::imprimeTablero(ostream& mycout){
    int c = 1;    
   
    mycout << "\n\n   ";
    for(int i=0; i<_nReynas;i++)
    {
        if(c<10)
            mycout << "  ";
        else
            mycout << " ";
        cout<< c++<<" ";
    }

    c='A';
    mycout <<endl<< "   ┌";
    for(int i=0; i<_nReynas;i++)
    {
        mycout << "───";
        if(i<_nReynas-1)
            mycout <<"┬";
    }
    mycout << "┐"<< endl;
    
    for(byte j=0; j<_nReynas;j++)
    {
        
        mycout << " "<<(char)c++;
        mycout<< " │ ";
        for(byte i=0; i<_nReynas; i++)
        {
            mycout << ((_tablero[i] & (0x80000000>>j))?QUEEN_SYMBOL:" ");
            if(i<_nReynas-1)
                mycout << " │ ";

        }
        mycout << " │" << endl;
        
        if(j<_nReynas-1){
            mycout << "   ├";
            for(int i=0; i<_nReynas;i++)
            {
                mycout << "───";
                if(i<_nReynas-1)
                    mycout <<"┼";
            }
            mycout << "┤"<< endl;
        }
        

    }
    mycout << "   └";
    for(int i=0; i<_nReynas;i++)
    {
        mycout << "───";
        if(i<_nReynas-1)
            mycout <<"┴";
    }
    mycout << "┘"<< endl;
    
    
}

/**
 * getEnergiaMax()
 * 
 * Devuelve la energía máxima del tablero.
 * 
 * @return 
 *          Energía máxima del tablero.
 */
int tablero::getEnergiaMax(){
    return _energiaMax;
}

/**
 * getEnergia()
 * 
 * Devuelve la energía del tablero actual.
 * 
 * @return 
 *          Energía del tablero actual.
 */
int tablero::getEnergia(){
    
    int energia=_energiaMax;
    
    for(columna i=0; i<_nReynas-1; i++){
        for(int j=i+1; j<_nReynas; j++)   
            if(_isAtack(i,j)==1)
                energia--;
    } 
    return energia;
}

/**
 * getDeltaEnergías(tablero& tab)
 * 
 * Devuelve la diferencia de energías entre 2 tableros.
 * Hace la resta de la energía de este tablero con la
 * del tablero especificado por "tab"
 * 
 * @param tab
 *          Tablero con el que se calcula la diferencia.
 * @return 
 *          Devuelve la diferencia de energías.
 */
int tablero::getDeltaEnergias(tablero& tab){
    return this->getEnergia()-tab.getEnergia();
}

/**
 * getArrayTablero()
 * 
 * Regresa una copia del arreglo de bytes con los que se representa
 * el tablero.
 * 
 * @return 
 *          Copia del arreglo de bytes del tablero.
 */
columna* tablero::getArrayTablero(){   
    columna* tNuevo= new columna[_nReynas]; 
    
    memcpy(tNuevo,_tablero,sizeof(columna)*_nReynas);    
    return tNuevo;
}

/**
 * getNumReinas()
 * 
 * Regresa el número de reinas que componen el tablero.
 * 
 * @return 
 *          Número de reinas del tablero.
 */
int tablero::getNumReinas(){
    return _nReynas;
}

/**
 * _isAtack(columna numcol_1, columna numcol_2)
 * 
 * Checa si 2 reinas en 2 columnas del tablero se atacan.
 * 
 * @param numcol_1
 *          Número de columna de la reina 1 a checar.
 * @param numcol_2
 *          Número de la columna de la reina 2 a checar.
 * @return 
 *          Regresa 1 si las reinas se atacan, de lo contrario 0.
 */
int tablero::_isAtack(columna numcol_1, columna numcol_2){    
    int desp;
    
    if(numcol_1==numcol_2)
        return 1;
    else 
        if( numcol_1 < 0 || numcol_1 > _nReynas-1 || numcol_2 < 0 || numcol_2 > _nReynas-1)
        return -1;
        
    desp=abs(numcol_2-numcol_1);
    
    if( (_tablero[numcol_1] & _tablero[numcol_2]) || (_tablero[numcol_1]<<desp & _tablero[numcol_2]) ||
            (_tablero[numcol_1]>>desp & _tablero[numcol_2]))
        return 1;
    
    return 0;
    
}
