#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"





using namespace std; 
int main(int argc, char** argv) {

    char *fileIN, *fileOUT;
    unsigned char *image;
    int width, height, pixelWidth; //meta info de la imagen

    // Ficheros de entrada y de salida 
    if (argc == 3) { fileIN = argv[1]; fileOUT = argv[2]; }
    else { printf("Usage: ./exe fileIN fileOUT\n"); exit(0); }


    //Reading image
    printf("Reading image...\n");
    image = stbi_load(fileIN, &width, &height, &pixelWidth, 0);
    if (!image) {
        fprintf(stderr, "Couldn't load image.\n");
        return (-1);
    }
    printf("Image Read. Width : %d, Height : %d, nComp: %d\n", width, height, pixelWidth);


}