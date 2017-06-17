#pragma once


template <typename type>
class OpCopyRow{
private:
public:
	OpCopyRow();
	~OpCopyRow();

	class mxs::MatrixStore<type>* pMS;
	unsigned int CopyRowNum;

	class OpCopyRow<type> operator=(class OpCopyRow<type> CR);
};
template <typename type>inline OpCopyRow<type>::OpCopyRow(){}
template <typename type>inline OpCopyRow<type>::~OpCopyRow(){}


template <typename type>
inline class OpCopyRow<type> OpCopyRow<type>::operator=(class OpCopyRow<type> CR)
{
	for(unsigned int q=0; q<this->pMS->cols; q++){
		(*(this->pMS))(this->CopyRowNum, q)
		 = (*(CR.pMS))(   CR.CopyRowNum, q);
	}
	return *this;
}