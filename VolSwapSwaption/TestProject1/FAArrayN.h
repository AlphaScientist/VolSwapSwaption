#ifndef __FA_ARRAY_H__
#define __FA_ARRAY_H__

#include <string.h>
#include <stdio.h>
#include <stdarg.h>

// Environment

#if (defined(WIN32) || defined(WIN64))
#define MSVC 1
#else
#define MSVC 0
#endif

// Compiler settings

#ifndef FA_CHECK_BOUNDS_FLAG
#ifdef _DEBUG
#define FA_CHECK_BOUNDS_FLAG 1
#else
#define FA_CHECK_BOUNDS_FLAG 0
#endif
#endif

#ifndef FA_USE_REF_COUNT
#define FA_USE_REF_COUNT 0
#endif

#ifndef FA_USE_NAMESPACE
#define FA_USE_NAMESPACE 0
#endif


// Setting-dependent macros

#if FA_CHECK_BOUNDS_FLAG
#define FA_CHECK_MATCH(src) check_match(src)
#define FA_CHECK_BOUNDS_1D(b0)                     check_bounds(b0)
#define FA_CHECK_COORDS_1D(i0)                     check_coords(i0)
#define FA_CHECK_BOUNDS_2D(b0, b1)                 check_bounds(b0, b1)
#define FA_CHECK_COORDS_2D(i0, i1)                 check_coords(i0, i1)
#define FA_CHECK_BOUNDS_3D(b0, b1, b2)             check_bounds(b0, b1, b2)
#define FA_CHECK_COORDS_3D(i0, i1, i2)             check_coords(i0, i1, i2)
#define FA_CHECK_BOUNDS_4D(b0, b1, b2, b3)         check_bounds(b0, b1, b2, b3)
#define FA_CHECK_COORDS_4D(i0, i1, i2, i3)         check_coords(i0, i1, i2, i3)
#define FA_CHECK_BOUNDS_5D(b0, b1, b2, b3, b4)     check_bounds(b0, b1, b2, b3, b4)
#define FA_CHECK_COORDS_5D(i0, i1, i2, i3, i4)     check_coords(i0, i1, i2, i3, i4)
#define FA_CHECK_BOUNDS_6D(b0, b1, b2, b3, b4, b5) check_bounds(b0, b1, b2, b3, b4, b5)
#define FA_CHECK_COORDS_6D(i0, i1, i2, i3, i4, i5) check_coords(i0, i1, i2, i3, i4, i5)
#else
#define FA_CHECK_MATCH(src)
#define FA_CHECK_BOUNDS_1D(b0)
#define FA_CHECK_COORDS_1D(i0) 
#define FA_CHECK_BOUNDS_2D(b0, b1)
#define FA_CHECK_COORDS_2D(i0, i1) 
#define FA_CHECK_BOUNDS_3D(b0, b1, b2)
#define FA_CHECK_COORDS_3D(i0, i1, i2) 
#define FA_CHECK_BOUNDS_4D(b0, b1, b2, b3)
#define FA_CHECK_COORDS_4D(i0, i1, i2, i3) 
#define FA_CHECK_BOUNDS_5D(b0, b1, b2, b3, b4)
#define FA_CHECK_COORDS_5D(i0, i1, i2, i3, i4) 
#define FA_CHECK_BOUNDS_6D(b0, b1, b2, b3, b4, b5)
#define FA_CHECK_COORDS_6D(i0, i1, i2, i3, i4, i5) 
#endif

#if FA_USE_REF_COUNT
#define MUTATE(f) ((this_t*)this)->mutate(f)
#else
#define MUTATE(f)
#endif

#if FA_USE_NAMESPACE
#define FA_NS_BEGIN    namespace FA {
#define FA_NS_END      };
#else
#define FA_NS_BEGIN
#define FA_NS_END
#endif

// Base types

typedef size_t SZ;

FA_NS_BEGIN

// Exceptions

// TODO - move strings to language-dependent list, e.g. English, German or French.
// Note - not as simple as it appears, because many strings are hard-coded in FA code.

#define FA_EXCEPTION_BUF_SIZE	1024

class FAException {
public:
	FAException() : msg_(0) {}
	FAException(const char* msg, ...) { 
		va_list va; 
		va_start(va, msg);
		vprint(msg, va); 
		va_end(va);
	}
	virtual ~FAException() { clear(); }
	const char* getMessage() const { return msg_; }
	void setMessageV(va_list va, const char* msg) { vprint(msg, va); }
protected:
	void clear() { if (msg_ != 0) { delete[] msg_; msg_ = 0; } }
	void copy(const char* msg) { 
		size_t len = msg ? strlen(msg) : 0; 
		msg_ = new char[len + 1]; 
		if (len > 0) 
			strcpy(msg_, msg);
		else
			msg_[0] = 0;
	}
	void vprint(const char* msg, va_list va) {
		char buf[FA_EXCEPTION_BUF_SIZE];
#if MSVC
		_vsnprintf(buf, sizeof(buf), msg, va);
#else
		vsnprintf(buf, sizeof(buf), msg, va);
#endif
		copy(buf);
	}
private:
	char* msg_;
};
class FABoundsException : public FAException {
public:
	FABoundsException() : FAException("index out of range") {}
};
class FAMismatchException : public FAException {
public:
	FAMismatchException() : FAException("operation cannot be completed; operand array sizes are mismatched") {}
};
class FADivideByZeroException : public FAException {
public:
	FADivideByZeroException() : FAException("divide by zero") {}
};
class FADimensionException : public FAException {
public:
	FADimensionException() : FAException("dimension argument out of bounds") {}
};
class FAErrorException : public FAException {
public:
	FAErrorException(const char* msg, int error_type) : FAException(msg), error_type_(error_type) {}
	FAErrorException(int error_type, const char* msg, ...) : FAException(), error_type_(error_type) 
    {
		va_list va; 
		va_start(va, msg);
        setMessageV(va, msg);
		va_end(va);
    }
	int getErrorType() const { return error_type_; }
private:
	int error_type_;
};
class FAFileException : public FAException {		
public:
	FAFileException(int error_type, const char* msg, ...) 
		: FAException(), error_type_(error_type)
    {
		va_list va; 
		va_start(va, msg);
        setMessageV(va, msg);
		va_end(va);
    }
	int getErrorType() const { return error_type_; }
private:
	int error_type_;

};
class FAMemoryException : public FAException {
public:
	FAMemoryException(SZ size, SZ count) : FAException("out of memory; could not allocate %lu x %lu bytes", count, size) ,
        size_(size), count_(count) {}
private:
    SZ size_, count_;
};

// Memory allocation

template<class T>
class FAAlloc {
public:
	static T* alloc(SZ n0) { 
        T* a = new T[n0]; 
        if (a == 0) throw new FAMemoryException(sizeof(T), n0);
        return a;
    }
	static T** alloc(SZ n0, SZ n1) { 
		T** a = new T*[n0];
        if (a == 0) throw new FAMemoryException(sizeof(T*), n0);
		for (SZ i = 0; i < n0; i++) a[i] = alloc(n1);
		return a;
	}
	static T*** alloc(SZ n0, SZ n1, SZ n2) { 
		T*** a = new T**[n0];
        if (a == 0) throw new FAMemoryException(sizeof(T**), n0);
		for (SZ i = 0; i < n0; i++) a[i] = alloc(n1, n2);
		return a;
	}
	static T**** alloc(SZ n0, SZ n1, SZ n2, SZ n3) { 
		T**** a = new T***[n0];
        if (a == 0) throw new FAMemoryException(sizeof(T***), n0);
		for (SZ i = 0; i < n0; i++) a[i] = alloc(n1, n2, n3);
		return a;
	}
	static T***** alloc(SZ n0, SZ n1, SZ n2, SZ n3, SZ n4) { 
		T***** a = new T****[n0];
        if (a == 0) throw new FAMemoryException(sizeof(T****), n0);
		for (SZ i = 0; i < n0; i++) a[i] = alloc(n1, n2, n3, n4);
		return a;
	}
	static T****** alloc(SZ n0, SZ n1, SZ n2, SZ n3, SZ n4, SZ n5) { 
		T****** a = new T*****[n0];
        if (a == 0) throw new FAMemoryException(sizeof(T*****), n0);
		for (SZ i = 0; i < n0; i++) a[i] = alloc(n1, n2, n3, n4, n5);
		return a;
	}

	static void free(T* a, SZ n0) { delete[] a; }
	static void free(T** a, SZ n0, SZ n1) { 
		for (SZ i = 0; i < n0; i++) free(a[i], n1);
		delete[] a; 
	}
	static void free(T*** a, SZ n0, SZ n1, SZ n2) { 
		for (SZ i = 0; i < n0; i++) free(a[i], n1, n2);
		delete[] a; 
	}
	static void free(T**** a, SZ n0, SZ n1, SZ n2, SZ n3) { 
		for (SZ i = 0; i < n0; i++) free(a[i], n1, n2, n3);
		delete[] a; 
	}
	static void free(T***** a, SZ n0, SZ n1, SZ n2, SZ n3, SZ n4) { 
		for (SZ i = 0; i < n0; i++) free(a[i], n1, n2, n3, n4);
		delete[] a; 
	}
	static void free(T****** a, SZ n0, SZ n1, SZ n2, SZ n3, SZ n4, SZ n5) { 
		for (SZ i = 0; i < n0; i++) free(a[i], n1, n2, n3, n4, n5);
		delete[] a; 
	}
};

// Divide-by-zero error traps for each base type

#include <float.h>

inline void FADivideBy(double& num, double div) {
	if (div > -DBL_EPSILON && div < DBL_EPSILON)
		throw new FADivideByZeroException();
	num /= div;
}
inline void FADivideBy(int& num, int div) {
	if (div == 0)
		throw new FADivideByZeroException();
	num /= div;
}
inline void FADivideBy(long& num, long div) {
	if (div == 0)
		throw new FADivideByZeroException();
	num /= div;
}

// Base array classes

template<class T>
class FAArray1Ref {
public:
    typedef FAArray1Ref<T> this_t;
public:
	FAArray1Ref<T>() : data_(0), n0_(0) {}
	FAArray1Ref<T>(T* data, SZ n0) {
		attach(data, n0);
	}
	FAArray1Ref<T>(const FAArray1Ref<T>& src) {
		attach((T*)src.array(), src.size0());
	}
public:
	SZ size(SZ dim) const { 
		switch(dim) {
		case 0: return n0_;
		default: throw new FABoundsException();
		}
	}
	SZ size0() const { return n0_; }
	T* array() { 
		MUTATE(true);
		return data_; 
	}
	const T* array() const { 
		return const_array();
	}
	T at(SZ i0) const { 
		FA_CHECK_COORDS_1D(i0);
		return data_[i0];
	}
	T& at(SZ i0) { 
		FA_CHECK_COORDS_1D(i0);
		MUTATE(true);
		return data_[i0];
	}
	static void copy(T* dest, const T* src, SZ n0) {
		if (src != dest)
			memcpy(dest, src, sizeof(T) * n0);
	}
	void copy(const T* src, SZ n0) {
		FA_CHECK_BOUNDS_1D(n0);
		MUTATE(true);
		copy(data_, src, n0);
	}
	void copy(const FAArray1Ref<T>& src) { copy(src.array(), src.size0()); }
public:
	const FAArray1Ref<T>& operator=(const FAArray1Ref<T>& src) {
		FA_CHECK_MATCH(src);
		copy(src.array(), src.size0());
		return *this;
	}

	T operator()(SZ i0) const { return at(i0); }
	T& operator()(SZ i0) { return at(i0); }

