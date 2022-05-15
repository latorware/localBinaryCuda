#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <iostream>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <malloc.h>
#include <chrono>
#include <math.h>
//#include <QTextBrowser>
using namespace std;


#pragma once








class processor
{



public:

	//processor(QTextBrowser* outputDisplay);
	int ReadFile(string imagePath); 
	void printImage3Color(); 
	void RGBtoGRAYSCALE(); 
	void globalBinaritzation(int threshold); 
	void NICKBinaritzationCPU(int tamanyFinestra, float k); 



private:

	//QTextBrowser* outputDisplay;

	bool imageLoaded; 

	char* fileIN, * fileOUT;
	unsigned char* image;
	int width, height, pixelWidth; //meta info de la imagen
	int tamanyFinestraLLiscant;

	chrono::steady_clock::time_point begin;
	chrono::steady_clock::time_point end;








};

#endif // MAINWINDOW_H