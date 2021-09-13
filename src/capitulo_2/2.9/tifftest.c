#include <stdio.h>
#include "tiffio.h"

int main(int argc, char **argv){

    printf("%s\n", "el archivo actual en el libro se introduce con un args \npero para comodidad de la prueba forzamos a un path incluido dogecoin.tiff");

    TIFF * tiff;
    tiff = TIFFOpen("./src/capitulo_2/2.9/dogecoin.tiff", "r");
    
    if(tiff == NULL){
        printf("Error abriendo el archivo\n");
    }else{
        printf("Archivo abierto correctamente\n");
    }
    
    TIFFClose(tiff);
    return 0;
}