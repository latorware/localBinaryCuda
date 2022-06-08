#include "processor.h"

//#define NICKGPU_IMPLEMENTATION
//#include "NickGPU.cuh"
//#include "NickGPU.cu"


#define STB_IMAGE_IMPLEMENTATION
#include "./Lib/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./Lib/stb_image_write.h"

#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <format>


//extern "C" void wrapper(QTextBrowser * outputDisplay);
extern "C" string NICKGPUMethod1(const float* grayscaledImage, int tamanyFinestra, float k, int width, int height, QTextBrowser * outputDisplay, string fileOUTGPUMETHOD1NICK);




processor::processor(QTextBrowser* outputDisplayy)
{
	//imageLoaded = false; 

	outputDisplay = outputDisplayy; 
}


int processor::getWidth()
{
	return width; 
}

int processor::getHeight()
{
	return height;
}



int processor::ReadFile(string imagePath)
{
	
	outputDisplay->append("Reading image..."); 
	
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();
	
	image = stbi_load(imagePath.c_str(), &width, &height, &pixelWidth, 0);
	
	if (!image) {
		outputDisplay->append("Couldn't load image");
		return (-1);
	}
	chrono::steady_clock::time_point end = chrono::steady_clock::now();
	outputDisplay->append(QString::fromStdString(string(std::format("Image Read in the processor. Width : {}, Height : {}, nComp: {}", width, height, pixelWidth))));
	outputDisplay->append(QString::fromStdString(string(std::format("Image Read in the processor in = {} [seconds]", (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0))));

	size_t lastindex = imagePath.find_last_of(".");
	string fileOUT = (imagePath.substr(0, lastindex)); 
	fileOUTGRAYSCALED = fileOUT + "GRAYSCALED.png";
	fileOUTGLOBALBINARITZATION = fileOUT + "GLOBALBINARIZED.png";
	fileOUTCPUNICK = fileOUT + "NICKCPUBINARITZATED.png";
	fileOUTGPUMETHOD1NICK = fileOUT + "NICKGPUMETHOD1BINARITZATED.png";
	fileOUTGPUMETHOD2NICK = fileOUT + "NICKGPUMETHOD2BINARITZATED.png";
	fileOUTGPUMETHOD3NICK = fileOUT + "NICKGPUMETHOD3BINARITZATED.png";
	
	return 0;

}
/*
void processor::printImage3Color()
{
}
*/
string processor::RGBtoGRAYSCALE()
{
	outputDisplay->append("RGB TO GRAYSCALE...");

	outputDisplay->append("ALLOCATING SPACE FOR NEW IMAGE...");
	begin = chrono::steady_clock::now();
	unsigned char* imageOUT = (unsigned char*)malloc(width * height * sizeof(unsigned char));
	end = chrono::steady_clock::now();
	outputDisplay->append(QString::fromStdString(string(std::format("ALLOCATED SPACE IN = {} [seconds]", (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0))));

	int pixelWidthOUT = 1;


	outputDisplay->append("CONVERTING TO GRAYSCALE...");
	begin = chrono::steady_clock::now();
	for (int i = 0; i < width * height; i++) {
		imageOUT[i] = (((float)0.2989 * (float)image[i * 3] + (float)0.5870 * (float)image[i * 3 + 1] + (float)0.1140 * (float)image[i * 3 + 2]));
	}
	end = chrono::steady_clock::now();
	outputDisplay->append(QString::fromStdString(string(std::format("CONVERTED TO GRAYSCALE IN = {} [seconds]", (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0))));


	outputDisplay->append("WRITING IMAGE...");
	begin = chrono::steady_clock::now();
	//ESCRITURA DE LA IMAGEN EN SECUENCIAL
	stbi_write_png(fileOUTGRAYSCALED.c_str(), width, height, pixelWidthOUT, imageOUT, 0);
	end = chrono::steady_clock::now();
	outputDisplay->append(QString::fromStdString(string(std::format("IMAGE WRITTEN IN = {} [seconds]", (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0))));
	outputDisplay->append(QString::fromStdString(string(std::format("Grayscaled image saved in: {}", fileOUTGRAYSCALED))));
	free(imageOUT); 
	return fileOUTGRAYSCALED;

}

string processor::globalBinaritzation(int threshold)
{
	outputDisplay->append("GLOBAL BINARITZATION...");
	outputDisplay->append(QString::fromStdString(string(std::format("threshold = {}", threshold))));


	outputDisplay->append("ALLOCATING SPACE FOR NEW IMAGE...");
	begin = chrono::steady_clock::now();
	unsigned char* imageOUT = (unsigned char*)malloc(width * height * sizeof(unsigned char));
	end = chrono::steady_clock::now();
	outputDisplay->append(QString::fromStdString(string(std::format("ALLOCATED SPACE IN = {} [seconds]", (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0))));


	int pixelWidthOUT = 1;

	outputDisplay->append("CONVERTING TO GRAYSCALE and BINARITZATING (at the same time)...");
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
	outputDisplay->append(QString::fromStdString(string(std::format("CONVERTED TO GRAYSCALE AND BINARITZATED IN = {} [seconds]", (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0))));


	outputDisplay->append("WRITING IMAGE...");
	begin = chrono::steady_clock::now();
	//ESCRITURA DE LA IMAGEN EN SECUENCIAL
	stbi_write_png(fileOUTGLOBALBINARITZATION.c_str(), width, height, pixelWidthOUT, imageOUT, 0);
	end = chrono::steady_clock::now();
	outputDisplay->append(QString::fromStdString(string(std::format("IMAGE WRITTEN IN = {} [seconds]", (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0))));
	outputDisplay->append(QString::fromStdString(string(std::format("Globally Binarized image saved in: {}", fileOUTGLOBALBINARITZATION))));
	free(imageOUT);
	return fileOUTGLOBALBINARITZATION;
}


string processor::NICKBinaritzationCPU(int tamanyFinestra, float k)
{
	outputDisplay->append("NICK CPU LOCAL BINARITZATION...");
	outputDisplay->append(QString::fromStdString(string(std::format("windowSize = {} x {}", tamanyFinestra, tamanyFinestra))));
	outputDisplay->append(QString::fromStdString(string(std::format("k = {}", k))));
	outputDisplay->append("ALLOCATING SPACE FOR NEW IMAGE...");
	begin = chrono::steady_clock::now();
	unsigned char* imageOUT = (unsigned char*)malloc(width * height * sizeof(unsigned char));
	unsigned char* imageFinalOUT = (unsigned char*)malloc(width * height * sizeof(unsigned char));


	end = chrono::steady_clock::now();
	outputDisplay->append(QString::fromStdString(string(std::format("ALLOCATED SPACE IN = {} [seconds]", (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0))));

	outputDisplay->append("CONVERTING TO GRAYSCALE...");
	begin = chrono::steady_clock::now();
	for (int i = 0; i < width * height; i++) {
		imageOUT[i] = (((float)0.2989 * (float)image[i * 3] + (float)0.5870 * (float)image[i * 3 + 1] + (float)0.1140 * (float)image[i * 3 + 2]));
		//cout << +imageOUT[i] << "      " << (((float)0.2989 * (float)image[i * 3] + (float)0.5870 * (float)image[i * 3 + 1] + (float)0.1140 * (float)image[i * 3 + 2])) << endl; 
	}
	end = chrono::steady_clock::now();
	outputDisplay->append(QString::fromStdString(string(std::format("CONVERTED TO GRAYSCALE IN = {} [seconds]", (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0))));



	outputDisplay->append("BINARITZATING...");
	begin = chrono::steady_clock::now();
	tamanyFinestra = tamanyFinestra / 2;
	for (int i = 0; i < width * height; i++) {
		int pixelsInWindow = 0; int mean = 0; int sumSquareIntensities = 0; int temp;
		float threshold;

		int fila = i / width;
		//int columna = i % width;
		for (int j = 0; j < tamanyFinestra; j++) {
			if ((i + j) / width == fila) {

				for (int k = 0; k < tamanyFinestra; k++) {
					if (((i + j) + k * width) / width < height) {
						pixelsInWindow++;
						temp = imageOUT[(i + j) + k * width];
						mean += temp;
						sumSquareIntensities += temp * temp;
					}

					if ((((i + j) - (k * width)) / (width * 1.0)) >= 0.0) {
						pixelsInWindow++;
						temp = imageOUT[(i + j) - (k * width)];
						mean += temp;
						sumSquareIntensities += temp * temp;
					}
				}


			}

			if (((i - j) / width == fila) && (i - j >= 0)) {

				for (int k = 0; k < tamanyFinestra; k++) {
					if (((i - j) + k * width) / width < height) {
						pixelsInWindow++;
						temp = imageOUT[(i - j) + k * width];
						mean += temp;
						sumSquareIntensities += temp * temp;
					}

					if ((((i - j) - (k * width)) / (width * 1.0)) >= 0.0) {
						pixelsInWindow++;
						temp = imageOUT[(i - j) - (k * width)];
						mean += temp;
						sumSquareIntensities += temp * temp;
					}
				}

			}


		}

		//cout << mean << endl; 
		//printf("%d \n", mean);
		mean = mean / pixelsInWindow;
		//cout << pixelsInWindow << endl; 
		threshold = (mean)+((k) * (sqrt((sumSquareIntensities - (mean * mean)) / (pixelsInWindow))));
		//cout << threshold << "         " << +imageOUT[i] << endl; 
		if (imageOUT[i] <= threshold) {
			imageFinalOUT[i] = 0;
		}
		else {
			imageFinalOUT[i] = 255;

		}




	}
	end = chrono::steady_clock::now();
	outputDisplay->append(QString::fromStdString(string(std::format("BINARITZATED IN = {} [seconds]", (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0))));


	int pixelWidthOUT = 1;
	
	outputDisplay->append("WRITING IMAGE...");
	begin = chrono::steady_clock::now();
	//ESCRITURA DE LA IMAGEN EN SECUENCIAL
	stbi_write_png(fileOUTCPUNICK.c_str(), width, height, pixelWidthOUT, imageFinalOUT, 0);
	end = chrono::steady_clock::now();
	outputDisplay->append(QString::fromStdString(string(std::format("IMAGE WRITTEN IN = {} [seconds]", (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0))));
	outputDisplay->append(QString::fromStdString(string(std::format("Nick cpu locally Binarized image saved in: {}", fileOUTCPUNICK))));
	free(imageOUT);
	return fileOUTCPUNICK;
}




string processor::NICKBinaritzationGPU1(int tamanyFinestra, float k)
{
	outputDisplay->append("NICK GPU METHOD1 LOCAL BINARITZATION...");
	outputDisplay->append(QString::fromStdString(string(std::format("windowSize = {} x {}", tamanyFinestra, tamanyFinestra))));
	outputDisplay->append(QString::fromStdString(string(std::format("k = {}", k))));
	outputDisplay->append("ALLOCATING SPACE FOR GRAYSCALED IMAGE ON CPU...");
	begin = chrono::steady_clock::now();
	float* imageOUT = (float*)malloc(width * height * sizeof(float));
	//char* imageFinalOUT = (char*)malloc(width * height * sizeof(char));


	end = chrono::steady_clock::now();
	outputDisplay->append(QString::fromStdString(string(std::format("ALLOCATED SPACE FOR GRAYSCALED IMAGE ON CPU IN = {} [seconds]", (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0))));

	outputDisplay->append("CONVERTING TO GRAYSCALE (CPU)...");
	begin = chrono::steady_clock::now();
	for (int i = 0; i < width * height; i++) {
		//imageOUT[i] = ((((float)0.2989 * (float)image[i * 3] + (float)0.5870 * (float)image[i * 3 + 1] + (float)0.1140 * (float)image[i * 3 + 2]))/(float)255);
		imageOUT[i] = (int)((((float)0.2989 * (float)image[i * 3] + (float)0.5870 * (float)image[i * 3 + 1] + (float)0.1140 * (float)image[i * 3 + 2])));
		//cout << imageOUT[i] << endl; 
	}
	end = chrono::steady_clock::now();
	outputDisplay->append(QString::fromStdString(string(std::format("CONVERTED TO GRAYSCALE (CPU) IN = {} [seconds]", (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0))));


	outputDisplay->append("NOW DOING GPU STUFF...");
	string a_retornar = NICKGPUMethod1(imageOUT, tamanyFinestra, k, width, height, outputDisplay, fileOUTGPUMETHOD1NICK); 
	free(imageOUT);
	return a_retornar;


}


string processor::NICKBinaritzationGPU2(int tamanyFinestra, float k)
{
	return "a";
}


string processor::NICKBinaritzationGPU3(int tamanyFinestra, float k)
{
	return "a"; 
}