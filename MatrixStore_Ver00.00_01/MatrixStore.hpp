#pragma once

#include <stdio.h>
#include "printf_dbger.h"
#include "OpCopyRow.hpp"
#include "OpCopyCol.hpp"


// プロトタイプ宣言
template <typename type>class OpCopyCol;
template <typename type>class OpCopyRow;



template <typename type>
class MatrixStore{
private:

public:
	type* MatX;
	unsigned int RowNum;	// 行数
	unsigned int ColNum;	// 列数

	MatrixStore(unsigned int Row, unsigned int Col);
	~MatrixStore();

	void Zeros();

	type& operator()(unsigned int p, unsigned int q);

	class OpCopyCol<type> operator()(const char c_dummy, unsigned int q);
	class OpCopyRow<type> operator()(unsigned int p, const char c_dummy);

	void printMatrixStore();
};
template <typename type>
inline MatrixStore<type>::MatrixStore(unsigned int Row, unsigned int Col){
	RowNum = Row;
	ColNum = Col;
	MatX = (type*)malloc(sizeof(type)*Row*Col);
	printf_dbger_if_Stop_Exit(MatX==0, "ERROR: This pointer is not allocated.\n");
}

template <typename type>
inline void MatrixStore<type>::Zeros(){
	for(unsigned int q=0; q<ColNum; q++){
		for(unsigned int p=0; p<RowNum; p++){
			MatX[p + RowNum*q] = (type)0;
		}
	}
}

template <typename type>
inline MatrixStore<type>::~MatrixStore(){
	free(MatX);
}

template <typename type>
inline type& MatrixStore<type>::operator()(unsigned int p, unsigned int q)
{
//	return *static_cast<type*>(&MatX[ColNum*q + p]);
//	printf_dbger_if_Stop_Exit(p>RowNum, "Over the length of RowNum: %d", RowNum);
//	printf_dbger_if_Stop_Exit(q>ColNum, "Over the length of ColNum: %d", ColNum);
	return *(type*)(&MatX[RowNum*q + p]);
}

template <>
inline void MatrixStore<int>::printMatrixStore(){
	for(unsigned int p=0; p<RowNum; p++){
		unsigned int q=0;
		printf("%d", MatX[p + RowNum*q]);
		for(q++; q<ColNum; q++){
			printf("\t %d", MatX[p + RowNum*q]);
		}
		printf("\n");
	}
}
template <>
inline void MatrixStore<unsigned int>::printMatrixStore(){
	for(unsigned int p=0; p<RowNum; p++){
		unsigned int q=0;
		printf("%u", MatX[p + RowNum*q]);
		for(q++; q<ColNum; q++){
			printf("\t %u", MatX[p + RowNum*q]);
		}
		printf("\n");
	}
}
template <>
inline void MatrixStore<float>::printMatrixStore(){
	for(unsigned int p=0; p<RowNum; p++){
		unsigned int q=0;
		printf("%f", MatX[p + RowNum*q]);
		for(q++; q<ColNum; q++){
			printf("\t %f", MatX[p + RowNum*q]);
		}
		printf("\n");
	}
}
template <>
inline void MatrixStore<double>::printMatrixStore(){
	for(unsigned int p=0; p<RowNum; p++){
		unsigned int q=0;
		printf("%lf", MatX[p + RowNum*q]);
		for(q++; q<ColNum; q++){
			printf("\t %lf", MatX[p + RowNum*q]);
		}
		printf("\n");
	}
}
template <typename type>
inline void MatrixStore<type>::printMatrixStore(){
	printf("This fundamental type is not defined.\n");
}
#define printm(var)\
	printf("%s = \n",(#var));(var).printMatrixStore()

/*

	How to use this?


	// 行列のメモリ確保
	class MatrixStore<double>* MatX = new MatrixStore<double>(ImageArrayLength, NumOfImg);//256*256: 16bits
	printf("MatX->RowNum: %d\n", MatX->RowNum);
	printf("MatX->ColNum: %d\n", MatX->ColNum);

	for(unsigned int q=0; q<(MatX->ColNum); q++){
		for(unsigned int p=0; p<MatX->RowNum; p++){
			(*MatX)(p, q) = 0;
		}
	}

	delete MatX;

 */

//--------------------------------------------------------------------------------------------------------


// 列のコピー
template <typename type>
inline void CopyCol(class MatrixStore<type>*& pWriteMat, unsigned int WriteCol, class MatrixStore<type>*& pReadMat, unsigned int ReadCol){
	for(unsigned int p=0; p<pReadMat->RowNum; p++){
		(*pWriteMat)(p, WriteCol) = (*pReadMat)(p, ReadCol);
	}
}


// 行列の切り取りコピー
// CutMat


//--------------------------------------------------------------------------------------------------------




template <typename type>
inline class OpCopyRow<type> MatrixStore<type>::operator()(unsigned int p, const char c_dummy)
{
	class OpCopyRow<type> CR;
	CR.pMS = this;
	CR.CopyRowNum = p;

	return CR;
}


template <typename type>
inline class OpCopyCol<type> MatrixStore<type>::operator()(const char c_dummy, unsigned int q)
{
	class OpCopyCol<type> CC;
	CC.pMS = this;
	CC.CopyColNum = q;

	return CC;
}