	const FAArray1Ref<T>& operator+=(const FAArray1Ref<T>& src) {
		FA_CHECK_MATCH(src);
		MUTATE(true);
		T* d = data_;
		const T* s = src.array();
		const T* e = s + n0_;
		for (; s < e; s++, d++) *d += *s;
		return *this;
	}
	const FAArray1Ref<T>& operator-=(const FAArray1Ref<T>& src) {
		FA_CHECK_MATCH(src);
		MUTATE(true);
		T* d = data_;
		const T* s = src.array();
		const T* e = s + n0_;
		for (; s < e; s++, d++) *d -= *s;
		return *this;
	}
	const FAArray1Ref<T>& operator*=(const FAArray1Ref<T>& src) {
		FA_CHECK_MATCH(src);
		MUTATE(true);
		T* d = data_;
		const T* s = src.array();
		const T* e = s + n0_;
		for (; s < e; s++, d++) *d *= *s;
		return *this;
	}
	const FAArray1Ref<T>& operator/=(const FAArray1Ref<T>& src) {
		FA_CHECK_MATCH(src);
		MUTATE(true);
		T* d = data_;
		const T* s = src.array();
		const T* e = s + n0_;
		for (; s < e; s++, d++) FADivideBy(*d, *s);
		return *this;
	}

    void fill(T src) {
		MUTATE(true);
		T* d0 = data_;
		T* e0 = d0 + n0_;
		for (; d0 < e0; d0++) *d0 = src;
    }
    /* 
        Note - this operator is truncated because it will not be called
    */
	const FAArray1Ref<T>& operator=(T src) {
        fill(src);
		return *this;
	}
	const FAArray1Ref<T>& operator+=(T src) {
		MUTATE(true);
		T* d0 = data_;
		T* e0 = d0 + n0_;
		for (; d0 < e0; d0++) *d0 += src;
		return *this;
	}
	const FAArray1Ref<T>& operator-=(T src) {
		MUTATE(true);
		T* d0 = data_;
		T* e0 = d0 + n0_;
		for (; d0 < e0; d0++) *d0 -= src;
		return *this;
	}
	const FAArray1Ref<T>& operator*=(T src) {
		MUTATE(true);
		T* d0 = data_;
		T* e0 = d0 + n0_;
		for (; d0 < e0; d0++) *d0 *= src;
		return *this;
	}
	const FAArray1Ref<T>& operator/=(T src) {
		MUTATE(true);
		T* d0 = data_;
		T* e0 = d0 + n0_;
		for (; d0 < e0; d0++) FADivideBy(*d0, src);
		return *this;
	}

public:
    int compare(const FAArray1Ref<T>& that) const {
        if (size0() < that.size0())
            return -1;
        else if (size0() > that.size0())
            return 1;
        for (SZ i = 0; i < size0(); i++)
        {
            T l = at(i);
            T r = that.at(i);
            if (l < r)
                return -1;
            else if (l > r)
                return 1;
        }
        return 0;
    }
    bool operator< (const FAArray1Ref<T>& that) const { return compare(that) <  0; }
    bool operator<=(const FAArray1Ref<T>& that) const { return compare(that) <= 0; }
    bool operator==(const FAArray1Ref<T>& that) const { return compare(that) == 0; }
    bool operator!=(const FAArray1Ref<T>& that) const { return compare(that) != 0; }
    bool operator>=(const FAArray1Ref<T>& that) const { return compare(that) >= 0; }
    bool operator> (const FAArray1Ref<T>& that) const { return compare(that) >  0; }
	// TODO - standard signature for classes of all dimensions
	//SZ[] sizes() const { SZ[1] s = { n0_ }; return s; }
public:
	void check_bounds(SZ b0) const { 
		if (b0 > n0_) throw new FABoundsException(); 
	}
	void check_coords(SZ i0) const { 
		if (i0 >= n0_) throw new FABoundsException(); 
	}
	void check_match(const FAArray1Ref<T>& that) const { 
		if (that.size0() != n0_) throw new FAMismatchException(); 
	}
protected:
	void attach(T* data, SZ n0) {
		data_ = data;
		n0_ = n0;
	}
	void detach() {
		data_ = 0;
		n0_ = 0;
	}
	virtual void mutate(bool writable) {}
	const T* const_array() const { return data_; }
private:
	T* data_;
	SZ n0_;
};

template<class T>
class FAArray2Ref {
public:
    typedef FAArray2Ref<T> this_t;
public:
	FAArray2Ref<T>() : data_(0), n0_(0), n1_(0) {}
	FAArray2Ref<T>(T** data, SZ n0, SZ n1) {
		attach(data, n0, n1);
	}
	FAArray2Ref<T>(const FAArray2Ref<T>& src) {
		attach((T**)src.array(), src.size0(), src.size1());
	}
public:
	SZ size(SZ dim) const { 
		switch(dim) {
		case 0: return n0_;
		case 1: return n1_;
		default: throw new FABoundsException();
		}
	}
	SZ size0() const { return n0_; }
	SZ size1() const { return n1_; }
	T** array() { 
		MUTATE(true);
		return data_; 
	}
	const T* const* array() const { 
		return const_array();
	}
	T at(SZ i0, SZ i1) const { 
		FA_CHECK_COORDS_2D(i0, i1);
		return data_[i0][i1];
	}
	T& at(SZ i0, SZ i1) { 
		FA_CHECK_COORDS_2D(i0, i1);
		MUTATE(true);
		return data_[i0][i1];
	}
	FAArray1Ref<T> at(SZ i0) const {
		FA_CHECK_COORDS_1D(i0);
		MUTATE(true);
		return FAArray1Ref<T>(data_[i0], n1_);
	}
	static void copy(T** dest, const T* const* src, SZ n0, SZ n1) {
		if ((T**)src != dest)
		{
			for (SZ i = 0; i < n0; i++)
				FAArray1Ref<T>::copy(dest[i], src[i], n1);
		}
	}
	void copy(const T* const* src, SZ n0, SZ n1) {
		FA_CHECK_BOUNDS_2D(n0, n1);
		MUTATE(true);
		copy(data_, src, n0, n1);
	}
	void copy(const FAArray2Ref<T>& src) { copy(src.array(), src.size0(), src.size1()); }
public:
	const FAArray2Ref<T>& operator=(const FAArray2Ref<T>& src) {
		FA_CHECK_MATCH(src);
		copy(src.array(), src.size0(), src.size1());
		return *this;
	}

	T operator()(SZ i0, SZ i1) const { return at(i0, i1); }
	T& operator()(SZ i0, SZ i1) { return at(i0, i1); }
	FAArray1Ref<T> operator()(SZ i0) const { return at(i0); }

	const FAArray2Ref<T>& operator+=(const FAArray2Ref<T>& src) {
		FA_CHECK_MATCH(src);
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) += src.at(i0);
		return *this;
	}
	const FAArray2Ref<T>& operator-=(const FAArray2Ref<T>& src) {
		FA_CHECK_MATCH(src);
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) -= src.at(i0);
		return *this;
	}
	const FAArray2Ref<T>& operator*=(const FAArray2Ref<T>& src) {
		FA_CHECK_MATCH(src);
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) *= src.at(i0);
		return *this;
	}
	const FAArray2Ref<T>& operator/=(const FAArray2Ref<T>& src) {
		FA_CHECK_MATCH(src);
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) /= src.at(i0);
		return *this;
	}

    void fill(T src) {
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0).fill(src);
    }
	const FAArray2Ref<T>& operator=(T src) {
        fill(src);
		return *this;
	}
	const FAArray2Ref<T>& operator+=(T src) {
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) += src;
		return *this;
	}
	const FAArray2Ref<T>& operator-=(T src) {
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) -= src;
		return *this;
	}
	const FAArray2Ref<T>& operator*=(T src) {
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) *= src;
		return *this;
	}
	const FAArray2Ref<T>& operator/=(T src) {
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) /= src;
		return *this;
	}

public:
    int compare(const FAArray2Ref<T>& that) const {
        if (size0() < that.size0())
            return -1;
        else if (size0() > that.size0())
            return 1;
        for (SZ i = 0; i < size0(); i++)
        {
            int c = at(i).compare(that.at(i));
            if (c != 0)
                return c;
        }
        return 0;
    }
    bool operator< (const FAArray2Ref<T>& that) const { return compare(that) <  0; }
    bool operator<=(const FAArray2Ref<T>& that) const { return compare(that) <= 0; }
    bool operator==(const FAArray2Ref<T>& that) const { return compare(that) == 0; }
    bool operator!=(const FAArray2Ref<T>& that) const { return compare(that) != 0; }
    bool operator>=(const FAArray2Ref<T>& that) const { return compare(that) >= 0; }
    bool operator> (const FAArray2Ref<T>& that) const { return compare(that) >  0; }

public:
	void check_bounds(SZ b0, SZ b1) const { 
		if (b0 > n0_) throw new FABoundsException(); 
		if (b1 > n1_) throw new FABoundsException(); 
	}
	void check_coords(SZ i0, SZ i1) const { 
		if (i0 >= n0_) throw new FABoundsException(); 
		if (i1 >= n1_) throw new FABoundsException(); 
	}
	void check_coords(SZ i0) const { 
		if (i0 >= n0_) throw new FABoundsException(); 
	}
	void check_match(const FAArray2Ref<T>& that) const { 
		if (that.size0() != n0_) throw new FAMismatchException(); 
		if (that.size1() != n1_) throw new FAMismatchException(); 
	}
protected:
	void attach(T** data, SZ n0, SZ n1) {
		data_ = data;
		n0_ = n0;
		n1_ = n1;
	}
	void detach() {
		data_ = 0;
		n0_ = 0;
		n1_ = 0;
	}
	virtual void mutate(bool writable) {}
	const T* const* const_array() const { return (const T* const*)data_; }
private:
	T** data_;
	SZ n0_, n1_;
};

template<class T>
class FAArray3Ref {
public:
    typedef FAArray3Ref<T> this_t;
public:
	FAArray3Ref<T>() : data_(0), n0_(0), n1_(0), n2_(0) {}
	FAArray3Ref<T>(T*** data, SZ n0, SZ n1, SZ n2) {
		attach(data, n0, n1, n2);
	}
	FAArray3Ref<T>(const FAArray3Ref<T>& src) {
		attach((T***)src.array(), src.size0(), src.size1(), src.size2());
	}
public:
	SZ size(SZ dim) const { 
		switch(dim) {
		case 0: return n0_;
		case 1: return n1_;
        case 2: return n2_;
		default: throw new FABoundsException();
		}
	}
	SZ size0() const { return n0_; }
	SZ size1() const { return n1_; }
	SZ size2() const { return n2_; }
	T*** array() { 
		MUTATE(true);
		return data_; 
	}
	const T* const* const* array() const { 
		return const_array();
	}
	T at(SZ i0, SZ i1, SZ i2) const { 
		FA_CHECK_COORDS_3D(i0, i1, i2);
		return data_[i0][i1][i2];
	}
	T& at(SZ i0, SZ i1, SZ i2) { 
		FA_CHECK_COORDS_3D(i0, i1, i2);
		MUTATE(true);
		return data_[i0][i1][i2];
	}
	FAArray2Ref<T> at(SZ i0) const {
		FA_CHECK_COORDS_1D(i0);
		MUTATE(true);
		return FAArray2Ref<T>(data_[i0], n1_, n2_);
	}
	FAArray1Ref<T> at(SZ i0, SZ i1) const {
		FA_CHECK_COORDS_2D(i0, i1);
		MUTATE(true);
		return FAArray1Ref<T>(data_[i0][i1], n2_);
	}
	static void copy(T*** dest, const T* const* const* src, SZ n0, SZ n1, SZ n2) {
		if ((T***)src != dest)
		{
			for (SZ i = 0; i < n0; i++)
				FAArray2Ref<T>::copy(dest[i], src[i], n1, n2);
		}
	}
	void copy(const T* const* const* src, SZ n0, SZ n1, SZ n2) {
		FA_CHECK_BOUNDS_3D(n0, n1, n2);
		MUTATE(true);
		copy(data_, src, n0, n1, n2);
	}
	void copy(const FAArray3Ref<T>& src) { copy(src.array(), src.size0(), src.size1(), src.size2()); }
public:
	const FAArray3Ref<T>& operator=(const FAArray3Ref<T>& src) {
		FA_CHECK_MATCH(src);
		copy(src.array(), src.size0(), src.size1(), src.size2());
		return *this;
	}

