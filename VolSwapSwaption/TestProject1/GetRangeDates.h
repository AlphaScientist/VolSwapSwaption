/**
 *  Filename : GetRangeDates.h
 *  All rights reserved.
 */

#ifndef GETRANGEDATES_H
#define GETRANGEDATES_H

static void GetRangeDates(
	double *RangeDates,
	double *AllDates,
	int *nRD,
	int nCoup,
	int nsub
	);

static void GetRangeDates(
	double *RangeDates,
	double *AllDates,
	int nCoup,
	int nsub
	)
{
	int i,j,k;
	k = 0;
	for (i=1; i<=nCoup; i++) {
		for (j=1; j<=nsub; j++) {
			RangeDates[++k] = AllDates[i-1] + (AllDates[i]-AllDates[i-1])* ((double)j/(double)nsub);
		}
	}
	return;
}

#endif /* GETRANGEDATES_H */
