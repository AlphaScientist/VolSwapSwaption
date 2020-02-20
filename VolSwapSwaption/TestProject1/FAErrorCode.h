/**
 *  Filename : FAErrorCode.h
 *  $Date: 2019/03/12 21:57:38 $
 *  
 */

#ifndef _FAERRORCODES_H_
#define _FAERRORCODES_H_

#define FANormalFlag 0
#define HaltingInKrylov 1
#define CGSolverOld 2
#define CGSolverAlpha 3
#define QMRSolverRho 4
#define QMRSolverXi 5
#define QMRSolverEpsi 6
#define QMRSolverDelta 7
#define QMRSolverGamma1 8
#define QMRSolverGamma2 9
#define BiCGSolverRho 10
#define BiCGSolverPtqq 11
#define CGSSolverRho 12
#define CGSSolverRtvh 13
#define PBCGSTSolverRho 14
#define PBCGSTSolverRtvv 15
#define PBCGSTSolverOmega 16
#define BinaryLoopSmallArrays 17
#define StabilityFailure 18
#define ErrorAbort 19
#define AllocationError 20
#define ToleranceTooSmall 21
#define MaxitExceeded 22
#define FileOpenError 23
#define FileNotFound 24
#define fscanfError 25
#define TaggedInputError 26
#define PinnedGridSamePointError 27
#define BisectionError 28
#define BisectionBracketError 29
#define InterpolationDeltaError 30
#define MissingUserTypeInitCode 31
#define MissingStubFunctionBody 32
#define UnsortedSampleArray 33
#define SawToothOnePointError 34
#define SawToothNoZeroError 35
#define MCFASobolOverflow 36
#define MCNoPhysicalCorrelation 37
#define MCFASobolOverflow2 38
#define BrentConvergenceFailure 39
#define MCFAOldSobolOverflow 40

#endif /* _FAERRORCODES_H_ */
