#ifndef __CUDACC__  
#define __CUDACC__
#endif
#include <iostream>
#include <QTextBrowser>
#include <driver_types.h>
#include <cuda_runtime.h>
using namespace std;


#include "./Lib/stb_image_write.h"

#include <malloc.h>
#include <device_launch_parameters.h>


#define BLOCKSIZE 32 //32x32 = 1024 (max threads per block)

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



__global__ void NickKernelMethod1(float* grayscaledImageDevice, float* FinalImageDevice, float k, int width, int height, int tamanyMEITATFinestra)
{
	//identificadors threads, fila i columna
	int tx = threadIdx.x;
	int ty = threadIdx.y;
	int row = (blockIdx.y * BLOCKSIZE) + ty;
	int col = (blockIdx.x * BLOCKSIZE) + tx;

	//bordes de la finestra lliscant
	int beginrow = max(0, row-tamanyMEITATFinestra);
	int begincolumn = max(0, col - tamanyMEITATFinestra);
	int endrow = min(height-1, row + tamanyMEITATFinestra); 
	int endcolumn = min(width-1, col + tamanyMEITATFinestra); 


	//calcular el pixel actual
	int numeropixelsfinestra = (endrow - beginrow + 1) * (endcolumn - begincolumn + 1);

	if (row < height && col < width)
	{
		float temp;
		float Total_sum = 0;
		float Total_sum_pow2 = 0;
		for (int i = beginrow; i <= endrow; i = i + 1)
			for (int j = begincolumn; j <= endcolumn; j = j + 1)
			{
				temp = grayscaledImageDevice[i * width + j]; 
				//printf("%f \n", temp);
				Total_sum = Total_sum + temp;
				Total_sum_pow2 = Total_sum_pow2 + (temp * temp);
			}

		//printf("%f \n", Total_sum);
		float mean = Total_sum / numeropixelsfinestra;
		float Threshold = mean + k * sqrtf((Total_sum_pow2 - mean * mean) / numeropixelsfinestra);
		//printf("%f      %f \n", Threshold, grayscaledImageDevice[row * width + col]);

		if (Threshold < grayscaledImageDevice[row * width + col])
		{
			FinalImageDevice[row * width + col] = 1; 
			//printf("Yes \n"); 
		}
		else
		{
			FinalImageDevice[row * width + col] = 0; 
			//printf("No \n"); 
		}
		//printf("%f \n", FinalImageDevice[row * width + col]);
	}


}


__global__ void NickKernelMethod2(float* grayscaledImageDevice, float* FinalImageDevice, float k, int width, int height, int tamanyMEITATFinestra)
{
	//Shared   memory
	__shared__ float SharedMemory[BLOCKSIZE][BLOCKSIZE];


	//identificadors threads, fila i columna
	int tx = threadIdx.x;
	int ty = threadIdx.y;
	int row = (blockIdx.y * BLOCKSIZE) + ty;
	int col = (blockIdx.x * BLOCKSIZE) + tx;

	//Bordes shared memory
	int beginrowshared = blockIdx.y * BLOCKSIZE;
	int endrowshared = (blockIdx.y + 1) * BLOCKSIZE - 1;
	int begincolshared = blockIdx.x * BLOCKSIZE;
	int endcolshared = (blockIdx.x + 1) * BLOCKSIZE - 1;

	//Carreguem a shared. Cada thread carrega un pixel
	if ((row < height) && (col < width))
		SharedMemory[ty][tx] = grayscaledImageDevice[row * width + col];
	//else
		//SharedMemory[ty][tx] = 0.0f; 
	

	//Ens assegurem que a partir d'aquí tinguem shared memory carregada
	__syncthreads();


	//bordes de la finestra lliscant
	int beginrow = max(0, row - tamanyMEITATFinestra);
	int begincolumn = max(0, col - tamanyMEITATFinestra);
	int endrow = min(height - 1, row + tamanyMEITATFinestra);
	int endcolumn = min(width - 1, col + tamanyMEITATFinestra);


	//calcular el pixel actual
	int numeropixelsfinestra = (endrow - beginrow + 1) * (endcolumn - begincolumn + 1);

	if (row < height && col < width)
	{
		float temp;
		float Total_sum = 0;
		float Total_sum_pow2 = 0;
		for (int i = beginrow; i <= endrow; i = i + 1)
			for (int j = begincolumn; j <= endcolumn; j = j + 1)
			{
				if ((beginrowshared < i) && (begincolshared < j) && (i < endrowshared) && (j < endcolshared))
					temp = SharedMemory[i % BLOCKSIZE][j % BLOCKSIZE];
				else
					temp = grayscaledImageDevice[i * width + j];
				//printf("%f \n", temp);
				Total_sum = Total_sum + temp;
				Total_sum_pow2 = Total_sum_pow2 + (temp * temp);
			}

		//printf("%f \n", Total_sum);
		float mean = Total_sum / numeropixelsfinestra;
		float Threshold = mean + k * sqrtf((Total_sum_pow2 - mean * mean) / numeropixelsfinestra);
		//printf("%f      %f \n", Threshold, grayscaledImageDevice[row * width + col]);

		if (Threshold < grayscaledImageDevice[row * width + col])
		{
			FinalImageDevice[row * width + col] = 1;
			//printf("Yes \n"); 
		}
		else
		{
			FinalImageDevice[row * width + col] = 0;
			//printf("No \n"); 
		}
		//printf("%f \n", FinalImageDevice[row * width + col]);
	}
}



