#pragma once

#include "MatrixStore.hpp"


// プロトタイプ宣言
template <typename type>
class MatrixStore;


template <typename type>
class ColCopy{
private:

public:
	ColCopy();
	~ColCopy();

	class MatrixStore<type>* pMS;
	unsigned int CopyColNum;

	void operator=(class ColCopy<type> CC);
};


template <typename type>
inline ColCopy<type>::ColCopy(){
}
template <typename type>
inline ColCopy<type>::~ColCopy(){
}


template <typename type>
inline void ColCopy<type>::operator=(class ColCopy<type> CC)
{
	for(unsigned int p=0; p<this->pMS->RowNum; p++){
		this->pMS->MatX[p + this->pMS->RowNum * this->CopyColNum]
		 = CC.pMS->MatX[p + CC.pMS->RowNum * CC.CopyColNum];
	}
	return;
}

