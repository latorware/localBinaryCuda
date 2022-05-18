#include <iostream>
#include <QTextBrowser>
using namespace std;



// gpu kernel function
__global__ void test_kernel(void) {
}

extern "C"
void wrapper(QTextBrowser * outputDisplay)
{
	test_kernel << <1, 1 >> > ();
}
