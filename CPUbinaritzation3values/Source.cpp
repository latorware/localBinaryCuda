#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <malloc.h>





using namespace std; 





//works correctly if the image has three channels
void printImage3Color(unsigned char* image, int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printf("(%d, %d, %d) ", image[(i * width * 3) + (j*3)], image[(i * width * 3) + (j * 3 + 1)], image[(i * width * 3) + (j * 3 + 2)]);
        }
        printf("En of line \n");
    }
}



int main(int argc, char** argv) {

    char *fileIN, *fileOUT;
    unsigned char *image;
    int width, height, pixelWidth; //meta info de la imagen
    int tamanyFinestraLLiscant; 

    // Ficheros de entrada y de salida 
    if (argc == 4) { fileIN = argv[1]; fileOUT = argv[2]; tamanyFinestraLLiscant = int(argv[3]); }
    else { printf("Usage: ./exe fileIN fileOUT\n"); exit(0); }


    //Reading image
    printf("Reading image...\n");
    image = stbi_load(fileIN, &width, &height, &pixelWidth, 0);
    if (!image) {
        fprintf(stderr, "Couldn't load image.\n");
        return (-1);
    }
    printf("Image Read. Width : %d, Height : %d, nComp: %d\n", width, height, pixelWidth);
    //printImage3Color(image, width, height);

    
    char* imageOUT = (char*)malloc(width * height * sizeof(char)*3); 
    int pixelWidthOUT = 1; 
    printf("RGB TO GRAYSCALE \n");
    for (int i = 0; i < width * height; i++) {
        imageOUT[i] = (((float)0.2989 * (float)image[i*3] + (float)0.5870 * (float)image[i*3 + 1] + (float)0.1140 * (float)image[i*3 + 2])); 
    }

    char* imageOUT = (char*)malloc(width * height * sizeof(char) * 3);

    printf("Escribiendo\n");
    //ESCRITURA DE LA IMAGEN EN SECUENCIAL
    stbi_write_png(fileOUT, width, height, pixelWidthOUT, imageOUT, 0);
    




}