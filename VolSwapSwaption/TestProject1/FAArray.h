#ifndef __FAARRAY_H
#define __FAARRAY_H

#include "FAError.h"

#include <iostream>

#include <vector>
#include <string>
#include <algorithm>

using namespace std;


class FAArray
{
   
    protected:
	
    vector<int> mNdVector;
    vector<int> mDimExistInfo;
	vector<int> mTrueDim;
	vector<double> mValues;
	vector<double>::iterator mValuesP;

    int mSize;
    int mCapacity; 
	
    public:
		 
		//constructor 
        FAArray() ;
		FAArray(int pNumDim, int p1=1, int p2=1, int p3=1, int p4=1, int p5=1, int p6=1, int p7=1, int p8=1);
		FAArray(vector<int>& pNdVector, vector<int>& pDimExistInfo, vector<double>& pValues) ;
		FAArray(vector<int>& pNdVector, vector<int>& pDimExistInfo );
		FAArray(const FAArray& pStencilArray);
		~FAArray();
		 
		//member functions
        FAArray& operator=(const FAArray& pStencilArray);
        FAArray& operator+=(const FAArray& pStencilArray);
        FAArray& operator-=(const FAArray& pStencilArray);
        FAArray& operator*=(const FAArray& pStencilArray);
		FAArray& operator+(const FAArray& pStencilArray);
        FAArray& operator-(const FAArray& pStencilArray);
        FAArray& operator*(const FAArray& pStencilArray);


        FAArray& multConst(double& pVal);
        FAArray& addConst(double& pVal); 
		double l2norm();
		void sortArray(int pStart, int pEnd, string pStr);

        //inline functions
        inline int size() { return mValues.size();};
        inline int capacity() { return mValues.capacity();};
        inline void resize(int pNewSize) 
        {
            mValues.resize(pNewSize);            
        }
        
		inline double& FAArray::operator[](int p1)
        {
            
#if 0
			mValuesP = mValues.begin();
			try
			{
				if(p1 <= mValues.size())
				{
					return *(mValuesP + p1);  //mValues[p1];  
				}
				else
				{
					throw new FAErrorStencilArray("access violation: error from bounds checking");
				}
			}
            catch(FAErrorStencilArray* pError)
            {
                pError->show();
                pError->getErrorLog().close();
                delete pError;
                exit(1);
            }
#endif
			return mValues[p1];
        };

        inline double& FAArray::operator()(int p1)
        {
            
#if 0
			mValuesP = mValues.begin();
			try
			{
				if(p1 <= mValues.size())
				{
					return *(mValuesP + p1);  //mValues[p1];  
				}
				else
				{
					throw new FAErrorStencilArray("access violation: error from bounds checking");
				}
			}
            catch(FAErrorStencilArray* pError)
            {
                pError->show();
                pError->getErrorLog().close();
                delete pError;
                exit(1);
            }
#endif
			return mValues[p1];
        };

		inline double& FAArray::operator()(int p1, int p2)
        {
            
			int pSize1, pSize2;
			pSize1 = mTrueDim[0];
			pSize2 = mTrueDim[1];
			
#if 0
			mValuesP = mValues.begin();
			try
			{
				if( (pSize1*pSize2) <= mValues.size())
				{
					return *(mValuesP + p1*pSize2 + p2); //mValues[p1*pSize2 + p2];  
				}
				else
				{
					throw new FAErrorStencilArray("access violation: error from bounds checking");
				}
			}
            catch(FAErrorStencilArray* pError)
            {
                pError->show();
                pError->getErrorLog().close();
                delete pError;
                exit(1);
            }
#endif
			return mValues[p1*pSize2 + p2];
        };

