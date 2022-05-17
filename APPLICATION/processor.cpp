#include "processor.h"


#define STB_IMAGE_IMPLEMENTATION
#include "./Lib/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./Lib/stb_image_write.h"

#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <format>



processor::processor(QTextBrowser* outputDisplayy)
{
	//imageLoaded = false; 

	outputDisplay = outputDisplayy; 
}



int processor::ReadFile(string imagePath)
{
	outputDisplay->append("Reading image..."); 
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();
	image = stbi_load(fileIN, &width, &height, &pixelWidth, 0);
	if (!image) {
		outputDisplay->append("Couldn't load image");
		return (-1);
	}
	chrono::steady_clock::time_point end = chrono::steady_clock::now();
	outputDisplay->append(QString::fromStdString(string(std::format("Image Read. Width : {}, Height : {}, nComp: {}", width, height, pixelWidth))));
	//printf("Image Read. Width : %d, Height : %d, nComp: %d\n", width, height, pixelWidth);
	cout << "Image Read in = " << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0 << "[seconds]" << std::endl;	
	return 0;
}

void processor::printImage3Color()
{
}

void processor::RGBtoGRAYSCALE()
{
}

void processor::globalBinaritzation(int threshold)
{
}

void processor::NICKBinaritzationCPU(int tamanyFinestra, float k)
{
}