__global__ void NickKernelMethod3(float* grayscaledImageDevice, float* FinalImageDevice, float k, int width, int height, int tamanyMEITATFinestra)
{
	//Shared   memory
	__shared__ float SharedMemory[BLOCKSIZE*3][BLOCKSIZE*3];


	//identificadors threads, fila i columna
	int tx = threadIdx.x;
	int ty = threadIdx.y;
	int row = (blockIdx.y * BLOCKSIZE) + ty;
	int col = (blockIdx.x * BLOCKSIZE) + tx;

	//Bordes shared memory
	int beginrowshared = (blockIdx.y-1) * BLOCKSIZE;
	int endrowshared = (blockIdx.y + 2) * BLOCKSIZE - 1;
	int begincolshared = (blockIdx.x-1) * BLOCKSIZE;
	int endcolshared = (blockIdx.x + 2) * BLOCKSIZE - 1;

	//Carreguem a shared. Cada thread carrega 9 pixels
	if ((row < height) && (col < width))
	{
		//Casos row i col anteriors
		if ((blockIdx.y > 0) && (blockIdx.x > 0))
		{
			//cas -1 -1
			SharedMemory[ty][tx] = grayscaledImageDevice[(beginrowshared + ty) * width + (begincolshared + tx)];
			//cas -1 0
			SharedMemory[ty][tx + BLOCKSIZE] = grayscaledImageDevice[(beginrowshared + ty) * width + col];
			//cas 0 -1
			SharedMemory[ty + BLOCKSIZE][tx] = grayscaledImageDevice[row * width + (begincolshared + tx)];
		}
		else if (blockIdx.y > 0)
		{
			//cas -1 0
			SharedMemory[ty][tx + BLOCKSIZE] = grayscaledImageDevice[(beginrowshared + ty) * width + col];
		}
		else if (blockIdx.x > 0)
		{
			//cas 0 -1
			SharedMemory[ty + BLOCKSIZE][tx] = grayscaledImageDevice[row * width + (begincolshared + tx)];
		}

	
		//La del centre
		SharedMemory[ty + BLOCKSIZE][tx + BLOCKSIZE] = grayscaledImageDevice[row * width + col];



		//Casos row i col seguents
		if ((endrowshared < (height-1)) && (endcolshared < (width-1)))
		{
			//cas 1 1
			SharedMemory[ty + (BLOCKSIZE * 2)][tx + (BLOCKSIZE * 2)] = grayscaledImageDevice[(((blockIdx.y + 1) * BLOCKSIZE) + ty) * width + (((blockIdx.x + 1) * BLOCKSIZE) + tx)];
			//cas 1 0
			SharedMemory[ty + (BLOCKSIZE * 2)][tx + BLOCKSIZE] = grayscaledImageDevice[(((blockIdx.y + 1) * BLOCKSIZE) + ty) * width + col];
			//cas 0 1
			SharedMemory[ty + BLOCKSIZE][tx + (BLOCKSIZE * 2)] = grayscaledImageDevice[row * width + (((blockIdx.x + 1) * BLOCKSIZE) + tx)];
		}
		else if (endrowshared < (height - 1))
		{
			//cas 1 0
			SharedMemory[ty + (BLOCKSIZE * 2)][tx + BLOCKSIZE] = grayscaledImageDevice[(((blockIdx.y + 1) * BLOCKSIZE) + ty) * width + col];
		}
		else if (endcolshared < (width - 1))
		{
			//cas 0 1
			SharedMemory[ty + BLOCKSIZE][tx + (BLOCKSIZE * 2)] = grayscaledImageDevice[row * width + (((blockIdx.x + 1) * BLOCKSIZE) + tx)];
		}

		//Casos 1,-1
		if ((endrowshared < (height - 1)) && (blockIdx.x > 0))
		{
			SharedMemory[ty + (BLOCKSIZE*2)][tx] = grayscaledImageDevice[(((blockIdx.y + 1) * BLOCKSIZE) + ty) * width + (begincolshared + tx)];
		}

		//Casos -1, 1
		if ((blockIdx.y > 0) && endcolshared < (width - 1))
		{
			SharedMemory[ty ][tx + (BLOCKSIZE * 2)] = grayscaledImageDevice[(beginrowshared + ty) * width + (((blockIdx.x + 1) * BLOCKSIZE) + tx)];
		}



		}
	//else
		//SharedMemory[ty][tx] = 0.0f; 


	//Ens assegurem que a partir d'aquí tinguem shared memory carregada
	__syncthreads();


	//bordes de la finestra lliscant
	int beginrow = max(0, row - tamanyMEITATFinestra);
	int begincolumn = max(0, col - tamanyMEITATFinestra);
	int endrow = min(height - 1, row + tamanyMEITATFinestra);
	int endcolumn = min(width - 1, col + tamanyMEITATFinestra);


	//calcular el pixel actual
	int numeropixelsfinestra = (endrow - beginrow + 1) * (endcolumn - begincolumn + 1);

	if (row < height && col < width)
	{
		float temp;
		float Total_sum = 0;
		float Total_sum_pow2 = 0;
		for (int i = beginrow; i <= endrow; i = i + 1)
			for (int j = begincolumn; j <= endcolumn; j = j + 1)
			{
				if ((beginrowshared < i) && (begincolshared < j) && (i < endrowshared) && (j < endcolshared))
				{
					int indexSharedy = ((((i / BLOCKSIZE) - blockIdx.y) + 1) * BLOCKSIZE) + (i % BLOCKSIZE);
					int indexSharedx = ((((j / BLOCKSIZE) - blockIdx.x) + 1) * BLOCKSIZE) + (j % BLOCKSIZE);
					temp = SharedMemory[indexSharedy][indexSharedx];
				}
				else
					temp = grayscaledImageDevice[i * width + j];
				//printf("%f \n", temp);
				Total_sum = Total_sum + temp;
				Total_sum_pow2 = Total_sum_pow2 + (temp * temp);
			}

		//printf("%f \n", Total_sum);
		float mean = Total_sum / numeropixelsfinestra;
		float Threshold = mean + k * sqrtf((Total_sum_pow2 - mean * mean) / numeropixelsfinestra);
		//printf("%f      %f \n", Threshold, grayscaledImageDevice[row * width + col]);

		if (Threshold < grayscaledImageDevice[row * width + col])
		{
			FinalImageDevice[row * width + col] = 1;
			//printf("Yes \n"); 
		}
		else
		{
			FinalImageDevice[row * width + col] = 0;
			//printf("No \n"); 
		}
		//printf("%f \n", FinalImageDevice[row * width + col]);
	}
}