	T operator()(SZ i0, SZ i1, SZ i2) const { return at(i0, i1, i2); }
	T& operator()(SZ i0, SZ i1, SZ i2) { return at(i0, i1, i2); }
	FAArray2Ref<T> operator()(SZ i0) { return at(i0); }
	FAArray1Ref<T> operator()(SZ i0, SZ i1) { return at(i0, i1); }

	const FAArray3Ref<T>& operator+=(const FAArray3Ref<T>& src) {
		FA_CHECK_MATCH(src);
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) += src.at(i0);
		return *this;
	}
	const FAArray3Ref<T>& operator-=(const FAArray3Ref<T>& src) {
		FA_CHECK_MATCH(src);
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) -= src.at(i0);
		return *this;
	}
	const FAArray3Ref<T>& operator*=(const FAArray3Ref<T>& src) {
		FA_CHECK_MATCH(src);
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) *= src.at(i0);
		return *this;
	}
	const FAArray3Ref<T>& operator/=(const FAArray3Ref<T>& src) {
		FA_CHECK_MATCH(src);
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) /= src.at(i0);
		return *this;
	}

    void fill(T src) {
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0).fill(src);
    }
	const FAArray3Ref<T>& operator=(T src) {
        fill(src);
		return *this;
	}
	const FAArray3Ref<T>& operator+=(T src) {
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) += src;
		return *this;
	}
	const FAArray3Ref<T>& operator-=(T src) {
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) -= src;
		return *this;
	}
	const FAArray3Ref<T>& operator*=(T src) {
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) *= src;
		return *this;
	}
	const FAArray3Ref<T>& operator/=(T src) {
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) /= src;
		return *this;
	}

public:
    int compare(const FAArray3Ref<T>& that) const {
        if (size0() < that.size0())
            return -1;
        else if (size0() > that.size0())
            return 1;
        for (SZ i = 0; i < size0(); i++)
        {
            int c = at(i).compare(that.at(i));
            if (c != 0)
                return c;
        }
        return 0;
    }
    bool operator< (const FAArray3Ref<T>& that) const { return compare(that) <  0; }
    bool operator<=(const FAArray3Ref<T>& that) const { return compare(that) <= 0; }
    bool operator==(const FAArray3Ref<T>& that) const { return compare(that) == 0; }
    bool operator!=(const FAArray3Ref<T>& that) const { return compare(that) != 0; }
    bool operator>=(const FAArray3Ref<T>& that) const { return compare(that) >= 0; }
    bool operator> (const FAArray3Ref<T>& that) const { return compare(that) >  0; }

public:
	void check_bounds(SZ b0, SZ b1, SZ b2) const { 
		if (b0 > n0_) throw new FABoundsException(); 
		if (b1 > n1_) throw new FABoundsException(); 
		if (b2 > n2_) throw new FABoundsException(); 
	}
	void check_coords(SZ i0, SZ i1, SZ i2) const { 
		if (i0 >= n0_) throw new FABoundsException(); 
		if (i1 >= n1_) throw new FABoundsException(); 
        if (i2 >= n2_) throw new FABoundsException(); 
	}
	void check_coords(SZ i0, SZ i1) const { 
		if (i0 >= n0_) throw new FABoundsException(); 
		if (i1 >= n1_) throw new FABoundsException(); 
	}
	void check_coords(SZ i0) const { 
		if (i0 >= n0_) throw new FABoundsException(); 
	}
	void check_match(const FAArray3Ref<T>& that) const { 
		if (that.size0() != n0_) throw new FAMismatchException(); 
		if (that.size1() != n1_) throw new FAMismatchException(); 
		if (that.size2() != n2_) throw new FAMismatchException(); 
	}
protected:
	void attach(T*** data, SZ n0, SZ n1, SZ n2) {
		data_ = data;
		n0_ = n0;
		n1_ = n1;
        n2_ = n2;
	}
	void detach() {
		data_ = 0;
		n0_ = 0;
		n1_ = 0;
        n2_ = 0;
	}
	virtual void mutate(bool writable) {}
	const T* const* const* const_array() const { return (const T* const* const*)data_; }
private:
	T*** data_;
	SZ n0_, n1_, n2_;
};

template<class T>
class FAArray4Ref {
public:
    typedef FAArray4Ref<T> this_t;
public:
	FAArray4Ref<T>() : data_(0), n0_(0), n1_(0), n2_(0), n3_(0) {}
	FAArray4Ref<T>(T**** data, SZ n0, SZ n1, SZ n2, SZ n3) {
		attach(data, n0, n1, n2, n3);
	}
	FAArray4Ref<T>(const FAArray4Ref<T>& src) {
		attach((T****)src.array(), src.size0(), src.size1(), src.size2(), src.size3());
	}
public:
	SZ size(SZ dim) const { 
		switch(dim) {
		case 0: return n0_;
		case 1: return n1_;
        case 2: return n2_;
        case 3: return n3_;
		default: throw new FABoundsException();
		}
	}
	SZ size0() const { return n0_; }
	SZ size1() const { return n1_; }
	SZ size2() const { return n2_; }
	SZ size3() const { return n3_; }
	T**** array() { 
		MUTATE(true);
		return data_; 
	}
	const T* const* const* const* array() const { 
		return const_array();
	}
	T at(SZ i0, SZ i1, SZ i2, SZ i3) const { 
		FA_CHECK_COORDS_4D(i0, i1, i2, i3);
		return data_[i0][i1][i2][i3];
	}
	T& at(SZ i0, SZ i1, SZ i2, SZ i3) { 
		FA_CHECK_COORDS_4D(i0, i1, i2, i3);
		MUTATE(true);
		return data_[i0][i1][i2][i3];
	}
	FAArray3Ref<T> at(SZ i0) const {
		FA_CHECK_COORDS_1D(i0);
		MUTATE(true);
		return FAArray3Ref<T>(data_[i0], n1_, n2_, n3_);
	}
	FAArray2Ref<T> at(SZ i0, SZ i1) const {
		FA_CHECK_COORDS_2D(i0, i1);
		MUTATE(true);
		return FAArray2Ref<T>(data_[i0][i1], n2_, n3_);
	}
	FAArray1Ref<T> at(SZ i0, SZ i1, SZ i2) const {
		FA_CHECK_COORDS_3D(i0, i1, i2);
		MUTATE(true);
		return FAArray1Ref<T>(data_[i0][i1][i2], n3_);
	}
	static void copy(T**** dest, const T* const* const* const* src, SZ n0, SZ n1, SZ n2, SZ n3) {
		if ((T****)src != dest)
		{
			for (SZ i = 0; i < n0; i++)
				FAArray3Ref<T>::copy(dest[i], src[i], n1, n2, n3);
		}
	}
	void copy(const T* const* const* const* src, SZ n0, SZ n1, SZ n2, SZ n3) {
		FA_CHECK_BOUNDS_4D(n0, n1, n2, n3);
		MUTATE(true);
		copy(data_, src, n0, n1, n2, n3);
	}
	void copy(const FAArray4Ref<T>& src) { copy(src.array(), src.size0(), src.size1(), src.size2(), src.size3()); }
public:
	const FAArray4Ref<T>& operator=(const FAArray4Ref<T>& src) {
		FA_CHECK_MATCH(src);
		copy(src.array(), src.size0(), src.size1(), src.size2(), src.size3());
		return *this;
	}

	T operator()(SZ i0, SZ i1, SZ i2, SZ i3) const { return at(i0, i1, i2, i3); }
	T& operator()(SZ i0, SZ i1, SZ i2, SZ i3) { return at(i0, i1, i2, i3); }
	FAArray3Ref<T> operator()(SZ i0) { return at(i0); }
	FAArray2Ref<T> operator()(SZ i0, SZ i1) { return at(i0, i1); }
	FAArray1Ref<T> operator()(SZ i0, SZ i1, SZ i2) { return at(i0, i1, i2); }

	const FAArray4Ref<T>& operator+=(const FAArray4Ref<T>& src) {
		FA_CHECK_MATCH(src);
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) += src.at(i0);
		return *this;
	}
	const FAArray4Ref<T>& operator-=(const FAArray4Ref<T>& src) {
		FA_CHECK_MATCH(src);
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) -= src.at(i0);
		return *this;
	}
	const FAArray4Ref<T>& operator*=(const FAArray4Ref<T>& src) {
		FA_CHECK_MATCH(src);
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) *= src.at(i0);
		return *this;
	}
	const FAArray4Ref<T>& operator/=(const FAArray4Ref<T>& src) {
		FA_CHECK_MATCH(src);
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) /= src.at(i0);
		return *this;
	}

    void fill(T src) {
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0).fill(src);
    }
	const FAArray4Ref<T>& operator=(T src) {
        fill(src);
		return *this;
	}
	const FAArray4Ref<T>& operator+=(T src) {
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) += src;
		return *this;
	}
	const FAArray4Ref<T>& operator-=(T src) {
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) -= src;
		return *this;
	}
	const FAArray4Ref<T>& operator*=(T src) {
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) *= src;
		return *this;
	}
	const FAArray4Ref<T>& operator/=(T src) {
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) /= src;
		return *this;
	}


public:
    int compare(const FAArray4Ref<T>& that) const {
        if (size0() < that.size0())
            return -1;
        else if (size0() > that.size0())
            return 1;
        for (SZ i = 0; i < size0(); i++)
        {
            int c = at(i).compare(that.at(i));
            if (c != 0)
                return c;
        }
        return 0;
    }
    bool operator< (const FAArray4Ref<T>& that) const { return compare(that) <  0; }
    bool operator<=(const FAArray4Ref<T>& that) const { return compare(that) <= 0; }
    bool operator==(const FAArray4Ref<T>& that) const { return compare(that) == 0; }
    bool operator!=(const FAArray4Ref<T>& that) const { return compare(that) != 0; }
    bool operator>=(const FAArray4Ref<T>& that) const { return compare(that) >= 0; }
    bool operator> (const FAArray4Ref<T>& that) const { return compare(that) >  0; }

public:
	void check_bounds(SZ b0, SZ b1, SZ b2, SZ b3) const { 
		if (b0 > n0_) throw new FABoundsException(); 
		if (b1 > n1_) throw new FABoundsException(); 
		if (b2 > n2_) throw new FABoundsException(); 
        if (b3 > n3_) throw new FABoundsException(); 
	}
	void check_coords(SZ i0, SZ i1, SZ i2, SZ i3) const { 
		if (i0 >= n0_) throw new FABoundsException(); 
		if (i1 >= n1_) throw new FABoundsException(); 
        if (i2 >= n2_) throw new FABoundsException(); 
        if (i3 >= n3_) throw new FABoundsException(); 
	}
	void check_coords(SZ i0, SZ i1, SZ i2) const { 
		if (i0 >= n0_) throw new FABoundsException(); 
		if (i1 >= n1_) throw new FABoundsException(); 
        if (i2 >= n2_) throw new FABoundsException(); 
	}
	void check_coords(SZ i0, SZ i1) const { 
		if (i0 >= n0_) throw new FABoundsException(); 
		if (i1 >= n1_) throw new FABoundsException(); 
	}
	void check_coords(SZ i0) const { 
		if (i0 >= n0_) throw new FABoundsException(); 
	}
	void check_match(const FAArray4Ref<T>& that) const { 
		if (that.size0() != n0_) throw new FAMismatchException(); 
		if (that.size1() != n1_) throw new FAMismatchException(); 
		if (that.size2() != n2_) throw new FAMismatchException(); 
		if (that.size3() != n3_) throw new FAMismatchException(); 
	}
