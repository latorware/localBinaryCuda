#ifndef PROCESSOR_H
#define PROCESSOR_H


#include <chrono>
#include <QTextBrowser>
using namespace std;


#pragma once



class processor
{


	
public:

	processor(QTextBrowser* outputDisplay);
	int ReadFile(string imagePath); 
	int getWidth(); 
	int getHeight(); 
	//void printImage3Color(); 
	string RGBtoGRAYSCALE(); 
	string globalBinaritzation(int threshold); 
	string NICKBinaritzationCPU(int tamanyFinestra, float k); 
	string NICKBinaritzationGPU1(int tamanyFinestra, float k);
	string NICKBinaritzationGPU2(int tamanyFinestra, float k);
	string NICKBinaritzationGPU3(int tamanyFinestra, float k);




private:

	QTextBrowser* outputDisplay;

	//bool imageLoaded; 

	string fileOUTGRAYSCALED;
	string fileOUTGLOBALBINARITZATION;
	string fileOUTCPUNICK;
	string fileOUTGPUMETHOD1NICK; 
	string fileOUTGPUMETHOD2NICK; 
	string fileOUTGPUMETHOD3NICK; 
	unsigned char* image;
	int width, height, pixelWidth; //meta info de la imagen
	int tamanyFinestraLLiscant;

	chrono::steady_clock::time_point begin;
	chrono::steady_clock::time_point end;




};

#endif	