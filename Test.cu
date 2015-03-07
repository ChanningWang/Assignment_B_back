#include <thrust/host_vector.h> 
#include <thrust/device_vector.h> 
#include <thrust/copy.h> 
#include <thrust/fill.h> 
#include <thrust/sequence.h>
#include <iostream>
#include "Curve.cpp"

int main(void){
	thrust::device_vector<int> D(10, 1);
//	thrust::fill(D.begin(), D.begin() + 7, 9);
//	thrust::host_vector<int> H(D.begin(), D.begin() + 5);
//	thrust::sequence(H.begin(), H.end());
//	thrust::copy(H.begin(), H.end(), D.begin());
	Curve curve('U');
	curve.rolling();
	curve.rolling();
	D[0]=curve.getFxRate(0.5);
	D[1]=curve.getFxRate(0.7);
	D[2]=curve.getFxRate(1.0);
	for(int i = 0; i < D.size(); i++){
		std::cout << "D[" << i << "] = " << D[i] << std::endl;

	}
	
	return 0;

}

