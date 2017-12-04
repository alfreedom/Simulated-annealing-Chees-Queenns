/* 
 * File:   utils.h
 * Author: alfredo
 *
 * Created on 2 de marzo de 2015, 02:52 PM
 */

#ifndef UTILS_H
#define	UTILS_H

int isFormatDouble(char* str);
int isFormatInt(char* str);
void showHelp();

int isFormatDouble(char* str){
    
    int isPoint=0;
    
    if(*str == '-')
        return 0;
    
    while(*str){     
        
        if(isdigit(*str) || *str == '.'){
            
            if(*str=='.')
                if(!isPoint)
                    isPoint=1;
                else
                    return 0;
        }  
        else
            return 0;
        
        *str++;
    }
    
    return 1;
}
int isFormatInt(char* str){
   
    if(*str == '-')
        return 0;
    
    while(*str){        
        if(!isdigit(*str++))        
            return 0;
    }
    
    return 1;
}

void showHelp(){
    
    printf("\n\n    #####################################################\n");
    printf("    #######  ALGORITMO DE ENFRIAMIENTO SIMULADO  ########\n");
    printf("    ################### A Y U D A #######################\n\n");
    printf("    Programa para simular el arlgoritmo de Enfriamiento\n");
    printf("    simulado  (Simulated Anhealing)  con  un tablero de\n");
    printf("    ajedrez con N reynas. El programa da  la solución a\n");
    printf("    una  configuración aleatoria de N reinas en las que\n");
    printf("    las reinas no se atacan.\n\n");
    printf("    Uso:\n         ./reinas [-k]<nn> [-q]<nn> [-t]<nn> [-p]<nn> [-?/?]\n\n");
    printf("    Los parámetros \"-k\", \"-q\", \"-t\" y \"-p\" pueden ser opcionales.\n\n");
    printf("    Opciones:\n");
    printf("\n              -k:  Constante de enfriamiento K.");
    printf("\n                   Formato entero o flotante (N, N.N)\n");
    printf("\n              -p:  Probabilidad de error para mala configuración.");
    printf("\n                   Formato entero o flotante (N, N.N)\n");
    printf("\n              -t:  Temperatura Inicial.");
    printf("\n                   Formato entero o flotante (N, N.N)\n");
    printf("\n              -q:  Número de reinas en el tablero (4 a 32).");
    printf("\n                   Formato entero\n");
    printf("\n              -d:  Opción depuración. Muestra información detallada");
    printf("\n                   de la ejecución del programa.\n");
    printf("\n            -?/?:  Muestra este menú de ayuda.\n");
    printf("\n\n        Ejemplo de uso:");
    printf("\n                ./reinas -t 10000.0 -p 0.5 -k 5.0 -q 5\n\n");
    printf("\n     -------------------------------------------------");
    printf("\n           Escrito por: Alfredo Orozco de la Paz\n");
    printf("\n           Universidad Autónoma de San Luis Potosí");
    printf("\n              Área de Computación e Informática");
    printf("\n\n           Materia: Inteligencia Artificial");
    printf("\n           Profesor: José Ignacio Nuñes Varela");
    printf("\n     ------------------ Marzo del 2015 ---------------");
    printf("\n\n    ###################################################\n");

}

#endif	/* UTILS_H */

