#pragma once

#include "MatrixStore.hpp"


// プロトタイプ宣言
template <typename type>class MatrixStore;


template <typename type>
class OpCopyCol{
private:

public:
	OpCopyCol();
	~OpCopyCol();

	class MatrixStore<type>* pMS;
	unsigned int CopyColNum;

	class OpCopyCol<type> operator=(class OpCopyCol<type> CC);
};

template <typename type>inline OpCopyCol<type>::OpCopyCol(){}
template <typename type>inline OpCopyCol<type>::~OpCopyCol(){}

template <typename type>
inline class OpCopyCol<type> OpCopyCol<type>::operator=(class OpCopyCol<type> CC)
{
	for(unsigned int p=0; p<this->pMS->RowNum; p++){
		this->pMS->MatX[p + this->pMS->RowNum * this->CopyColNum]
		 = CC.pMS->MatX[p + CC.pMS->RowNum * CC.CopyColNum];
	}
	return *this;
}

