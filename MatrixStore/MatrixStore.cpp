#include "./MatrixStore.hpp"


void mxs::printMatrixStore(class MatrixStore<char>& Mat){
	for(unsigned int p=0; p<Mat.rows; p++){
		unsigned int q=0;
		printf("%d", Mat(p, q));
		for(q++; q<Mat.cols; q++){
			printf("\t %d", Mat(p, q));
		}
		printf("\n");
	}
}
void mxs::printMatrixStore(class MatrixStore<unsigned char>& Mat){
	for(unsigned int p=0; p<Mat.rows; p++){
		unsigned int q=0;
		printf("%d", Mat(p, q));
		for(q++; q<Mat.cols; q++){
			printf("\t %d", Mat(p, q));
		}
		printf("\n");
	}
}
void mxs::printMatrixStore(class MatrixStore<int>& Mat){
	for(unsigned int p=0; p<Mat.rows; p++){
		unsigned int q=0;
		printf("%d", Mat(p, q));
		for(q++; q<Mat.cols; q++){
			printf("\t %d", Mat(p, q));
		}
		printf("\n");
	}
}
void mxs::printMatrixStore(class MatrixStore<unsigned int>& Mat){
	for(unsigned int p=0; p<Mat.rows; p++){
		unsigned int q=0;
		printf("%u", Mat(p, q));
		for(q++; q<Mat.cols; q++){
			printf("\t %u", Mat(p, q));
		}
		printf("\n");
	}
}
void mxs::printMatrixStore(class MatrixStore<float>& Mat){
	for(unsigned int p=0; p<Mat.rows; p++){
		unsigned int q=0;
		printf("%f", Mat(p, q));
		for(q++; q<Mat.cols; q++){
			printf("\t %f", Mat(p, q));
		}
		printf("\n");
	}
}
void mxs::printMatrixStore(class MatrixStore<double>& Mat){
	for(unsigned int p=0; p<Mat.rows; p++){
		unsigned int q=0;
		printf("%lf", Mat(p, q));
		for(q++; q<Mat.cols; q++){
			printf("\t %lf", Mat(p, q));
		}
		printf("\n");
	}
}