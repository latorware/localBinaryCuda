#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <malloc.h>
#include <chrono>
using namespace std; 

//CLOCK SHIT
/*
chrono::steady_clock::time_point begin = chrono::steady_clock::now();
chrono::steady_clock::time_point end = chrono::steady_clock::now();

cout << "Time difference = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
cout << "Time difference = " << chrono::duration_cast<chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
cout << "Image Read in = " << (chrono::duration_cast<chrono::microseconds>(end - begin).count())/1000000.0 << "[seconds]" << std::endl;
*/





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


void RGBtoGRAYSCALE(unsigned char* image, int width, int height, char* fileOUT, chrono::steady_clock::time_point begin, chrono::steady_clock::time_point end)
{
    printf("RGB TO GRAYSCALE... \n");


    printf("ALLOCATING SPACE FOR NEW IMAGE... \n");
    begin = chrono::steady_clock::now();
    char* imageOUT = (char*)malloc(width * height * sizeof(char));
    end = chrono::steady_clock::now();
    cout << "ALLOCATED SPACE IN = " << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0 << "[seconds]" << std::endl;


    int pixelWidthOUT = 1;
    
    printf("CONVERTING TO GRAYSCALE... \n");
    begin = chrono::steady_clock::now();
    for (int i = 0; i < width * height; i++) {
        imageOUT[i] = (((float)0.2989 * (float)image[i * 3] + (float)0.5870 * (float)image[i * 3 + 1] + (float)0.1140 * (float)image[i * 3 + 2]));
    }
    end = chrono::steady_clock::now();
    cout << "CONVERTED TO GRAYSCALE IN = " << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0 << "[seconds]" << std::endl;

    printf("WRITING IMAGE... \n");
    begin = chrono::steady_clock::now();
    //ESCRITURA DE LA IMAGEN EN SECUENCIAL
    stbi_write_png(fileOUT, width, height, pixelWidthOUT, imageOUT, 0);
    end = chrono::steady_clock::now();
    cout << "IMAGE WRITTEN IN = " << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0 << "[seconds]" << std::endl;
}

void globalBinaritzation(unsigned char* image, int width, int height, char* fileOUT, chrono::steady_clock::time_point begin, chrono::steady_clock::time_point end, int threshold)
{
    printf("ALLOCATING SPACE FOR NEW IMAGE... \n");
    begin = chrono::steady_clock::now();
    char* imageOUT = (char*)malloc(width * height * sizeof(char));
    end = chrono::steady_clock::now();
    cout << "ALLOCATED SPACE IN = " << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0 << "[seconds]" << std::endl;


    int pixelWidthOUT = 1;

    printf("CONVERTING TO GRAYSCALE and BINARITZATING (at the same time)... \n");
    begin = chrono::steady_clock::now();
    for (int i = 0; i < width * height; i++) {
        float grayscaleValue = (((float)0.2989 * (float)image[i * 3] + (float)0.5870 * (float)image[i * 3 + 1] + (float)0.1140 * (float)image[i * 3 + 2]));
        if (grayscaleValue <= threshold)
        {
            imageOUT[i] = float(0.0); 
        }
        else
        {
            imageOUT[i] = float(255.0); 
        }

    }
    end = chrono::steady_clock::now();
    cout << "CONVERTED TO GRAYSCALE AND BINARITZATED in = " << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0 << "[seconds]" << std::endl;


    printf("WRITING IMAGE... \n");
    begin = chrono::steady_clock::now();
    //ESCRITURA DE LA IMAGEN EN SECUENCIAL
    stbi_write_png(fileOUT, width, height, pixelWidthOUT, imageOUT, 0);
    end = chrono::steady_clock::now();
    cout << "IMAGE WRITTEN IN = " << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0 << "[seconds]" << std::endl;
}


