#include "FAArray.h"
#include <math.h>

//constructor 
FAArray::FAArray()
{
	
}

FAArray::FAArray(int pNumDim, int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8)
{
   
	int i, pSize, pCounter, pValuesSize;

	pValuesSize = p1*p2*p3*p4*p5*p6*p7*p8;
	mValues.resize(pValuesSize);	
	mNdVector.resize(pNumDim);
	mDimExistInfo.resize(pNumDim);
	
	for(i=0; i<pValuesSize; i++)
		mValues[i] = 0.0;

	for(i=0; i<pNumDim; i++)
	{
		mDimExistInfo[i] = 1;	
	}

	for(i=0; i<pNumDim; i++)
	{

		if(i==0)  mNdVector[i] = p1;
		if(i==1)  mNdVector[i] = p2;
		if(i==2)  mNdVector[i] = p3;
		if(i==3)  mNdVector[i] = p4;
		if(i==4)  mNdVector[i] = p5;
		if(i==5)  mNdVector[i] = p6;
		if(i==6)  mNdVector[i] = p7;
		if(i==7)  mNdVector[i] = p8;
		
	}
	
	pSize = mNdVector.size();
	pCounter = 0;
	for(i=0; i<pSize; i++)
	{
		if(mDimExistInfo[i] != 0)
		{
			pCounter++;
			mTrueDim.resize(pCounter);
			mTrueDim[pCounter - 1] = mNdVector[i];
		}
	}

	
	//for(i=0; i<pSize; i++)
	//	cout << mNdVector[i] << "    " << mTrueDim[i] << endl;
}


FAArray::FAArray(vector<int>& pNdVector, vector<int>& pDimExistInfo, vector<double>& pValues )
{
	int i, pSize, pCounter;
	
	mNdVector = pNdVector;
	mDimExistInfo = pDimExistInfo;
	mValues = pValues;

	pSize = pNdVector.size();
	try
	{
		if(pDimExistInfo.size() < pSize) throw new FAError("pDimExistInfo should have at least the size of pNdVector");
	}
	catch(FAError* pError)
	{
		pError->show();
		pError->getErrorLog().close();
		delete pError;
		exit(1);
	}

	pCounter = 0;
	for(i=0; i<pSize; i++)
	{
		if(pDimExistInfo[i] != 0)
		{
			pCounter++;
			mTrueDim.resize(pCounter);
			mTrueDim[pCounter - 1] = pNdVector[i];
		}
	}

}



FAArray::FAArray(vector<int>& pNdVector, vector<int>& pDimExistInfo )
{
	int i, nDim, pMax, pCounter;
	
	mNdVector		= pNdVector;
	mDimExistInfo	= pDimExistInfo;
	nDim = pNdVector.size();
	
	try
	{
		if(pDimExistInfo.size() < nDim) throw new FAError("pDimExistInfo should have at least the size of pNdVector");
	}
	catch(FAError* pError)
	{
		pError->show();
		pError->getErrorLog().close();
		delete pError;
		exit(1);
	}
	
	pMax = 1;
	pCounter = 0;
	for(i=0; i<nDim; i++)
	{
		if(pDimExistInfo[i] != 0)
		{
			pMax *= pNdVector[i];
			pCounter++;
			mTrueDim.resize(pCounter);
			mTrueDim[pCounter - 1] = pNdVector[i];
		}
	}

	mValues.resize(pMax);

}


//copy constructor
FAArray::FAArray(const FAArray& pStencilArray) 
{

		mNdVector.resize(0);
		mDimExistInfo.resize(0);
		mValues.resize(0);
		mTrueDim.resize(0);

		mNdVector = pStencilArray.mNdVector;
		mDimExistInfo = pStencilArray.mDimExistInfo;
		mValues = pStencilArray.mValues;
		mTrueDim = pStencilArray.mTrueDim;

}

//destructor		
FAArray::~FAArray()
{
	
}

 
//member functions
FAArray& FAArray::operator=(const FAArray& pStencilArray)
{
	if(&pStencilArray == this)
		return *this;
	else
	{
	
		mNdVector.resize(0);
		mDimExistInfo.resize(0);
		mValues.resize(0);
		mTrueDim.resize(0);

		mNdVector = pStencilArray.mNdVector;
		mDimExistInfo = pStencilArray.mDimExistInfo;
		mValues = pStencilArray.mValues;
		mTrueDim = pStencilArray.mTrueDim;

	}
	
	return *this;
}

