#include <stdio.h>
#include <tiffio.h>

int main(int argc, char **argv){
    TIFF * tiff;
    tiff = TIFFOpen(argv[1], "r");
    
    if(tiff == NULL){
        printf("Error abriendo el archivo\n");
    }else{
        printf("Archivo abierto correctamente\n");
    }
    
    TIFFClose(tiff);
    return 0;
}