protected:
	void attach(T**** data, SZ n0, SZ n1, SZ n2, SZ n3) {
		data_ = data;
		n0_ = n0;
		n1_ = n1;
        n2_ = n2;
        n3_ = n3;
	}
	void detach() {
		data_ = 0;
		n0_ = 0;
		n1_ = 0;
        n2_ = 0;
        n3_ = 0;
	}
	virtual void mutate(bool writable) {}
	const T* const* const* const* const_array() const { return (const T* const* const* const*)data_; }
private:
	T**** data_;
	SZ n0_, n1_, n2_, n3_;
};

template<class T>
class FAArray5Ref {
public:
    typedef FAArray5Ref<T> this_t;
public:
	FAArray5Ref<T>() : data_(0), n0_(0), n1_(0), n2_(0), n3_(0), n4_(0) {}
	FAArray5Ref<T>(T***** data, SZ n0, SZ n1, SZ n2, SZ n3, SZ n4) {
		attach(data, n0, n1, n2, n3, n4);
	}
	FAArray5Ref<T>(const FAArray5Ref<T>& src) {
		attach((T*****)src.array(), src.size0(), src.size1(), src.size2(), src.size3(), src.size4());
	}
public:
	SZ size(SZ dim) const { 
		switch(dim) {
		case 0: return n0_;
		case 1: return n1_;
        case 2: return n2_;
        case 3: return n3_;
        case 4: return n4_;
		default: throw new FABoundsException();
		}
	}
	SZ size0() const { return n0_; }
	SZ size1() const { return n1_; }
	SZ size2() const { return n2_; }
	SZ size3() const { return n3_; }
	SZ size4() const { return n4_; }
	T***** array() { 
		MUTATE(true);
		return data_; 
	}
	const T* const* const* const* const* array() const { 
		return const_array();
	}
	T at(SZ i0, SZ i1, SZ i2, SZ i3, SZ i4) const { 
		FA_CHECK_COORDS_5D(i0, i1, i2, i3, i4);
		return data_[i0][i1][i2][i3][i4];
	}
	T& at(SZ i0, SZ i1, SZ i2, SZ i3, SZ i4) { 
		FA_CHECK_COORDS_5D(i0, i1, i2, i3, i4);
		MUTATE(true);
		return data_[i0][i1][i2][i3][i4];
	}
	FAArray4Ref<T> at(SZ i0) const {
		FA_CHECK_COORDS_1D(i0);
		MUTATE(true);
		return FAArray4Ref<T>(data_[i0], n1_, n2_, n3_, n4_);
	}
	FAArray3Ref<T> at(SZ i0, SZ i1) const {
		FA_CHECK_COORDS_2D(i0, i1);
		MUTATE(true);
		return FAArray3Ref<T>(data_[i0][i1], n2_, n3_, n4_);
	}
	FAArray2Ref<T> at(SZ i0, SZ i1, SZ i2) const {
		FA_CHECK_COORDS_3D(i0, i1, i2);
		MUTATE(true);
		return FAArray2Ref<T>(data_[i0][i1][i2], n3_, n4_);
	}
	FAArray1Ref<T> at(SZ i0, SZ i1, SZ i2, SZ i3) const {
		FA_CHECK_COORDS_4D(i0, i1, i2, i3);
		MUTATE(true);
		return FAArray1Ref<T>(data_[i0][i1][i2][i3], n4_);
	}
	static void copy(T***** dest, const T* const* const* const* const* src, SZ n0, SZ n1, SZ n2, SZ n3, SZ n4) {
		if ((T*****)src != dest)
		{
			for (SZ i = 0; i < n0; i++)
				FAArray4Ref<T>::copy(dest[i], src[i], n1, n2, n3, n4);
		}
	}
	void copy(const T* const* const* const* const* src, SZ n0, SZ n1, SZ n2, SZ n3, SZ n4) {
		FA_CHECK_BOUNDS_5D(n0, n1, n2, n3, n4);
		MUTATE(true);
		copy(data_, src, n0, n1, n2, n3, n4);
	}
	void copy(const FAArray5Ref<T>& src) { copy(src.array(), src.size0(), src.size1(), 
        src.size2(), src.size3(), src.size4()); }
public:
	const FAArray5Ref<T>& operator=(const FAArray5Ref<T>& src) {
		FA_CHECK_MATCH(src);
		copy(src.array(), src.size0(), src.size1(), src.size2(), src.size3(), src.size4());
		return *this;
	}

	T operator()(SZ i0, SZ i1, SZ i2, SZ i3, SZ i4) const { return at(i0, i1, i2, i3, i4); }
	T& operator()(SZ i0, SZ i1, SZ i2, SZ i3, SZ i4) { return at(i0, i1, i2, i3, i4); }
	FAArray4Ref<T> operator()(SZ i0) { return at(i0); }
	FAArray3Ref<T> operator()(SZ i0, SZ i1) { return at(i0, i1); }
	FAArray2Ref<T> operator()(SZ i0, SZ i1, SZ i2) { return at(i0, i1, i2); }
	FAArray1Ref<T> operator()(SZ i0, SZ i1, SZ i2, SZ i3) { return at(i0, i1, i2, i3); }

	const FAArray5Ref<T>& operator+=(const FAArray5Ref<T>& src) {
		FA_CHECK_MATCH(src);
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) += src.at(i0);
		return *this;
	}
	const FAArray5Ref<T>& operator-=(const FAArray5Ref<T>& src) {
		FA_CHECK_MATCH(src);
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) -= src.at(i0);
		return *this;
	}
	const FAArray5Ref<T>& operator*=(const FAArray5Ref<T>& src) {
		FA_CHECK_MATCH(src);
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) *= src.at(i0);
		return *this;
	}
	const FAArray5Ref<T>& operator/=(const FAArray5Ref<T>& src) {
		FA_CHECK_MATCH(src);
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) /= src.at(i0);
		return *this;
	}

    void fill(T src) {
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0).fill(src);
    }
	const FAArray5Ref<T>& operator=(T src) {
        fill(src);
		return *this;
	}
	const FAArray5Ref<T>& operator+=(T src) {
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) += src;
		return *this;
	}
	const FAArray5Ref<T>& operator-=(T src) {
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) -= src;
		return *this;
	}
	const FAArray5Ref<T>& operator*=(T src) {
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) *= src;
		return *this;
	}
	const FAArray5Ref<T>& operator/=(T src) {
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) /= src;
		return *this;
	}

public:
    int compare(const FAArray5Ref<T>& that) const {
        if (size0() < that.size0())
            return -1;
        else if (size0() > that.size0())
            return 1;
        for (SZ i = 0; i < size0(); i++)
        {
            int c = at(i).compare(that.at(i));
            if (c != 0)
                return c;
        }
        return 0;
    }
    bool operator< (const FAArray5Ref<T>& that) const { return compare(that) <  0; }
    bool operator<=(const FAArray5Ref<T>& that) const { return compare(that) <= 0; }
    bool operator==(const FAArray5Ref<T>& that) const { return compare(that) == 0; }
    bool operator!=(const FAArray5Ref<T>& that) const { return compare(that) != 0; }
    bool operator>=(const FAArray5Ref<T>& that) const { return compare(that) >= 0; }
    bool operator> (const FAArray5Ref<T>& that) const { return compare(that) >  0; }

public:
	void check_bounds(SZ b0, SZ b1, SZ b2, SZ b3, SZ b4) const { 
		if (b0 > n0_) throw new FABoundsException(); 
		if (b1 > n1_) throw new FABoundsException(); 
		if (b2 > n2_) throw new FABoundsException(); 
        if (b3 > n3_) throw new FABoundsException(); 
        if (b4 > n4_) throw new FABoundsException(); 
	}
	void check_coords(SZ i0, SZ i1, SZ i2, SZ i3, SZ i4) const { 
		if (i0 >= n0_) throw new FABoundsException(); 
		if (i1 >= n1_) throw new FABoundsException(); 
        if (i2 >= n2_) throw new FABoundsException(); 
        if (i3 >= n3_) throw new FABoundsException(); 
        if (i4 >= n4_) throw new FABoundsException(); 
	}
	void check_coords(SZ i0, SZ i1, SZ i2, SZ i3) const { 
		if (i0 >= n0_) throw new FABoundsException(); 
		if (i1 >= n1_) throw new FABoundsException(); 
        if (i2 >= n2_) throw new FABoundsException(); 
        if (i3 >= n3_) throw new FABoundsException(); 
	}
	void check_coords(SZ i0, SZ i1, SZ i2) const { 
		if (i0 >= n0_) throw new FABoundsException(); 
		if (i1 >= n1_) throw new FABoundsException(); 
        if (i2 >= n2_) throw new FABoundsException(); 
	}
	void check_coords(SZ i0, SZ i1) const { 
		if (i0 >= n0_) throw new FABoundsException(); 
		if (i1 >= n1_) throw new FABoundsException(); 
	}
	void check_coords(SZ i0) const { 
		if (i0 >= n0_) throw new FABoundsException(); 
	}
	void check_match(const FAArray5Ref<T>& that) const { 
		if (that.size0() != n0_) throw new FAMismatchException(); 
		if (that.size1() != n1_) throw new FAMismatchException(); 
		if (that.size2() != n2_) throw new FAMismatchException(); 
		if (that.size3() != n3_) throw new FAMismatchException(); 
		if (that.size4() != n4_) throw new FAMismatchException(); 
	}
protected:
	void attach(T***** data, SZ n0, SZ n1, SZ n2, SZ n3, SZ n4) {
		data_ = data;
		n0_ = n0;
		n1_ = n1;
        n2_ = n2;
        n3_ = n3;
        n4_ = n4;
	}
	void detach() {
		data_ = 0;
		n0_ = 0;
		n1_ = 0;
        n2_ = 0;
        n3_ = 0;
        n4_ = 0;
	}
	virtual void mutate(bool writable) {}
	const T* const* const* const* const* const_array() const { return (const T* const* const* const* const*)data_; }
private:
	T***** data_;
	SZ n0_, n1_, n2_, n3_, n4_;
};