FAArray& FAArray::operator+=(const FAArray& pStencilArray)
{
	int i;
	
	try
	{
		if(mValues.size() != pStencilArray.mValues.size()) throw new FAError("Vector sizes should be same for addition");
	}
	catch(FAError* pError)
	{
		pError->show();
		pError->getErrorLog().close();
		delete pError;
		exit(1);
	}

	int pSize = mValues.size();
	for(i=0; i<pSize; i++)
	{
		mValues[i] += pStencilArray.mValues[i];
	}
	
	return *this;
}

FAArray& FAArray::operator-=(const FAArray& pStencilArray)
{
	int i;
	
	try
	{
		if(mValues.size() != pStencilArray.mValues.size()) throw new FAError("Vector sizes should be same for subtraction");
	}
	catch(FAError* pError)
	{
		pError->show();
		pError->getErrorLog().close();
		delete pError;
		exit(1);
	}

	int pSize = mValues.size();
	for(i=0; i<pSize; i++)
	{
		mValues[i] -= pStencilArray.mValues[i];
	}
	
	return *this;
}

FAArray& FAArray::operator*=(const FAArray& pStencilArray)
{
	
	int i;
	
	try
	{
		if(mValues.size() != pStencilArray.mValues.size()) throw new FAError("Vector sizes should be same for multiplication");
	}
	catch(FAError* pError)
	{
		pError->show();
		pError->getErrorLog().close();
		delete pError;
		exit(1);
	}

	int pSize = mValues.size();
	for(i=0; i<pSize; i++)
	{
		mValues[i] *= pStencilArray.mValues[i];
	}

	return *this;
}

FAArray& FAArray::operator+(const FAArray& pStencilArray)
{
	
	int i;
	
	try
	{
		if(mValues.size() != pStencilArray.mValues.size()) throw new FAError("Vector sizes should be same for addition");
	}
	catch(FAError* pError)
	{
		pError->show();
		pError->getErrorLog().close();
		delete pError;
		exit(1);
	}

	int pSize = mValues.size();
	for(i=0; i<pSize; i++)
	{
		mValues[i] += pStencilArray.mValues[i];
	}
	
	return *this;
}

FAArray& FAArray::operator-(const FAArray& pStencilArray)
{

	int i;
	
	try
	{
		if(mValues.size() != pStencilArray.mValues.size()) throw new FAError("Vector sizes should be same for subtraction");
	}
	catch(FAError* pError)
	{
		pError->show();
		pError->getErrorLog().close();
		delete pError;
		exit(1);
	}

	int pSize = mValues.size();
	for(i=0; i<pSize; i++)
	{
		mValues[i] -= pStencilArray.mValues[i];
	}

	return *this;
}
 
FAArray& FAArray::operator*(const FAArray& pStencilArray)
{

	int i;
	
	try
	{
		if(mValues.size() != pStencilArray.mValues.size()) throw new FAError("Vector sizes should be same for multiplication");
	}
	catch(FAError* pError)
	{
		pError->show();
		pError->getErrorLog().close();
		delete pError;
		exit(1);
	}

	int pSize = mValues.size();
	for(i=0; i<pSize; i++)
	{
		mValues[i] *= pStencilArray.mValues[i];
	}

	return *this;	
}


FAArray& FAArray::multConst(double& pVal)
{
	
	int i, pSize;
	pSize = mValues.size();
	
	for(i=0; i<pSize; i++)
	{
		mValues[i] *= pVal;
	}

	return *this;
}

FAArray& FAArray::addConst(double& pVal)
{
	
	int i, pSize;
	pSize = mValues.size();
	
	for(i=0; i<pSize; i++)
	{
		mValues[i] += pVal;
	}
	
	return *this;
}


double FAArray::l2norm()
{

	int i, pSize;
	double pNorm =0;

	pSize = mValues.size();
	
	for(i=0; i<pSize; i++)
	{
		pNorm += (mValues[i]*mValues[i]);		
	}

	pNorm = sqrt(pNorm);
	
	return pNorm;

}

