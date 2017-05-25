#pragma once

#include "MatrixStore.hpp"


// プロトタイプ宣言
template <typename type>class MatrixStore;


template <typename type>
class OpCopyRow{
private:

public:
	OpCopyRow();
	~OpCopyRow();

	class MatrixStore<type>* pMS;
	unsigned int CopyRowNum;

	class OpCopyRow<type> operator=(class OpCopyRow<type> CR);
};


template <typename type>inline OpCopyRow<type>::OpCopyRow(){}
template <typename type>inline OpCopyRow<type>::~OpCopyRow(){}


template <typename type>
inline class OpCopyRow<type> OpCopyRow<type>::operator=(class OpCopyRow<type> CR)
{
	for(unsigned int q=0; q<this->pMS->RowNum; q++){
		this->pMS->MatX[this->CopyRowNum + this->pMS->RowNum * q]
		 = CR.pMS->MatX[CR.CopyRowNum + CR.pMS->RowNum * q];
	}
	return *this;
}