template<class T>
class FAArray6Ref {
public:
    typedef FAArray6Ref<T> this_t;
public:
	FAArray6Ref<T>() : data_(0), n0_(0), n1_(0), n2_(0), n3_(0), n4_(0), n5_(0) {}
	FAArray6Ref<T>(T****** data, SZ n0, SZ n1, SZ n2, SZ n3, SZ n4, SZ n5) {
		attach(data, n0, n1, n2, n3, n4, n5);
	}
	FAArray6Ref<T>(const FAArray6Ref<T>& src) {
		attach((T******)src.array(), src.size0(), src.size1(), src.size2(), src.size3(), src.size4(), src.size5());
	}
public:
	SZ size(SZ dim) const { 
		switch(dim) {
		case 0: return n0_;
		case 1: return n1_;
        case 2: return n2_;
        case 3: return n3_;
        case 4: return n4_;
        case 5: return n5_;
		default: throw new FABoundsException();
		}
	}
	SZ size0() const { return n0_; }
	SZ size1() const { return n1_; }
	SZ size2() const { return n2_; }
	SZ size3() const { return n3_; }
	SZ size4() const { return n4_; }
    SZ size5() const { return n5_; }
	T****** array() { 
		MUTATE(true);
		return data_; 
	}
	const T* const* const* const* const* const* array() const { 
		return const_array();
	}
	T at(SZ i0, SZ i1, SZ i2, SZ i3, SZ i4, SZ i5) const { 
		FA_CHECK_COORDS_6D(i0, i1, i2, i3, i4, i5);
		return data_[i0][i1][i2][i3][i4][i5];
	}
	T& at(SZ i0, SZ i1, SZ i2, SZ i3, SZ i4, SZ i5) { 
		FA_CHECK_COORDS_6D(i0, i1, i2, i3, i4, i5);
		MUTATE(true);
		return data_[i0][i1][i2][i3][i4][i5];
	}
	FAArray5Ref<T> at(SZ i0) const {
		FA_CHECK_COORDS_1D(i0);
		MUTATE(true);
		return FAArray5Ref<T>(data_[i0], n1_, n2_, n3_, n4_, n5_);
	}
	FAArray4Ref<T> at(SZ i0, SZ i1) const {
		FA_CHECK_COORDS_2D(i0, i1);
		MUTATE(true);
		return FAArray4Ref<T>(data_[i0][i1], n2_, n3_, n4_, n5_);
	}
	FAArray3Ref<T> at(SZ i0, SZ i1, SZ i2) const {
		FA_CHECK_COORDS_3D(i0, i1, i2);
		MUTATE(true);
		return FAArray3Ref<T>(data_[i0][i1][i2], n3_, n4_, n5_);
	}
	FAArray2Ref<T> at(SZ i0, SZ i1, SZ i2, SZ i3) const {
		FA_CHECK_COORDS_4D(i0, i1, i2, i3);
		MUTATE(true);
		return FAArray2Ref<T>(data_[i0][i1][i2][i3], n4_, n5_);
	}
	FAArray1Ref<T> at(SZ i0, SZ i1, SZ i2, SZ i3, SZ i4) const {
		FA_CHECK_COORDS_5D(i0, i1, i2, i3, i4);
		MUTATE(true);
		return FAArray1Ref<T>(data_[i0][i1][i2][i3][i4], n5_);
	}
	static void copy(T****** dest, const T* const* const* const* const* const* src, SZ n0, SZ n1, SZ n2, SZ n3, SZ n4, SZ n5) {
		if ((T******)src != dest)
		{
			for (SZ i = 0; i < n0; i++)
				FAArray5Ref<T>::copy(dest[i], src[i], n1, n2, n3, n4, n5);
		}
	}
	void copy(const T* const* const* const* const* const* src, SZ n0, SZ n1, SZ n2, SZ n3, SZ n4, SZ n5) {
		FA_CHECK_BOUNDS_6D(n0, n1, n2, n3, n4, n5);
		MUTATE(true);
		copy(data_, src, n0, n1, n2, n3, n4, n5);
	}
	void copy(const FAArray6Ref<T>& src) { copy(src.array(), src.size0(), src.size1(), 
        src.size2(), src.size3(), src.size4(), src.size5()); }
public:
	const FAArray6Ref<T>& operator=(const FAArray6Ref<T>& src) {
		FA_CHECK_MATCH(src);
		copy(src.array(), src.size0(), src.size1(), src.size2(), src.size3(), src.size4(), src.size5());
		return *this;
	}

	T operator()(SZ i0, SZ i1, SZ i2, SZ i3, SZ i4, SZ i5) const { return at(i0, i1, i2, i3, i4, i5); }
	T& operator()(SZ i0, SZ i1, SZ i2, SZ i3, SZ i4, SZ i5) { return at(i0, i1, i2, i3, i4, i5); }
	FAArray5Ref<T> operator()(SZ i0) { return at(i0); }
	FAArray4Ref<T> operator()(SZ i0, SZ i1) { return at(i0, i1); }
	FAArray3Ref<T> operator()(SZ i0, SZ i1, SZ i2) { return at(i0, i1, i2); }
	FAArray2Ref<T> operator()(SZ i0, SZ i1, SZ i2, SZ i3) { return at(i0, i1, i2, i3); }
	FAArray1Ref<T> operator()(SZ i0, SZ i1, SZ i2, SZ i3, SZ i4) { return at(i0, i1, i2, i3, i4); }

	const FAArray6Ref<T>& operator+=(const FAArray6Ref<T>& src) {
		FA_CHECK_MATCH(src);
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) += src.at(i0);
		return *this;
	}
	const FAArray6Ref<T>& operator-=(const FAArray6Ref<T>& src) {
		FA_CHECK_MATCH(src);
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) -= src.at(i0);
		return *this;
	}
	const FAArray6Ref<T>& operator*=(const FAArray6Ref<T>& src) {
		FA_CHECK_MATCH(src);
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) *= src.at(i0);
		return *this;
	}
	const FAArray6Ref<T>& operator/=(const FAArray6Ref<T>& src) {
		FA_CHECK_MATCH(src);
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) /= src.at(i0);
		return *this;
	}

    void fill(T src) {
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0).fill(src);
    }
	const FAArray6Ref<T>& operator=(T src) {
        fill(src);
		return *this;
	}
	const FAArray6Ref<T>& operator+=(T src) {
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) += src;
		return *this;
	}
	const FAArray6Ref<T>& operator-=(T src) {
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) -= src;
		return *this;
	}
	const FAArray6Ref<T>& operator*=(T src) {
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) *= src;
		return *this;
	}
	const FAArray6Ref<T>& operator/=(T src) {
		MUTATE(true);
        for (SZ i0 = 0; i0 < n0_; i0++)
            at(i0) /= src;
		return *this;
	}

public:
    int compare(const FAArray6Ref<T>& that) const {
        if (size0() < that.size0())
            return -1;
        else if (size0() > that.size0())
            return 1;
        for (SZ i = 0; i < size0(); i++)
        {
            int c = at(i).compare(that.at(i));
            if (c != 0)
                return c;
        }
        return 0;
    }
    bool operator< (const FAArray6Ref<T>& that) const { return compare(that) <  0; }
    bool operator<=(const FAArray6Ref<T>& that) const { return compare(that) <= 0; }
    bool operator==(const FAArray6Ref<T>& that) const { return compare(that) == 0; }
    bool operator!=(const FAArray6Ref<T>& that) const { return compare(that) != 0; }
    bool operator>=(const FAArray6Ref<T>& that) const { return compare(that) >= 0; }
    bool operator> (const FAArray6Ref<T>& that) const { return compare(that) >  0; }

public:
	void check_bounds(SZ b0, SZ b1, SZ b2, SZ b3, SZ b4, SZ b5) const { 
		if (b0 > n0_) throw new FABoundsException(); 
		if (b1 > n1_) throw new FABoundsException(); 
		if (b2 > n2_) throw new FABoundsException(); 
        if (b3 > n3_) throw new FABoundsException(); 
        if (b4 > n4_) throw new FABoundsException(); 
        if (b5 > n5_) throw new FABoundsException(); 
	}
	void check_coords(SZ i0, SZ i1, SZ i2, SZ i3, SZ i4, SZ i5) const { 
		if (i0 >= n0_) throw new FABoundsException(); 
		if (i1 >= n1_) throw new FABoundsException(); 
        if (i2 >= n2_) throw new FABoundsException(); 
        if (i3 >= n3_) throw new FABoundsException(); 
        if (i4 >= n4_) throw new FABoundsException(); 
        if (i5 >= n5_) throw new FABoundsException(); 
	}
	void check_coords(SZ i0, SZ i1, SZ i2, SZ i3, SZ i4) const { 
		if (i0 >= n0_) throw new FABoundsException(); 
		if (i1 >= n1_) throw new FABoundsException(); 
        if (i2 >= n2_) throw new FABoundsException(); 
        if (i3 >= n3_) throw new FABoundsException(); 
        if (i4 >= n4_) throw new FABoundsException(); 
	}
	void check_coords(SZ i0, SZ i1, SZ i2, SZ i3) const { 
		if (i0 >= n0_) throw new FABoundsException(); 
		if (i1 >= n1_) throw new FABoundsException(); 
        if (i2 >= n2_) throw new FABoundsException(); 
        if (i3 >= n3_) throw new FABoundsException(); 
	}
	void check_coords(SZ i0, SZ i1, SZ i2) const { 
		if (i0 >= n0_) throw new FABoundsException(); 
		if (i1 >= n1_) throw new FABoundsException(); 
        if (i2 >= n2_) throw new FABoundsException(); 
	}
	void check_coords(SZ i0, SZ i1) const { 
		if (i0 >= n0_) throw new FABoundsException(); 
		if (i1 >= n1_) throw new FABoundsException(); 
	}
	void check_coords(SZ i0) const { 
		if (i0 >= n0_) throw new FABoundsException(); 
	}
	void check_match(const FAArray6Ref<T>& that) const { 
		if (that.size0() != n0_) throw new FAMismatchException(); 
		if (that.size1() != n1_) throw new FAMismatchException(); 
		if (that.size2() != n2_) throw new FAMismatchException(); 
		if (that.size3() != n3_) throw new FAMismatchException(); 
		if (that.size4() != n4_) throw new FAMismatchException(); 
		if (that.size5() != n5_) throw new FAMismatchException(); 
	}
protected:
	void attach(T****** data, SZ n0, SZ n1, SZ n2, SZ n3, SZ n4, SZ n5) {
		data_ = data;
		n0_ = n0;
		n1_ = n1;
        n2_ = n2;
        n3_ = n3;
        n4_ = n4;
        n5_ = n5;
	}
	void detach() {
		data_ = 0;
		n0_ = 0;
		n1_ = 0;
        n2_ = 0;
        n3_ = 0;
        n4_ = 0;
        n5_ = 0;
	}
	virtual void mutate(bool writable) {}
	const T* const* const* const* const* const* const_array() const { return (const T* const* const* const* const* const*)data_; }
private:
	T****** data_;
	SZ n0_, n1_, n2_, n3_, n4_, n5_;
};

