#include <stdio.h>
#include <iostream>
#include "MatrixStore.hpp"

int main(){

	class MatrixStore<double> MatA(3, 3); MatA.Zeros();
	class MatrixStore<double> MatB(3, 3); MatB.Zeros();

	for(unsigned int q=0; q<MatA.ColNum; q++){
		for(unsigned int p=0; p<MatA.RowNum; p++){
			MatA(p, q) = (MatA.ColNum)*p + q;
		}
	}

	printm(MatA); printf("\n");

	MatB(':', 0) = MatA(':', 1);
//	MatB(':', 1) = MatA(':', 2);
//	MatB(':', 2) = MatA(':', 0);

	printm(MatB); printf("\n");

	MatB(0, ':') = MatA(0, ':');
//	MatB(1, ':') = MatA(1, ':');
	MatB(2, ':') = MatA(2, ':');

	printm(MatB);

	return 0;
}