extern "C"
//Nomes funciona amb memoria global (transicions CPU-GPU amb pinned)
string NICKGPUMethod1(const float* grayscaledImage, int tamanyFinestra, float k, int width, int height, QTextBrowser * outputDisplay, string fileOUTGPUMETHOD1NICK)
{
	float millisecondsMemoryEvent = 0;
	float millisecondsKernelEvent = 0;
	float millisecondsMemoryBackEvent = 0;
	dim3 dimGrid, dimBlock; 

	dimBlock.x = BLOCKSIZE;
	dimBlock.y = BLOCKSIZE;
	dimBlock.z = 1;
	// + BLOCKSIZE necessari pels pixels que queden
	dimGrid.x = (width + BLOCKSIZE - 1) / BLOCKSIZE;
	dimGrid.y = (height + BLOCKSIZE - 1) / BLOCKSIZE;
	dimGrid.z = 1;

	float* FinalImageHost; 
	float* grayscaledImagePinned; 
	unsigned char* FinalImageHostChar = (unsigned char*)malloc(width * height * sizeof(unsigned char));

	cudaMallocHost((float**)&FinalImageHost, width * height * sizeof(float));
	cudaMallocHost((float**)&grayscaledImagePinned, width * height * sizeof(float));
	memcpy(grayscaledImagePinned, grayscaledImage, width * height * sizeof(float)); 

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
	cudaMemcpy(grayscaledImageDevice, grayscaledImagePinned, width * height * sizeof(float), cudaMemcpyHostToDevice);
	cudaEventRecord(StopMemoryEvent);

	
	//Execution of the kernel
	cudaEventCreate(&startKernelEvent);
	cudaEventCreate(&StopKernelEvent);
	cudaEventRecord(startKernelEvent);
	int tamanyMEITATFinestra = tamanyFinestra / 2; 
	NickKernelMethod1 << <dimGrid, dimBlock >> > (grayscaledImageDevice, FinalImageDevice, k, width, height, tamanyMEITATFinestra);
	//cudaDeviceSynchronize();  // SA DE TREURE
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
	cudaEventElapsedTime(&millisecondsMemoryEvent, startMemoryEvent, StopMemoryEvent);

	cudaEventSynchronize(StopKernelEvent);
	cudaEventElapsedTime(&millisecondsKernelEvent, startKernelEvent, StopKernelEvent);

	cudaEventSynchronize(StopMemoryBackEvent);
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
	outputDisplay->append(QString::fromStdString(string("TIME SPENT ALLOCATING AND COPYING INTO GPU = " + to_string((millisecondsMemoryEvent) / 1000.0f) + " [seconds]" )));
	outputDisplay->append(QString::fromStdString(string("TIME SPENT IN THE GPU KERNEL = " + to_string((millisecondsKernelEvent) / 1000.0) + " [seconds]")));
	outputDisplay->append(QString::fromStdString(string("TIME SPENT COPYING DATA FROM GPU TO CPU = " + to_string((millisecondsMemoryBackEvent) / 1000.0f) + " [seconds]")));

	chrono::steady_clock::time_point begin;
	chrono::steady_clock::time_point end;

	
	outputDisplay->append("CONVERTING IMAGE FLOAT POINTER TO CHAR POINTER TO WRITE THE IMAGE (CPU)...");
	begin = chrono::steady_clock::now();
	
	for (int i = 0; i < width * height; i++) {
		if (FinalImageHost[i] == 0)
		{
			FinalImageHostChar[i] = 0;
		}
		else
		{
			FinalImageHostChar[i] = 255;
		}
		//cout << FinalImageHost[i] << endl; 
	}
	
	end = chrono::steady_clock::now();
	outputDisplay->append(QString::fromStdString(string("CONVERTED FLOAT POINTER TO CHAR POINTER IN(CPU) = " + to_string((chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0f) + " [seconds]")));
	
	/*
	for (int i = 0; i < width * height; i++) {
		cout << FinalImageHost[i] << endl;
	}
	*/
	
	outputDisplay->append("WRITING IMAGE...");
	int pixelWidthOUT = 1;
	begin = chrono::steady_clock::now();
	//ESCRITURA DE LA IMAGEN EN SECUENCIAL
	stbi_write_png(fileOUTGPUMETHOD1NICK.c_str(), width, height, pixelWidthOUT, FinalImageHostChar, 0);
	end = chrono::steady_clock::now();
	outputDisplay->append(QString::fromStdString(string("IMAGE WRITTEN IN = " + to_string((chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0f) + " [seconds]")));
	outputDisplay->append(QString::fromStdString(string("Nick gpu method1 image saved in: " + fileOUTGPUMETHOD1NICK)));


	//free mmemory, host
	
	free(FinalImageHostChar);
	cudaFreeHost(FinalImageHost);
	cudaFreeHost(grayscaledImagePinned); 



	return fileOUTGPUMETHOD1NICK;
}

//Funciona amb shared i global (transicions CPU-GPU amb pinned)
extern "C"
string NICKGPUMethod2(const float* grayscaledImage, int tamanyFinestra, float k, int width, int height, QTextBrowser* outputDisplay, string fileOUTGPUMETHOD2NICK)
{
	float millisecondsMemoryEvent = 0;
	float millisecondsKernelEvent = 0;
	float millisecondsMemoryBackEvent = 0;
	dim3 dimGrid, dimBlock;

	dimBlock.x = BLOCKSIZE;
	dimBlock.y = BLOCKSIZE;
	dimBlock.z = 1;
	// + BLOCKSIZE necessari pels pixels que queden
	dimGrid.x = (width + BLOCKSIZE - 1) / BLOCKSIZE;
	dimGrid.y = (height + BLOCKSIZE - 1) / BLOCKSIZE;
	dimGrid.z = 1;

	float* FinalImageHost;
	float* grayscaledImagePinned;
	unsigned char* FinalImageHostChar = (unsigned char*)malloc(width * height * sizeof(unsigned char));

	cudaMallocHost((float**)&FinalImageHost, width * height * sizeof(float));
	cudaMallocHost((float**)&grayscaledImagePinned, width * height * sizeof(float));
	memcpy(grayscaledImagePinned, grayscaledImage, width * height * sizeof(float));

	//test_kernel << <1, 1 >> > ();
	cudaEvent_t startMemoryEvent, StopMemoryEvent, startKernelEvent, StopKernelEvent, startMemoryBackEvent, StopMemoryBackEvent;

	//Allocating and copia memoria a la gpu
	cudaEventCreate(&startMemoryEvent);
	cudaEventCreate(&StopMemoryEvent);
	cudaEventRecord(startMemoryEvent);
	float* grayscaledImageDevice;
	float* FinalImageDevice;
	cudaMalloc((float**)&grayscaledImageDevice, width * height * sizeof(float));
	cudaMalloc((float**)&FinalImageDevice, width * height * sizeof(float));
	cudaMemcpy(grayscaledImageDevice, grayscaledImagePinned, width * height * sizeof(float), cudaMemcpyHostToDevice);
	cudaEventRecord(StopMemoryEvent);


	//Execution of the kernel
	cudaEventCreate(&startKernelEvent);
	cudaEventCreate(&StopKernelEvent);
	cudaEventRecord(startKernelEvent);
	int tamanyMEITATFinestra = tamanyFinestra / 2;
	NickKernelMethod2 << <dimGrid, dimBlock >> > (grayscaledImageDevice, FinalImageDevice, k, width, height, tamanyMEITATFinestra);
	//cudaDeviceSynchronize();  // SA DE TREURE
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
	cudaEventElapsedTime(&millisecondsMemoryEvent, startMemoryEvent, StopMemoryEvent);

	cudaEventSynchronize(StopKernelEvent);
	cudaEventElapsedTime(&millisecondsKernelEvent, startKernelEvent, StopKernelEvent);

	cudaEventSynchronize(StopMemoryBackEvent);
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
	outputDisplay->append(QString::fromStdString(string("TIME SPENT ALLOCATING AND COPYING INTO GPU = " + to_string((millisecondsMemoryEvent) / 1000.0f) + " [seconds]")));
	outputDisplay->append(QString::fromStdString(string("TIME SPENT IN THE GPU KERNEL = " + to_string((millisecondsKernelEvent) / 1000.0) + " [seconds]")));
	outputDisplay->append(QString::fromStdString(string("TIME SPENT COPYING DATA FROM GPU TO CPU = " + to_string((millisecondsMemoryBackEvent) / 1000.0f) + " [seconds]")));

	chrono::steady_clock::time_point begin;
	chrono::steady_clock::time_point end;


	outputDisplay->append("CONVERTING IMAGE FLOAT POINTER TO CHAR POINTER TO WRITE THE IMAGE (CPU)...");
	begin = chrono::steady_clock::now();

	for (int i = 0; i < width * height; i++) {
		if (FinalImageHost[i] == 0)
		{
			FinalImageHostChar[i] = 0;
		}
		else
		{
			FinalImageHostChar[i] = 255;
		}
		//cout << FinalImageHost[i] << endl; 
	}

	end = chrono::steady_clock::now();
	outputDisplay->append(QString::fromStdString(string("CONVERTED FLOAT POINTER TO CHAR POINTER IN(CPU) = " + to_string((chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0f) + " [seconds]")));

	/*
	for (int i = 0; i < width * height; i++) {
		cout << FinalImageHost[i] << endl;
	}
	*/

	outputDisplay->append("WRITING IMAGE...");
	int pixelWidthOUT = 1;
	begin = chrono::steady_clock::now();
	//ESCRITURA DE LA IMAGEN EN SECUENCIAL
	stbi_write_png(fileOUTGPUMETHOD2NICK.c_str(), width, height, pixelWidthOUT, FinalImageHostChar, 0);
	end = chrono::steady_clock::now();
	outputDisplay->append(QString::fromStdString(string("IMAGE WRITTEN IN = " + to_string((chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0f) + " [seconds]")));
	outputDisplay->append(QString::fromStdString(string("Nick gpu method2 image saved in: " + fileOUTGPUMETHOD2NICK)));


	//free mmemory, host

	free(FinalImageHostChar);
	cudaFreeHost(FinalImageHost);
	cudaFreeHost(grayscaledImagePinned);



	return fileOUTGPUMETHOD2NICK;
}




//Funciona amb shared i global (transicions CPU-GPU amb pinned)
extern "C"
string NICKGPUMethod3(const float* grayscaledImage, int tamanyFinestra, float k, int width, int height, QTextBrowser * outputDisplay, string fileOUTGPUMETHOD3NICK)
{
	float millisecondsMemoryEvent = 0;
	float millisecondsKernelEvent = 0;
	float millisecondsMemoryBackEvent = 0;
	dim3 dimGrid, dimBlock;

	dimBlock.x = BLOCKSIZE;
	dimBlock.y = BLOCKSIZE;
	dimBlock.z = 1;
	// + BLOCKSIZE necessari pels pixels que queden
	dimGrid.x = (width + BLOCKSIZE - 1) / BLOCKSIZE;
	dimGrid.y = (height + BLOCKSIZE - 1) / BLOCKSIZE;
	dimGrid.z = 1;

	float* FinalImageHost;
	float* grayscaledImagePinned;
	unsigned char* FinalImageHostChar = (unsigned char*)malloc(width * height * sizeof(unsigned char));

	cudaMallocHost((float**)&FinalImageHost, width * height * sizeof(float));
	cudaMallocHost((float**)&grayscaledImagePinned, width * height * sizeof(float));
	memcpy(grayscaledImagePinned, grayscaledImage, width * height * sizeof(float));

	//test_kernel << <1, 1 >> > ();
	cudaEvent_t startMemoryEvent, StopMemoryEvent, startKernelEvent, StopKernelEvent, startMemoryBackEvent, StopMemoryBackEvent;

	//Allocating and copia memoria a la gpu
	cudaEventCreate(&startMemoryEvent);
	cudaEventCreate(&StopMemoryEvent);
	cudaEventRecord(startMemoryEvent);
	float* grayscaledImageDevice;
	float* FinalImageDevice;
	cudaMalloc((float**)&grayscaledImageDevice, width * height * sizeof(float));
	cudaMalloc((float**)&FinalImageDevice, width * height * sizeof(float));
	cudaMemcpy(grayscaledImageDevice, grayscaledImagePinned, width * height * sizeof(float), cudaMemcpyHostToDevice);
	cudaEventRecord(StopMemoryEvent);


	//Execution of the kernel
	cudaEventCreate(&startKernelEvent);
	cudaEventCreate(&StopKernelEvent);
	cudaEventRecord(startKernelEvent);
	int tamanyMEITATFinestra = tamanyFinestra / 2;
	NickKernelMethod3 << <dimGrid, dimBlock >> > (grayscaledImageDevice, FinalImageDevice, k, width, height, tamanyMEITATFinestra);
	//cudaDeviceSynchronize();  // SA DE TREURE
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
	cudaEventElapsedTime(&millisecondsMemoryEvent, startMemoryEvent, StopMemoryEvent);

	cudaEventSynchronize(StopKernelEvent);
	cudaEventElapsedTime(&millisecondsKernelEvent, startKernelEvent, StopKernelEvent);

	cudaEventSynchronize(StopMemoryBackEvent);
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
	outputDisplay->append(QString::fromStdString(string("TIME SPENT ALLOCATING AND COPYING INTO GPU = " + to_string((millisecondsMemoryEvent) / 1000.0f) + " [seconds]")));
	outputDisplay->append(QString::fromStdString(string("TIME SPENT IN THE GPU KERNEL = " + to_string((millisecondsKernelEvent) / 1000.0) + " [seconds]")));
	outputDisplay->append(QString::fromStdString(string("TIME SPENT COPYING DATA FROM GPU TO CPU = " + to_string((millisecondsMemoryBackEvent) / 1000.0f) + " [seconds]")));

	chrono::steady_clock::time_point begin;
	chrono::steady_clock::time_point end;


	outputDisplay->append("CONVERTING IMAGE FLOAT POINTER TO CHAR POINTER TO WRITE THE IMAGE (CPU)...");
	begin = chrono::steady_clock::now();

	for (int i = 0; i < width * height; i++) {
		if (FinalImageHost[i] == 0)
		{
			FinalImageHostChar[i] = 0;
		}
		else
		{
			FinalImageHostChar[i] = 255;
		}
		//cout << FinalImageHost[i] << endl; 
	}

	end = chrono::steady_clock::now();
	outputDisplay->append(QString::fromStdString(string("CONVERTED FLOAT POINTER TO CHAR POINTER IN(CPU) = " + to_string((chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0f) + " [seconds]")));

	/*
	for (int i = 0; i < width * height; i++) {
		cout << FinalImageHost[i] << endl;
	}
	*/

	outputDisplay->append("WRITING IMAGE...");
	int pixelWidthOUT = 1;
	begin = chrono::steady_clock::now();
	//ESCRITURA DE LA IMAGEN EN SECUENCIAL
	stbi_write_png(fileOUTGPUMETHOD3NICK.c_str(), width, height, pixelWidthOUT, FinalImageHostChar, 0);
	end = chrono::steady_clock::now();
	outputDisplay->append(QString::fromStdString(string("IMAGE WRITTEN IN = " + to_string((chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0f) + " [seconds]")));
	outputDisplay->append(QString::fromStdString(string("Nick gpu method3 image saved in: " + fileOUTGPUMETHOD3NICK)));


	//free mmemory, host

	free(FinalImageHostChar);
	cudaFreeHost(FinalImageHost);
	cudaFreeHost(grayscaledImagePinned);



	return fileOUTGPUMETHOD3NICK;
}