// Array classes with memory management
#if FA_USE_REF_COUNT
template<class T>
class FAArray1 : public FAArray1Ref<T> {
public:
	FAArray1<T>() { init(); }
	FAArray1<T>(SZ n0) { init(); alloc(n0); fill((T)0); }
	FAArray1<T>(const T* data_, SZ n0) { init(); alloc(n0); copy(data_, n0); }
	FAArray1<T>(const FAArray1Ref<T>& src) { init(); alloc(src.size0()); copy(src); }
	FAArray1<T>(const FAArray1<T>& src) { 
		add_ref(src);
	}
	virtual ~FAArray1<T>() { release(); }
	const FAArray1<T>& operator=(const FAArray1Ref<T>& src) { 
		if (this->size0() == 0)
			add_ref(src); 
		else
		{
			FA_CHECK_MATCH(src);
			copy(src);
		}
        return *this;
	}
	const FAArray1<T>& operator=(const FAArray1<T>& src) { 
        return (*this = (const FAArray1Ref<T>&)src);
	}
	const FAArray1<T>& operator=(T src) { 
        fill(src);
        return *this;
	}
protected:
	void alloc(SZ n0) { attach(FAAlloc<T>::alloc(n0), n0); }
	void free() { FAAlloc<T>::free(this->array(), this->size0()); this->detach(); }
	void init() { ref_count = new int(1); }
	virtual void mutate(bool writable) {
		if (*ref_count > 1 && writable)
		{
			(*ref_count)--;
			ref_count = new int(1);
			const T* old_data = this->const_array();
			SZ n0 = this->size0();
			alloc(n0);
			copy(old_data, n0);
		}
	}
	void add_ref(const FAArray1<T>& src) { 
		if (&src == this)
			return;
		attach((T*)src.array(), src.size0());
		ref_count = src.ref_count;
		(*ref_count)++;
	}
	void release() {
		if ((--(*ref_count)) == 0)
		{
			free();
			delete ref_count;
			ref_count = 0;
		}
	}
private:
	int* ref_count;
};
#else
template<class T>
class FAArray1 : public FAArray1Ref<T> {
public:
	FAArray1<T>() { init(); }
	FAArray1<T>(SZ n0) { init(); alloc(n0); FAArray1Ref<T>::fill((T)0); }
	FAArray1<T>(const T* data_, SZ n0) { init(); alloc(n0); FAArray1Ref<T>::copy(data_, n0); }
	FAArray1<T>(const FAArray1Ref<T>& src) { init(); alloc(src.size0()); copy(src); }
	FAArray1<T>(const FAArray1<T>& src) { 
		alloc(src.size0()); 
		copy(src);
	}
	virtual ~FAArray1<T>() { free(); }
	const FAArray1<T>& operator=(const FAArray1Ref<T>& src) { 
		if (this->size0() == 0)
			alloc(src.size0()); 
		else
			FA_CHECK_MATCH(src);
		FAArray1Ref<T>::copy(src); 
        return *this;
	}
	const FAArray1<T>& operator=(const FAArray1<T>& src) { 
        return (*this = (const FAArray1Ref<T>&)src);
	}
	const FAArray1<T>& operator=(T src) { 
		FAArray1Ref<T>::fill(src);
        return *this;
	}
protected:
	void alloc(SZ n0) { FAArray1Ref<T>::attach(FAAlloc<T>::alloc(n0), n0); }
	void free() { FAAlloc<T>::free(this->array(), this->size0()); this->detach(); }
	void init() {}
};
#endif

#if FA_USE_REF_COUNT
template<class T>
class FAArray2 : public FAArray2Ref<T> {
public:
	FAArray2<T>() { init(); }
	FAArray2<T>(SZ n0, SZ n1) { init(); alloc(n0, n1); fill((T)0); }
	FAArray2<T>(const T* const* data_, SZ n0, SZ n1) { init(); alloc(n0, n1); copy(data_, n0, n1); }
	FAArray2<T>(const FAArray2Ref<T>& src) { init(); alloc(src.size0(), src.size1()); copy(src); }
	FAArray2<T>(const FAArray2<T>& src) { 
		add_ref(src);
	}
	virtual ~FAArray2<T>() { release(); }
	const FAArray2<T>& operator=(const FAArray2Ref<T>& src) { 
		if (this->size0() == 0 || this->size1() == 0)
			add_ref(src); 
		else
		{
			FA_CHECK_MATCH(src);
			copy(src);
		}
        return *this;
	}
	const FAArray2<T>& operator=(const FAArray2<T>& src) { 
        return (*this = (const FAArray2Ref<T>&)src);
	}
	const FAArray2<T>& operator=(T src) { 
        fill(src);
        return *this;
	}
protected:
	void alloc(SZ n0, SZ n1) { attach(FAAlloc<T>::alloc(n0, n1), n0, n1); }
	void free() { FAAlloc<T>::free(this->array(), this->size0(), this->size1()); this->detach(); }
	void init() { ref_count = new int(1); }
	virtual void mutate(bool writable) {
		if (*ref_count > 1 && writable)
		{
			(*ref_count)--;
			ref_count = new int(1);
			const T* const* old_data = this->const_array();
			SZ n0 = this->size0();
			SZ n1 = this->size1();
			alloc(n0, n1);
			copy(old_data, n0, n1);
		}
	}
	void add_ref(const FAArray2<T>& src) { 
		if (&src == this)
			return;
		attach((T**)src.array(), src.size0(), src.size1());
		ref_count = src.ref_count;
		(*ref_count)++;
	}
	void release() {
		if ((--(*ref_count)) == 0)
		{
			free();
			delete ref_count;
			ref_count = 0;
		}
	}
private:
	int* ref_count;
};
#else
template<class T>
class FAArray2 : public FAArray2Ref<T> {
public:
	FAArray2<T>() { init(); }
	FAArray2<T>(SZ n0, SZ n1) { init(); alloc(n0, n1); FAArray2Ref<T>::fill((T)0); }
	FAArray2<T>(const T* const* data_, SZ n0, SZ n1) { init(); alloc(n0, n1); copy(data_, n0, n1); }
	FAArray2<T>(const FAArray2Ref<T>& src) { init(); alloc(src.size0(), src.size1()); FAArray2Ref<T>::copy(src); }
	FAArray2<T>(const FAArray2<T>& src) { 
		alloc(src.size0(), src.size1()); 
		FAArray2Ref<T>::copy(src);
	}
	virtual ~FAArray2<T>() { free(); }
	const FAArray2<T>& operator=(const FAArray2Ref<T>& src) { 
		if (this->size0() == 0 || this->size1() == 0)
			alloc(src.size0(), src.size1()); 
		else
			FA_CHECK_MATCH(src);
		copy(src); 
        return *this;
	}
	const FAArray2<T>& operator=(const FAArray2<T>& src) { 
        return (*this = (const FAArray2Ref<T>&)src);
	}
	const FAArray2<T>& operator=(T src) { 
        fill(src);
        return *this;
	}
protected:
	void alloc(SZ n0, SZ n1) { FAArray2Ref<T>::attach(FAAlloc<T>::alloc(n0, n1), n0, n1); }
	void free() { FAAlloc<T>::free(this->array(), this->size0(), this->size1()); this->detach(); }
	void init() {}
};
#endif

#if FA_USE_REF_COUNT
template<class T>
class FAArray3 : public FAArray3Ref<T> {
public:
	FAArray3<T>() { init(); }
	FAArray3<T>(SZ n0, SZ n1, SZ n2) { init(); alloc(n0, n1, n2); fill((T)0); }
	FAArray3<T>(const T* const* const* data_, SZ n0, SZ n1, SZ n2) { init(); alloc(n0, n1, n2); copy(data_, n0, n1, n2); }
	FAArray3<T>(const FAArray3Ref<T>& src) { init(); alloc(src.size0(), src.size1(), src.size2()); copy(src); }
	FAArray3<T>(const FAArray3<T>& src) { 
		add_ref(src);
	}
	virtual ~FAArray3<T>() { release(); }
	const FAArray3<T>& operator=(const FAArray3Ref<T>& src) { 
		if (this->size0() == 0 || this->size1() == 0 || this->size2() == 0)
			add_ref(src); 
		else
		{
			FA_CHECK_MATCH(src);
			copy(src);
		}
        return *this;
	}
	const FAArray3<T>& operator=(const FAArray3<T>& src) { 
        return (*this = (const FAArray3Ref<T>&)src);
	}
	const FAArray3<T>& operator=(T src) { 
        fill(src);
        return *this;
	}
protected:
	void alloc(SZ n0, SZ n1, SZ n2) { attach(FAAlloc<T>::alloc(n0, n1, n2), n0, n1, n2); }
	void free() { FAAlloc<T>::free(this->array(), this->size0(), this->size1(), this->size2()); this->detach(); }
	void init() { ref_count = new int(1); }
	virtual void mutate(bool writable) {
		if (*ref_count > 1 && writable)
		{
			(*ref_count)--;
			ref_count = new int(1);
			const T* const* const* old_data = this->const_array();
			SZ n0 = this->size0();
			SZ n1 = this->size1();
            SZ n2 = this->size2();
			alloc(n0, n1, n2);
			copy(old_data, n0, n1, n2);
		}
	}
	void add_ref(const FAArray3<T>& src) { 
		if (&src == this)
			return;
		attach((T***)src.array(), src.size0(), src.size1(), src.size2());
		ref_count = src.ref_count;
		(*ref_count)++;
	}
	void release() {
		if ((--(*ref_count)) == 0)
		{
			free();
			delete ref_count;
			ref_count = 0;
		}
	}
private:
	int* ref_count;
};
#else
template<class T>
class FAArray3 : public FAArray3Ref<T> {
public:
	FAArray3<T>() { init(); }
	FAArray3<T>(SZ n0, SZ n1, SZ n2) { init(); alloc(n0, n1, n2); FAArray3Ref<T>::fill((T)0); }
	FAArray3<T>(const T* const* const* data_, SZ n0, SZ n1, SZ n2) { init(); alloc(n0, n1, n2); copy(data_, n0, n1, n2); }
	FAArray3<T>(const FAArray3Ref<T>& src) { init(); alloc(src.size0(), src.size1(), src.size2()); copy(src); }
	FAArray3<T>(const FAArray3<T>& src) { 
		alloc(src.size0(), src.size1(), src.size2()); 
		copy(src);
	}
	virtual ~FAArray3<T>() { free(); }
	const FAArray3<T>& operator=(const FAArray3Ref<T>& src) { 
		if (this->size0() == 0 || this->size1() == 0 || this->size2() == 0)
			alloc(src.size0(), src.size1(), src.size2()); 
		else
			FA_CHECK_MATCH(src);
		copy(src); 
        return *this;
	}
	const FAArray3<T>& operator=(const FAArray3<T>& src) { 
        return (*this = (const FAArray3Ref<T>&)src);
	}
	const FAArray3<T>& operator=(T src) { 
        fill(src);
        return *this;
	}
protected:
	void alloc(SZ n0, SZ n1, SZ n2) { FAArray3Ref<T>::attach(FAAlloc<T>::alloc(n0, n1, n2), n0, n1, n2); }
	void free() { FAAlloc<T>::free(this->array(), this->size0(), this->size1(), this->size2()); this->detach(); }
	void init() {}
};
#endif

