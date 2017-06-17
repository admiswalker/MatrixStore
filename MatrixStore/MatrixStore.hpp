#pragma once

#include "macros.hpp"

#include <stdio.h>
#include <stdlib.h>
#include "../sstd/printf_dbger.h"

//--------------------------------------------------------------------------------------------------------

namespace mxs{

	template <typename type> class MatrixStore;

	template <typename type> void zeros(class MatrixStore<type>& Mat);

	template <typename type> class MatrixStore<type>* CopyRect(class MatrixStore<type>*& pMat, unsigned int RowStart, unsigned int RowEnd, unsigned int ColStart, unsigned int ColEnd);

	void printMatrixStore(class MatrixStore         <char>& Mat);
	void printMatrixStore(class MatrixStore<unsigned char>& Mat);
	void printMatrixStore(class MatrixStore          <int>& Mat);
	void printMatrixStore(class MatrixStore <unsigned int>& Mat);
	void printMatrixStore(class MatrixStore        <float>& Mat);
	void printMatrixStore(class MatrixStore       <double>& Mat);
};

//--------------------------------------------------------------------------------------------------------

#include "OpCopyRow.hpp"	// "namespace mxs{};" の後で include すること!!!
#include "OpCopyCol.hpp"	// "namespace mxs{};" の後で include すること!!!

//--------------------------------------------------------------------------------------------------------

template <typename type>
class mxs::MatrixStore{
private:
public:
	type* MatX;
	unsigned int rows;	// 行数
	unsigned int cols;	// 列数

	MatrixStore(unsigned int row, unsigned int col);
	~MatrixStore();

	type& operator()(unsigned int p, unsigned int q);
	type& operator()(         int p, unsigned int q);
	type& operator()(unsigned int p,          int q);
	type& operator()(         int p,          int q);

	class OpCopyCol<type> operator()(const char c_dummy, unsigned int q);
	class OpCopyCol<type> operator()(const char c_dummy,          int q);

	class OpCopyRow<type> operator()(unsigned int p, const char c_dummy);
	class OpCopyRow<type> operator()(         int p, const char c_dummy);
};
template <typename type>
inline mxs::MatrixStore<type>::MatrixStore(unsigned int row, unsigned int col){
	rows = row;
	cols = col;
	MatX = (type*)malloc(sizeof(type)*row*col);
	printf_dbger_if_Stop_Exit(MatX==0, "ERROR: This pointer is not allocated.\n");
}
template <typename type>
inline mxs::MatrixStore<type>::~MatrixStore(){
	free(MatX);
}

template <typename type> inline type& mxs::MatrixStore<type>::operator()(unsigned int p, unsigned int q){ return *(type*)(&MatX[              p + rows*              q]); }
template <typename type> inline type& mxs::MatrixStore<type>::operator()(         int p, unsigned int q){ return *(type*)(&MatX[(unsigned int)p + rows*              q]); }
template <typename type> inline type& mxs::MatrixStore<type>::operator()(unsigned int p,          int q){ return *(type*)(&MatX[              p + rows*(unsigned int)q]); }
template <typename type> inline type& mxs::MatrixStore<type>::operator()(         int p,          int q){ return *(type*)(&MatX[(unsigned int)p + rows*(unsigned int)q]); }

//--------------------------------------------------------------------------------------------------------

// 行のコピー, 例: MatB(1, ':') = MatB(0, ':') = MatA(0, ':');
template <typename type>
inline class OpCopyRow<type> CopyRow(mxs::MatrixStore<type>* pthis, unsigned int p, const char& c_dummy)
{
	class OpCopyRow<type> CR;
	CR.pMS = pthis;
	CR.CopyRowNum = p;

	return CR;
}
template <typename type> inline class OpCopyRow<type> mxs::MatrixStore<type>::operator()(unsigned int p, const char c_dummy){ return CopyRow<type>(this, p, c_dummy); }
template <typename type> inline class OpCopyRow<type> mxs::MatrixStore<type>::operator()(         int p, const char c_dummy){ return CopyRow<type>(this, p, c_dummy); }


// 列のコピー, 例: MatB(':', 1) = MatB(':', 0) = MatA(':', 0);
template <typename type>
inline class OpCopyCol<type> CopyCol(mxs::MatrixStore<type>* pthis, const char& c_dummy, unsigned int q)
{
	class OpCopyCol<type> CC;
	CC.pMS = pthis;
	CC.CopyColNum = q;

	return CC;
}
template <typename type> inline class OpCopyCol<type> mxs::MatrixStore<type>::operator()(const char c_dummy, unsigned int q){ return CopyCol<type>(this, c_dummy, q); }
template <typename type> inline class OpCopyCol<type> mxs::MatrixStore<type>::operator()(const char c_dummy,          int q){ return CopyCol<type>(this, c_dummy, q); }

//--------------------------------------------------------------------------------------------------------

template <typename type>
inline void mxs::zeros(class MatrixStore<type>& Mat){
	for(unsigned int q=0; q<Mat.cols; q++){
		for(unsigned int p=0; p<Mat.rows; p++){
			Mat(p, q) = (type)0;
		}
	}
}

//--------------------------------------------------------------------------------------------------------

template <typename type>
inline class mxs::MatrixStore<type>* mxs::CopyRect(class mxs::MatrixStore<type>*& pMat, unsigned int RowStart, unsigned int RowEnd, unsigned int ColStart, unsigned int ColEnd){

	class mxs::MatrixStore<type>* pMatBuf = new mxs::MatrixStore<type>(RowEnd-RowStart, ColEnd-ColStart);

	for(unsigned int q=0; q<(ColEnd-ColStart); q++){
		for(unsigned int p=0; p<(RowEnd-RowStart); p++){
			(*pMatBuf)(p, q) = (*pMat)(p+RowStart, q+ColStart);
		}
	}

	return pMatBuf;
}

//--------------------------------------------------------------------------------------------------------