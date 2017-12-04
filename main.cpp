/* 
 * File:   main.cpp
 * Author: alfredo
 *
 * Created on 25 de febrero de 2015, 07:44 PM
 */

#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>

#include "tablero.h"
#include "utils.h"

using namespace std;

float temp = 100000.0;
float kpasos = 5.0;
float probabilidad = 0.5;
int numReinas = 4;
int debug=0;

#define CMD_TEMPERATURA     "-t"
#define CMD_KPASOS          "-k"
#define CMD_PROBABILIDAD    "-p"
#define CMD_NUM_REINAS      "-q"
#define CMD_HELP1           "?"
#define CMD_HELP2           "-?"
#define CMD_DEBUG           "-d"



void anealing(int nReinas);

int main(int argc, char** argv) {   
    
    int hasError=0;
   
    if(argc>1 && (!strcmp(CMD_HELP1, argv[1]) || !strcmp(CMD_HELP2, argv[1])))
    {
            showHelp();
            exit(0);
    }
    
    for(int i=1; argc>1, i< argc;i++){       
        
        if(!strcmp(CMD_TEMPERATURA, argv[i])){
            if(i+1 < argc){
                i++;
                if(isFormatDouble(argv[i])){
                    temp = atof(argv[i]);
                }
                else
                    printf("%d - #ERROR: formato de temperatura T erroneo.\n",hasError++);
            }
            else
                printf("%d - #ERROR: no se ingresó el valor de la temperatura T.\n",hasError++);
        }
        else
        if(!strcmp(CMD_KPASOS, argv[i])){

            if(i+1 < argc){
                i++;
                if(isFormatDouble(argv[i])){
                    kpasos = atof(argv[i]);
                }
                else
                    printf("%d - #ERROR: formato de constante K erroneo.\n",hasError++);
            }
            else
                printf("%d - #ERROR: no se ingresó el valor de la constante K.\n",hasError++);
        }
        else
        if(!strcmp(CMD_PROBABILIDAD, argv[i])){

            if(i+1 < argc){
                i++;
                if(isFormatDouble(argv[i])){
                    probabilidad = atof(argv[i]);
                }
                else
                    printf("%d - #ERROR: formato de probabilidad P erroneo.\n",hasError++);
            }
            else
                printf("%d - #ERROR: no se ingresó el valor de la robabilidad P.\n",hasError++);
        }
        else
        if(!strcmp(CMD_NUM_REINAS, argv[i])){

            if(i+1 < argc){
                i++;
                if(isFormatInt(argv[i])){
                    numReinas = atoi(argv[i]);
                }
                else
                    printf("%d - #ERROR: formato de numero de reinas erroneo.\n",hasError++);
            }
            else
                printf("%d - #ERROR: no se ingresó el número de reinas.\n",hasError++);
        }
        else
        if(!strcmp(CMD_DEBUG, argv[i]))
            debug=1;
        else
            if(!strcmp(CMD_HELP1, argv[i]) || !strcmp(CMD_HELP2, argv[i]))
            {}
        else
        {
            printf("%d - #ERROR: No se reconoce el comando \"%s\".\n",hasError++,argv[i]);
            exit(1);
        }
    }
    
    if(!hasError)
    {
        if(debug){
            printf("\n\n ************************************************");
            printf("\n *** BÚSQUEDA ÓPTIMA CON ENFRIAMENTO SIMULADO ***");
            printf("\n ************************************************");
            printf("\n * Opciones del algoritmo: \n");
            printf(" *          Número de reinas: %d\n", numReinas);
            printf(" *               Temperatura: %.2f\n", temp);
            printf(" *               Constante K: %.2f\n", kpasos);
            printf(" *     Probabilidad de error: %.2f\n", probabilidad);
            printf(" *        Muestra depuración: %s\n",debug?"SI":"NO");
            printf(" ************************************************\n\n");

        }

        anealing(numReinas);
        return 0;
    }
    
    return 1;
    
}

void anealing(int nReinas)
{
    tablero tactual(nReinas),tviejo,tmejor;
    int aceptadas=0,totales=0;
    float prob;
    
    tactual.revuelveTablero();
    printf("Configuración Inicial:\n");
    printf("Energía: %d",tactual.getEnergia());
    tactual.imprimeTablero();
    tmejor=tactual;
    while(temp>0)
    {   
        // Incrementa el numero de configuraciones generadas.
        totales++;
        
        // Guarda la configuracion actual.
        tviejo=tactual;
        
        // Genera una configuración aleatorio nueva.
        tactual.mueveReinaAleatoria();
        
        // Obtiene la diferencia de energia de la tabla nueva respecto
        // a la vieja.
        int deltaene=tactual.getDeltaEnergias(tviejo);
        
        // Si el delta es positivo (deltaene > 0) significa que
        // la nueva configuración es mejor y se acepta como la
        // actual.
        if(deltaene > 0)
        {
            // Incrementa el número de configuraciones aceptadas.
            aceptadas++;
            if(debug)
            {
                printf("\nConfiguración aceptada #%d de %d",aceptadas,totales);
                tactual.imprimeTablero(); 
            }
            
            // Si el actual es mejor que el "mejor",
            // hace el actual como el mejor.
            if(tactual.getDeltaEnergias(tmejor)>0)
                tmejor=tactual;
            
            // Si la mejor configuración tiene la máxima energía del
            // tablero (ninguna reina se ataca), entonces se encontró
            // la solución.
            if(tmejor.getEnergia() == tmejor.getEnergiaMax())
                break;
            
        }
        else            
        if(deltaene < 0)// Si el delta es negativo.
        {
            prob=exp(deltaene/temp);
            if(prob>probabilidad)
                tactual = tviejo;
        }
        temp = (temp/kpasos)* kpasos-1;
    }
    
    printf("\n\n ************************************************");
    printf("\n *********** RESULTADOS DEL ALGORITMO ***********");
    printf("\n ************************************************\n");
    printf(" *    Configuraciones totales: %d\n",totales);
    printf(" *  Configuraciones aceptadas: %d\n",aceptadas);        
    printf(" *             Energia máxima: %d\n",tmejor.getEnergiaMax());
    printf(" *              Mejor Energía: %d\n",tmejor.getEnergia());
    printf(" *        Mejor Configuración:");
    tmejor.imprimeTablero();
    printf("\n ************************************************\n\n");


}

