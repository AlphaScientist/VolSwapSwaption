#ifndef __FAERROR_H
#define __FAERROR_H

#include <fstream>
#include <vector>
#include <string>

using namespace std;



class FAError
{
   
    private:
	
		string mErrorMessage;
		ofstream mErrorLog;

    public:
		 
        //constructor 
        FAError();
		FAError(string pErrorMessage);
		virtual ~FAError();

		virtual void show();
       
		//accessor methods
		string getErrorMessage() { return mErrorMessage; };
		ofstream& getErrorLog() { return mErrorLog; };
		
		//mutator methods
		void setErrorMessage(string pErrorMessage) { mErrorMessage = pErrorMessage; };
		//void setErrorLog(ofstream& pErrorLog) { mErrorLog = pErrorLog; };
		
};

#endif                              


