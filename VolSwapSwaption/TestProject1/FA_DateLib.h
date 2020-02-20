/**
 *  Filename : FADateLib.h
 *  
 */

#ifndef FADATELIB_H
#define FADATELIB_H

#include <stdlib.h>

#define FA_MAX(a,b)  (((a) > (b)) ? (a) : (b))
#define FA_MIN(a,b)  (((a) < (b)) ? (a) : (b))


// The following two functions convert Excel serial dates to DMY
// and back and correct for Excel's Feb 29,1900 'bug'
// Ref: http://www.codeproject.com/datetime/exceldmy.asp
//      Victor Vogelpoel
static void ExcelSerialDateToDMY(
    int nSerialDate,
    int *D, 
    int *M,
    int *Y
    );
static int DMYToExcelSerialDate(
    int D,
    int M,
    int Y
	);

// The following three functions index holiday serial dates into a
// simple hash table and check if a particular date is stored.
static void MakeHolidayHashTable(
    double *HolidaySerialDates,
	int nHoliday,
    int *HashTable,
    int nHash
    );
static int FibonacciHash(
    int x
	);
static int isHoliday(
	int date,
	int *HashTable,
    int nHash
    );

// The following three functions roll dates to business days
// and compute year fractions according to daycount conventions
// and roll date by Count periods (days,weeks,months,years)
static double RollDay(
    double fdate,
    int RollConvention,
    int *HashTable,
    int nHash
    );

static double YearFraction(
    double StartDate,
    double EndDate,
    int RollConvention,
    int Adjust,
    int DayCount,
    int *HashTable,
    int nHash
    );

static double NextDate(
    double fdate,
	int Period,
	int Count
    );

static void BuildSchedule(
    double Inception,
    int Unit,
    int Interval,
    double* Schedule,
	int imin,
    int imax,
    int RollConvention,
    int *HashTable,
    int nHash
	);

static double NextIMMDate(
    double fdate,
	int Months
    );

static void BuildIMMSchedule(
    double Inception,
	int Months,
    double* Schedule,
	int imin,
    int imax,
    int RollConvention,
    int *HashTable,
    int nHash
	);
	
///////////////////////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////////////	

 static void ExcelSerialDateToDMY(
    int nSerialDate,
    int *D, 
    int *M,
    int *Y
    )
{
	int l,n,i,j;

    // Excel bug: it thinks 1900 was leap year.  It was not.
    if (nSerialDate==60) {
        *D = 29;
        *M = 2;
        *Y = 1900;
        return;
    }
    else if (nSerialDate<60) {
        // Because of the 29-02-1900 bug, any serial date 
        // under 60 is one off. Compensate.
        nSerialDate++;
    }

    // Modified Julian to DMY calculation with an addition of 2415019
    l = nSerialDate + 68569 + 2415019;
    n = (int)((4*l)/146097);
    l = l - (int)((146097*n+3)/4);
    i = (int)((4000*(l+1))/1461001);
    l = l - (int)((1461*i)/4)+31;
    j = (int)((80*l)/2447);
    *D = l - (int)((2447*j)/80);
    l = (int)(j/11);
    *M = j+2-(12*l);
    *Y = 100*(n-49)+i+l;
    return;
}

///////////////////////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////////////	

 static int DMYToExcelSerialDate(
    int D,
    int M,
    int Y
	)
{
	long nSerialDate;
    // Excel bug: it thinks 1900 was leap year.  It was not.
    if (D==29 && M==02 && Y==1900)
        return 60;

    // DMY to Modified Julian with an extra substraction of 2415019.
    nSerialDate = 
        (int)((1461*(Y+4800+(int)((M-14)/12)))/4) +
        (int)((367*(M-2-12*((M-14)/12)))/12) -
        (int)((3*((int)((Y+4900+(int)((M-14)/12))/100)))/4) +
        D - 2415019 - 32075;

    if (nSerialDate<60)
    {
        // Because of the 29-02-1900 bug, any serial date 
        // under 60 is one off. Compensate.
        nSerialDate--;
    }
    return (int)nSerialDate;
}

///////////////////////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////////////	

static int FibonacciHash(
    int x
	)
{
	// Fibonacci Hashing
    static int k = 10; // 1024 element hash table; each element with 4 slots
    static int w = 32; // word length
    static int a = (int) 2654435769L; // Fibonacci
    return ((unsigned)(x*a)) >> (w - k);
}

///////////////////////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////////////	

static void MakeHolidayHashTable(
    double *HolidaySerialDates,
	int nHoliday,
    int *HashTable,
    int nHash
    )
{
    // Makes a 1024 element hash table of holiday serial dates
	// To handle collisions, each element has 4 contiguous slots
    // The probability of filling 4 slots with a reasonable length
    // holiday list (say 300-400 holidays is vanishingly small)
    int h,i,j,k;

    for (i=1; i<=nHoliday; i++) {
        k = (int)HolidaySerialDates[i];
        h = 4*FibonacciHash(k);
		j = 0;
        while (j<3) {
            if (HashTable[h+j]==k) break;  // duplicate
            if (HashTable[h+j]==0) {HashTable[h+j] = k;  break;}
            j++;
        }
	}
    return;
}