#if FA_USE_REF_COUNT
template<class T>
class FAArray4 : public FAArray4Ref<T> {
public:
	FAArray4<T>() { init(); }
	FAArray4<T>(SZ n0, SZ n1, SZ n2, SZ n3) { init(); alloc(n0, n1, n2, n3); fill((T)0); }
	FAArray4<T>(const T* const* const* const* data_, SZ n0, SZ n1, SZ n2, SZ n3) { init(); alloc(n0, n1, n2, n3); copy(data_, n0, n1, n2, n3); }
	FAArray4<T>(const FAArray4Ref<T>& src) { init(); alloc(src.size0(), src.size1(), src.size2(), src.size3()); copy(src); }
	FAArray4<T>(const FAArray4<T>& src) { 
		add_ref(src);
	}
	virtual ~FAArray4<T>() { release(); }
	const FAArray4<T>& operator=(const FAArray4Ref<T>& src) { 
		if (this->size0() == 0 || this->size1() == 0 || this->size2() == 0 || this->size3() == 0)
			add_ref(src); 
		else
		{
			FA_CHECK_MATCH(src);
			copy(src);
		}
        return *this;
	}
	const FAArray4<T>& operator=(const FAArray4<T>& src) { 
        return (*this = (const FAArray4Ref<T>&)src);
	}
	const FAArray4<T>& operator=(T src) { 
        fill(src);
        return *this;
	}
protected:
	void alloc(SZ n0, SZ n1, SZ n2, SZ n3) { attach(FAAlloc<T>::alloc(n0, n1, n2, n3), n0, n1, n2, n3); }
	void free() { FAAlloc<T>::free(this->array(), this->size0(), this->size1(), this->size2(), this->size3()); this->detach(); }
	void init() { ref_count = new int(1); }
	virtual void mutate(bool writable) {
		if (*ref_count > 1 && writable)
		{
			(*ref_count)--;
			ref_count = new int(1);
			const T* const* const* const* old_data = this->const_array();
			SZ n0 = this->size0();
			SZ n1 = this->size1();
            SZ n2 = this->size2();
            SZ n3 = this->size3();
			alloc(n0, n1, n2, n3);
			copy(old_data, n0, n1, n2, n3);
		}
	}
	void add_ref(const FAArray4<T>& src) { 
		if (&src == this)
			return;
		attach((T****)src.array(), src.size0(), src.size1(), src.size2(), src.size3());
		ref_count = src.ref_count;
		(*ref_count)++;
	}
	void release() {
		if ((--(*ref_count)) == 0)
		{
			free();
			delete ref_count;
			ref_count = 0;
		}
	}
private:
	int* ref_count;
};
#else
template<class T>
class FAArray4 : public FAArray4Ref<T> {
public:
	FAArray4<T>() { init(); }
	FAArray4<T>(SZ n0, SZ n1, SZ n2, SZ n3) { init(); alloc(n0, n1, n2, n3); fill((T)0); }
	FAArray4<T>(const T* const* const* const* data_, SZ n0, SZ n1, SZ n2, SZ n3) { init(); alloc(n0, n1, n2, n3); copy(data_, n0, n1, n2, n3); }
	FAArray4<T>(const FAArray4Ref<T>& src) { init(); alloc(src.size0(), src.size1(), src.size2(), src.size3()); copy(src); }
	FAArray4<T>(const FAArray4<T>& src) { 
		alloc(src.size0(), src.size1(), src.size2(), src.size3()); 
		copy(src);
	}
	virtual ~FAArray4<T>() { free(); }
	const FAArray4<T>& operator=(const FAArray4Ref<T>& src) { 
		if (this->size0() == 0 || this->size1() == 0 || this->size2() == 0 || this->size3() == 0)
			alloc(src.size0(), src.size1(), src.size2(), src.size3()); 
		else
			FA_CHECK_MATCH(src);
		copy(src); 
        return *this;
	}
	const FAArray4<T>& operator=(const FAArray4<T>& src) { 
        return (*this = (const FAArray4Ref<T>&)src);
	}
	const FAArray4<T>& operator=(T src) { 
        fill(src);
        return *this;
	}
protected:
	void alloc(SZ n0, SZ n1, SZ n2, SZ n3) { attach(FAAlloc<T>::alloc(n0, n1, n2, n3), n0, n1, n2, n3); }
	void free() { FAAlloc<T>::free(this->array(), this->size0(), this->size1(), this->size2(), this->size3()); this->detach(); }
	void init() {}
};
#endif

#if FA_USE_REF_COUNT
template<class T>
class FAArray5 : public FAArray5Ref<T> {
public:
	FAArray5<T>() { init(); }
	FAArray5<T>(SZ n0, SZ n1, SZ n2, SZ n3, SZ n4) { init(); alloc(n0, n1, n2, n3, n4); fill((T)0); }
	FAArray5<T>(const T* const* const* const* const* data_, SZ n0, SZ n1, SZ n2, SZ n3, SZ n4) { init(); alloc(n0, n1, n2, n3, n4); copy(data_, n0, n1, n2, n3, n4); }
	FAArray5<T>(const FAArray5Ref<T>& src) { init(); alloc(src.size0(), src.size1(), src.size2(), src.size3(), src.size4()); copy(src); }
	FAArray5<T>(const FAArray5<T>& src) { 
		add_ref(src);
	}
	virtual ~FAArray5<T>() { release(); }
	const FAArray5<T>& operator=(const FAArray5Ref<T>& src) { 
		if (this->size0() == 0 || this->size1() == 0 || this->size2() == 0 || this->size3() == 0 || this->size4() == 0)
			add_ref(src); 
		else
		{
			FA_CHECK_MATCH(src);
			copy(src);
		}
        return *this;
	}
	const FAArray5<T>& operator=(const FAArray5<T>& src) { 
        return (*this = (const FAArray5Ref<T>&)src);
	}
	const FAArray5<T>& operator=(T src) { 
        fill(src);
        return *this;
	}
protected:
	void alloc(SZ n0, SZ n1, SZ n2, SZ n3, SZ n4) { attach(FAAlloc<T>::alloc(n0, n1, n2, n3, n4), n0, n1, n2, n3, n4); }
	void free() { FAAlloc<T>::free(this->array(), this->size0(), this->size1(), this->size2(), this->size3(), this->size4()); this->detach(); }
	void init() { ref_count = new int(1); }
	virtual void mutate(bool writable) {
		if (*ref_count > 1 && writable)
		{
			(*ref_count)--;
			ref_count = new int(1);
			const T* const* const* const* const* old_data = this->const_array();
			SZ n0 = this->size0();
			SZ n1 = this->size1();
            SZ n2 = this->size2();
            SZ n3 = this->size3();
            SZ n4 = this->size4();
			alloc(n0, n1, n2, n3, n4);
			copy(old_data, n0, n1, n2, n3, n4);
		}
	}
	void add_ref(const FAArray5<T>& src) { 
		if (&src == this)
			return;
		attach((T*****)src.array(), src.size0(), src.size1(), src.size2(), src.size3(), src.size4());
		ref_count = src.ref_count;
		(*ref_count)++;
	}
	void release() {
		if ((--(*ref_count)) == 0)
		{
			free();
			delete ref_count;
			ref_count = 0;
		}
	}
private:
	int* ref_count;
};
#else
template<class T>
class FAArray5 : public FAArray5Ref<T> {
public:
	FAArray5<T>() { init(); }
	FAArray5<T>(SZ n0, SZ n1, SZ n2, SZ n3, SZ n4) { init(); alloc(n0, n1, n2, n3, n4); fill((T)0); }
	FAArray5<T>(const T* const* const* const* const* data_, SZ n0, SZ n1, SZ n2, SZ n3, SZ n4) { init(); alloc(n0, n1, n2, n3, n4); copy(data_, n0, n1, n2, n3, n4); }
	FAArray5<T>(const FAArray5Ref<T>& src) { init(); alloc(src.size0(), src.size1(), src.size2(), src.size3(), src.size4()); copy(src); }
	FAArray5<T>(const FAArray5<T>& src) { 
		alloc(src.size0(), src.size1(), src.size2(), src.size3(), src.size4()); 
		copy(src);
	}
	virtual ~FAArray5<T>() { free(); }
	const FAArray5<T>& operator=(const FAArray5Ref<T>& src) { 
		if (this->size0() == 0 || this->size1() == 0 || this->size2() == 0 || this->size3() == 0 || this->size4() == 0)
			alloc(src.size0(), src.size1(), src.size2(), src.size3(), src.size4()); 
		else
			FA_CHECK_MATCH(src);
		copy(src); 
        return *this;
	}
	const FAArray5<T>& operator=(const FAArray5<T>& src) { 
        return (*this = (const FAArray5Ref<T>&)src);
	}
	const FAArray5<T>& operator=(T src) { 
        fill(src);
        return *this;
	}
protected:
	void alloc(SZ n0, SZ n1, SZ n2, SZ n3, SZ n4) { attach(FAAlloc<T>::alloc(n0, n1, n2, n3, n4), n0, n1, n2, n3, n4); }
	void free() { FAAlloc<T>::free(this->array(), this->size0(), this->size1(), this->size2(), this->size3(), this->size4()); this->detach(); }
	void init() {}
};
#endif

#if FA_USE_REF_COUNT
template<class T>
class FAArray6 : public FAArray6Ref<T> {
public:
	FAArray6<T>() { init(); }
	FAArray6<T>(SZ n0, SZ n1, SZ n2, SZ n3, SZ n4, SZ n5) { init(); alloc(n0, n1, n2, n3, n4, n5); fill((T)0); }
	FAArray6<T>(const T* const* const* const* const* const* data_, SZ n0, SZ n1, SZ n2, SZ n3, SZ n4, SZ n5) { init(); alloc(n0, n1, n2, n3, n4, n5); copy(data_, n0, n1, n2, n3, n4, n5); }
	FAArray6<T>(const FAArray6Ref<T>& src) { init(); alloc(src.size0(), src.size1(), src.size2(), src.size3(), src.size4(), src.size5()); copy(src); }
	FAArray6<T>(const FAArray6<T>& src) { 
		add_ref(src);
	}
	virtual ~FAArray6<T>() { release(); }
	const FAArray6<T>& operator=(const FAArray6Ref<T>& src) { 
		if (this->size0() == 0 || this->size1() == 0 || this->size2() == 0 || this->size3() == 0 || this->size4() == 0 || this->size5() == 0)
			add_ref(src); 
		else
		{
			FA_CHECK_MATCH(src);
			copy(src);
		}
        return *this;
	}
	const FAArray6<T>& operator=(const FAArray6<T>& src) { 
        return (*this = (const FAArray6Ref<T>&)src);
	}
	const FAArray6<T>& operator=(T src) { 
        fill(src);
        return *this;
	}
protected:
	void alloc(SZ n0, SZ n1, SZ n2, SZ n3, SZ n4, SZ n5) { attach(FAAlloc<T>::alloc(n0, n1, n2, n3, n4, n5), n0, n1, n2, n3, n4, n5); }
	void free() { FAAlloc<T>::free(this->array(), this->size0(), this->size1(), this->size2(), this->size3(), this->size4(), this->size5()); this->detach(); }
	void init() { ref_count = new int(1); }
	virtual void mutate(bool writable) {
		if (*ref_count > 1 && writable)
		{
			(*ref_count)--;
			ref_count = new int(1);
			const T* const* const* const* const* const* old_data = this->const_array();
			SZ n0 = this->size0();
			SZ n1 = this->size1();
            SZ n2 = this->size2();
            SZ n3 = this->size3();
            SZ n4 = this->size4();
            SZ n5 = this->size5();
			alloc(n0, n1, n2, n3, n4, n5);
			copy(old_data, n0, n1, n2, n3, n4, n5);
		}
	}
	void add_ref(const FAArray6<T>& src) { 
		if (&src == this)
			return;
		attach((T******)src.array(), src.size0(), src.size1(), src.size2(), src.size3(), src.size4(), src.size5());
		ref_count = src.ref_count;
		(*ref_count)++;
	}
	void release() {
		if ((--(*ref_count)) == 0)
		{
			free();
			delete ref_count;
			ref_count = 0;
		}
	}
private:
	int* ref_count;
};
#else
template<class T>
class FAArray6 : public FAArray6Ref<T> {
public:
	FAArray6<T>() { init(); }
	FAArray6<T>(SZ n0, SZ n1, SZ n2, SZ n3, SZ n4, SZ n5) { init(); alloc(n0, n1, n2, n3, n4, n5); fill((T)0); }
	FAArray6<T>(const T* const* const* const* const* const* data_, SZ n0, SZ n1, SZ n2, SZ n3, SZ n4, SZ n5) { init(); alloc(n0, n1, n2, n3, n4, n5); copy(data_, n0, n1, n2, n3, n4, n5); }
	FAArray6<T>(const FAArray6Ref<T>& src) { init(); alloc(src.size0(), src.size1(), src.size2(), src.size3(), src.size4(), src.size5()); copy(src); }
	FAArray6<T>(const FAArray6<T>& src) { 
		alloc(src.size0(), src.size1(), src.size2(), src.size3(), src.size4(), src.size5()); 
		copy(src);
	}
	virtual ~FAArray6<T>() { free(); }
	const FAArray6<T>& operator=(const FAArray6Ref<T>& src) { 
		if (this->size0() == 0 || this->size1() == 0 || this->size2() == 0 || this->size3() == 0 || this->size4() == 0 || this->size5() == 0)
			alloc(src.size0(), src.size1(), src.size2(), src.size3(), src.size4(), src.size5()); 
		else
			FA_CHECK_MATCH(src);
		copy(src); 
        return *this;
	}
	const FAArray6<T>& operator=(const FAArray6<T>& src) { 
        return (*this = (const FAArray6Ref<T>&)src);
	}
	const FAArray6<T>& operator=(T src) { 
        fill(src);
        return *this;
	}
protected:
	void alloc(SZ n0, SZ n1, SZ n2, SZ n3, SZ n4, SZ n5) { attach(FAAlloc<T>::alloc(n0, n1, n2, n3, n4, n5), n0, n1, n2, n3, n4, n5); }
	void free() { FAAlloc<T>::free(this->array(), this->size0(), this->size1(), this->size2(), this->size3(), this->size4(), this->size5()); this->detach(); }
	void init() {}
};
#endif

