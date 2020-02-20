/**
 *  Filename : FACommonLib.h
 *  All rights reserved.
 */

#ifndef FACOMMONLIB_H
#define FACOMMONLIB_H

#include <cmath>

template<class T> static inline const T& max ( const T& a, const T& b ){
	return (b < a) ? a : b;
} 

template<class T> static inline const T& min ( const T& a, const T& b ){
	return (b < a) ? b : a;
} 

static inline bool fpequal ( const double a, const double b, const double tol){
        return fabs(b - a) <= (tol * (fabs(b) + fabs(a)));
}

static inline bool fplequal ( const double a, const double b, const double tol){
        return (a) <= (b) + (tol * (fabs(b) + fabs(a)));
}


static inline bool fppmequal ( const double a, const double b, const double tol){
	return fabs(b - a) <= (tol * max(fabs(b), fabs(a)));
}

static inline bool fppmlequal ( const double a, const double b, const double tol){
	return (b - a) > (-tol * max(fabs(b), fabs(a)));
}

static inline bool fppmlthan ( const double a, const double b, const double tol){
	return (b - a) > (tol * max(fabs(b), fabs(a)));
}


#endif // FACOMMONLIB_H
