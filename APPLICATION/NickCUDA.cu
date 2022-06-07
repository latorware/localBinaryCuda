#include <iostream>
#include <QTextBrowser>
#include <driver_types.h>
#include <cuda_runtime.h>
using namespace std;


#include "./Lib/stb_image_write.h"

#include <malloc.h>


#define BLOCKSIZE 32

//max image size: 10.000 x 10.000 pixels
//__constant__ float GrayscaledImageConstant[10000 * 10000];


/*
// gpu kernel function
__global__ void test_kernel(void) {
}
*/





/*
extern "C"
void wrapper(QTextBrowser * outputDisplay)
{
	test_kernel << <1, 1 >> > ();
}
*/

extern "C"
string NICKGPUMethod1(const float* grayscaledImage, int tamanyFinestra, float k, int width, int height, QTextBrowser * outputDisplay, string fileOUTGPUMETHOD1NICK)
{

	dim3 dimGrid, dimBlock; 

	dimBlock.x = BLOCKSIZE;
	dimBlock.y = BLOCKSIZE;
	dimBlock.z = 1;

	dimGrid.x = (width + BLOCKSIZE - 1) / BLOCKSIZE;
	dimGrid.y = (height + BLOCKSIZE - 1) / BLOCKSIZE;
	dimGrid.z = 1;

	float* FinalImageHost = (float*)malloc(width * height * sizeof(float));

	//test_kernel << <1, 1 >> > ();
	cudaEvent_t startMemoryEvent, StopMemoryEvent, startKernelEvent, StopKernelEvent, startMemoryBackEvent, StopMemoryBackEvent;

	//Allocating and copia memoria a la gpu
	cudaEventCreate(&startMemoryEvent);
	cudaEventCreate(&StopMemoryEvent);
	cudaEventRecord(startMemoryEvent);
	float* grayscaledImageDevice; 
	float* FinalImageDevice; 
	cudaMalloc((float**)&grayscaledImageDevice, width*height*sizeof(float));
	cudaMalloc((float**)&FinalImageDevice, width * height * sizeof(float));
	cudaMemcpy(grayscaledImageDevice, grayscaledImage, width * height * sizeof(float), cudaMemcpyHostToDevice);
	cudaEventRecord(StopMemoryEvent);

	
	//Execution of the kernel
	cudaEventCreate(&startKernelEvent);
	cudaEventCreate(&StopKernelEvent);
	cudaEventRecord(startKernelEvent);
	//NickKernel << <dimGrid, dimBlock >> > (Nd, Pd_global, Nd.width, Nd.height);
	cudaEventRecord(StopKernelEvent);


	//Memory Back
	cudaEventCreate(&startMemoryBackEvent);
	cudaEventCreate(&StopMemoryBackEvent);
	cudaEventRecord(startMemoryBackEvent);
	cudaMemcpy(FinalImageHost, FinalImageDevice, width * height * sizeof(float), cudaMemcpyDeviceToHost);
	cudaEventRecord(StopMemoryBackEvent);


	//Free memory, events
	cudaFree(grayscaledImageDevice);
	cudaFree(FinalImageDevice); 

	cudaEventSynchronize(StopMemoryEvent);
	float millisecondsMemoryEvent = 0;
	cudaEventElapsedTime(&millisecondsMemoryEvent, startMemoryEvent, StopMemoryEvent);

	cudaEventSynchronize(StopKernelEvent);
	float millisecondsKernelEvent = 0;
	cudaEventElapsedTime(&millisecondsKernelEvent, startKernelEvent, StopKernelEvent);

	cudaEventSynchronize(StopMemoryBackEvent);
	float millisecondsMemoryBackEvent = 0;
	cudaEventElapsedTime(&millisecondsMemoryBackEvent, startMemoryBackEvent, StopMemoryBackEvent);

	cudaEventDestroy(startMemoryEvent);
	cudaEventDestroy(StopMemoryEvent);
	cudaEventDestroy(startKernelEvent);
	cudaEventDestroy(StopKernelEvent);
	cudaEventDestroy(startMemoryBackEvent);
	cudaEventDestroy(StopMemoryBackEvent);



	//Writing results, and writing file
	cudaDeviceSynchronize(); 
	outputDisplay->append("GPU computation done: ");
	outputDisplay->append(QString::fromStdString(string("TIME SPENT ALLOCATING AND COPYING INTO GPU = " + to_string((millisecondsMemoryEvent) / 1000.0) + " [seconds]" )));
	outputDisplay->append(QString::fromStdString(string("TIME SPENT IN THE GPU KERNEL = " + to_string((millisecondsKernelEvent) / 1000.0) + " [seconds]")));
	outputDisplay->append(QString::fromStdString(string("TIME SPENT COPYING DATA FROM GPU TO CPU = " + to_string((millisecondsMemoryBackEvent) / 1000.0) + " [seconds]")));

	outputDisplay->append("WRITING IMAGE...");
	int pixelWidthOUT = 1;
	chrono::steady_clock::time_point begin;
	chrono::steady_clock::time_point end;
	begin = chrono::steady_clock::now();
	//ESCRITURA DE LA IMAGEN EN SECUENCIAL
	stbi_write_png(fileOUTGPUMETHOD1NICK.c_str(), width, height, pixelWidthOUT, FinalImageDevice, 0);
	end = chrono::steady_clock::now();
	outputDisplay->append(QString::fromStdString(string("IMAGE WRITTEN IN = " + to_string((chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0) + " [seconds]")));
	outputDisplay->append(QString::fromStdString(string("Nick gpu method1 image saved in: " + fileOUTGPUMETHOD1NICK)));


	//free mmemory, host
	free(FinalImageDevice); 



	return fileOUTGPUMETHOD1NICK;
}