// Operators

// 1d op 1d
template<class T>
FAArray1<T> operator+(const FAArray1Ref<T>& op1, const FAArray1Ref<T>& op2) {
	FAArray1<T> res(op1);
	res += op2;
	return res;
}
template<class T>
FAArray1<T> operator-(const FAArray1Ref<T>& op1, const FAArray1Ref<T>& op2) {
	FAArray1<T> res(op1);
	res -= op2;
	return res;
}
template<class T>
FAArray1<T> operator*(const FAArray1Ref<T>& op1, const FAArray1Ref<T>& op2) {
	FAArray1<T> res(op1);
	res *= op2;
	return res;
}
template<class T>
FAArray1<T> operator/(const FAArray1Ref<T>& op1, const FAArray1Ref<T>& op2) {
	FAArray1<T> res(op1);
	res /= op2;
	return res;
}
template<class T>
FAArray1<T> operator-(const FAArray1Ref<T>& op) {
	FAArray1<T> res(op.size0());
	res -= op;
	return res;
}

// 1d op scalar
template<class T>
FAArray1<T> operator+(const FAArray1Ref<T>& op1, T op2) {
	FAArray1<T> res(op1);
	res += op2;
	return res;
}
template<class T>
FAArray1<T> operator-(const FAArray1Ref<T>& op1, T op2) {
	FAArray1<T> res(op1);
	res -= op2;
	return res;
}
template<class T>
FAArray1<T> operator*(const FAArray1Ref<T>& op1, T op2) {
	FAArray1<T> res(op1);
	res *= op2;
	return res;
}
template<class T>
FAArray1<T> operator/(const FAArray1Ref<T>& op1, T op2) {
	FAArray1<T> res(op1);
	res /= op2;
	return res;
}

// 2d op 2d
template<class T>
FAArray2<T> operator+(const FAArray2Ref<T>& op1, const FAArray2Ref<T>& op2) {
	FAArray2<T> res(op1);
	res += op2;
	return res;
}
template<class T>
FAArray2<T> operator-(const FAArray2Ref<T>& op1, const FAArray2Ref<T>& op2) {
	FAArray2<T> res(op1);
	res -= op2;
	return res;
}
template<class T>
FAArray2<T> operator*(const FAArray2Ref<T>& op1, const FAArray2Ref<T>& op2) {
	FAArray2<T> res(op1);
	res *= op2;
	return res;
}
template<class T>
FAArray2<T> operator/(const FAArray2Ref<T>& op1, const FAArray2Ref<T>& op2) {
	FAArray2<T> res(op1);
	res /= op2;
	return res;
}
template<class T>
FAArray2<T> operator-(const FAArray2Ref<T>& op) {
	FAArray2<T> res(op.size0(), op.size1());
	res -= op;
	return res;
}

// 2d op scalar
template<class T>
FAArray2<T> operator+(const FAArray2Ref<T>& op1, T op2) {
	FAArray2<T> res(op1);
	res += op2;
	return res;
}
template<class T>
FAArray2<T> operator-(const FAArray2Ref<T>& op1, T op2) {
	FAArray2<T> res(op1);
	res -= op2;
	return res;
}
template<class T>
FAArray2<T> operator*(const FAArray2Ref<T>& op1, T op2) {
	FAArray2<T> res(op1);
	res *= op2;
	return res;
}
template<class T>
FAArray2<T> operator/(const FAArray2Ref<T>& op1, T op2) {
	FAArray2<T> res(op1);
	res /= op2;
	return res;
}

// 3d op 3d
template<class T>
FAArray3<T> operator+(const FAArray3Ref<T>& op1, const FAArray3Ref<T>& op2) {
	FAArray3<T> res(op1);
	res += op2;
	return res;
}
template<class T>
FAArray3<T> operator-(const FAArray3Ref<T>& op1, const FAArray3Ref<T>& op2) {
	FAArray3<T> res(op1);
	res -= op2;
	return res;
}
template<class T>
FAArray3<T> operator*(const FAArray3Ref<T>& op1, const FAArray3Ref<T>& op2) {
	FAArray3<T> res(op1);
	res *= op2;
	return res;
}
template<class T>
FAArray3<T> operator/(const FAArray3Ref<T>& op1, const FAArray3Ref<T>& op2) {
	FAArray3<T> res(op1);
	res /= op2;
	return res;
}
template<class T>
FAArray3<T> operator-(const FAArray3Ref<T>& op) {
	FAArray3<T> res(op.size0(), op.size1(), op.size2());
	res -= op;
	return res;
}

// 3d op scalar
template<class T>
FAArray3<T> operator+(const FAArray3Ref<T>& op1, T op2) {
	FAArray3<T> res(op1);
	res += op2;
	return res;
}
template<class T>
FAArray3<T> operator-(const FAArray3Ref<T>& op1, T op2) {
	FAArray3<T> res(op1);
	res -= op2;
	return res;
}
template<class T>
FAArray3<T> operator*(const FAArray3Ref<T>& op1, T op2) {
	FAArray3<T> res(op1);
	res *= op2;
	return res;
}
template<class T>
FAArray3<T> operator/(const FAArray3Ref<T>& op1, T op2) {
	FAArray3<T> res(op1);
	res /= op2;
	return res;
}

// 4d op 4d
template<class T>
FAArray4<T> operator+(const FAArray4Ref<T>& op1, const FAArray4Ref<T>& op2) {
	FAArray4<T> res(op1);
	res += op2;
	return res;
}
template<class T>
FAArray4<T> operator-(const FAArray4Ref<T>& op1, const FAArray4Ref<T>& op2) {
	FAArray4<T> res(op1);
	res -= op2;
	return res;
}
template<class T>
FAArray4<T> operator*(const FAArray4Ref<T>& op1, const FAArray4Ref<T>& op2) {
	FAArray4<T> res(op1);
	res *= op2;
	return res;
}
template<class T>
FAArray4<T> operator/(const FAArray4Ref<T>& op1, const FAArray4Ref<T>& op2) {
	FAArray4<T> res(op1);
	res /= op2;
	return res;
}
template<class T>
FAArray4<T> operator-(const FAArray4Ref<T>& op) {
	FAArray4<T> res(op.size0(), op.size1(), op.size2(), op.size3());
	res -= op;
	return res;
}

// 4d op scalar
template<class T>
FAArray4<T> operator+(const FAArray4Ref<T>& op1, T op2) {
	FAArray4<T> res(op1);
	res += op2;
	return res;
}
template<class T>
FAArray4<T> operator-(const FAArray4Ref<T>& op1, T op2) {
	FAArray4<T> res(op1);
	res -= op2;
	return res;
}
template<class T>
FAArray4<T> operator*(const FAArray4Ref<T>& op1, T op2) {
	FAArray4<T> res(op1);
	res *= op2;
	return res;
}
template<class T>
FAArray4<T> operator/(const FAArray4Ref<T>& op1, T op2) {
	FAArray4<T> res(op1);
	res /= op2;
	return res;
}

// 5d op 5d
template<class T>
FAArray5<T> operator+(const FAArray5Ref<T>& op1, const FAArray5Ref<T>& op2) {
	FAArray5<T> res(op1);
	res += op2;
	return res;
}
template<class T>
FAArray5<T> operator-(const FAArray5Ref<T>& op1, const FAArray5Ref<T>& op2) {
	FAArray5<T> res(op1);
	res -= op2;
	return res;
}
template<class T>
FAArray5<T> operator*(const FAArray5Ref<T>& op1, const FAArray5Ref<T>& op2) {
	FAArray5<T> res(op1);
	res *= op2;
	return res;
}
template<class T>
FAArray5<T> operator/(const FAArray5Ref<T>& op1, const FAArray5Ref<T>& op2) {
	FAArray5<T> res(op1);
	res /= op2;
	return res;
}
template<class T>
FAArray5<T> operator-(const FAArray5Ref<T>& op) {
	FAArray5<T> res(op.size0(), op.size1(), op.size2(), op.size3(), op.size4());
	res -= op;
	return res;
}

// 5d op scalar
template<class T>
FAArray5<T> operator+(const FAArray5Ref<T>& op1, T op2) {
	FAArray5<T> res(op1);
	res += op2;
	return res;
}
template<class T>
FAArray5<T> operator-(const FAArray5Ref<T>& op1, T op2) {
	FAArray5<T> res(op1);
	res -= op2;
	return res;
}
template<class T>
FAArray5<T> operator*(const FAArray5Ref<T>& op1, T op2) {
	FAArray5<T> res(op1);
	res *= op2;
	return res;
}
template<class T>
FAArray5<T> operator/(const FAArray5Ref<T>& op1, T op2) {
	FAArray5<T> res(op1);
	res /= op2;
	return res;
}


// 6d op 6d
template<class T>
FAArray6<T> operator+(const FAArray6Ref<T>& op1, const FAArray6Ref<T>& op2) {
	FAArray6<T> res(op1);
	res += op2;
	return res;
}
template<class T>
FAArray6<T> operator-(const FAArray6Ref<T>& op1, const FAArray6Ref<T>& op2) {
	FAArray6<T> res(op1);
	res -= op2;
	return res;
}
template<class T>
FAArray6<T> operator*(const FAArray6Ref<T>& op1, const FAArray6Ref<T>& op2) {
	FAArray6<T> res(op1);
	res *= op2;
	return res;
}
template<class T>
FAArray6<T> operator/(const FAArray6Ref<T>& op1, const FAArray6Ref<T>& op2) {
	FAArray6<T> res(op1);
	res /= op2;
	return res;
}
template<class T>
FAArray6<T> operator-(const FAArray6Ref<T>& op) {
	FAArray6<T> res(op.size0(), op.size1(), op.size2(), op.size3(), op.size4(), op.size5());
	res -= op;
	return res;
}

// 6d op scalar
template<class T>
FAArray6<T> operator+(const FAArray6Ref<T>& op1, T op2) {
	FAArray6<T> res(op1);
	res += op2;
	return res;
}
template<class T>
FAArray6<T> operator-(const FAArray6Ref<T>& op1, T op2) {
	FAArray6<T> res(op1);
	res -= op2;
	return res;
}
template<class T>
FAArray6<T> operator*(const FAArray6Ref<T>& op1, T op2) {
	FAArray6<T> res(op1);
	res *= op2;
	return res;
}
template<class T>
FAArray6<T> operator/(const FAArray6Ref<T>& op1, T op2) {
	FAArray6<T> res(op1);
	res /= op2;
	return res;
}

FA_NS_END

#endif //__FA_ARRAY_H__
