#include <iostream>
#include <QTextBrowser>
#include <NickCUDAKERNEL.cu>
using namespace std;



// gpu kernel function
__global__ void test_kernel(void) {
}






/*
extern "C"
void wrapper(QTextBrowser * outputDisplay)
{
	test_kernel << <1, 1 >> > ();
}
*/

extern "C"
string NICKBinaritzationGPU1(const float* grayscaledImage, int tamanyFinestra, float k)
{
	test_kernel << <1, 1 >> > ();
	return "c"; 
}