		inline double& FAArray::operator()(int p1, int p2, int p3)
        {
            
			int pSize1, pSize2, pSize3;
			pSize1 = mTrueDim[0];
			pSize2 = mTrueDim[1];
			pSize3 = mTrueDim[2];
			
#if 0
			mValuesP = mValues.begin();
			try
			{
				if( (pSize1*pSize2*pSize3) <= mValues.size())
				{
					return *(mValuesP + p1*(pSize2*pSize3) + p2*pSize3 + p3);  //mValues[p1*(pSize2*pSize3) + p2*pSize3 + p3];  
				}
				else
				{
					throw new FAErrorStencilArray("access violation: error from bounds checking");
				}
			}
            catch(FAErrorStencilArray* pError)
            {
                pError->show();
                pError->getErrorLog().close();
                delete pError;
                exit(1);
            }
#endif
			return mValues[p1*(pSize2*pSize3) + p2*pSize3 + p3]; 
        };

		inline double& FAArray::operator()(int p1, int p2, int p3, int p4)
        {
            
			int pSize1, pSize2, pSize3, pSize4;
			pSize1 = mTrueDim[0];
			pSize2 = mTrueDim[1];
			pSize3 = mTrueDim[2];
			pSize4 = mTrueDim[3];
			
#if 0
			mValuesP = mValues.begin();
			try
			{
				if( (pSize1*pSize2*pSize3*pSize3) <= mValues.size())
				{
					return *(mValuesP + p1*(pSize2*pSize3*pSize4) + p2*(pSize3*pSize4) + p3*pSize4 + p4); //mValues[p1*(pSize2*pSize3*pSize4) + p2*(pSize3*pSize4) + p3*pSize4 + p4];  
				}
				else
				{
					throw new FAErrorStencilArray("access violation: error from bounds checking");
				}
			}
            catch(FAErrorStencilArray* pError)
            {
                pError->show();
                pError->getErrorLog().close();
                delete pError;
                exit(1);
            }
#endif
			return mValues[p1*(pSize2*pSize3*pSize4) + p2*(pSize3*pSize4) + p3*pSize4 + p4];
        };
 
		//5D
		inline double& FAArray::operator()(int p1, int p2, int p3, int p4, int p5)
        {
            
			int pSize1, pSize2, pSize3, pSize4, pSize5;
			pSize1 = mTrueDim[0];
			pSize2 = mTrueDim[1];
			pSize3 = mTrueDim[2];
			pSize4 = mTrueDim[3];
			pSize5 = mTrueDim[4];
			
			return mValues[p1*(pSize2*pSize3*pSize4*pSize5) + p2*(pSize3*pSize4*pSize5) + p3*(pSize4*pSize5) + p4*pSize5 + p5];
        };

		//6D
		inline double& FAArray::operator()(int p1, int p2, int p3, int p4, int p5, int p6)
        {
            
			int pSize1, pSize2, pSize3, pSize4, pSize5, pSize6;
			pSize1 = mTrueDim[0];
			pSize2 = mTrueDim[1];
			pSize3 = mTrueDim[2];
			pSize4 = mTrueDim[3];
			pSize5 = mTrueDim[4];
			pSize6 = mTrueDim[5];
			
			return mValues[p1*(pSize2*pSize3*pSize4*pSize5*pSize6) + p2*(pSize3*pSize4*pSize5*pSize6) + p3*(pSize4*pSize5*pSize6) 
							+ p4*(pSize5*pSize6) + p5*pSize6 + p6];
        };

		double sumTotal();
        double minTotal();
        double maxTotal();
        
#if 0
		double sumOneDir(int pDir);
        double minOneDir(int pDir);
        double maxOneDir(int pDir); 
#endif

		void show();

		//accessor methods
		vector<int>& getNdVector() { return mNdVector; };
		vector<int>& getDimExistInfo() { return mDimExistInfo;};
		vector<int>& getTrueDim() { return mTrueDim;};
		vector<double>& getValues() { return mValues;};

		//mutator methods
		void setNdVector(vector<int>& pNdVector) { mNdVector = pNdVector;};
		void setDimExistInfo(vector<int>& pDimExistInfo) { mDimExistInfo = pDimExistInfo;};
		void setTrueDim(vector<int>& pTrueDim) { mTrueDim = pTrueDim; };
		void setValues(vector<double>& pValues) { mValues = pValues;};


};

#endif                              