///////////////////////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////////////	

static int isHoliday(
	int date,
	int *HashTable,
    int nHash
    )
{
	// Check four slots of hash table for holiday serial dates
	// Return if a 0 is encountered, else check next slot
	int h,j,k;

    h = 4*FibonacciHash(date);
	j = 0;
	while (j<=3) {
		k = HashTable[h+j];
		if (k==0) return 0;
		if (k==date) return 1;
		j++;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////////////	

static double RollDay(
    double fdate,
    int RollConvention,
    int *HashTable,
    int nHash
    )
{
    // RollConvention = -2,-2,0,1,2
    // = ModifiedPrevious, Previous, NoRoll, Following, ModifiedFollowing
    int date = (int)fdate;
    int d1,m1,y1,d2,m2,y2,origdate,adjustdir;

    // RollConvention = 0: No Adjustment
    if (RollConvention==0) return fdate;

    // RollConvention = -1: Previous  OR  RollConvention = +1: Following
    if (abs(RollConvention)==1) {
        adjustdir = RollConvention;
        while ( (date%7 < 2) || isHoliday(date,HashTable,nHash)==1) {date += adjustdir;}
        return (double)date;
    }

    // RollConvention = -2: Modified Previous  OR  RollConvention = +2: Modified Following
    if (abs(RollConvention)==2) {
        adjustdir = RollConvention/2;
        origdate = date;
        ExcelSerialDateToDMY(date,&d1,&m1,&y1); 
        while ( (date%7 < 2) || isHoliday(date,HashTable,nHash)==1) {date += adjustdir;}
        ExcelSerialDateToDMY(date,&d2,&m2,&y2);
        if (m1!=m2) {
            date = origdate;
            while ( (date%7 < 2) || isHoliday(date,HashTable,nHash)==1) {date -= adjustdir;}
        }
        return (double)date;
    }
	return fdate;
}

///////////////////////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////////////	

static double YearFraction(
    double StartDate,
    double EndDate,
    int RollConvention,
    int Adjust,
    int DayCount,
    int *HashTable,
    int nHash
    )
{
    // year fraction under various daycount and roll conventions
    // RollConvention = -2,-2,0,1,2
    // = ModifiedPrevious, Previous, NoRoll, Following, ModifiedFollowing
    // Adjust = 0,1
    // = unadjusted (not rolled) or adjusted (rolled) dates

    int Date1,Date2,d1,d2,m1,m2,y1,y2;
	double xx,yy,zz;

    if (StartDate==EndDate) {return 0.;}

    // dates are already year fractions
    if (StartDate<=30000. && EndDate<=30000.) {
        return EndDate-StartDate;
    }

    // roll Adjusted dates
    if (Adjust!=0) {
        StartDate = RollDay(StartDate,RollConvention,HashTable,nHash);
        EndDate   = RollDay(EndDate,  RollConvention,HashTable,nHash);
    }
    Date1 = (int)StartDate;  Date2 = (int)EndDate;

	// Act/Act
    if (DayCount==1) {
        ExcelSerialDateToDMY(Date1,&d1,&m1,&y1);
		xx = 365.;
		if (((y1+1)%4==0 && m1>=3) || (y1%4==0 && m1<3)) xx = 366.;
		yy = (Date2-Date1)/xx;
		if (yy <=1.) return yy;
		zz = ((yy-1.)*365.25 + xx)/yy;
		return (Date2-Date1)/zz;

	// Act/360
    } else if (DayCount==2) {
        return (double)(Date2-Date1)/360.;

	// Act/360
    } else if (DayCount==3) {
        return (double)(Date2-Date1)/365.;

	// 30/360
    } else if (DayCount==0) {
        ExcelSerialDateToDMY(Date1,&d1,&m1,&y1); 
        ExcelSerialDateToDMY(Date2,&d2,&m2,&y2);
        d1=FA_MIN(d1,30);
        if (d1==30) d2=FA_MIN(d2,30);
        return (double)((d2-d1)+30*(m2-m1)+360*(y2-y1))/360.;

	// 30/360E
    } else if (DayCount==4) {
        ExcelSerialDateToDMY(Date1,&d1,&m1,&y1); 
        ExcelSerialDateToDMY(Date2,&d2,&m2,&y2);
        d1=FA_MIN(d1,30);
        d2=FA_MIN(d2,30);
        return (double)((d2-d1)+30*(m2-m1)+360*(y2-y1))/360.;
    }
    return 0.;
}

///////////////////////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////////////	

static double NextDate(
    double fdate,
	int Period,
	int Count
    )
{
	// increments a date by Count Periods. Non-business days are not
	// rolled to business days.
	// Period=1 --> increment Count days
	// Period=2 --> increment Count weeks
	// Period=3 --> increment Count months
	// Period=4 --> increment Count years

    int date=(int)fdate,d1,m1,y1,dy,dm;

	// days
	if (Period==1) return fdate + Count;

	// weeks
	if (Period==2) return fdate + 7*Count;

	// months
	if (Period==3) {
        ExcelSerialDateToDMY(date,&d1,&m1,&y1);
		dm = Count%12;
		dy = (Count-dm)/12;
		m1 += dm;  
		y1 += dy;
		if (m1>12) {m1=m1-12; y1++;}
		if (m1==4||m1==6||m1==9||m1==11) {
			return (double)DMYToExcelSerialDate(FA_MIN(d1,30),m1,y1);
		} else if (m1==2) {
			if ( (y1%400==0) || ((y1%4==0)&&(y1%100>0)) ) {
				return (double)DMYToExcelSerialDate(FA_MIN(d1,29),m1,y1);  // leap year
			} else {
				return (double)DMYToExcelSerialDate(FA_MIN(d1,28),m1,y1);  // not leap year
			}
		} else {
			return (double)DMYToExcelSerialDate(FA_MIN(d1,31),m1,y1);
		}
	}

	// years
	if (Period==4) {
        ExcelSerialDateToDMY(date,&d1,&m1,&y1);
		y1 += Count;
		if (m1==4||m1==6||m1==9||m1==11) {
			return (double)DMYToExcelSerialDate(FA_MIN(d1,30),m1,y1);
		} else if (m1==2) {
			if ( (y1%400==0) || ((y1%4==0)&&(y1%100>0)) ) {
				return (double)DMYToExcelSerialDate(FA_MIN(d1,29),m1,y1);  // leap year
			} else {
				return (double)DMYToExcelSerialDate(FA_MIN(d1,28),m1,y1);  // not leap year
			}
		} else {
			return (double)DMYToExcelSerialDate(FA_MIN(d1,31),m1,y1);
		}
	}
	return fdate;
}

///////////////////////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////////////	

static void BuildSchedule(
    double Inception,
    int Unit,
    int Interval,
    double* Schedule,
	int imin,
    int imax,
    int RollConvention,
    int *HashTable,
    int nHash
	)
{
	int i;

	Schedule[imin] = Inception;
	for (i=imin+1; i<=imax; i++) {
        Schedule[i] = NextDate(Schedule[i-1], Unit, Interval);
	}
	if (RollConvention != 0) {
	    for (i=imin; i<=imax; i++) {
            Schedule[i] = RollDay(Schedule[i], RollConvention, HashTable, nHash);
		}
	}	
}

///////////////////////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////////////	

static double NextIMMDate(
    double fdate,
	int Months
    )
{
	// next IMM date

    int date=(int)fdate,d1,m1,y1,m2,y2,m,y,dw;

	// Months > 0 -- 3rd Wed of the month which is Months ahead of fdate
	if (Months>0) {

        // serial date: 1st of target month
        ExcelSerialDateToDMY(date,&d1,&m1,&y1);
	    m = Months%12;
	    y = y1 + (Months-m)/12;
        m2 = m1 + m;
	    m = 1+(m2-1)%12;
        y2 = y + (m2-m)/12;
	    m2 = m;
        date = DMYToExcelSerialDate(1,m2,y2);

        // day of the week: 1st of target month
	    dw = date%7;

        // serial date: IMM date
	    if (dw<=4) {          // 1st of month is Sat-Wed
		    date += (18 - dw);
		} else {             // 1st of month is Thurs-Fri
		    date += (25 - dw);
		}
	    return (double)date;
	}

	// Months = 0 -- Mar 20, Jun 20, Sep 20, Dec 20
	else if (Months==0) {
        ExcelSerialDateToDMY(date,&d1,&m1,&y1);
	    if (d1<20) {
		    m2 = 3*((m1-1)/3 + 1);
		    y2 = y1;
		} else {
		    m2 = 3*(m1/3 + 1); 
		    y2 = y1;
		    if (m2>12) {
			    m2 = m2-12;
			    y2 = y1+1;
			}
		}
	    return (double)DMYToExcelSerialDate(20,m2,y2);
	}

	// error
	return 0.;
}

///////////////////////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////////////	

static void BuildIMMSchedule(
    double Inception,
	int Months,
    double* Schedule,
	int imin,
    int imax,
    int RollConvention,
    int *HashTable,
    int nHash
	)
{
	int i;

	Schedule[imin] = NextIMMDate(Inception,Months);
	for (i=imin+1; i<=imax; i++) {
        Schedule[i] = NextIMMDate(Schedule[i-1],Months);
	}
	if (RollConvention != 0) {
	    for (i=imin; i<=imax; i++) {
            Schedule[i] = RollDay(Schedule[i], RollConvention, HashTable, nHash);
		}
	}	
}

///////////////////////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////////////	
#undef FA_MAX
#undef FA_MIN

#endif /* FADATELIB_H */
