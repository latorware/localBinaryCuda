#include <iostream>
using namespace std;



// gpu kernel function
__global__ void test_kernel(void) {
}

extern "C"
void wrapper(void)
{
	test_kernel << <1, 1 >> > ();
	cout << 'b' << endl;
}