void FAArray::sortArray(int pStart, int pEnd, string pStr)
{

	vector<double>::iterator perfSortI;
	vector<double>::iterator perfSortE;
	if(pStart == 0)
	{
		perfSortI = mValues.begin();
	}
	else
	{
		perfSortI = mValues.begin() + pStart + 1;
	}
	
	if(pEnd == 0)
	{
		perfSortE = mValues.end();
	}
	else
	{
		perfSortE = perfSortI + pEnd + 1;
	}

	sort(perfSortI, perfSortE);
	if(pStr == "descending")
		reverse(perfSortI, perfSortE);
}


double FAArray::sumTotal()
{
	double pResult = 0;
	int i, pSize;

	pSize = mValues.size();
	for(i=0; i<pSize; i++)
	{
		pResult += mValues[i];
	}

	return pResult;
}

double FAArray::minTotal()
{
	double amin, amax;
	int i, pSize;

	pSize = mValues.size();

	amax = 0;
	for(i=0; i<pSize; i++)
	{
		amax = (amax > mValues[i]) ? amax : mValues[i];
	}
	amin = amax;
	for(i=0; i<pSize; i++)
	{
		amin = (amin < mValues[i]) ? amin : mValues[i];
	}

	return amin;
}

double FAArray::maxTotal()
{
	double amax;
	int i, pSize;

	pSize = mValues.size();

	amax = 0;
	for(i=0; i<pSize; i++)
	{
		amax = (amax > mValues[i]) ? amax : mValues[i];
	}
	
	return amax;
}

#if 0
double FAArray::sumOneDir(int pDir)
{
	double pResult = 0;
	int i, pSize, pOffset;
	
	try
	{
		if(mDimExistInfo[pDir] == 0) throw new FAError("Cannot sum of a zero dimensional vector.  No Data Entry.");
	}
	catch(FAError* pError)
	{
		pError->show();
		pError->getErrorLog().close();
		delete pError;
		exit(1);
	}

	pOffset = 0;
	pSize = mNdVector[pDir];
	for(i=0; i<pDir; i++)
	{
		pOffset += mNdVector[i];
	}

	pResult = 0.0;
	for(i=0; i<pSize; i++)
	{
		pResult += mValues[pOffset+i];
	}
	
	
	return pResult;
}

double FAArray::minOneDir(int pDir)
{
	double pResult, amax;
	int i, pSize, pOffset;
	
	try
	{
		if(mDimExistInfo[pDir] == 0) throw new FAError("Cannot sum of a zero dimensional vector.  No Data Entry.");
	}
	catch(FAError* pError)
	{
		pError->show();
		pError->getErrorLog().close();
		delete pError;
		exit(1);
	}

	pOffset = 0;
	pSize = mNdVector[pDir];
	for(i=0; i<pDir; i++)
	{
		pOffset += mNdVector[i];
	}

	amax = 0.0;
	for(i=0; i<pSize; i++)
	{
		amax = (amax > mValues[pOffset+i]) ? amax : mValues[pOffset+i];
	}

	pResult = amax;
	for(i=0; i<pSize; i++)
	{
		pResult = (pResult < mValues[pOffset+i]) ? pResult : mValues[pOffset+i];
	}
	
	return pResult;
}

double FAArray::maxOneDir(int pDir)
{
	double pResult;
	int i, pSize, pOffset;
	
	try
	{
		if(mDimExistInfo[pDir] == 0) throw new FAError("Cannot sum of a zero dimensional vector.  No Data Entry.");
	}
	catch(FAError* pError)
	{
		pError->show();
		pError->getErrorLog().close();
		delete pError;
		exit(1);
	}

	pOffset = 0;
	pSize = mNdVector[pDir];
	for(i=0; i<pDir; i++)
	{
		pOffset += mNdVector[i];
	}

	pResult = 0.0;
	for(i=0; i<pSize; i++)
	{
		pResult = (pResult > mValues[pOffset+i]) ? pResult : mValues[pOffset+i];
	}


	return pResult;
} 

#endif

void FAArray::show()
{	
	ofstream fout("outputfiles/vectorResult.out");

	int i;
	int pSize = mValues.size();
	for(i=0; i<pSize; i++)
	{
		fout << mValues[i] << endl;
	}

	fout << "**************************************************" << endl;

	fout.close();
}
