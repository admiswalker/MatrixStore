#pragma once


template <typename type>
class OpCopyCol{
private:
public:
	OpCopyCol();
	~OpCopyCol();

	class mxs::MatrixStore<type>* pMS;
	unsigned int CopyColNum;

	class OpCopyCol<type> operator=(class OpCopyCol<type> CC);
};
template <typename type>inline OpCopyCol<type>::OpCopyCol(){}
template <typename type>inline OpCopyCol<type>::~OpCopyCol(){}


template <typename type>
inline class OpCopyCol<type> OpCopyCol<type>::operator=(class OpCopyCol<type> CC)
{
	for(unsigned int p=0; p<this->pMS->rows; p++){
		(*(this->pMS))(p, this->CopyColNum)
		 = (*(CC.pMS))(p,    CC.CopyColNum);
	}
	return *this;
}