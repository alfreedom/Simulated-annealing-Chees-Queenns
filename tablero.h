/************************************************************************
 *
 *      Archivo:  tablero.h
 *        Autor:  Alfredo Orozco de la Paz
 *        Fecha:  25 de Febrero del 2015
 *   Compilador:  GNU GCC++ 
 *
 *  Descripción:
 * 
 *      Define la estructura y las operaciones que se pueden realizar 
 *      sobre  un  tablero de ajedrez para el problema de las REYNAS.
 * 
 *      Las reynas se guardan en un arreglo de 8 columnas (tablero),  en 
 *      donde cada columna representa  una  columna del tablero,  y cada 
 *      bit de ese columna representa un renglón del tablero. Sólo un bit 
 *      de cada columna  está a 1. El bit puesto en  1  de la columna 
 *      indica en que renglón esta la reyna.
 * 
 *      EJ:
 *                        Renglón
 *               1   2   3   4   5   6   7   8
 *             ---------------------------------
 *          1  | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
 *             ---------------------------------
 *          2  | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 |
 *       c     ---------------------------------
 *       o  3  | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 
 *       l     ---------------------------------
 *       u  4  | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 |
 *       m     ---------------------------------
 *       n  5  | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
 *       a     ---------------------------------
 *          6  | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 |
 *             ---------------------------------
 *          7  | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 |
 *             ---------------------------------
 *          8  | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
 *             ---------------------------------
 * 
 *      Se  implementan  métodos  para  crear  un  tablero  aleatorio 
 *      (configuración inicial), para hacer  un movimiento  de alguna
 *      pieza  (mutación),  para  obtener  la  energía de  un tablero 
 *      (número de pares de reynas que no se atacan) y para  imprimir
 *      el tablero en consola.
 * 
 ************************************************************************
 *    Copyright:
 *
 *        Copyrigth© 2014
 *        Alfredo Orozco
 *        e-mail:  alfredoopa@gmail.com
 *
 *     Licencia:
 *
 *        Este programa es software libre;  usted lo puede distribuir y/o
 *        modificar bajo los terminos   de la General Public License GNU, 
 *        según es publicada en la  Free  Software  Foundation;  ya se la 
 *        versión 2 de la Licencia, o (a su elección) una versión poster-
 *        ior.
 *
 *        Este programa se distribuye con la esperanza  de que sea  útil, 
 *        pero SIN NINGUNA GARANTÍA, incluso sin la garantía implícita de
 *        COMERCIALIZACIÓN  o  IDONEIDAD  PARA  UN  PROPÓSITO PARTICULAR. 
 *        Consulte la Licencia Pública General de GNU para más detalles.
 *
 *        Debería haber recibido una copia de la Licencia Pública General 
 *        de GNU junto con este programa; si no, visite:
 *                                          http://www.gnu.org/licenses.
 * 
 ************************************************************************/

#ifndef TABLERO_H
#define	TABLERO_H

#include <stdint.h>
#include <iostream>
using namespace std;

#define MIN_REYNAS  4
#define MAX_REYNAS  32
#define QUEEN_SYMBOL "■"

typedef uint8_t byte;
typedef uint32_t columna;

class tablero {
public:
    
    tablero(int numReinas=MIN_REYNAS);
    tablero(const tablero& orig);
    virtual ~tablero();
    
    int getEnergia();
    columna* getArrayTablero();
    int comparaEnergias(tablero& tab);
    int getDeltaEnergias(tablero& tab);
    
    void imprimeTablero(ostream& mycout=cout); 
    
    void revuelveTablero();
    void mueveReinaAleatoria(uint8_t col=-1);

    int getEnergiaMax();
    int getNumReinas();
    
    tablero& operator =(const tablero& tab);
    
private:
    int _isAtack(columna numcol_1, columna numcol_2);
    byte _nReynas;
    int _energiaMax;
    columna* _tablero;
    
};

#endif	/* TABLERO_H */