void meanBinaritzation(unsigned char* image, int width, int height, char* fileOUT, chrono::steady_clock::time_point begin, chrono::steady_clock::time_point end, int tamanyFinestra)
{
    printf("ALLOCATING SPACE FOR NEW IMAGE... \n");
    begin = chrono::steady_clock::now();
    char* imageOUT = (char*)malloc(width * height * sizeof(char));
    char* imageFinalOUT = (char*)malloc(width * height * sizeof(char));


    end = chrono::steady_clock::now();
    cout << "ALLOCATED SPACE IN = " << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0 << "[seconds]" << std::endl;

    printf("CONVERTING TO GRAYSCALE... \n");
    begin = chrono::steady_clock::now();
    for (int i = 0; i < width * height; i++) {
        imageOUT[i] = (((float)0.2989 * (float)image[i * 3] + (float)0.5870 * (float)image[i * 3 + 1] + (float)0.1140 * (float)image[i * 3 + 2]));
    }
    end = chrono::steady_clock::now();
    cout << "CONVERTED TO GRAYSCALE IN = " << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0 << "[seconds]" << std::endl;



    printf("BINARITZATING... \n");
    begin = chrono::steady_clock::now();
    for (int i = 0; i < width * height; i++) {
        int lenght = 0; int mean = 0;

        int fila = i / width;
        //int columna = i % width;
        for (int j = 0; j < tamanyFinestra; j++) {
            if ((i + j) / width == fila) {

                for (int k = 0; k < tamanyFinestra; k++) {
                    if (((i+j)+k*width) / width < height) {
                        lenght++;
                        mean += imageOUT[(i + j) + k * width];
                    }

                    if ((((i + j) - (k * width)) / (width*1.0)) >= 0.0 ) {
                        lenght++;
                        mean += imageOUT[(i + j) - (k * width)];
                    }
                }


            }

            if (((i - j) / width == fila) && (i-j>=0)) {

                for (int k = 0; k < tamanyFinestra; k++) {
                    if (((i - j) + k * width) / width < height) {
                        lenght++;
                        mean += imageOUT[(i - j) + k * width];
                    }

                    if ((((i - j) - (k * width)) / (width * 1.0)) >= 0.0) {
                        lenght++;
                        mean += imageOUT[(i - j) - (k * width)];
                    }
                }

            }


        }



        mean = mean / lenght;
        if (imageOUT[i] <= mean) {
            imageFinalOUT[i] = 0;
        }
        else {
            imageFinalOUT[i] = 255;

        }

      


    }
    end = chrono::steady_clock::now();
    cout << "BINARITZATED in = " << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0 << "[seconds]" << std::endl;


    int pixelWidthOUT = 1;

    printf("WRITING IMAGE... \n");
    begin = chrono::steady_clock::now();
    //ESCRITURA DE LA IMAGEN EN SECUENCIAL
    stbi_write_png(fileOUT, width, height, pixelWidthOUT, imageFinalOUT, 0);
    end = chrono::steady_clock::now();
    cout << "IMAGE WRITTEN IN = " << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0 << "[seconds]" << std::endl;
}

int main(int argc, char** argv) {

    char *fileIN, *fileOUT;
    unsigned char *image;
    int width, height, pixelWidth; //meta info de la imagen
    int tamanyFinestraLLiscant; 

    // Ficheros de entrada y de salida 
    if (argc == 3) { fileIN = argv[1]; fileOUT = argv[2]; }
    else { printf("Usage: ./exe fileIN fileOUT\n"); exit(0); }


    //Reading image
    printf("Reading image...\n");
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    image = stbi_load(fileIN, &width, &height, &pixelWidth, 0);
    if (!image) {
        fprintf(stderr, "Couldn't load image.\n");
        return (-1);
    }
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    printf("Image Read. Width : %d, Height : %d, nComp: %d\n", width, height, pixelWidth);
    cout << "Image Read in = " << (chrono::duration_cast<chrono::microseconds>(end - begin).count())/1000000.0 << "[seconds]" << std::endl;


    //What do you want to do
    cout << "What do you want to do? (0) Print image as matrix of numbers.    (1)RGB to GRASCALE     (2)GLOBAL BINARITZATION \n (3)MEAN local binaritzation     (4)NIBLACK'S binaritzation     (5)SAUVOLA'S binaritzation  \n (6)BERNSEN'S binaritzation     (7)0TSU'S binaritzation" << endl; 
    int option; 
    cin >> option; 

    if (option == 0)
    {
        printImage3Color(image, width, height); 
    }
    else if (option == 1)
    {
        RGBtoGRAYSCALE(image, width, height, fileOUT, begin, end); 
    }
    else if (option == 2)
    {
        cout << "GLOBAL BINARITZATION WAS PICKED" << endl; 
        cout << "Introduce the threshold as a 0-255 integer:" << endl; 
        int threshold; 
        cin >> threshold; 
        globalBinaritzation(image, width, height, fileOUT, begin, end, threshold); 

    }
    else if (option == 3)
    {
        cout << "MEAN local binaritzation WAS PICKED" << endl;
        cout << "Introduce the window size as an integer (it has to be smaller than the width and height of the image):" << endl;
        int tamanyFinestra;
        cin >> tamanyFinestra;
        meanBinaritzation(image, width, height, fileOUT, begin, end, tamanyFinestra);


    }
    else if (option == 4)
    {

    }
    else if (option == 5)
    {

    }
    else if (option == 6)
    {

    }
    else if (option == 7)
    {

    }
    




}