/**
 *  Filename : FAInterpLib.h
 *  All rights reserved.
 */
#ifndef FAInterpLib_H
#define FAInterpLib_H

#include "FAArrayN.h"
#include "FAStdIncludes.h"
#include "FACommonLib.h"

static void Locate(
    double xint,
    const FAArray1Ref<double>& x,
    double uniformdx,
    int nlow,
    int nhi,
    int ascend,
    int *locp
    );
static void FindStairStepIndex(
    const FAArray1Ref<double>& x,
    double uniformdx,
    double xint,
    int nlow,
    int nhi,
    int ascend,
    int bias,
    double eps,
    int *locp,
    int *index
    );
static double StairStep(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x,
    double xint,
    int nlow,
    int nhi,
    double uniformdx,
    int bias,
    double eps
    );
static void StairStepLoop(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& xint,
    FAArray1Ref<double>& yint,
    int nlow,
    int nhi,
    int ilow,
    int ihi,
    double uniformdx,
    int bias,
    double eps
    );
static double SawTooth(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x,
    double xint,
    int nlow,
    int nhi,
    double uniformdx,
    int valleys,
    double eps
    );
static void SawToothLoop(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& xint,
    FAArray1Ref<double>& yint,
    int nlow,
    int nhi,
    int ilow,
    int ihi,
    double uniformdx,
    int valleys,
    double eps
    );
static void ComputeInterpInterval(
    const FAArray1Ref<double>& x,
    double uniformdx,
    double xint,
    int nlow,
    int nhi,
    int ascend,
    int extrap,
    int *loc,
    int *index,
    double *tt,
    char *ErrorMsg
    );
static double InterpolateLinear(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x,
    double xint,
    int nlow,
    int nhi,
    double uniformdx,
    int extrap
    );
static void InterpolateLinearLoop(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& xint,
    FAArray1Ref<double>& yint,
    int nlow,
    int nhi,
    int ilow,
    int ihi,
    double uniformdx,
    int extrap
    );
static double Quadratic(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x,
    double xint,
    int nlow,
    int nhi,
    double uniformdx,
	int bias,
    int extrap
    );
static void QuadraticLoop(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& xint,
    FAArray1Ref<double>& yint,
    int nlow,
    int nhi,
    int ilow,
    int ihi,
    double uniformdx,
	int bias,
    int extrap
    );
static double Cubic(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x,
    double xint,
    int nlow,
    int nhi,
    double uniformdx,
    int extrap
    );
static void CubicLoop(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& xint,
    FAArray1Ref<double>& yint,
    int nlow,
    int nhi,
    int ilow,
    int ihi,
    double uniformdx,
    int extrap
    );
static void SplineForwardSweep(
    const FAArray1Ref<double>& x,
    double uniformdx,
    FAArray1Ref<double>& TriT,
    FAArray1Ref<double>& TriT2,
    int nlow,
    int nhi
    );
static void SplineCoefficients(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x,
    double uniformdx,
    FAArray1Ref<double>& fpp,
    const FAArray1Ref<double>& TriT,
    const FAArray1Ref<double>& TriT2,
    int nlow,
    int nhi
    );
static double CubicSpline(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& fpp,
    double xint,
    int nlow,
    int nhi,
    double uniformdx,
    int extrap
    );
static double DCubicSpline(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& fpp,
    double xint,
    int nlow,
    int nhi,
    double uniformdx,
    int extrap
    );
static void CubicSplineLoop(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& fpp,
    const FAArray1Ref<double>& xint,
    FAArray1Ref<double>& yint,
    int nlow,
    int nhi,
    int ilow,
    int ihi,
    double uniformdx,
    int extrap
    );
static void DCubicSplineLoop(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& fpp,
    const FAArray1Ref<double>& xint,
    FAArray1Ref<double>& yint,
    int nlow,
    int nhi,
    int ilow,
    int ihi,
    double uniformdx,
    int extrap
    );
static void ForwardMonotoneConvexCoefficients(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x, 
    double uniformdx,
    FAArray1Ref<double>& FMCdiscf,
    FAArray1Ref<double>& FMCavef, 
    int nlow,
    int nhi
	);
static double ForwardMonotoneConvex(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x, 
    const FAArray1Ref<double>& FMCdiscf,
    const FAArray1Ref<double>& FMCavef, 
    double xint,
    int nlow,
    int nhi,
    double uniformdx
    );
static void ForwardMonotoneConvexLoop(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x, 
    const FAArray1Ref<double>& FMCdiscf,
    const FAArray1Ref<double>& FMCavef, 
    const FAArray1Ref<double>& xint,
    FAArray1Ref<double>& yint,
    int nlow,
    int nhi,
    int ilow,
    int ihi,
    double uniformdx
    );
static int ForwardMonotoneConvexOld(
	const FAArray1Ref<double>& y,
	const FAArray1Ref<double>& x, 
	const FAArray1Ref<double>& xint,
	FAArray1Ref<double>& yint,
	int nlow,
	int nhi,
	int ilow,
	int ihi,
	double uniformdx
	);
static double BiStairStep(
    const FAArray2Ref<double>& z,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    double xint,
    double yint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    double uniformdx,
    double uniformdy,
    int bias,
    double eps
    );
static void BiStairStepLoop(
//  x - loop
    const FAArray2Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& xint,
    double yint,
    FAArray1Ref<double>& uint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int ilow,
    int ihi,
    double uniformdx,
    double uniformdy,
    int bias,
    double eps
    );
static void BiStairStepLoop(
//  y - loop
	const FAArray2Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
	double xint,
    const FAArray1Ref<double>& yint,
    FAArray1Ref<double>& uint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int ilow,
    int ihi,
    double uniformdx,
    double uniformdy,
    int bias,
    double eps
    );
static double Bilinear(
    const FAArray2Ref<double>& z,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    double xint,
    double yint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    double uniformdx,
    double uniformdy,
    int extrap
    );
static void BilinearLoop(
//  x - loop
	const FAArray2Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& xint,
    double yint,
    FAArray1Ref<double>& uint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int ilow,
    int ihi,
    double uniformdx,
    double uniformdy,
    int extrap
    );
static void BilinearLoop(
//	y - loop
    const FAArray2Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    double xint,
    const FAArray1Ref<double>& yint,
    FAArray1Ref<double>& uint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int ilow,
    int ihi,
    double uniformdx,
    double uniformdy,
    int extrap
    );
static double BiCubicCore(
    const FAArray2Ref<double>& z,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    int ix,
    int iy,
    double ttx,
    double tty,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int *err,
    FAArray1Ref<double>& zx
    );
static double BiCubic(
    const FAArray2Ref<double>& z,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    double xint,
    double yint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    double uniformdx,
    double uniformdy,
    int extrap
    );
static void BiCubicLoop(
//  x - loop
    const FAArray2Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    FAArray1Ref<double>& xint,
    double yint,
    FAArray1Ref<double>& uint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
	int ilow,
	int ihi,
    double uniformdx,
    double uniformdy,
    int extrap
    );
static void BiCubicLoop(
//  y - loop
    const FAArray2Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    double xint,
    FAArray1Ref<double>& yint,
    FAArray1Ref<double>& uint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
	int ilow,
	int ihi,
    double uniformdx,
    double uniformdy,
    int extrap
    );
static double BiCubicSpline(
    const FAArray2Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    double xint,
    double yint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    double uniformdx,
    double uniformdy,
    int extrap,
    int dir,
    FAArray2Ref<double>& fpp,
    FAArray1Ref<double>& TriTx,
    FAArray1Ref<double>& TriT2x,
    FAArray1Ref<double>& TriTy,
    FAArray1Ref<double>& TriT2y,
    FAArray1Ref<double>& ux,
    FAArray1Ref<double>& fppx,
    FAArray1Ref<double>& uy,
    FAArray1Ref<double>& fppy 
    );
static void BiCubicSplineCoefficients(
    const FAArray2Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    double uniformdx,
    double uniformdy,
    FAArray2Ref<double>& fpp,
    FAArray1Ref<double>& TriTx,
    FAArray1Ref<double>& TriT2x,
    FAArray1Ref<double>& TriTy,
    FAArray1Ref<double>& TriT2y,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int dir
    );
static void BiCubicSplineLoop(
//  x - loop
    const FAArray2Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
	FAArray1Ref<double>& xint,
    double yint,
    FAArray1Ref<double>& uint,
	int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int ilow,
    int ihi,
    double uniformdx,
    double uniformdy,
    int extrap,
    FAArray2Ref<double>& fpp,
	FAArray1Ref<double>& TriTx,
    FAArray1Ref<double>& TriT2x,
	FAArray1Ref<double>& TriTy,
    FAArray1Ref<double>& TriT2y,
    FAArray1Ref<double>& ux,
    FAArray1Ref<double>& fppx,
    FAArray1Ref<double>& uy,
    FAArray1Ref<double>& fppy 
    );
static void BiCubicSplineLoop(
//  y - loop
    const FAArray2Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
	double xint,
	FAArray1Ref<double>& yint,
    FAArray1Ref<double>& uint,
	int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int ilow,
    int ihi,
    double uniformdx,
    double uniformdy,
    int extrap,
    FAArray2Ref<double>& fpp,
	FAArray1Ref<double>& TriTx,
    FAArray1Ref<double>& TriT2x,
	FAArray1Ref<double>& TriTy,
    FAArray1Ref<double>& TriT2y,
    FAArray1Ref<double>& ux,
    FAArray1Ref<double>& fppx,
    FAArray1Ref<double>& uy,
    FAArray1Ref<double>& fppy 
    );
static double TriStairStep(
    const FAArray3Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
    double xint,
    double yint,
    double zint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    int bias,
    double eps
    );

static void TriStairStepLoop(
//  x - loop
    const FAArray3Ref<double>& vf,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
    FAArray1Ref<double>& xint,
    double yint,
    double zint,
    FAArray1Ref<double>& uint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
    int ilow,
    int ihi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    int bias,
    double eps
    );
static void TriStairStepLoop(
//  y - loop
    const FAArray3Ref<double>& vf,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
    double xint,
    FAArray1Ref<double>& yint,
	double zint,
    FAArray1Ref<double>& uint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
	int ilow,
	int ihi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    int bias,
    double eps
    );
static void TriStairStepLoop(
//  z - loop
    const FAArray3Ref<double>& vf,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
    double xint,
    double yint,
    FAArray1Ref<double>& zint,
    FAArray1Ref<double>& uint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
	int ilow,
	int ihi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    int bias,
    double eps
    );
static double Trilinear(
    const FAArray3Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
    double xint,
    double yint,
    double zint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    int extrap
    );
static void TrilinearLoop(
//  x - loop
    const FAArray3Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
    FAArray1Ref<double>& xint,
    double yint,
    double zint,
    FAArray1Ref<double>& uint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
	int ilow,
	int ihi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    int extrap
    );
static void TrilinearLoop(
//  y - loop
	const FAArray3Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
    double xint,
    FAArray1Ref<double>& yint,
    double zint,
    FAArray1Ref<double>& uint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
	int ilow,
	int ihi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    int extrap
    );
static void TrilinearLoop(
//  z - loop    
	const FAArray3Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
    double xint,
    double yint,
    FAArray1Ref<double>& zint,
    FAArray1Ref<double>& uint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
	int ilow,
	int ihi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    int extrap
    );
static double TriCubic(
    const FAArray3Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
	double xint,
    double yint,
    double zint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    int extrap
    );
static void TriCubicLoop(
//  x - loop
    const FAArray3Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
	FAArray1Ref<double>& xint,
    double yint,
    double zint,
	FAArray1Ref<double>& uint,
	int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
	int ilow,
	int ihi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    int extrap
    );
static void TriCubicLoop(
//  y - loop
    const FAArray3Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
	double xint,
    FAArray1Ref<double>& yint,
    double zint,
	FAArray1Ref<double>& uint,
	int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
	int ilow,
	int ihi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    int extrap
    );
static void TriCubicLoop(
//  z - loop
    const FAArray3Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
	double xint,
    double yint,
    FAArray1Ref<double>& zint,
	FAArray1Ref<double>& uint,
	int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
	int ilow,
	int ihi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    int extrap
    );
static double TriCubicSpline(
    const FAArray3Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
	double xint,
    double yint,
    double zint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    int extrap,
	int dir,
    FAArray3Ref<double>& fpp,
    FAArray1Ref<double>& TriTx,
    FAArray1Ref<double>& TriT2x,
    FAArray1Ref<double>& TriTy,
    FAArray1Ref<double>& TriT2y,
    FAArray1Ref<double>& TriTz,
    FAArray1Ref<double>& TriT2z
    );
static void TriCubicSplineLoop(
//  x - loop
    const FAArray3Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
	FAArray1Ref<double>& xint,
    double yint,
    double zint,
	FAArray1Ref<double>& uint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
	int ilow,
	int ihi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    int extrap,
    FAArray3Ref<double>& fpp,
    FAArray1Ref<double>& TriTx,
    FAArray1Ref<double>& TriT2x,
    FAArray1Ref<double>& TriTy,
    FAArray1Ref<double>& TriT2y,
    FAArray1Ref<double>& TriTz,
    FAArray1Ref<double>& TriT2z
    );
static void TriCubicSplineLoop(
//  y - loop
    const FAArray3Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
	double xint,
    FAArray1Ref<double>& yint,
    double zint,
	FAArray1Ref<double>& uint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
	int ilow,
	int ihi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    int extrap,
    FAArray3Ref<double>& fpp,
    FAArray1Ref<double>& TriTx,
    FAArray1Ref<double>& TriT2x,
    FAArray1Ref<double>& TriTy,
    FAArray1Ref<double>& TriT2y,
    FAArray1Ref<double>& TriTz,
    FAArray1Ref<double>& TriT2z
    );
static void TriCubicSplineLoop(
//  z - loop
    const FAArray3Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
	double xint,
    double yint,
    FAArray1Ref<double>& zint,
	FAArray1Ref<double>& uint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
	int ilow,
	int ihi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    int extrap,
    FAArray3Ref<double>& fpp,
    FAArray1Ref<double>& TriTx,
    FAArray1Ref<double>& TriT2x,
    FAArray1Ref<double>& TriTy,
    FAArray1Ref<double>& TriT2y,
    FAArray1Ref<double>& TriTz,
    FAArray1Ref<double>& TriT2z
    );

/***********************************************************/
static double Quadlinear(
    const FAArray4Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
    const FAArray1Ref<double>& w,
    double xint,
    double yint,
    double zint,
	double wint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
    int nwlow,
    int nwhi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    double uniformdw,
    int extrap
    );
static double QuadCubic(
    const FAArray4Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
    const FAArray1Ref<double>& w,
    double xint,
    double yint,
    double zint,
	double wint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
    int nwlow,
    int nwhi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    double uniformdw,
    int extrap
    );
static double QuadCubicCore(
    const FAArray4Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
    const FAArray1Ref<double>& w,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
    int nwlow,
    int nwhi,
	int indexx,
	int indexy,
	int indexz,
	int indexw,
	double ttx,
	double tty,
	double ttz,
	double ttw,
	FAArray1Ref<double>& ux,
	FAArray1Ref<double>& uy,
	FAArray1Ref<double>& uz
    );
/***********************************************************/


/***********************************************************/
/**************** 1D interpolation *************************/
/***********************************************************/

static void Locate(
    double xint,
    const FAArray1Ref<double>& x,
    double uniformdx,
    int nlow,
    int nhi,
    int ascend,
    int *locp
    )
{
    int ihigh,ilow,imid,incr;
    
    // ascend: True if x array (assumed monotonic) ascends, else False
    // ihigh:  index above the interpolation index
    // ilow:   index below interpolation index
    // imid:   average of ilow and ihigh
    // locp:   raw interpolation index
    // x:      abscissa
    // nlow:   lower abscissa index
    // nhi:    upper abscissa index
    // xint:   value to interpolate at
    // loc:    index of x just to left of xint
    //         = nlow-1 if xint out of range to the left
    //         = nhi+1  if xint out of range to the right

    // Out of range.
    if (ascend) {
        if (xint<x(nlow)) {
            *locp = nlow - 1; 
            return;
        } 
        else {
            if (xint>x(nhi)) {
                *locp = nhi + 1; 
                return;
            }
        }
    } else {
        if (xint<x(nhi)) {
            *locp = nhi + 1; 
            return;
        }
        else {
            if (xint>x(nlow)) {
                *locp = nlow - 1; 
                return; 
            }
        }
    }

    // uniform grid
    if (uniformdx>0.) {
        *locp = nlow + (int)((xint-x(nlow))/uniformdx);
        if (*locp==nhi) *locp = nhi-1;
        return;
    }

    // Hunt until bracketing indices found
    incr = 1;
    if (ascend) {
        ilow = *locp;
        ihigh = ilow + incr;
        if (xint>=x(min(nhi,max(ilow,nlow)))) {
            while (xint>x(max(min(ihigh,nhi),nlow))) {
                ilow = ihigh;
                incr = 2*incr;
                ihigh = min(ilow + incr,nhi);
            }
        } 
        else {
            ihigh = ilow;
            ilow = ihigh - incr;
            while (xint<x(min(nhi,max(ilow,nlow)))) {
                ihigh = ilow;
                incr = 2*incr;
                ilow = max(ihigh - incr,nlow);
            }
        }
    }
    else {
        ilow = *locp;
        ihigh = ilow + incr;
        if (xint>=x(max(min(ihigh,nhi),nlow))) {
            while (xint>x(min(nhi,max(ilow,nlow)))) {
                ihigh = ilow;
                incr = 2*incr;
                ilow = max(ihigh - incr,nlow);
            }
        }
        else {
            ilow = ihigh;
            ihigh = ilow + incr;
            while (xint<x(max(min(ihigh,nhi),nlow))) {
                ilow = ihigh;
                incr = 2*incr;
                ihigh = min(ilow - incr,nlow);
            }
        }
    }

    // Narrow bracket
    while (ihigh - ilow>1) {
        imid = (int)(floor((double)((ihigh + ilow) / 2)));
        if (((ascend&&xint<=x(imid))||(xint>x(imid)&&!ascend))) {
            ihigh = imid;
        }
        else {
            ilow = imid;
        }
    }
    *locp = ilow;
    if (*locp<nhi-1) {
        if (xint==x(*locp+1)) {*locp=*locp+1;}
    }
    return;
}

/***********************************************************/
/***********************************************************/

static void FindStairStepIndex(
    const FAArray1Ref<double>& x,
    double uniformdx,
    double xint,
    int nlow,
    int nhi,
	int ascend,
    int bias,
    double eps,
    int *locp,
	int *index
    )
{
    // used piecewise constant interpolation
	// returns -999 for out of range
    
    // ascend: True if x array (assumed monotonic) ascends, else False
    // loc:    raw interpolation index
    // x:      abscissa
    // y:      ordinate
    // nlow:   lower abscissa index
    // nhi:    upper abscissa index
    // xint:   value to interpolate at
    // bias:   =-1(+1) for left (right) bias

    // one data point
    if (nlow==nhi) {
        if (bias<0) {
            *index = (xint<x(nlow) ? -999 : nlow);
        }
        else {
            *index = (xint>x(nhi)  ? -999 : nhi);
        }
		return;
    }

    // locate index just to the left of xint
    Locate(xint,x,uniformdx,nlow,nhi,ascend,locp);

    // out of range
    if ((bias<0 && *locp<nlow) || (bias>0 && *locp>nhi))   {*index = -999; return;}

    // exact hit
    if (bias>0 && *locp>=nlow && fpequal(x(*locp),xint,1000*eps))   {*index = *locp;   return;}
    if (bias<0 && *locp<nhi   && fpequal(x(*locp+1),xint,1000*eps)) {*index = *locp+1; return;}
    
    // within range
    if (bias<0) {
        *index = min(*locp,nhi);
    }
    else {
        *index = *locp+1;
    }
	return;
}

/***********************************************************/
/***********************************************************/

static double StairStep(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x,
    double xint,
    int nlow,
    int nhi,
    double uniformdx,
    int bias,
    double eps
    )
{
    // piecewise constant interpolation
    int ix,loc,ascend;
    
    // ascend: True if x array (assumed monotonic) ascends, else False
    // loc:    raw interpolation index
    // x:      abscissa
    // y:      ordinate
    // nlow:   lower abscissa index
    // nhi:    upper abscissa index
    // xint:   value to interpolate at
    // bias:   =-1(+1) for left (right) bias

    ascend = x(nhi)>=x(nlow);
	loc = nlow;
	FindStairStepIndex(x,uniformdx,xint,nlow,nhi,ascend,bias,eps,&loc,&ix);
	return ((ix==-999) ? 0. : y(ix));
}

/***********************************************************/
/***********************************************************/

static void StairStepLoop(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& xint,
    FAArray1Ref<double>& yint,
    int nlow,
    int nhi,
    int ilow,
    int ihi,
    double uniformdx,
    int bias,
    double eps
    )
{
    // piecewise constant interpolation
    // loop version
    int loc,i,ix,ascend;
    
    // loc:    raw interpolation index
    // x:      abscissa
    // y:      ordinate
    // nlow:   lower abscissa index
    // nhi:    upper abscissa index
    // xint:   array of values at which to interpolate
    // yint:   array of interpolated values
    // bias:   =-1(+1) for left (right) bias
    // ilow    lower index of xint
    // ihi     upper index of xint
    
    ascend = x(nhi)>=x(nlow);
    loc = nlow;
    for (i=ilow; i<=ihi; i++) {
	    FindStairStepIndex(x,uniformdx,xint(i),nlow,nhi,ascend,bias,eps,&loc,&ix);
	    yint(i) = (ix==-999) ? 0. : y(ix);
    }
    return;
}

/***********************************************************/
/***********************************************************/

static double SawTooth(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x,
    double xint,
    int nlow,
    int nhi,
    double uniformdx,
    int valleys,
    double eps
    )
{
    // SawTooth interpolation (accrual function)
    int loc,ascend;
    double Delta;
    
    // ascend: True if x array (assumed monotonic) ascends, else False
    // loc:    raw interpolation index
    // x:      abscissa
    // y:      ordinate
    // nlow:   lower abscissa index
    // nhi:    upper abscissa index
    // xint:   value to interpolate at
    // valleys:  =1(0) for valleys(peaks)
    // Delta:  interval

    // Out of range
    if (xint>x(nhi) || xint<x(nlow)) return 0.;

    loc = nlow;
    ascend = x(nhi)>=x(nlow);
    Locate(xint,x,uniformdx,nlow,nhi,ascend,&loc);

    // Exact hit
    if (fpequal(xint,x(loc),1000*eps)) return (valleys==1 ? 0. : y(loc));
    if (fpequal(xint,x(nhi),1000*eps)) return (valleys==1 ? 0. : y(nhi));

    Delta = x(loc + 1) - x(loc);
    if (Delta==0.) {
        throw new FAErrorException(        
           "SawTooth: Error - The interval between interpolation points is 0."
            ,InterpolationDeltaError);
    }
    return ((xint - x(loc))*y(loc + 1)) / Delta;
}

/***********************************************************/
/***********************************************************/

static void SawToothLoop(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& xint,
    FAArray1Ref<double>& yint,
    int nlow,
    int nhi,
    int ilow,
    int ihi,
    double uniformdx,
    int valleys,
    double eps
    )
{
    // SawTooth interpolation (accrual function)
    // loop version
    int loc,ascend,i;
    double Delta;
    
    // ascend: True if x array (assumed monotonic) ascends, else False
    // loc:    raw interpolation index
    // x:      abscissa
    // y:      ordinate
    // nlow:   lower abscissa index
    // nhi:    upper abscissa index
    // xint:   array of values at which to interpolate
    // yint:   array of interpolated values
    // ilow    lower index of xint
    // ihi     upper index of xint
    // valleys:  =1(0) for valleys(peaks)
    // Delta:  interval

    loc = nlow;
    ascend = x(nhi)>=x(nlow);
    for (i=ilow; i<=ihi; i++) {
        // Out of range
        if (xint(i)>x(nhi) || xint(i)<x(nlow)) {
            yint(i) = 0.;
        }
        // Right end point
        else if (fpequal(xint(i),x(nhi),1000*eps)) {
            yint(i) = (valleys==1 ? 0. : y(nhi));
        }
        else {
            Locate(xint(i),x,uniformdx,nlow,nhi,ascend,&loc);
            // Exact hit
            if (fpequal(xint(i),x(loc),1000*eps)) {
                yint(i) = (valleys==1 ? 0. : y(loc));
            }
            else {
                Delta = x(loc + 1) - x(loc);
                if (Delta==0.) {
                    throw new FAErrorException(        
                       "SawToothLoop: Error - The interval between interpolation points is 0."
                        ,InterpolationDeltaError);
                }
                yint(i) = ((xint(i) - x(loc))*y(loc + 1)) / Delta;
            }
        }
    }
    return; 
}

/***********************************************************/
/***********************************************************/

static void ComputeIntervalFraction(
    const FAArray1Ref<double>& x,
    double uniformdx,
    double xint,
    int nlow,
    int nhi,
    int ascend,
    int extrap,
    int *loc,
    int *index,
    double *tt,
    char *ErrorMsg
    )
{
    double Delta;

	// check for degenerate data
	if (nlow==nhi) {
		*index = nlow;
		*tt = 0.;
		*loc = nlow;
	    return;
	}

    // compute the interpolation interval tt
    // and the interpolation index
    Locate(xint,x,uniformdx,nlow,nhi,ascend,loc);

    // Adjust the indices of the end points.
    *tt = -1.;
    if (*loc<=nlow-1) {
        *index = nlow;
        if (extrap==0) *tt = 0.;
    }
    else if (*loc>=nhi) {
        *index = max(nhi-1,nlow);
        if (extrap==0) *tt = 1.;
    }
    else {
        *index = *loc;
    }

    // Compute the fraction of the interval if not yet defined
    if (*tt==-1.) {
        Delta = x(*index+1) - x(*index);
        if (Delta==0.) {
            throw new FAErrorException(ErrorMsg,InterpolationDeltaError);
        }
        *tt = (xint - x(*index)) / Delta;
    }
    return;
}

/***********************************************************/
/***********************************************************/

static double InterpolateLinear(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x,
    double xint,
    int nlow,
    int nhi,
    double uniformdx,
    int extrap
    )
{
    // linear interpolation
    int index,loc,ascend;
    double tt;
    char ErrorMsg[] = "InterpolateLinear: Error - The interval between interpolation points is 0.";
    
    // ascend: True if x array (assumed monotonic) ascends, else False
    // index:   adjusted interpolation index
    // loc:    raw interpolation index
    // x:      abscissa
    // y:      ordinate
    // nlow:   lower abscissa index
    // nhi:    upper abscissa index
    // xint:   value to interpolate at
    // tt:     fraction of interval
    // extrap: =1(0): do(not) linearly extrapolate out of range xint

    // single data point
    if (nhi==nlow) {
        return y(nhi);
    }

    // locate point just to the left and compute interval fraction
    loc = nlow;
    ascend = x(nhi)>=x(nlow);
    ComputeIntervalFraction(x,uniformdx,xint,nlow,nhi,ascend,extrap,&loc,&index,&tt,ErrorMsg);

    return y(index) + tt*(y(index+1) - y(index));
}

/***********************************************************/
/***********************************************************/

static void InterpolateLinearLoop(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& xint,
    FAArray1Ref<double>& yint,
    int nlow,
    int nhi,
    int ilow,
    int ihi,
    double uniformdx,
    int extrap
    )
{
    // linear interpolation
    // loop version
    int loc,i,ascend,index;
    double tt;
    char ErrorMsg[] = "InterpolateLinearLoop: Error - The interval between interpolation points is 0.";

    // ascend: True if x array (assumed monotonic) ascends, else False
    // index:  adjusted interpolation index
    // loc:    raw interpolation index
    // x:      abscissa
    // y:      ordinate
    // nlow:   lower abscissa index
    // nhi:    upper abscissa index
    // xint:   array of values at which to interpolate
    // yint:   array of interpolated values
    // ilow    lower index of xint
    // ihi     upper index of xint
    // tt:     fraction of interval
    // extrap: =1(0): do(not) linearly extrapolate out of range xint

    if (nhi==nlow) {
        for (i=ilow; i<=ihi; i++) {
            yint(i) = y(nlow);
        }
        return;
    }

    loc = nlow;
    ascend = x(nhi)>=x(nlow);
    for (i=ilow; i<=ihi; i++) {
        // locate point just to the left and compute interval fraction
        ComputeIntervalFraction(x,uniformdx,xint(i),nlow,nhi,ascend,extrap,&loc,&index,&tt,ErrorMsg);
        yint(i) = y(index) + tt*(y(index+1) - y(index));
    }
    return;
}

/***********************************************************/
/***********************************************************/

static double Quadratic(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x,
    double xint,
    int nlow,
    int nhi,
    double uniformdx,
	int bias,
    int extrap
    )
{
    // quadratic interpolation
    int index,loc,ascend;
    double tt,Q,Delta,Deltam,Deltap,fpp,fp0,fpm,fpp0;
    char ErrorMsg[] = "Quadratic: Error - The interval between interpolation points is 0.";
    
    // ascend: True if x array (assumed monotonic) ascends, else False
    // index:   adjusted interpolation index
    // loc:    raw interpolation index
    // x:      abscissa
    // y:      ordinate
    // nlow:   lower abscissa index
    // nhi:    upper abscissa index
    // xint:   value to interpolate at
	// bias:   +(-)1 for right(left) bias
    // tt:     fraction of interval
    // extrap: =1(0): do(not) linearly extrapolate out of range xint

    // single data point
    if (nhi==nlow) {
        return y(nhi);
    }

    // locate point just to the left and compute interval fraction
    loc = nlow;
    ascend = x(nhi)>=x(nlow);
    ComputeIntervalFraction(x,uniformdx,xint,nlow,nhi,ascend,extrap,&loc,&index,&tt,ErrorMsg);

    // linear piece
    Q = y(index) + tt*(y(index+1) - y(index));
    if (index<=nlow || (nhi-nlow)<2 || index>=nhi-1) return Q;

    // quadratic correction
    if (bias>0) {
        Delta  = x(index+1) - x(index);
        Deltap = x(index+2) - x(index+1);
        if (Delta==0. || Deltap==0.) {
            throw new FAErrorException(ErrorMsg,InterpolationDeltaError);
		}
        fp0 = (y(index+1) - y(index))/Delta;
        fpp = (y(index+2) - y(index+1))/Deltap;
        fpp0 =  2*(fpp - fp0) / (Delta + Deltap);
        Q = Q + tt*(tt-1.)*fpp0*Delta*Delta/2;
	} else {
        Deltam = x(index) - x(index-1);
        Delta  = x(index+1) - x(index);
        if (Delta==0. || Deltam==0.) {
            throw new FAErrorException(ErrorMsg,InterpolationDeltaError);
		}
        fpm = (y(index) - y(index-1))/Deltam;
        fp0 = (y(index+1) - y(index))/Delta;
        fpp0 =  2*(fp0 - fpm) / (Delta + Deltam);
        Q = Q + tt*(tt-1.)*fpp0*Delta*Delta/2;
	}
    return Q;
}

/***********************************************************/
/***********************************************************/

static void QuadraticLoop(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& xint,
    FAArray1Ref<double>& yint,
    int nlow,
    int nhi,
    int ilow,
    int ihi,
    double uniformdx,
	int bias,
    int extrap
    )
{
    // quadratic interpolation
    // loop version
    int loc,i,ascend,index;
    double tt,Delta,Deltam,Deltap,fpp,fp0,fpm,fpp0;
    char ErrorMsg[] = "QuadraticLoop: Error - The interval between interpolation points is 0.";

    // ascend: True if x array (assumed monotonic) ascends, else False
    // index:  adjusted interpolation index
    // loc:    raw interpolation index
    // x:      abscissa
    // y:      ordinate
    // nlow:   lower abscissa index
    // nhi:    upper abscissa index
    // xint:   array of values at which to interpolate
    // yint:   array of interpolated values
    // ilow    lower index of xint
    // ihi     upper index of xint
    // tt:     fraction of interval
	// bias:   +(-)1 for right(left) bias
    // extrap: =1(0): do(not) linearly extrapolate out of range xint

    if (nhi==nlow) {
        for (i=ilow; i<=ihi; i++) {
            yint(i) = y(nlow);
        }
        return;
    }

    loc = nlow;
    ascend = x(nhi)>=x(nlow);
    for (i=ilow; i<=ihi; i++) {
        // locate point just to the left and compute interval fraction
        ComputeIntervalFraction(x,uniformdx,xint(i),nlow,nhi,ascend,extrap,&loc,&index,&tt,ErrorMsg);
        yint(i) = y(index) + tt*(y(index+1) - y(index));
        // quadratic correction
        if (index>nlow && (nhi-nlow)>=2 && index<nhi-1) {
			if (bias>0) {
                Delta  = x(index+1) - x(index);
                Deltap = x(index+2) - x(index+1);
                if (Delta==0. || Deltap==0.) {
                    throw new FAErrorException(ErrorMsg,InterpolationDeltaError);
				}
                fp0 = (y(index+1) - y(index))/Delta;
                fpp = (y(index+2) - y(index+1))/Deltap;
                fpp0 =  2*(fpp - fp0) / (Delta + Deltap);
                yint(i) = yint(i) + tt*(tt-1.)*fpp0*Delta*Delta/2;
			}
			else {
                Deltam = x(index) - x(index-1);
                Delta  = x(index+1) - x(index);
                if (Delta==0. || Deltam==0.) {
                    throw new FAErrorException(ErrorMsg,InterpolationDeltaError);
				}
                fpm = (y(index) - y(index-1))/Deltam;
                fp0 = (y(index+1) - y(index))/Delta;
                fpp0 =  2*(fp0 - fpm) / (Delta + Deltam);
                yint(i) = yint(i) + tt*(tt-1.)*fpp0*Delta*Delta/2;
			}

        }
    }
    return;
}

/***********************************************************/
/***********************************************************/

static double Cubic(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x,
    double xint,
    int nlow,
    int nhi,
    double uniformdx,
    int extrap
    )
{
    // cubic interpolation
    int index,loc,ascend;
    double tt,ttc,C,Delta,Deltam,Deltap,fpp,fp0,fpm,fpp0,fpp1;
    char ErrorMsg[] = "Cubic: Error - The interval between interpolation points is 0.";
    
    // ascend: True if x array (assumed monotonic) ascends, else False
    // index:   adjusted interpolation index
    // loc:    raw interpolation index
    // x:      abscissa
    // y:      ordinate
    // nlow:   lower abscissa index
    // nhi:    upper abscissa index
    // xint:   value to interpolate at
    // tt:     fraction of interval
    // extrap: =1(0): do(not) linearly extrapolate out of range xint

    // single data point
    if (nhi==nlow) {
        return y(nhi);
    }

    // locate point just to the left and compute interval fraction
    loc = nlow;
    ascend = x(nhi)>=x(nlow);
    ComputeIntervalFraction(x,uniformdx,xint,nlow,nhi,ascend,extrap,&loc,&index,&tt,ErrorMsg);

    // linear piece
    C = y(index) + tt*(y(index+1) - y(index));
    if (index<=nlow || (nhi-nlow)<3 || index>=nhi-1) return C;

    // cubic correction
    Deltam = x(index) - x(index-1);
    Delta  = x(index+1) - x(index);
    Deltap = x(index+2) - x(index+1);
    if (Deltam==0. || Delta==0. || Deltap==0) {
        throw new FAErrorException(ErrorMsg,InterpolationDeltaError);
    }
    fpm = (y(index) - y(index-1))/Deltam;
    fp0 = (y(index+1) - y(index))/Delta;
    fpp = (y(index+2) - y(index+1))/Deltap;
    fpp0 =  2*(fp0 - fpm) / (Delta + Deltam);
    fpp1 =  2*(fpp - fp0) / (Deltap + Delta);
    ttc = 1. - tt;
    C = C + (ttc*(ttc*ttc-1.)*fpp0 + tt*(tt*tt-1.)*fpp1)*Delta*Delta/6.;
    return C;
}

/***********************************************************/
/***********************************************************/

static void CubicLoop(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& xint,
    FAArray1Ref<double>& yint,
    int nlow,
    int nhi,
    int ilow,
    int ihi,
    double uniformdx,
    int extrap
    )
{
    // cubic interpolation
    // loop version
    int loc,i,ascend,index;
    double tt,ttc,Delta,Deltam,Deltap,fpp,fp0,fpm,fpp0,fpp1;
    char ErrorMsg[] = "CubicLoop: Error - The interval between interpolation points is 0.";

    // ascend: True if x array (assumed monotonic) ascends, else False
    // index:  adjusted interpolation index
    // loc:    raw interpolation index
    // x:      abscissa
    // y:      ordinate
    // nlow:   lower abscissa index
    // nhi:    upper abscissa index
    // xint:   array of values at which to interpolate
    // yint:   array of interpolated values
    // ilow    lower index of xint
    // ihi     upper index of xint
    // tt:     fraction of interval
    // extrap: =1(0): do(not) linearly extrapolate out of range xint

    if (nhi==nlow) {
        for (i=ilow; i<=ihi; i++) {
            yint(i) = y(nlow);
        }
        return;
    }

    loc = nlow;
    ascend = x(nhi)>=x(nlow);
    for (i=ilow; i<=ihi; i++) {
        // locate point just to the left and compute interval fraction
        ComputeIntervalFraction(x,uniformdx,xint(i),nlow,nhi,ascend,extrap,&loc,&index,&tt,ErrorMsg);
        yint(i) = y(index) + tt*(y(index+1) - y(index));
        // cubic correction
        if (index>nlow && (nhi-nlow)>=3 && index<nhi-1) {
            Deltam = x(index) - x(index-1);
            Delta  = x(index+1) - x(index);
            Deltap = x(index+2) - x(index+1);
            if (Deltam==0. || Delta==0. || Deltap==0) {
                throw new FAErrorException(ErrorMsg,InterpolationDeltaError);
            }
            fpm = (y(index) - y(index-1))/Deltam;
            fp0 = (y(index+1) - y(index))/Delta;
            fpp = (y(index+2) - y(index+1))/Deltap;
            fpp0 =  2*(fp0 - fpm) / (Delta + Deltam);
            fpp1 =  2*(fpp - fp0) / (Deltap + Delta);
            ttc = 1. - tt;
            yint(i) = yint(i) + (ttc*(ttc*ttc-1.)*fpp0 + tt*(tt*tt-1.)*fpp1)*Delta*Delta/6.;
        }
    }
    return;
}

/***********************************************************/
/***********************************************************/

static void SplineForwardSweep(
    const FAArray1Ref<double>& x,
    double uniformdx,
    FAArray1Ref<double>& TriT,
    FAArray1Ref<double>& TriT2,
    int nlow,
    int nhi
    )
{
    int i;
    
    TriT(nlow) = 1.;
    TriT2(nlow) = 0.;
    // uniform grid
    if (uniformdx>0.) {
        for (i=nlow+1; i<=nhi-1; i++) {
            TriT(i) = 1. / (TriT2(i-1)*uniformdx/6. + 4.*uniformdx/6.);
            TriT2(i) = -TriT(i)*uniformdx/6.;
        }
    }
    else {
        for (i=nlow+1; i<=nhi-1; i++) {
            TriT(i) = 1. / (TriT2(i-1)*(x(i)-x(i-1))/6. + (x(i+1)-x(i-1))/3.);
            TriT2(i) = TriT(i)*(x(i)-x(i+1))/6.;
        }
    }
    TriT(nhi) = 1.;
    TriT2(nhi) = 0.;
    return;
}

/***********************************************************/
/***********************************************************/

static void SplineCoefficients(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x,
    double uniformdx,
    FAArray1Ref<double>& fpp,
    const FAArray1Ref<double>& TriT,
    const FAArray1Ref<double>& TriT2,
    int nlow,
    int nhi
    )
{
    int i;
    
    fpp(nlow) = 0.;
    // uniform grid
    if (uniformdx>0.) {
        for (i=nlow+1; i<=nhi-1; i++) {
            fpp(i) = TriT(i)*((y(i+1)-y(i))/uniformdx - (y(i)-y(i-1))/uniformdx - fpp(i-1)*uniformdx/6.);
        }
    }
    // nonuniform grid
    else {
        for (i=nlow+1; i<=nhi-1; i++) {
            fpp(i) = TriT(i)*((y(i+1)-y(i))/(x(i+1)-x(i)) - (y(i)-y(i-1))/(x(i)-x(i-1)) - fpp(i-1)*(x(i)-x(i-1))/6.);
        }
    }

    fpp(nhi) = 0.;
    for (i=1; i<=nhi-nlow; i++) {
        fpp(nhi-i) = fpp(nhi-i) + fpp(nhi-i+1)*TriT2(nhi-i);
    }
    return;
}

/***********************************************************/
/***********************************************************/

static double CubicSpline(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& fpp,
    double xint,
    int nlow,
    int nhi,
    double uniformdx,
    int extrap
    )
{
    // cubic spline interpolation
    int index,loc,ascend;
    double tt,ttc,CS,Delta;
    char ErrorMsg[] = "CubicSpline: Error - The interval between interpolation points is 0.";
    
    // ascend: True if x array (assumed monotonic) ascends, else False
    // index:   adjusted interpolation index
    // loc:    raw interpolation index
    // x:      abscissa
    // y:      ordinate
    // nlow:   lower abscissa index
    // nhi:    upper abscissa index
    // xint:   value to interpolate at
    // tt:     fraction of interval
    // extrap: =1(0): do(not) linearly extrapolate out of range xint

    // single data point
    if (nhi==nlow) {
        return y(nhi);
    }

    // locate point just to the left and compute interval fraction
    loc = nlow;
    ascend = x(nhi)>=x(nlow);
    ComputeIntervalFraction(x,uniformdx,xint,nlow,nhi,ascend,extrap,&loc,&index,&tt,ErrorMsg);

    // linear piece
    CS = y(index) + tt*(y(index+1) - y(index));

    // cubic spline correction
    if (tt>=0. && (nhi-nlow)>=2 && tt<=1.) {
        Delta = x(index + 1) - x(index);
        ttc = 1. - tt;
        CS = CS + (ttc*(ttc*ttc - 1.)*fpp(index) + tt*(tt*tt - 1.)*fpp(index+1))*Delta*Delta/6.;
    }
    return CS;
}

/***********************************************************/
/***********************************************************/

static double DCubicSpline(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& fpp,
    double xint,
    int nlow,
    int nhi,
    double uniformdx,
    int extrap
    )
{
    // derivative of a cubic spline interpolation
    int index,loc,ascend;
    double tt,ttc,dCS,Delta;
    char ErrorMsg[] = "DCubicSpline: Error - The interval between interpolation points is 0.";
    
    // ascend: True if x array (assumed monotonic) ascends, else False
    // index:   adjusted interpolation index
    // loc:    raw interpolation index
    // x:      abscissa
    // y:      ordinate
    // nlow:   lower abscissa index
    // nhi:    upper abscissa index
    // xint:   value to interpolate at
    // tt:     fraction of interval
    // extrap: =1(0): do(not) linearly extrapolate out of range xint

    // single data point
    if (nhi==nlow) {
        return 0.;
    }

    // locate point just to the left and compute interval fraction
    loc = nlow;
    ascend = x(nhi)>=x(nlow);
    ComputeIntervalFraction(x,uniformdx,xint,nlow,nhi,ascend,extrap,&loc,&index,&tt,ErrorMsg);

    // linear piece
    Delta = x(index + 1) - x(index);
    dCS = (y(index+1) - y(index)) / Delta;

    // cubic spline correction
    if (tt>=0. && (nhi-nlow)>=2 && tt<=1.) {
        ttc = 1. - tt;
        dCS = dCS - ((3.*ttc*ttc - 1.)*fpp(index) + (3.*tt*tt - 1.)*fpp(index+1))*Delta/6.;
    }
    return dCS;
}

/***********************************************************/
/***********************************************************/

static void CubicSplineLoop(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& fpp,
    const FAArray1Ref<double>& xint,
    FAArray1Ref<double>& yint,
    int nlow,
    int nhi,
    int ilow,
    int ihi,
    double uniformdx,
    int extrap
    )

{
    // cubic spline interpolation
    // loop version
    int index,loc,ascend,i;
    double tt,ttc,CS,Delta;
    char ErrorMsg[] = "CubicSplineLoop: Error - The interval between interpolation points is 0.";
    
    // ascend: True if x array (assumed monotonic) ascends, else False
    // index:   adjusted interpolation index
    // loc:    raw interpolation index
    // x:      abscissa
    // y:      ordinate
    // nlow:   lower abscissa index
    // nhi:    upper abscissa index
    // xint:   array of values at which to interpolate
    // yint:   array of interpolated values
    // ilow    lower index of xint
    // ihi     upper index of xint
    // tt:     fraction of interval
    // extrap: =1(0): do(not) linearly extrapolate out of range xint

    // single data point
    if (nhi==nlow) {
        for (i=ilow; i<=ihi; i++) {
            yint(i) = y(nlow);
        }
        return;
    }

    loc = nlow;
    ascend = x(nhi)>=x(nlow);
    for (i=ilow; i<=ihi; i++) {

        // locate point just to the left and compute interval fraction
        ComputeIntervalFraction(x,uniformdx,xint(i),nlow,nhi,ascend,extrap,&loc,&index,&tt,ErrorMsg);

        // linear piece
        CS = y(index) + tt*(y(index+1) - y(index));

        // cubic spline correction
        if (tt>=0. && (nhi-nlow)>=2 && tt<=1.) {
            Delta = x(index + 1) - x(index);
            ttc = 1. - tt;
            CS = CS + (ttc*(ttc*ttc - 1.)*fpp(index) + tt*(tt*tt - 1.)*fpp(index+1))*Delta*Delta/6.;
        }
        yint(i) = CS;
    }
    return;
}

/***********************************************************/
/***********************************************************/

static void DCubicSplineLoop(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& fpp,
    const FAArray1Ref<double>& xint,
    FAArray1Ref<double>& yint,
    int nlow,
    int nhi,
    int ilow,
    int ihi,
    double uniformdx,
    int extrap
    )

{
    // derivative of a cubic spline interpolation
    // loop version
    int index,loc,ascend,i;
    double tt,ttc,dCS,Delta;
    char ErrorMsg[] = "DCubicSplineLoop: Error - The interval between interpolation points is 0.";
    
    // ascend: True if x array (assumed monotonic) ascends, else False
    // index:   adjusted interpolation index
    // loc:    raw interpolation index
    // x:      abscissa
    // y:      ordinate
    // nlow:   lower abscissa index
    // nhi:    upper abscissa index
    // xint:   array of values at which to interpolate
    // yint:   array of interpolated values
    // ilow    lower index of xint
    // ihi     upper index of xint
    // tt:     fraction of interval
    // extrap: =1(0): do(not) linearly extrapolate out of range xint

    // single data point
    if (nhi==nlow) {
        for (i=ilow; i<=ihi; i++) {
            yint(i) = y(nlow);
        }
        return;
    }

    loc = nlow;
    ascend = x(nhi)>=x(nlow);
    for (i=ilow; i<=ihi; i++) {

        // locate point just to the left and compute interval fraction
        ComputeIntervalFraction(x,uniformdx,xint(i),nlow,nhi,ascend,extrap,&loc,&index,&tt,ErrorMsg);

        // linear piece
        Delta = x(index + 1) - x(index);
        dCS = (y(index+1) - y(index)) / Delta;

        // cubic spline correction
        if (tt>=0. && (nhi-nlow)>=2 && tt<=1.) {
            ttc = 1. - tt;
            dCS = dCS - ((3.*ttc*ttc - 1.)*fpp(index) + (3.*tt*tt - 1.)*fpp(index+1))*Delta/6.;
        }
        yint(i) = dCS;
    }
    return;
}

/***********************************************************/
/***********************************************************/

static void ForwardMonotoneConvexCoefficients(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x, 
    double uniformdx,
    FAArray1Ref<double>& FMCdiscf,
    FAArray1Ref<double>& FMCavef, 
    int nlow,
    int nhi
	)
{
    // Compute auxiliary arrays for forward monotone convex spline interpolation
  	// x:          abscissa (assuming ascending)
 	// y:          ordinate
    // uniformdx:  grid spacing (if uniform), otherwise 0.0
    // xint:       array of values at which to interpolate
    // yint:       array of interpolated values
    // nlow:       lower abscissa index
    // nhi:        upper abscissa index
 	// ilow:       lower index of xint
 	// ihi:        upper index of xint
 
	int i;
	double xf;
    char ErrorMsg1[] = "ForwardMonotoneConvex: Error - The maturity points are not monotonic ascending.";
    char ErrorMsg2[] = "ForwardMonotoneConvex: Error - The interval between interpolation points is 0.";

	// check if ascending
	int ascend=(x(nhi)>=x(nlow));
	if (!ascend) {
         throw new FAErrorException(ErrorMsg1, InterpolationDeltaError);
	}

	// Calculating the discrete forward rates
	FMCdiscf(nlow) = y(nlow);
	if (uniformdx>0.) {	// uniform grid
		for (i = nlow+1; i <= nhi; i++){
			FMCdiscf(i) = ( y(i)*x(i) - y(i-1)*x(i-1) ) / uniformdx;
		}
	}
	else {				// nonuniform grid
		for (i = nlow+1; i <= nhi; i++){
            if ((x(i)-x(i-1))>0.) {
				FMCdiscf(i) = ( y(i)*x(i) - y(i-1)*x(i-1) ) / (x(i) - x(i-1));
			}
			else{
                throw new FAErrorException(ErrorMsg2, InterpolationDeltaError);
            }
		}
	}

	// Calculate the average forward rates
	xf = ( x(nlow+1)-x(nlow) ) / x(nlow+1);
	FMCavef(nlow) = (1.0-xf)*FMCdiscf(nlow+1)+xf*FMCdiscf(nlow);

	if (uniformdx>0.) {	// uniform grid
	    for (i=nlow+1; i<=nhi-1; i++) 
			FMCavef(i) = 0.5*(FMCdiscf(i+1)+FMCdiscf(i));
	}
	else{				// nonuniform grid
	    for (i = nlow+1;i <= nhi-1; i++){
			xf = ( x(i+1)-x(i) )/( x(i+1)-x(i-1) );
			FMCavef(i) = (1.0-xf)*FMCdiscf(i+1)+xf*FMCdiscf(i);
		}
	}
	FMCavef(nhi) = FMCdiscf(nhi) - 0.5*( FMCavef(nhi-1)-FMCdiscf(nhi) );
	return;

}

/***********************************************************/
/***********************************************************/

static double ForwardMonotoneConvex(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x, 
    const FAArray1Ref<double>& FMCdiscf,
    const FAArray1Ref<double>& FMCavef, 
    double xint,
    int nlow,
    int nhi,
    double uniformdx
    )
{
    // Forward monotone convex spline interpolation
  	// x:          abscissa (assuming ascending)
 	// y:          ordinate
    // uniformdx:  grid spacing (if uniform), otherwise 0.0
    // xint:       array of values at which to interpolate
    // yint:       array of interpolated values
    // nlow:       lower abscissa index
    // nhi:        upper abscissa index
 	// ilow:       lower index of xint
 	// ihi:        upper index of xint
 
	int i;
	double FMCavef0,ggi,ggi1,u,Iu,yint,eta,Acoeff,u2,u3,eta2,eta2m,eta3;

	// assume have already checked for descending in coefficient computation
	int ascend = 1;
	FMCavef0 = FMCdiscf(nlow) - 0.5*( FMCavef(nlow)-FMCdiscf(nlow) );

	i=0;	// must be initialized
	Locate(xint, x, uniformdx, nlow, nhi, ascend, &i);
	// out of range left = nlow-1
	// out of range right = nhi-1
	// inside nlow,nlow+1, ... , nhi-1
	i=i+1; // convenience convention
	// out of range left = nlow
	// out of range right = nhi+1
	// inside nlow,nlow+2, ... , nhi

	// Extrapolation around zero
	if (i<=nlow) {
		u = xint / x(nlow);
		u2 = u*u;
		u3 = u*u*u;
		ggi = FMCavef(nlow) - FMCdiscf(nlow);
		ggi1 = FMCavef0 - FMCdiscf(nlow);
		    
		// Basic interpolator
		Iu = ggi1*(u-2*u2+u3) + ggi*(-u2+u3);
		if (xint > 0.0) 
			yint = ( xint*FMCdiscf(i) + x(nlow)*Iu )/xint;
		else
			yint = FMCavef0;
		return yint;
	}
				
	if (i >= nlow+1 && i <= nhi){	//within data range
		u = (xint - x(i-1)) / (x(i) - x(i-1));
		u2 = u*u;
		u3 = u*u*u;
		ggi = FMCavef(i) - FMCdiscf(i);
		ggi1 = FMCavef(i-1) - FMCdiscf(i);
		// Basic interpolator
		Iu = ggi1*(u-2*u2+u3) + ggi*(-u2+u3);
		    
		// Convex monotonic adjustment 
		if ( (ggi1<0 && ggi>-2.0*ggi1) || (ggi1>0 && ggi<-2.0*ggi1) ){
			eta = (ggi+2.0*ggi1)/(ggi-ggi1);
			eta2 = eta*eta;
			eta3 = eta2*eta;
			eta2m = (1-eta)*(1-eta);
			if (u<=eta && u>=0){
				Iu=ggi1*u;    
			}
			if (u>eta && u<=1.0){
				Iu = ggi1*eta+ggi1*u +
				    (ggi-ggi1)/eta2m*(u3/3.0-eta*u2+eta2*u) -
				    (ggi1*eta+(ggi-ggi1)/eta2m*eta3/3.0);
			}
		}
		
		else if ( (ggi1>0 && ggi<0 && ggi>-0.5*ggi1) || 
			( ggi1<0 && ggi>0 && ggi<-0.5*ggi1) ){
			eta = 3*ggi/(ggi-ggi1);
			eta2 = eta*eta;
			eta3 = eta2*eta;
			if (u<eta && u>0){
				Iu = ggi*u + (ggi1-ggi)/eta2*(eta2*u-eta*u2+u3/3.0);
			}
			if (u>=eta && u<1){
				Iu = ggi*eta + (ggi1-ggi)/eta2*eta3/3.0+ggi*(u-eta);
			}
		}

		else if ( (ggi1==0 && ggi==0 ) ){
			Iu=0.;
		}

		if ( (ggi1>0 && ggi>0 ) || (ggi1<0 && ggi<0) ){
			eta = ggi/(ggi+ggi1);
			eta2 = eta*eta;
			eta2m = (1-eta)*(1-eta);
			eta3 = eta2*eta;
			Acoeff = -ggi1*ggi/(ggi1+ggi);
			if (u<eta && u>0) {
				Iu = Acoeff*u + (ggi1-Acoeff)/eta2*(eta2*u-eta*u2+u3/3.0);
			}
			if (u==eta){
				Iu = Acoeff*eta + (ggi1-Acoeff)/eta2*eta3/3.0;
			}
       		if (u>eta && u<1){
				Iu = Acoeff*eta + (ggi1-Acoeff)/eta2*eta3/3.0 +
				     Acoeff*u + (ggi-Acoeff)/eta2m*(u3/3.0-eta*u2+eta2*u) -
				    (Acoeff*eta + (ggi-Acoeff)/eta2m*eta3/3.0 );
			}
		}

		if (xint>x(i-1)) {
			yint=( y(i-1)*x(i-1)+ (xint-x(i-1))*FMCdiscf(i)+
					  (x(i)-x(i-1))*Iu )/xint;
		}
		else{
			yint=y(i-1);
		}
		return yint;
	}

	// Extrapolation to the future
	if (i >= nhi+1){
		yint = ( y(nhi)*x(nhi)+ (xint-x(nhi))*FMCavef(nhi) )/xint;
		return yint;
	}
	return 0;   // should not reach here
}

/***********************************************************/
/***********************************************************/

static void ForwardMonotoneConvexLoop(
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& x, 
    const FAArray1Ref<double>& FMCdiscf,
    const FAArray1Ref<double>& FMCavef, 
    const FAArray1Ref<double>& xint,
    FAArray1Ref<double>& yint,
    int nlow,
    int nhi,
    int ilow,
    int ihi,
    double uniformdx
    )
{
    // Forward monotone convex spline interpolation -- loop version
  	// x:          abscissa (assuming ascending)
 	// y:          ordinate
    // uniformdx:  grid spacing (if uniform), otherwise 0.0
    // xint:       array of values at which to interpolate
    // yint:       array of interpolated values
    // nlow:       lower abscissa index
    // nhi:        upper abscissa index
 	// ilow:       lower index of xint
 	// ihi:        upper index of xint
 
	for (int k=ilow; k<=ihi; k++){
        yint(k) = ForwardMonotoneConvex(y,x,FMCdiscf,FMCavef,xint(k),nlow,nhi,uniformdx);
	}
	return;
}

/***********************************************************/
/***********************************************************/

static int ForwardMonotoneConvexOld(
	const FAArray1Ref<double>& y,
	const FAArray1Ref<double>& x, 
	const FAArray1Ref<double>& xint,
	FAArray1Ref<double>& yint,
	int nlow,
	int nhi,
	int ilow,
	int ihi,
	double uniformdx
	)
{
    //  Forward monotone convex spline interpolation
 	
 	// x:          abscissa (assuming ascending)
 	// y:          ordinate
    // uniformdx:  grid spacing (if uniform), otherwise 0.0
    // xint:       array of values at which to interpolate
    // yint:       array of interpolated values
    // nlow:       lower abscissa index
    // nhi:        upper abscissa index
 	// ilow:       lower index of xint
 	// ihi:        upper index of xint
 
	int i, k;
	double f_av_0, ggi,ggi1,u,Iu;
	double xf, eta, Acoeff;
	double u2, u3, eta2, eta2m, eta3;
    char ErrorMsg[] = "ForwardMonotoneConvex: Error - The interval between interpolation points is 0.";

	// check if ascending
	int ascend=(x(nhi)>=x(nlow));
	if (!ascend) return 1;

	// allocating memory for spline data
	FAArray1<double> f_disc(nhi-nlow+1); 
	FAArray1<double> f_av(nhi-nlow+1); 

	// Calculating the discrete forward rates
	f_disc(nlow) = y(nlow);
	if (uniformdx>0.) {	// uniform grid
		for (i = nlow+1; i <= nhi; i++){
			f_disc(i) = ( y(i) * x(i) - y(i-1) * x(i-1) ) / uniformdx;
		}
	}
	else {				// nonuniform grid
		for (i = nlow+1; i <= nhi; i++){
            if ((x(i)-x(i-1))>0.) {
				f_disc(i) = ( y(i) * x(i) - y(i-1) * x(i-1) ) / (x(i) - x(i-1));
			}
			else{
                throw new FAErrorException(ErrorMsg, InterpolationDeltaError);
            }
		}
	}

	// Calculate the average forward rates
	xf=( x(nlow+1)-x(nlow) )/x(nlow+1);
	f_av(nlow)=(1.0-xf)*f_disc(nlow+1)+xf*f_disc(nlow);

	if (uniformdx>0.) {	// uniform grid
	    for (i = nlow+1;i <= nhi-1; i++) 
			f_av(i)=0.5*(f_disc(i+1)+f_disc(i));
	}
	else{				// nonuniform grid
	    for (i = nlow+1;i <= nhi-1; i++){
			xf=( x(i+1)-x(i) )/( x(i+1)-x(i-1) );
			f_av(i)=(1.0-xf)*f_disc(i+1)+xf*f_disc(i);
		}
	}
	f_av_0=f_disc(nlow)-0.5*( f_av(nlow)-f_disc(nlow) );
	f_av(nhi)=f_disc(nhi)-0.5*( f_av(nhi-1)-f_disc(nhi) );

	for (k = ilow; k <= ihi; k++){
		// Calculate segment index
		i=0;	// must be initialized
		Locate(xint(k), x, uniformdx, nlow, nhi, ascend, &i);
		// out of range left = nlow-1
		// out of range right = nhi-1
		// inside nlow,nlow+1, ... , nhi-1
		i=i+1; // convenience convention
		// out of range left = nlow
		// out of range right = nhi+1
		// inside nlow,nlow+2, ... , nhi

		// Extrapolation around zero
		if (i<=nlow){
			
			u=xint(k) / x(nlow);
			u2=u*u;
			u3=u*u*u;

			ggi=f_av(nlow)-f_disc(nlow);
			ggi1=f_av_0-f_disc(nlow);
		    
			// Basic interpolator
			Iu=ggi1*(u-2*u2+u3)+ggi*(-u2+u3);

			if (xint(k)>0.0) 
				yint(k)=( xint(k)*f_disc(i)+x(nlow)*Iu )/xint(k);
			else
				yint(k)=f_av_0;
			
		}
				
		if (i>=nlow+1 && i <= nhi){	//within data range
            if ((x(i)-x(i-1))>0.) {
				f_disc(i) = ( y(i) * x(i) - y(i-1) * x(i-1) ) / (x(i) - x(i-1));
			}
			else{
                throw new FAErrorException(ErrorMsg, InterpolationDeltaError);
            }
			u=(xint(k) - x(i-1)) / (x(i) - x(i-1));
			u2=u*u;
			u3=u*u*u;

			ggi=f_av(i)-f_disc(i);
			ggi1=f_av(i-1)-f_disc(i);
		    
			// Basic interpolator
			Iu=ggi1*(u-2*u2+u3)+ggi*(-u2+u3);

			// Convex monotonic adjustment 
			if ( (ggi1<0 && ggi>-2.0*ggi1) || (ggi1>0 && ggi<-2.0*ggi1) ){
				eta=(ggi+2.0*ggi1)/(ggi-ggi1);
				eta2=eta*eta;
				eta3=eta2*eta;
				eta2m=(1-eta)*(1-eta);
				
				if (u<=eta && u>=0){
					Iu=ggi1*u;    
				}
				if (u>eta && u<=1.0){
					Iu = ggi1*eta+ggi1*u+
					 (ggi-ggi1)/eta2m*(u3/3.0-eta*u2+eta2*u)-
					(ggi1*eta+(ggi-ggi1)/eta2m*eta3/3.0);
				}
			}
		
			if ( (ggi1>0 && ggi<0 && ggi>-0.5*ggi1) || 
				( ggi1<0 && ggi>0 && ggi<-0.5*ggi1) ){
				eta=3*ggi/(ggi-ggi1);
				eta2=eta*eta;
				eta3=eta2*eta;
				
				if (u<eta && u>0){
					Iu=ggi*u+(ggi1-ggi)/eta2*(eta2*u-eta*u2+u3/3.0);
				}
				if (u>=eta && u<1){
					Iu=ggi*eta+(ggi1-ggi)/eta2*eta3/3.0+ggi*(u-eta);
				}
			}

			if ( (ggi1>=0 && ggi>=0 ) || (ggi1<=0 && ggi<=0) ){
				eta=ggi/(ggi+ggi1);
				eta2=eta*eta;
				eta2m=(1-eta)*(1-eta);
				eta3=eta2*eta;
				Acoeff=-ggi1*ggi/(ggi1+ggi);

				if (u<eta && u>0) {
					Iu=Acoeff*u+(ggi1-Acoeff)/eta2*(eta2*u-eta*u2+u3/3.0);
				}
				if (u==eta){
					Iu=Acoeff*eta+(ggi1-Acoeff)/eta2*eta3/3.0;
				}
       			if (u>eta && u<1){
					Iu=Acoeff*eta+(ggi1-Acoeff)/eta2*eta3/3.0+
					Acoeff*u+(ggi-Acoeff)/eta2m*(u3/3.0-eta*u2+eta2*u)-
					(Acoeff*eta+(ggi-Acoeff)/eta2m*eta3/3.0 );
				}
			}

			yint(k)=( y(i-1)*x(i-1)+ (xint(k)-x(i-1))*f_disc(i)+
					  (x(i)-x(i-1))*Iu )/xint(k);
		}

		// Extrapolation to the future
		if (i >= nhi+1){
			yint(k)=( y(nhi)*x(nhi)+ (xint(k)-x(nhi))*f_av(nhi) )/xint(k);
		}

	}
	return 0;

}

/*****************************************************************************/
/**************** 2D interpolation *******************************************/
/*****************************************************************************/

static double BiStairStep(
    const FAArray2Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    double xint,
    double yint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    double uniformdx,
    double uniformdy,
    int bias,
    double eps
    )
{
    // piecewise constant interpolation in 2D
    int locx,locy,ix,iy,ascendx,ascendy;
    
    // u:			ordinate
    // x:			x abscissa
    // y:			y abscissa
    // xint, yint:  x,y  values to interpolate at
	// nxlow, nxhi: lower and upper x abscissa index
	// nylow, nyhi: lower and upper y abscissa index
    // uniformdx:   =0 if dx is nonuniform, else is the uniform dx
    //				y variables similar
    // bias:		=-1(+1) for left (right) bias
	// eps:			

    // ascendx: True if x array (assumed monotonic) ascends, else False
    // ttx:     fraction of interval
    // ix:      adjusted interpolation index
    // locx:    raw interpolation index
    ascendx = x(nxhi)>=x(nxlow);
	locx = nxlow;
	FindStairStepIndex(x,uniformdx,xint,nxlow,nxhi,ascendx,bias,eps,&locx,&ix);

    ascendy = y(nyhi)>=y(nylow);
	locy = nylow;
	FindStairStepIndex(y,uniformdy,yint,nylow,nyhi,ascendy,bias,eps,&locy,&iy);

	return ((ix==-999)||(iy==-999) ? 0. : u(ix,iy));
}

/***********************************************************/
/***********************************************************/

static void BiStairStepLoop(
//  x - loop
    const FAArray2Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& xint,
    double yint,
    FAArray1Ref<double>& uint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int ilow,
    int ihi,
    double uniformdx,
    double uniformdy,
    int bias,
    double eps
    )
{
    // BiStairStep interpolation, looping over one direction
    int locx,locy,ix,iy,ascendx,ascendy,i;
    
    locx = nxlow;
    ascendx = x(nxhi)>=x(nxlow);
    locy = nylow;
    ascendy = y(nyhi)>=y(nylow);

    // find y interpolation interval
    FindStairStepIndex(y,uniformdy,yint,nylow,nyhi,ascendy,bias,eps,&locy,&iy);
    // find x interpolation interval
    for (i=ilow; i<=ihi; i++) {
        FindStairStepIndex(x,uniformdx,xint(i),nxlow,nxhi,ascendx,bias,eps,&locx,&ix);
        uint(i) = ((ix==-999)||(iy==-999) ? 0. : u(ix,iy));
    }
}

/***********************************************************/
/***********************************************************/

static void BiStairStepLoop(
//  y - loop
	const FAArray2Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
	double xint,
    const FAArray1Ref<double>& yint,
    FAArray1Ref<double>& uint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int ilow,
    int ihi,
    double uniformdx,
    double uniformdy,
    int bias,
    double eps
    )
{
    // BiStairStep interpolation, looping over one direction
    int locx,locy,ix,iy,ascendx,ascendy,i;
    
    locx = nxlow;
    ascendx = x(nxhi)>=x(nxlow);
    locy = nylow;
    ascendy = y(nyhi)>=y(nylow);

    // find x interpolation interval
    FindStairStepIndex(x,uniformdx,xint,nxlow,nxhi,ascendx,bias,eps,&locx,&ix);
    // find y interpolation interval
    for (i=ilow; i<=ihi; i++) {
        FindStairStepIndex(y,uniformdy,yint(i),nylow,nyhi,ascendy,bias,eps,&locy,&iy);
        uint(i) = ((ix==-999)||(iy==-999) ? 0. : u(ix,iy));
    }
}

/***********************************************************/
/***********************************************************/

static double Bilinear(
    const FAArray2Ref<double>& z,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    double xint,
    double yint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    double uniformdx,
    double uniformdy,
    int extrap
    )
{
    // bilinear interpolation at a single point
    int locx,locy,ix,iy,ascendx,ascendy;
    double ttx,tty,ttcx,ttcy;
    char ErrorMsgx[] = "Bilinear: Error - The interval between x interpolation points is 0.";
    char ErrorMsgy[] = "Bilinear: Error - The interval between y interpolation points is 0.";
    
    // x:       x abscissa
    // y:       y abscissa
    // z:       ordinate
    // nxlow:   lower x abscissa index
    // nxhi:    upper x abscissa index
    // xint:    x value to interpolate at
    // ttx:     fraction of interval
    // ascendx: True if x array (assumed monotonic) ascends, else False
    // ix:      adjusted interpolation index
    // locx:    raw interpolation index
    // uniformdx =0 if dx is nonuniform, else is the uniform dx
    //          y variables similar
    // extrap: =1(0): do(not) linearly extrapolate out of range xint,yint

    locx = nxlow;
    ascendx = x(nxhi)>=x(nxlow);
    ComputeIntervalFraction(x,uniformdx,xint,nxlow,nxhi,ascendx,extrap,&locx,&ix,&ttx,ErrorMsgx);
    ttcx = 1.-ttx;

    // find y interpolation interval
    locy = nylow;
    ascendy = y(nyhi)>=y(nylow);
    ComputeIntervalFraction(y,uniformdy,yint,nylow,nyhi,ascendy,extrap,&locy,&iy,&tty,ErrorMsgy);
    ttcy = 1.-tty;

    // degenerate cases
    if (nxlow==nxhi) {
		if (nylow==nyhi) return z(nxlow,nylow);
        return ttcy*z(nxlow,iy) + tty*z(nxlow,iy+1);
    }
	if (nylow==nyhi) return ttcx*z(ix,nylow) + ttx*z(ix+1,nylow);
    
    return ttcx*(ttcy*z(ix,iy) + tty*z(ix,iy+1)) + ttx*(ttcy*z(ix+1,iy) + tty*z(ix+1,iy+1));
}

/***********************************************************/
/***********************************************************/

static void BilinearLoop(
//  x - loop
	const FAArray2Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& xint,
    double yint,
    FAArray1Ref<double>& uint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int ilow,
    int ihi,
    double uniformdx,
    double uniformdy,
    int extrap
    )
{
    // bilinear interpolation, looping over one direction
    int locx,locy,ix,iy,ascendx,ascendy,i;
    double ttx,tty,ttcx,ttcy;
    char ErrorMsgx[] = "BilinearLoop: Error - The interval between x interpolation points is 0.";
    char ErrorMsgy[] = "BilinearLoop: Error - The interval between y interpolation points is 0.";
    
    // single data point
    if (nxlow==nxhi && nylow==nyhi) {
        for (i=ilow; i<=ihi; i++) {
            uint(i) = u(nxlow,nylow);
        }
    }

    locy = nylow;
    ascendy = y(nyhi)>=y(nylow);
    // find y interpolation interval
    ComputeIntervalFraction(y,uniformdy,yint,nylow,nyhi,ascendy,extrap,&locy,&iy,&tty,ErrorMsgy);
    ttcy = 1.-tty;
    // find x interpolation interval
    locx = nxlow;
    ascendx = x(nxhi)>=x(nxlow);
    for (i=ilow; i<=ihi; i++) {
        ComputeIntervalFraction(x,uniformdx,xint(i),nxlow,nxhi,ascendx,extrap,&locx,&ix,&ttx,ErrorMsgx);
        ttcx = 1.-ttx;
        uint(i) = ttcx*(ttcy*u(ix,iy) + tty*u(ix,iy+1)) + ttx*(ttcy*u(ix+1,iy) + tty*u(ix+1,iy+1));
    }
}

/***********************************************************/
/***********************************************************/

static void BilinearLoop(
//	y - loop
    const FAArray2Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    double xint,
    const FAArray1Ref<double>& yint,
    FAArray1Ref<double>& uint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int ilow,
    int ihi,
    double uniformdx,
    double uniformdy,
    int extrap
    )
{
    // bilinear interpolation, looping over one direction
    int locx,locy,ix,iy,ascendx,ascendy,i;
    double ttx,tty,ttcx,ttcy;
    char ErrorMsgx[] = "BilinearLoop: Error - The interval between x interpolation points is 0.";
    char ErrorMsgy[] = "BilinearLoop: Error - The interval between y interpolation points is 0.";
    
    // single data point
    if (nxlow==nxhi && nylow==nyhi) {
        for (i=ilow; i<=ihi; i++) {
            uint(i) = u(nxlow,nylow);
        }
    }

    locx = nxlow;
    ascendx = x(nxhi)>=x(nxlow);
    locy = nylow;
    ascendy = y(nyhi)>=y(nylow);

    // find x interpolation interval
    ComputeIntervalFraction(x,uniformdx,xint,nxlow,nxhi,ascendx,extrap,&locx,&ix,&ttx,ErrorMsgx);
    ttcx = 1.-ttx;
    // find y interpolation interval
    for (i=ilow; i<=ihi; i++) {
        ComputeIntervalFraction(y,uniformdy,yint(i),nylow,nyhi,ascendy,extrap,&locy,&iy,&tty,ErrorMsgy);
        ttcy = 1.-tty;
        uint(i) = ttcx*(ttcy*u(ix,iy) + tty*u(ix,iy+1)) + ttx*(ttcy*u(ix+1,iy) + tty*u(ix+1,iy+1));
    }
}

/***********************************************************/
/***********************************************************/

static double BiCubicCore(
    const FAArray2Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int indexx,
    int indexy,
    double ttx,
	double tty,
	FAArray1Ref<double>& ux
    )
{
	double ans;
	double fpp,fp0,fpm,fpp0,fpp1;

    double ttcx,Deltax,Deltamx,Deltapx;
    char ErrorMsgx[] = "Cubic: Error - The interval between interpolation points is 0.";

	// precalculation in Y direction
	double ttcy,Deltay,Deltamy,Deltapy;
	char ErrorMsgy[] = "Cubic: Error - The interval between interpolation points is 0.";

	int ilow, ihi;

    if (indexx<=nxlow || (nxhi-nxlow)<3 || indexx>=nxhi-1){
		ilow=indexx; ihi=indexx+1;
	}
	else {
		ilow=indexx-1; ihi=indexx+2;
	}

	if (indexy>nylow && (nyhi-nylow)>=3 && indexy<nyhi-1) {
		ttcy = 1. - tty;
		// cubic correction
		Deltamy = y(indexy) - y(indexy-1);
		Deltay  = y(indexy+1) - y(indexy);
		Deltapy = y(indexy+2) - y(indexy+1);
		if (Deltamy==0. || Deltay==0. || Deltapy==0) {
			throw new FAErrorException(ErrorMsgy,InterpolationDeltaError);
		}
	}

	for (int i=ilow; i<=ihi; i++){
		// linear piece
		ux(i) = u(i,indexy) + tty*(u(i,indexy+1) - u(i,indexy));
		if (indexy<=nylow || (nyhi-nylow)<3 || indexy>=nyhi-1) continue;

		fpm = (u(i,indexy) - u(i,indexy-1))/Deltamy;
		fp0 = (u(i,indexy+1) - u(i,indexy))/Deltay;
		fpp = (u(i,indexy+2) - u(i,indexy+1))/Deltapy;
		fpp0 =  2.0*(fp0 - fpm) / (Deltay + Deltamy);
		fpp1 =  2.0*(fpp - fp0) / (Deltapy + Deltay);
		ux(i) += (ttcy*(ttcy*ttcy-1.)*fpp0 + tty*(tty*tty-1.)*fpp1)*Deltay*Deltay/6.;
	}

    // linear piece
    ans = ux(indexx) + ttx*(ux(indexx+1) - ux(indexx));
    if (indexx<=nxlow || (nxhi-nxlow)<3 || indexx>=nxhi-1) return ans;

    ttcx = 1. - ttx;
    // cubic correction
    Deltamx = x(indexx) - x(indexx-1);
    Deltax  = x(indexx+1) - x(indexx);
    Deltapx = x(indexx+2) - x(indexx+1);
    if (Deltamx==0. || Deltax==0. || Deltapx==0) {
        throw new FAErrorException(ErrorMsgx,InterpolationDeltaError);
    }

    fpm = (ux(indexx) - ux(indexx-1))/Deltamx;
    fp0 = (ux(indexx+1) - ux(indexx))/Deltax;
    fpp = (ux(indexx+2) - ux(indexx+1))/Deltapx;
    fpp0 =  2.0*(fp0 - fpm) / (Deltax + Deltamx);
    fpp1 =  2.0*(fpp - fp0) / (Deltapx + Deltax);
    ans += (ttcx*(ttcx*ttcx-1.)*fpp0 + ttx*(ttx*ttx-1.)*fpp1)*Deltax*Deltax/6.;
    return ans;
}

/***********************************************************/
/***********************************************************/

static double BiCubic(
    const FAArray2Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    double xint,
    double yint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    double uniformdx,
    double uniformdy,
    int extrap
    )
{
	double ans;

    // single data point
    if (nxlow==nxhi && nylow==nyhi) {
        return u(nxlow,nylow);
    }
	
	FAArray1<double> ux(x.size0());

	// precalculation in Y direction
    int indexx,locx,ascendx;
    double ttx;
    char ErrorMsgx[] = "Cubic: Error - The interval between interpolation points is 0.";
    // locate point just to the left and compute interval fraction
    locx = nxlow;
    ascendx = x(nxhi)>=x(nxlow);
    ComputeIntervalFraction(x,uniformdx,xint,nxlow,nxhi,ascendx,extrap,&locx,&indexx,&ttx,ErrorMsgx);

	// precalculation in Y direction
	int indexy,locy,ascendy;
	double tty;
	char ErrorMsgy[] = "Cubic: Error - The interval between interpolation points is 0.";
    // locate point just to the left and compute interval fraction
	locy = nylow;
	ascendy = y(nyhi)>=y(nylow);
	ComputeIntervalFraction(y,uniformdy,yint,nylow,nyhi,ascendy,extrap,&locy,&indexy,&tty,ErrorMsgy);



	ans = BiCubicCore(u,x,y,nxlow,nxhi,nylow,nyhi,indexx,indexy,ttx,tty,ux);
    return ans;
}

/***********************************************************/
/***********************************************************/

static void BiCubicLoop(
//  x - loop
    const FAArray2Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    FAArray1Ref<double>& xint,
    double yint,
    FAArray1Ref<double>& uint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
	int ilow,
	int ihi,
    double uniformdx,
    double uniformdy,
    int extrap
    )
{
    // single data point
    if (nxlow==nxhi && nylow==nyhi) {
        for (int i=ilow; i<=ihi; i++) {
            uint(i) = u(nxlow,nylow);
        }
    }
	
	FAArray1<double> ux(x.size0());

	// precalculation in Y direction
	int indexy,locy,ascendy;
	double tty;
	char ErrorMsgy[] = "Cubic: Error - The interval between interpolation points is 0.";
    // locate point just to the left and compute interval fraction
	locy = nylow;
	ascendy = y(nyhi)>=y(nylow);
	ComputeIntervalFraction(y,uniformdy,yint,nylow,nyhi,ascendy,extrap,&locy,&indexy,&tty,ErrorMsgy);

	// precalculation in X direction
    int indexx,locx,ascendx;
    double ttx;
    char ErrorMsgx[] = "Cubic: Error - The interval between interpolation points is 0.";
    // locate point just to the left and compute interval fraction
    locx = nxlow;
    ascendx = x(nxhi)>=x(nxlow);
	for (int i=ilow;i<=ihi;i++){
		ComputeIntervalFraction(x,uniformdx,xint(i),nxlow,nxhi,ascendx,extrap,&locx,&indexx,&ttx,ErrorMsgx);
		uint(i)=BiCubicCore(u,x,y,nxlow,nxhi,nylow,nyhi,indexx,indexy,ttx,tty,ux);
	}
}

/***********************************************************/
/***********************************************************/

static void BiCubicLoop(
//  y - loop
    const FAArray2Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    double xint,
    FAArray1Ref<double>& yint,
    FAArray1Ref<double>& uint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
	int ilow,
	int ihi,
    double uniformdx,
    double uniformdy,
    int extrap
    )
{
    // single data point
    if (nxlow==nxhi && nylow==nyhi) {
        for (int i=ilow; i<=ihi; i++) {
            uint(i) = u(nxlow,nylow);
        }
    }
	
	FAArray1<double> ux(x.size0());

	// precalculation in X direction
    int indexx,locx,ascendx;
    double ttx;
    char ErrorMsgx[] = "Cubic: Error - The interval between interpolation points is 0.";
    // locate point just to the left and compute interval fraction
    locx = nxlow;
    ascendx = x(nxhi)>=x(nxlow);
	ComputeIntervalFraction(x,uniformdx,xint,nxlow,nxhi,ascendx,extrap,&locx,&indexx,&ttx,ErrorMsgx);

	// precalculation in Y direction
	int indexy,locy,ascendy;
	double tty;
	char ErrorMsgy[] = "Cubic: Error - The interval between interpolation points is 0.";
    // locate point just to the left and compute interval fraction
	locy = nylow;
	ascendy = y(nyhi)>=y(nylow);

	for (int i=ilow;i<=ihi;i++){
		ComputeIntervalFraction(y,uniformdy,yint(i),nylow,nyhi,ascendy,extrap,&locy,&indexy,&tty,ErrorMsgy);
		uint(i)=BiCubicCore(u,x,y,nxlow,nxhi,nylow,nyhi,indexx,indexy,ttx,tty,ux);
	}
}

/***********************************************************/
/***********************************************************/

static void BiCubicSplineCoefficients(
    const FAArray2Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    double uniformdx,
    double uniformdy,
    FAArray2Ref<double>& fpp,
    FAArray1Ref<double>& TriTx,
    FAArray1Ref<double>& TriT2x,
    FAArray1Ref<double>& TriTy,
    FAArray1Ref<double>& TriT2y,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int dir
    )
{
    int i,j;
	if (dir==1) {
		// Auxiliary arrays for slicing
		FAArray1<double> uy(y.size0());
		FAArray1<double> fppy(y.size0());
		for (i=nxlow; i<=nxhi; i++) {
			for (j=nylow;j<=nyhi;j++)
				uy(j)=u(i,j);			//slicing
			
			SplineCoefficients(uy,y,uniformdy,fppy,TriTy,TriT2y,nylow,nyhi);

			for (j=nylow;j<=nyhi;j++)
				fpp(i,j)=fppy(j);		//stuffing
			
		}
	}
	else if (dir==2) {
		// Auxiliary arrays for slicing
	    FAArray1<double> ux(x.size0());
		FAArray1<double> fppx(x.size0());
		for (j=nylow; j<=nyhi; j++) {
			for (i=nxlow;i<=nxhi;i++)
				ux(i)=u(i,j);			//slicing
			
			SplineCoefficients(ux,x,uniformdx,fppx,TriTx,TriT2x,nxlow,nxhi);

			for (i=nxlow;i<=nxhi;i++)
				fpp(i,j)=fppx(i);		//stuffing
		}
	}
    return;
}

/***********************************************************/
/***********************************************************/

static double BiCubicSpline(
    const FAArray2Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
	double xint,
    double yint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    double uniformdx,
    double uniformdy,
    int extrap,
    int dir,
    FAArray2Ref<double>& fpp,
	FAArray1Ref<double>& TriTx,
    FAArray1Ref<double>& TriT2x,
	FAArray1Ref<double>& TriTy,
    FAArray1Ref<double>& TriT2y,
    FAArray1Ref<double>& ux,
    FAArray1Ref<double>& fppx,
    FAArray1Ref<double>& uy,
    FAArray1Ref<double>& fppy 
    )
{
    // bicubic spline interpolation at a single point

    int i,j;
	double ans;
	// single data point
    if (nxlow==nxhi && nylow==nyhi) {
        return u(nxlow,nylow);
    }

    if (dir==1) {

	   // locate point just to the left and compute interval fraction
	    int locy = nylow;
		int ascendy = y(nyhi)>=y(nylow);
		int indexy = 0;
		char ErrorMsgy[] = "CubicSpline: Error - The interval between interpolation points is 0.";
		double tty, ttcy, Deltay;
		ComputeIntervalFraction(y,uniformdy,yint,nylow,nyhi,ascendy,extrap,&locy,&indexy,&tty,ErrorMsgy);
		Deltay = y(indexy + 1) - y(indexy);
		ttcy = 1. - tty;
		for (i=nxlow; i<=nxhi; i++) {
			// linear piece
			ux(i) = u(i,indexy) + tty*(u(i,indexy+1) - u(i,indexy));
			// cubic spline correction
		    if (tty>=0. && (nyhi-nylow)>=2 && tty<=1.) {
				ux(i)+= (ttcy*(ttcy*ttcy - 1.)*fpp(i,indexy) + tty*(tty*tty - 1.)*fpp(i,indexy+1))*Deltay*Deltay/6.;
			}
		}	
	    		
		// interpolate in x
		SplineCoefficients(ux,x,uniformdx,fppx,TriTx,TriT2x,nxlow,nxhi);
		ans = CubicSpline(ux,x,fppx,xint,nxlow,nxhi,uniformdx,extrap);
	}
	
    else if (dir==2) {
		// locate point just to the left and compute interval fraction
	    int locx = nxlow;
		int ascendx = x(nxhi)>=x(nxlow);
		int indexx = 0;
		char ErrorMsgx[] = "CubicSpline: Error - The interval between interpolation points is 0.";
		double ttx, ttcx, Deltax;
		ComputeIntervalFraction(x,uniformdx,xint,nxlow,nxhi,ascendx,extrap,&locx,&indexx,&ttx,ErrorMsgx);
		Deltax = x(indexx + 1) - x(indexx);
		ttcx = 1. - ttx;
		for (j=nylow; j<=nyhi; j++) {
			// linear piece
			uy(j) = u(indexx,j) + ttx*(u(indexx+1,j) - u(indexx,j));
			// cubic spline correction
		    if (ttx>=0. && (nxhi-nxlow)>=2 && ttx<=1.) {
				uy(j)+= (ttcx*(ttcx*ttcx - 1.)*fpp(indexx,j) + ttx*(ttx*ttx - 1.)*fpp(indexx+1,j))*Deltax*Deltax/6.;
			}
		}		    

	    // interpolate in y
		SplineCoefficients(uy,y,uniformdy,fppy,TriTy,TriT2y,nylow,nyhi);
		ans = CubicSpline(uy,y,fppy,yint,nylow,nyhi,uniformdy,extrap);
	}
	return ans;
}

/***********************************************************/
/***********************************************************/

static void BiCubicSplineLoop(
//  x - loop
    const FAArray2Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
	FAArray1Ref<double>& xint,
    double yint,
    FAArray1Ref<double>& uint,
	int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int ilow,
    int ihi,
    double uniformdx,
    double uniformdy,
    int extrap,
    FAArray2Ref<double>& fpp,
	FAArray1Ref<double>& TriTx,
    FAArray1Ref<double>& TriT2x,
	FAArray1Ref<double>& TriTy,
    FAArray1Ref<double>& TriT2y,
    FAArray1Ref<double>& ux,
    FAArray1Ref<double>& fppx,
    FAArray1Ref<double>& uy,
    FAArray1Ref<double>& fppy 
    )
{
    int i;
   
    // single data point
    if (nxlow==nxhi && nylow==nyhi) {
        for (i=ilow; i<=ihi; i++) {
            uint(i) = u(nxlow,nylow);
        }
    }

   // locate point just to the left and compute interval fraction
    int locy = nylow;
	int ascendy = y(nyhi)>=y(nylow);
	int indexy = 0;
	char ErrorMsgy[] = "CubicSpline: Error - The interval between interpolation points is 0.";
	double tty, ttcy, Deltay;
	ComputeIntervalFraction(y,uniformdy,yint,nylow,nyhi,ascendy,extrap,&locy,&indexy,&tty,ErrorMsgy);
	Deltay = y(indexy + 1) - y(indexy);
	ttcy = 1. - tty;
	for (i=nxlow; i<=nxhi; i++) {
		// linear piece
		ux(i) = u(i,indexy) + tty*(u(i,indexy+1) - u(i,indexy));
		// cubic spline correction
	    if (tty>=0. && (nyhi-nylow)>=2 && tty<=1.) {
			ux(i)+= (ttcy*(ttcy*ttcy - 1.)*fpp(i,indexy) + tty*(tty*tty - 1.)*fpp(i,indexy+1))*Deltay*Deltay/6.;
		}
	}	
    
//  interpolate in x
	SplineCoefficients(ux,x,uniformdx,fppx,TriTx,TriT2x,nxlow,nxhi);
	CubicSplineLoop(ux,x,fppx,xint,uint,nxlow,nxhi,ilow,ihi,uniformdx,extrap);
	return;
}

/***********************************************************/
/***********************************************************/

static void BiCubicSplineLoop(
//  y - loop
    const FAArray2Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
	double xint,
	FAArray1Ref<double>& yint,
    FAArray1Ref<double>& uint,
	int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int ilow,
    int ihi,
    double uniformdx,
    double uniformdy,
    int extrap,
    FAArray2Ref<double>& fpp,
	FAArray1Ref<double>& TriTx,
    FAArray1Ref<double>& TriT2x,
	FAArray1Ref<double>& TriTy,
    FAArray1Ref<double>& TriT2y,
    FAArray1Ref<double>& ux,
    FAArray1Ref<double>& fppx,
    FAArray1Ref<double>& uy,
    FAArray1Ref<double>& fppy 
    )
{
    int i,j;
    
    // single data point
    if (nxlow==nxhi && nylow==nyhi) {
        for (i=ilow; i<=ihi; i++) {
            uint(i) = u(nxlow,nylow);
        }
    }

	// locate point just to the left and compute interval fraction
    int locx = nxlow;
	int ascendx = x(nxhi)>=x(nxlow);
	int indexx = 0;
	char ErrorMsgx[] = "CubicSpline: Error - The interval between interpolation points is 0.";
	double ttx, ttcx, Deltax;
	ComputeIntervalFraction(x,uniformdx,xint,nxlow,nxhi,ascendx,extrap,&locx,&indexx,&ttx,ErrorMsgx);
	Deltax = x(indexx + 1) - x(indexx);
	ttcx = 1. - ttx;
	for (j=nylow; j<=nyhi; j++) {
		// linear piece
		uy(j) = u(indexx,j) + ttx*(u(indexx+1,j) - u(indexx,j));
		// cubic spline correction
	    if (ttx>=0. && (nxhi-nxlow)>=2 && ttx<=1.) {
			uy(j)+= (ttcx*(ttcx*ttcx - 1.)*fpp(indexx,j) + ttx*(ttx*ttx - 1.)*fpp(indexx+1,j))*Deltax*Deltax/6.;
		}
	}		    
		
	// interpolate in y
	SplineCoefficients(uy,y,uniformdy,fppy,TriTy,TriT2y,nylow,nyhi);
	CubicSplineLoop(uy,y,fppy,yint,uint,nylow,nyhi,ilow,ihi,uniformdy,extrap);
	return;
}

/*****************************************************************************/
/**************** 3D interpolation *******************************************/
/*****************************************************************************/

static double TriStairStep(
    const FAArray3Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
    double xint,
    double yint,
	double zint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    int bias,
    double eps
    )
{
    // piecewise constant interpolation in 3D
    
    // u:       ordinate
    // x:       x abscissa
	// ........
    // xint:    x value to interpolate at
    // ........
    // nxlow:   lower x abscissa index
    // nxhi:    upper x abscissa index
	// ........
    // uniformdx =0 if dx is nonuniform, else is the uniform dx
	// ........
    // bias:    =-1(+1) for left (right) bias
	// eps:		machine epsilon

    int locx,locy,locz,ix,iy,iz, ascendx,ascendy, ascendz;

    ascendx = x(nxhi)>=x(nxlow);
	locx = nxlow;
	FindStairStepIndex(x,uniformdx,xint,nxlow,nxhi,ascendx,bias,eps,&locx,&ix);

    ascendy = y(nyhi)>=y(nylow);
	locy = nylow;
	FindStairStepIndex(y,uniformdy,yint,nylow,nyhi,ascendy,bias,eps,&locy,&iy);

    ascendz = z(nzhi)>=z(nzlow);
	locz = nzlow;
	FindStairStepIndex(z,uniformdz,zint,nzlow,nzhi,ascendz,bias,eps,&locz,&iz);

	return ((ix==-999)||(iy==-999)||(iz==-999) ? 0. : u(ix,iy,iz));
}

/***********************************************************/
/***********************************************************/

static void TriStairStepLoop(
//  x - loop
    const FAArray3Ref<double>& vf,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
    FAArray1Ref<double>& xint,
    double yint,
	double zint,
    FAArray1Ref<double>& uint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
	int ilow,
	int ihi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    int bias,
    double eps
    )
{
    // piecewise constant interpolation in 3D
	// u:       ordinate
    // x:       x abscissa
	// ........
    // xint:    x value to interpolate at
    // ........
	// ilow:	lower interpolation index
	// ihi:		upper interpolation index
	// uint:	interpolated values
    // nxlow:   lower x abscissa index
    // nxhi:    upper x abscissa index
	// ........
    // uniformdx =0 if dx is nonuniform, else is the uniform dx
	// ........
    // bias:    =-1(+1) for left (right) bias
	// eps:		machine epsilon

	int i;
    int locx,locy,locz,ix,iy,iz, ascendx,ascendy, ascendz;
    
    ascendx = x(nxhi)>=x(nxlow);
	locx = nxlow;

    ascendy = y(nyhi)>=y(nylow);
	locy = nylow;
	FindStairStepIndex(y,uniformdy,yint,nylow,nyhi,ascendy,bias,eps,&locy,&iy);

    ascendz = z(nzhi)>=z(nzlow);
	locz = nzlow;
	FindStairStepIndex(z,uniformdz,zint,nzlow,nzhi,ascendz,bias,eps,&locz,&iz);

	for (i=ilow;i<=ihi;i++){
		FindStairStepIndex(x,uniformdx,xint(i),nxlow,nxhi,ascendx,bias,eps,&locx,&ix);
		uint(i) = ((ix==-999)||(iy==-999)||(iz==-999) ? 0. : vf(ix,iy,iz));
	}
	return;
}

/***********************************************************/
/***********************************************************/

static void TriStairStepLoop(
//  y - loop
    const FAArray3Ref<double>& vf,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
    double xint,
    FAArray1Ref<double>& yint,
	double zint,
    FAArray1Ref<double>& uint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
	int ilow,
	int ihi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    int bias,
    double eps
    )
{
    // piecewise constant interpolation in 3D
	int i;
    int locx,locy,locz,ix,iy,iz, ascendx,ascendy, ascendz;
    
    ascendx = x(nxhi)>=x(nxlow);
	locx = nxlow;
	FindStairStepIndex(x,uniformdx,xint,nxlow,nxhi,ascendx,bias,eps,&locx,&ix);

    ascendy = y(nyhi)>=y(nylow);
	locy = nylow;

    ascendz = z(nzhi)>=z(nzlow);
	locz = nzlow;
	FindStairStepIndex(z,uniformdz,zint,nzlow,nzhi,ascendz,bias,eps,&locz,&iz);

	for (i=ilow;i<=ihi;i++){
		FindStairStepIndex(y,uniformdy,yint(i),nylow,nyhi,ascendy,bias,eps,&locy,&iy);
		uint(i) = ((ix==-999)||(iy==-999)||(iz==-999) ? 0. : vf(ix,iy,iz));
	}
	return;
}

/***********************************************************/
/***********************************************************/

static void TriStairStepLoop(
//  z - loop
    const FAArray3Ref<double>& vf,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
    double xint,
    double yint,
    FAArray1Ref<double>& zint,
    FAArray1Ref<double>& uint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
	int ilow,
	int ihi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    int bias,
    double eps
    )
{
    // piecewise constant interpolation in 3D
	int i;
    int locx,locy,locz,ix,iy,iz, ascendx,ascendy, ascendz;
    
    ascendx = x(nxhi)>=x(nxlow);
	locx = nxlow;
	FindStairStepIndex(x,uniformdx,xint,nxlow,nxhi,ascendx,bias,eps,&locx,&ix);

    ascendy = y(nyhi)>=y(nylow);
	locy = nylow;
	FindStairStepIndex(y,uniformdy,yint,nylow,nyhi,ascendy,bias,eps,&locy,&iy);

    ascendz = z(nzhi)>=z(nzlow);
	locz = nzlow;

	for (i=ilow;i<=ihi;i++){
		FindStairStepIndex(z,uniformdz,zint(i),nzlow,nzhi,ascendz,bias,eps,&locz,&iz);
		uint(i) = ((ix==-999)||(iy==-999)||(iz==-999) ? 0. : vf(ix,iy,iz));
	}
	return;
}

/***********************************************************/
/***********************************************************/

static double Trilinear(
    const FAArray3Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
    double xint,
    double yint,
    double zint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    int extrap
    )
{
    // trilinear interpolation at a single point
    // u:       ordinate
    // x:       x abscissa
	// ........
    // xint:    x value to interpolate at
    // ........
    // nxlow:   lower x abscissa index
    // nxhi:    upper x abscissa index
	// ........
    // uniformdx =0 if dx is nonuniform, else is the uniform dx
	// ........
    // extrap: =1(0): do(not) linearly extrapolate out of range xint,yint

    int locx,locy,locz,ix,iy,iz,ascendx,ascendy,ascendz;
    double ttx,tty,ttcx,ttcy,ttz,ttcz,u0,u1;
    char ErrorMsgx[] = "Trilinear: Error - The interval between x interpolation points is 0.";
    char ErrorMsgy[] = "Trilinear: Error - The interval between y interpolation points is 0.";
    char ErrorMsgz[] = "Trilinear: Error - The interval between z interpolation points is 0.";
    
    // single data point
    if (nxlow==nxhi && nylow==nyhi && nzlow==nzhi) {
        return u(nxlow,nylow,nzlow);
    }

    // find x interpolation interval
    locx = nxlow;
    ascendx = x(nxhi)>=x(nxlow);
    ComputeIntervalFraction(x,uniformdx,xint,nxlow,nxhi,ascendx,extrap,&locx,&ix,&ttx,ErrorMsgx);
    ttcx = 1.-ttx;

    // find y interpolation interval
    locy = nylow;
    ascendy = y(nyhi)>=y(nylow);
    ComputeIntervalFraction(y,uniformdy,yint,nylow,nyhi,ascendy,extrap,&locy,&iy,&tty,ErrorMsgy);
    ttcy = 1.-tty;
    
    // find y interpolation interval
    locz = nzlow;
    ascendz = z(nzhi)>=z(nzlow);
    ComputeIntervalFraction(z,uniformdz,zint,nzlow,nzhi,ascendz,extrap,&locz,&iz,&ttz,ErrorMsgz);
    ttcz = 1.-ttz;

    u0 = ttcx*(ttcy*u(ix,iy,iz)   + tty*u(ix,iy+1,iz))   + ttx*(ttcy*u(ix+1,iy,iz)   + tty*u(ix+1,iy+1,iz));
    u1 = ttcx*(ttcy*u(ix,iy,iz+1) + tty*u(ix,iy+1,iz+1)) + ttx*(ttcy*u(ix+1,iy,iz+1) + tty*u(ix+1,iy+1,iz+1));

    return ttcz*u0 + ttz*u1;
}

/***********************************************************/
/***********************************************************/

static void TrilinearLoop(
//  x - loop
    const FAArray3Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
    FAArray1Ref<double>& xint,
    double yint,
    double zint,
    FAArray1Ref<double>& uint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
	int ilow,
	int ihi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    int extrap
    )
{
	// linear interpolation in 3D
	// u:       ordinate
    // x:       x abscissa
	// ........
    // xint:    x value to interpolate at
    // ........
	// ilow:	lower interpolation index
	// ihi:		upper interpolation index
	// uint:	interpolated values
    // nxlow:   lower x abscissa index
    // nxhi:    upper x abscissa index
	// ........
    // uniformdx =0 if dx is nonuniform, else is the uniform dx
	// ........
	// extrap: =1(0): do(not) linearly extrapolate out of range

	int i;
	int locx,locy,locz,ix,iy,iz,ascendx,ascendy,ascendz;
    double ttx,tty,ttcx,ttcy,ttz,ttcz,u0,u1;
    char ErrorMsgx[] = "Trilinear: Error - The interval between x interpolation points is 0.";
    char ErrorMsgy[] = "Trilinear: Error - The interval between y interpolation points is 0.";
    char ErrorMsgz[] = "Trilinear: Error - The interval between z interpolation points is 0.";
    
	// single data point
    if (nxlow==nxhi && nylow==nyhi && nzlow==nzhi) {
        for (i=ilow; i<=ihi; i++) {
            uint(i) = u(nxlow,nylow,nzlow);
        }
    }
    
	// find y interpolation interval
    locy = nylow;
    ascendy = y(nyhi)>=y(nylow);
    ComputeIntervalFraction(y,uniformdy,yint,nylow,nyhi,ascendy,extrap,&locy,&iy,&tty,ErrorMsgy);
    ttcy = 1.-tty;
    
    // find z interpolation interval
    locz = nzlow;
    ascendz = z(nzhi)>=z(nzlow);
    ComputeIntervalFraction(z,uniformdz,zint,nzlow,nzhi,ascendz,extrap,&locz,&iz,&ttz,ErrorMsgz);
    ttcz = 1.-ttz;

    // find x interpolation interval
	locx = nxlow;
	ascendx = x(nxhi)>=x(nxlow);

	for (i=ilow;i<=ihi;i++){
		// find x interpolation interval
		ComputeIntervalFraction(x,uniformdx,xint(i),nxlow,nxhi,ascendx,extrap,&locx,&ix,&ttx,ErrorMsgx);
		ttcx = 1.-ttx;
		u0 = ttcx*(ttcy*u(ix,iy,iz)   + tty*u(ix,iy+1,iz))   + ttx*(ttcy*u(ix+1,iy,iz)   + tty*u(ix+1,iy+1,iz));
		u1 = ttcx*(ttcy*u(ix,iy,iz+1) + tty*u(ix,iy+1,iz+1)) + ttx*(ttcy*u(ix+1,iy,iz+1) + tty*u(ix+1,iy+1,iz+1));
		uint(i)=ttcz*u0 + ttz*u1;
	}
	return;
}

/***********************************************************/
/***********************************************************/

static void TrilinearLoop(
//  y - loop
	const FAArray3Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
    double xint,
    FAArray1Ref<double>& yint,
    double zint,
    FAArray1Ref<double>& uint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
	int ilow,
	int ihi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    int extrap
    )
{
    int i;
	int locx,locy,locz,ix,iy,iz,ascendx,ascendy,ascendz;
    double ttx,tty,ttcx,ttcy,ttz,ttcz,u0,u1;
    char ErrorMsgx[] = "Trilinear: Error - The interval between x interpolation points is 0.";
    char ErrorMsgy[] = "Trilinear: Error - The interval between y interpolation points is 0.";
    char ErrorMsgz[] = "Trilinear: Error - The interval between z interpolation points is 0.";
    
	// single data point
    if (nxlow==nxhi && nylow==nyhi && nzlow==nzhi) {
        for (i=ilow; i<=ihi; i++) {
            uint(i) = u(nxlow,nylow,nzlow);
        }
    }
    
	// find x interpolation interval
	locx = nxlow;
	ascendx = x(nxhi)>=x(nxlow);
	ComputeIntervalFraction(x,uniformdx,xint,nxlow,nxhi,ascendx,extrap,&locx,&ix,&ttx,ErrorMsgx);
    ttcx = 1.-ttx;

    // find y interpolation interval
    locy = nylow;
    ascendy = y(nyhi)>=y(nylow);
    
    // find z interpolation interval
    locz = nzlow;
    ascendz = z(nzhi)>=z(nzlow);
    ComputeIntervalFraction(z,uniformdz,zint,nzlow,nzhi,ascendz,extrap,&locz,&iz,&ttz,ErrorMsgz);
    ttcz = 1.-ttz;

	for (i=ilow;i<=ihi;i++){
		// find y interpolation interval
	    ComputeIntervalFraction(y,uniformdy,yint(i),nylow,nyhi,ascendy,extrap,&locy,&iy,&tty,ErrorMsgy);
		ttcy = 1.-tty;
		u0 = ttcx*(ttcy*u(ix,iy,iz)   + tty*u(ix,iy+1,iz))   + ttx*(ttcy*u(ix+1,iy,iz)   + tty*u(ix+1,iy+1,iz));
		u1 = ttcx*(ttcy*u(ix,iy,iz+1) + tty*u(ix,iy+1,iz+1)) + ttx*(ttcy*u(ix+1,iy,iz+1) + tty*u(ix+1,iy+1,iz+1));
		uint(i)=ttcz*u0 + ttz*u1;
	}
	return;
}

/***********************************************************/
/***********************************************************/

static void TrilinearLoop(
//  z - loop    
    const FAArray3Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
    double xint,
    double yint,
    FAArray1Ref<double>& zint,
    FAArray1Ref<double>& uint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
	int ilow,
	int ihi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    int extrap
    )
{
    int i;
	int locx,locy,locz,ix,iy,iz,ascendx,ascendy,ascendz;
    double ttx,tty,ttcx,ttcy,ttz,ttcz,u0,u1;
    char ErrorMsgx[] = "Trilinear: Error - The interval between x interpolation points is 0.";
    char ErrorMsgy[] = "Trilinear: Error - The interval between y interpolation points is 0.";
    char ErrorMsgz[] = "Trilinear: Error - The interval between z interpolation points is 0.";
    
	// single data point
    if (nxlow==nxhi && nylow==nyhi && nzlow==nzhi) {
        for (i=ilow; i<=ihi; i++) {
            uint(i) = u(nxlow,nylow,nzlow);
        }
    }
    
	// find x interpolation interval
	locx = nxlow;
	ascendx = x(nxhi)>=x(nxlow);
	ComputeIntervalFraction(x,uniformdx,xint,nxlow,nxhi,ascendx,extrap,&locx,&ix,&ttx,ErrorMsgx);
    ttcx = 1.-ttx;

	// find y interpolation interval
    locy = nylow;
    ascendy = y(nyhi)>=y(nylow);
    ComputeIntervalFraction(y,uniformdy,yint,nylow,nyhi,ascendy,extrap,&locy,&iy,&tty,ErrorMsgy);
    ttcy = 1.-tty;
    
    // find z interpolation interval
    locz = nzlow;
    ascendz = z(nzhi)>=z(nzlow);

	for (i=ilow;i<=ihi;i++){
	    // find z interpolation interval
		ComputeIntervalFraction(z,uniformdz,zint(i),nzlow,nzhi,ascendz,extrap,&locz,&iz,&ttz,ErrorMsgz);
	    ttcz = 1.-ttz;
		u0 = ttcx*(ttcy*u(ix,iy,iz)   + tty*u(ix,iy+1,iz))   + ttx*(ttcy*u(ix+1,iy,iz)   + tty*u(ix+1,iy+1,iz));
		u1 = ttcx*(ttcy*u(ix,iy,iz+1) + tty*u(ix,iy+1,iz+1)) + ttx*(ttcy*u(ix+1,iy,iz+1) + tty*u(ix+1,iy+1,iz+1));
		uint(i)=ttcz*u0 + ttz*u1;
	}
	return;
}

/***********************************************************/
/***********************************************************/

static double TriCubicCore(
    const FAArray3Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
	int indexx,
	int indexy,
	int indexz,
	double ttx,
	double tty,
	double ttz,
	FAArray1Ref<double>& ux,
	FAArray1Ref<double>& uy
    )
{
    double ans;
	double ttcx,Deltax,Deltamx,Deltapx;
	double ttcy,Deltay,Deltamy,Deltapy;
	double ttcz,Deltaz,Deltamz,Deltapz;
	char ErrorMsgx[] = "Cubic: Error - The interval between interpolation points is 0.";
	char ErrorMsgy[] = "Cubic: Error - The interval between interpolation points is 0.";
	char ErrorMsgz[] = "Cubic: Error - The interval between interpolation points is 0.";
	double fpp,fp0,fpm,fpp0,fpp1;

	if (indexy>nylow && (nyhi-nylow)>=3 && indexy<nyhi-1) {
		ttcy = 1. - tty;
		// cubic correction
		Deltamy = y(indexy) - y(indexy-1);
		Deltay  = y(indexy+1) - y(indexy);
		Deltapy = y(indexy+2) - y(indexy+1);
		if (Deltamy==0. || Deltay==0. || Deltapy==0) {
			throw new FAErrorException(ErrorMsgy,InterpolationDeltaError);
		}
	}
	
	if (indexz>nzlow && (nzhi-nzlow)>=3 && indexz<nzhi-1) {
		ttcz = 1. - ttz;
		// cubic correction
		Deltamz = z(indexz) - z(indexz-1);
		Deltaz  = z(indexz+1) - z(indexz);
		Deltapz = z(indexz+2) - z(indexz+1);
		if (Deltamz==0. || Deltaz==0. || Deltapz==0) {
			throw new FAErrorException(ErrorMsgz,InterpolationDeltaError);
		}
	}

	int ilow,ihi, jlow, jhi;

	if (indexy<=nylow || (nyhi-nylow)<3 || indexy>=nyhi-1){
		jlow=indexy; jhi=indexy+1;
	}
	else {
		jlow=indexy-1; jhi=indexy+2;
	}

	if (indexx<=nxlow || (nxhi-nxlow)<3 || indexx>=nxhi-1){
		ilow=indexx; ihi=indexx+1;
	}
	else {
		ilow=indexx-1; ihi=indexx+2;
	}
	
	for (int i=ilow; i<=ihi; i++){
		for (int j=jlow; j<=jhi; j++){
			// linear piece
			uy(j) = u(i,j,indexz) + ttz*(u(i,j,indexz+1) - u(i,j,indexz));
			if (indexz<=nzlow || (nzhi-nzlow)<3 || indexz>=nzhi-1) continue;
		
			fpm = (u(i,j,indexz) - u(i,j,indexz-1))/Deltamz;
			fp0 = (u(i,j,indexz+1) - u(i,j,indexz))/Deltaz;
			fpp = (u(i,j,indexz+2) - u(i,j,indexz+1))/Deltapz;
			fpp0 =  2.0*(fp0 - fpm) / (Deltaz + Deltamz);
			fpp1 =  2.0*(fpp - fp0) / (Deltapz + Deltaz);
			uy(j) += (ttcz*(ttcz*ttcz-1.)*fpp0 + ttz*(ttz*ttz-1.)*fpp1)*Deltaz*Deltaz/6.;
		}

		// linear piece
		ux(i) = uy(indexy) + tty*(uy(indexy+1) - uy(indexy));
		if (indexy<=nylow || (nyhi-nylow)<3 || indexy>=nyhi-1) continue;

	    fpm = (uy(indexy) - uy(indexy-1))/Deltamy;
		fp0 = (uy(indexy+1) - uy(indexy))/Deltay;
	    fpp = (uy(indexy+2) - uy(indexy+1))/Deltapy;
		fpp0 =  2.0*(fp0 - fpm) / (Deltay + Deltamy);
		fpp1 =  2.0*(fpp - fp0) / (Deltapy + Deltay);
	    ux(i) += (ttcy*(ttcy*ttcy-1.)*fpp0 + tty*(tty*tty-1.)*fpp1)*Deltay*Deltay/6.;
	}

    // linear piece
    ans = ux(indexx) + ttx*(ux(indexx+1) - ux(indexx));
    if (indexx<=nxlow || (nxhi-nxlow)<3 || indexx>=nxhi-1) return ans;

    ttcx = 1. - ttx;
    // cubic correction
    Deltamx = x(indexx) - x(indexx-1);
    Deltax  = x(indexx+1) - x(indexx);
    Deltapx = x(indexx+2) - x(indexx+1);
    if (Deltamx==0. || Deltax==0. || Deltapx==0) {
        throw new FAErrorException(ErrorMsgx,InterpolationDeltaError);
    }
    fpm = (ux(indexx) - ux(indexx-1))/Deltamx;
    fp0 = (ux(indexx+1) - ux(indexx))/Deltax;
    fpp = (ux(indexx+2) - ux(indexx+1))/Deltapx;
    fpp0 =  2.0*(fp0 - fpm) / (Deltax + Deltamx);
    fpp1 =  2.0*(fpp - fp0) / (Deltapx + Deltax);
    ans += (ttcx*(ttcx*ttcx-1.)*fpp0 + ttx*(ttx*ttx-1.)*fpp1)*Deltax*Deltax/6.;
    return ans;
}

/***********************************************************/
/***********************************************************/

static double TriCubic(
    const FAArray3Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
	double xint,
    double yint,
    double zint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    int extrap
    )
{
	double ans;
    // single data point
    if (nxlow==nxhi && nylow==nyhi && nzlow==nzhi) {
        return u(nxlow,nylow,nzlow);
    }
	
	// precalculation in X direction
    int indexx,locx,ascendx;
    double ttx;
    char ErrorMsgx[] = "Cubic: Error - The interval between interpolation points is 0.";
    // locate point just to the left and compute interval fraction
    locx = nxlow;
    ascendx = x(nxhi)>=x(nxlow);
    ComputeIntervalFraction(x,uniformdx,xint,nxlow,nxhi,ascendx,extrap,&locx,&indexx,&ttx,ErrorMsgx);

	// precalculation in Y direction
	int indexy,locy,ascendy;
	double tty;
	char ErrorMsgy[] = "Cubic: Error - The interval between interpolation points is 0.";
    // locate point just to the left and compute interval fraction
	locy = nylow;
	ascendy = y(nyhi)>=y(nylow);
	ComputeIntervalFraction(y,uniformdy,yint,nylow,nyhi,ascendy,extrap,&locy,&indexy,&tty,ErrorMsgy);

	// precalculation in Z direction
	int indexz,locz,ascendz;
	double ttz;
	char ErrorMsgz[] = "Cubic: Error - The interval between interpolation points is 0.";
    // locate point just to the left and compute interval fraction
	locz = nzlow;
	ascendz = z(nzhi)>=z(nzlow);
	ComputeIntervalFraction(z,uniformdz,zint,nzlow,nzhi,ascendz,extrap,&locz,&indexz,&ttz,ErrorMsgz);

	FAArray1<double> uy(y.size0());
	FAArray1<double> ux(x.size0());
	
	ans = TriCubicCore(u,x,y,z,nxlow,nxhi,nylow,nyhi,nzlow,nzhi,indexx,indexy,indexz,ttx,tty,ttz,ux,uy);
	return ans;
}

/***********************************************************/
/***********************************************************/

static void TriCubicLoop(
//  x - loop
    const FAArray3Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
	FAArray1Ref<double>& xint,
    double yint,
    double zint,
	FAArray1Ref<double>& uint,
	int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
	int ilow,
	int ihi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    int extrap
    )
{
    if (nxlow==nxhi && nylow==nyhi && nzlow==nzhi) {
        for (int i=ilow; i<=ihi; i++) {
            uint(i) = u(nxlow,nylow,nzlow);
        }
    }
	
	// precalculation in Y direction
	int indexy,locy,ascendy;
	double tty;
	char ErrorMsgy[] = "Cubic: Error - The interval between interpolation points is 0.";
    // locate point just to the left and compute interval fraction
	locy = nylow;
	ascendy = y(nyhi)>=y(nylow);
	ComputeIntervalFraction(y,uniformdy,yint,nylow,nyhi,ascendy,extrap,&locy,&indexy,&tty,ErrorMsgy);

	// precalculation in Z direction
	int indexz,locz,ascendz;
	double ttz;
	char ErrorMsgz[] = "Cubic: Error - The interval between interpolation points is 0.";
    // locate point just to the left and compute interval fraction
	locz = nzlow;
	ascendz = z(nzhi)>=z(nzlow);
	ComputeIntervalFraction(z,uniformdz,zint,nzlow,nzhi,ascendz,extrap,&locz,&indexz,&ttz,ErrorMsgz);

	FAArray1<double> uy(y.size0());
	FAArray1<double> ux(x.size0());
	
	// precalculation in X direction
	int indexx,locx,ascendx;
	double ttx;
	char ErrorMsgx[] = "Cubic: Error - The interval between interpolation points is 0.";
	// locate point just to the left and compute interval fraction
	locx = nxlow;
	ascendx = x(nxhi)>=x(nxlow);

	for (int i=ilow; i<=ihi; i++){
		ComputeIntervalFraction(x,uniformdx,xint(i),nxlow,nxhi,ascendx,extrap,&locx,&indexx,&ttx,ErrorMsgx);
		uint(i)=TriCubicCore(u,x,y,z,nxlow,nxhi,nylow,nyhi,nzlow,nzhi,indexx,indexy,indexz,ttx,tty,ttz,ux,uy);
	}
	return;
}

/***********************************************************/
/***********************************************************/

static void TriCubicLoop(
//  y - loop
    const FAArray3Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
	double xint,
    FAArray1Ref<double>& yint,
    double zint,
	FAArray1Ref<double>& uint,
	int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
	int ilow,
	int ihi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    int extrap
    )
{
    if (nxlow==nxhi && nylow==nyhi && nzlow==nzhi) {
        for (int i=ilow; i<=ihi; i++) {
            uint(i) = u(nxlow,nylow,nzlow);
        }
    }
	
	FAArray1<double> uy(y.size0());
	FAArray1<double> ux(x.size0());
	
	// precalculation in X direction
	int indexx,locx,ascendx;
	double ttx;
	char ErrorMsgx[] = "Cubic: Error - The interval between interpolation points is 0.";
	// locate point just to the left and compute interval fraction
	locx = nxlow;
	ascendx = x(nxhi)>=x(nxlow);
	ComputeIntervalFraction(x,uniformdx,xint,nxlow,nxhi,ascendx,extrap,&locx,&indexx,&ttx,ErrorMsgx);

	// precalculation in Z direction
	int indexz,locz,ascendz;
	double ttz;
	char ErrorMsgz[] = "Cubic: Error - The interval between interpolation points is 0.";
    // locate point just to the left and compute interval fraction
	locz = nzlow;
	ascendz = z(nzhi)>=z(nzlow);
	ComputeIntervalFraction(z,uniformdz,zint,nzlow,nzhi,ascendz,extrap,&locz,&indexz,&ttz,ErrorMsgz);

	// precalculation in Y direction
	int indexy,locy,ascendy;
	double tty;
	char ErrorMsgy[] = "Cubic: Error - The interval between interpolation points is 0.";
    // locate point just to the left and compute interval fraction
	locy = nylow;
	ascendy = y(nyhi)>=y(nylow);
	for (int i=ilow; i<=ihi; i++){
		ComputeIntervalFraction(y,uniformdy,yint(i),nylow,nyhi,ascendy,extrap,&locy,&indexy,&tty,ErrorMsgy);
		uint(i)=TriCubicCore(u,x,y,z,nxlow,nxhi,nylow,nyhi,nzlow,nzhi,indexx,indexy,indexz,ttx,tty,ttz,ux,uy);
	}
	return;
}

/***********************************************************/
/***********************************************************/

static void TriCubicLoop(
//  z - loop
    const FAArray3Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
	double xint,
    double yint,
    FAArray1Ref<double>& zint,
	FAArray1Ref<double>& uint,
	int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
	int ilow,
	int ihi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    int extrap
    )
{
    if (nxlow==nxhi && nylow==nyhi && nzlow==nzhi) {
        for (int i=ilow; i<=ihi; i++) {
            uint(i) = u(nxlow,nylow,nzlow);
        }
    }
	
	FAArray1<double> uy(y.size0());
	FAArray1<double> ux(x.size0());
	
	// precalculation in X direction
	int indexx,locx,ascendx;
	double ttx;
	char ErrorMsgx[] = "Cubic: Error - The interval between interpolation points is 0.";
	// locate point just to the left and compute interval fraction
	locx = nxlow;
	ascendx = x(nxhi)>=x(nxlow);
	ComputeIntervalFraction(x,uniformdx,xint,nxlow,nxhi,ascendx,extrap,&locx,&indexx,&ttx,ErrorMsgx);

	// precalculation in Y direction
	int indexy,locy,ascendy;
	double tty;
	char ErrorMsgy[] = "Cubic: Error - The interval between interpolation points is 0.";
    // locate point just to the left and compute interval fraction
	locy = nylow;
	ascendy = y(nyhi)>=y(nylow);
	ComputeIntervalFraction(y,uniformdy,yint,nylow,nyhi,ascendy,extrap,&locy,&indexy,&tty,ErrorMsgy);

	// precalculation in Z direction
	int indexz,locz,ascendz;
	double ttz;
	char ErrorMsgz[] = "Cubic: Error - The interval between interpolation points is 0.";
    // locate point just to the left and compute interval fraction
	locz = nzlow;
	ascendz = z(nzhi)>=z(nzlow);

	for (int i=ilow; i<=ihi; i++){
		ComputeIntervalFraction(z,uniformdz,zint(i),nzlow,nzhi,ascendz,extrap,&locz,&indexz,&ttz,ErrorMsgz);
		uint(i)=TriCubicCore(u,x,y,z,nxlow,nxhi,nylow,nyhi,nzlow,nzhi,indexx,indexy,indexz,ttx,tty,ttz,ux,uy);
	}
	return;
}

/***********************************************************/
/***********************************************************/

static void TriCubicSplineCoefficients(
    const FAArray3Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    FAArray3Ref<double>& fpp,
    FAArray1Ref<double>& TriTx,
    FAArray1Ref<double>& TriT2x,
    FAArray1Ref<double>& TriTy,
    FAArray1Ref<double>& TriT2y,
    FAArray1Ref<double>& TriTz,
    FAArray1Ref<double>& TriT2z,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
    int dir
    )
{
	int i,j,k;

	if (dir==1) {
		// Auxiliary arrays for slicing
		FAArray2<double> uyz(y.size0(),z.size0());
		FAArray2<double> fppyz(y.size0(),z.size0());
	    
		for (i=nxlow; i<=nxhi; i++) {
	
			for (j=nylow;j<=nyhi;j++){ // slicing
				for (k=nzlow;k<=nzhi;k++){
					uyz(j,k)=u(i,j,k);
				}
			}
			// make interpolation for the current plane at (yint,zint) 
			// use y direction for scan
			BiCubicSplineCoefficients(uyz,y,z,uniformdy,uniformdz,fppyz,TriTy,TriT2y,TriTz,TriT2z,nylow,nyhi,nzlow,nzhi,1);
	
			for (j=nylow;j<=nyhi;j++){ // stuffing
				for (k=nzlow;k<=nzhi;k++){
					fpp(i,j,k)=fppyz(j,k);
				}	
			}
		}
	}
	    
	if (dir==2) {
		// Auxiliary arrays for slicing
		FAArray2<double> uxz(x.size0(),z.size0());
		FAArray2<double> fppxz(x.size0(),z.size0());
	    
		for (j=nylow; j<=nyhi; j++) {
	
			for (i=nxlow;i<=nxhi;i++){ // slicing
				for (k=nzlow;k<=nzhi;k++){
					uxz(i,k)=u(i,j,k);
				}
			}
			// make interpolation for the current plane at (xint,zint) 
			// use y direction for scan
			BiCubicSplineCoefficients(uxz,x,z,uniformdx,uniformdz,fppxz,TriTx,TriT2x,TriTz,TriT2z,nxlow,nxhi,nzlow,nzhi,1);
			for (i=nxlow;i<=nxhi;i++){ // stuffing
				for (k=nzlow;k<=nzhi;k++){
					fpp(i,j,k)=fppxz(i,k);
				}	
			}
		}
	}

	if (dir==3) {
		// Auxiliary arrays for slicing
		FAArray2<double> uxy(x.size0(),y.size0());
		FAArray2<double> fppxy(x.size0(),y.size0());
	    
		for (k=nzlow; k<=nzhi; k++) {
	
			for (i=nxlow;i<=nxhi;i++){ // slicing
				for (j=nylow;j<=nyhi;j++){
					uxy(i,j)=u(i,j,k);
				}
			}
			// make interpolation for the current plane at (xint,yint) 
			// use y direction for scan
			BiCubicSplineCoefficients(uxy,x,y,uniformdx,uniformdy,fppxy,TriTx,TriT2x,TriTy,TriT2y,nxlow,nxhi,nylow,nyhi,1);
			for (i=nxlow;i<=nxhi;i++){ // stuffing
				for (j=nylow;j<=nyhi;j++){
					fpp(i,j,k)=fppxy(i,j);
				}	
			}
		}
	}
	return;
}

/***********************************************************/
/***********************************************************/

static double TriCubicSpline(
    const FAArray3Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
	double xint,
    double yint,
    double zint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    int extrap,
	int dir,
    FAArray3Ref<double>& fpp,
    FAArray1Ref<double>& TriTx,
    FAArray1Ref<double>& TriT2x,
    FAArray1Ref<double>& TriTy,
    FAArray1Ref<double>& TriT2y,
    FAArray1Ref<double>& TriTz,
    FAArray1Ref<double>& TriT2z
    )
{
    // tri cubic spline interpolation at a single point

	int i,j,k;
	double ans;

	// single data point
    if (nxlow==nxhi && nylow==nyhi && nzlow==nzhi) {
        return u(nxlow,nylow,nzlow);
    }

	if (dir==1){
		// Auxiliary arrays
		FAArray1<double> ux(x.size0());
		FAArray1<double> fppx(x.size0());
		FAArray1<double> uy(y.size0());
		FAArray1<double> fppy(y.size0());
	    // locate point just to the left and compute interval fraction
		int locy = nylow;
		int ascendy = y(nyhi)>=y(nylow);
		int indexy = 0;
		char ErrorMsgy[] = "CubicSpline: Error - The interval between interpolation points is 0.";
		double tty, ttcy, Deltay;
		ComputeIntervalFraction(y,uniformdy,yint,nylow,nyhi,ascendy,extrap,&locy,&indexy,&tty,ErrorMsgy);
		Deltay = y(indexy + 1) - y(indexy);
		ttcy = 1. - tty;
		// locate point just to the left and compute interval fraction
	    int locz = nzlow;
		int ascendz = z(nzhi)>=z(nzlow);
		int indexz = 0;
		char ErrorMsgz[] = "CubicSpline: Error - The interval between interpolation points is 0.";
		double ttz, ttcz, Deltaz;
		ComputeIntervalFraction(z,uniformdz,zint,nzlow,nzhi,ascendz,extrap,&locz,&indexz,&ttz,ErrorMsgz);
		Deltaz = z(indexz + 1) - z(indexz);
		ttcz = 1. - ttz;

		for (i=nxlow; i<=nxhi; i++) {
			for (j=nylow; j<=nyhi; j++) {
				// linear piece
				uy(j) = u(i,j,indexz) + ttz*(u(i,j,indexz+1) - u(i,j,indexz));
				// cubic spline correction
				if (ttz>=0. && (nzhi-nzlow)>=2 && ttz<=1.) {
					uy(j)+= (ttcz*(ttcz*ttcz - 1.)*fpp(i,j,indexz) + ttz*(ttz*ttz - 1.)*fpp(i,j,indexz+1))*Deltaz*Deltaz/6.;
				}
			}	
	    
			// interpolate in x
			SplineCoefficients(uy,y,uniformdy,fppy,TriTy,TriT2y,nylow,nyhi);
			// linear piece
			ux(i) = uy(indexy) + tty*(uy(indexy+1) - uy(indexy));
			// cubic spline correction
			if (tty>=0. && (nyhi-nylow)>=2 && tty<=1.) {
				ux(i)+= (ttcy*(ttcy*ttcy- 1.)*fppy(indexy) + tty*(tty*tty - 1.)*fppy(indexy+1))*Deltay*Deltay/6.;
			}
		}
		// interpolate in x
		SplineCoefficients(ux,x,uniformdx,fppx,TriTx,TriT2x,nxlow,nxhi);
		ans = CubicSpline(ux,x,fppx,xint,nxlow,nxhi,uniformdx,extrap);
	}
	else if (dir==2){
		FAArray1<double> ux(x.size0());
		FAArray1<double> fppx(x.size0());
		FAArray1<double> uy(y.size0());
		FAArray1<double> fppy(y.size0());
		// locate point just to the left and compute interval fraction
		int locx = nxlow;
		int ascendx = x(nxhi)>=x(nxlow);
		int indexx = 0;
		char ErrorMsgx[] = "CubicSpline: Error - The interval between interpolation points is 0.";
		double ttx, ttcx, Deltax;
		ComputeIntervalFraction(x,uniformdx,xint,nxlow,nxhi,ascendx,extrap,&locx,&indexx,&ttx,ErrorMsgx);
		Deltax = x(indexx + 1) - x(indexx);
		ttcx = 1. - ttx;
		// locate point just to the left and compute interval fraction
		int locz = nzlow;
		int ascendz = z(nzhi)>=z(nzlow);
		int indexz = 0;
		char ErrorMsgz[] = "CubicSpline: Error - The interval between interpolation points is 0.";
		double ttz, ttcz, Deltaz;
		ComputeIntervalFraction(z,uniformdz,zint,nzlow,nzhi,ascendz,extrap,&locz,&indexz,&ttz,ErrorMsgz);
		Deltaz = z(indexz + 1) - z(indexz);
		ttcz = 1. - ttz;

		for	(j=nylow; j<=nyhi; j++) {
			for (i=nxlow; i<=nxhi; i++) {
				// linear piece
				ux(i) = u(i,j,indexz) + ttz*(u(i,j,indexz+1) - u(i,j,indexz));
				// cubic spline correction
			    if (ttz>=0. && (nzhi-nzlow)>=2 && ttz<=1.) {
					ux(i)+= (ttcz*(ttcz*ttcz - 1.)*fpp(i,j,indexz) + ttz*(ttz*ttz - 1.)*fpp(i,j,indexz+1))*Deltaz*Deltaz/6.;
				}
			}	
	    
			// interpolate in x
			SplineCoefficients(ux,x,uniformdx,fppx,TriTx,TriT2x,nxlow,nxhi);
			// linear piece
			uy(j) = ux(indexx) + ttx*(ux(indexx+1) - ux(indexx));
			// cubic spline correction
			if (ttx>=0. && (nxhi-nxlow)>=2 && ttx<=1.) {
				uy(j)+= (ttcx*(ttcx*ttcx- 1.)*fppx(indexx) + ttx*(ttx*ttx - 1.)*fppx(indexx+1))*Deltax*Deltax/6.;
			}
		}
	    
		// interpolate in y
		SplineCoefficients(uy,y,uniformdy,fppy,TriTy,TriT2y,nylow,nyhi);
		ans=CubicSpline(uy,y,fppy,yint,nylow,nyhi,uniformdy,extrap);
	}
	else if(dir==3){
		FAArray1<double> ux(x.size0());
		FAArray1<double> fppx(x.size0());
		FAArray1<double> uz(z.size0());
		FAArray1<double> fppz(z.size0());
	    // locate point just to the left and compute interval fraction
		int locx = nxlow;
		int ascendx = x(nxhi)>=x(nxlow);
		int indexx = 0;
		char ErrorMsgx[] = "CubicSpline: Error - The interval between interpolation points is 0.";
		double ttx, ttcx, Deltax;
		ComputeIntervalFraction(x,uniformdx,xint,nxlow,nxhi,ascendx,extrap,&locx,&indexx,&ttx,ErrorMsgx);
		Deltax = x(indexx + 1) - x(indexx);
		ttcx = 1. - ttx;
		// locate point just to the left and compute interval fraction
	    int locy = nylow;
		int ascendy = y(nyhi)>=y(nylow);
		int indexy = 0;
		char ErrorMsgy[] = "CubicSpline: Error - The interval between interpolation points is 0.";
		double tty, ttcy, Deltay;
		ComputeIntervalFraction(y,uniformdy,yint,nylow,nyhi,ascendy,extrap,&locy,&indexy,&tty,ErrorMsgy);
		Deltay = y(indexy + 1) - y(indexy);
		ttcy = 1. - tty;
	
		for (k=nzlow; k<=nzhi; k++) {
			for (i=nxlow; i<=nxhi; i++) {
				// linear piece
				ux(i) = u(i,indexy,k) + tty*(u(i,indexy+1,k) - u(i,indexy,k));
				// cubic spline correction
			    if (tty>=0. && (nyhi-nylow)>=2 && tty<=1.) {
					ux(i)+= (ttcy*(ttcy*ttcy - 1.)*fpp(i,indexy,k) + tty*(tty*tty - 1.)*fpp(i,indexy+1,k))*Deltay*Deltay/6.;
				}
			}	
		    
			// interpolate in x
			SplineCoefficients(ux,x,uniformdx,fppx,TriTx,TriT2x,nxlow,nxhi);
			// linear piece
			uz(k) = ux(indexx) + ttx*(ux(indexx+1) - ux(indexx));
			// cubic spline correction
			if (ttx>=0. && (nxhi-nxlow)>=2 && ttx<=1.) {
				uz(k)+= (ttcx*(ttcx*ttcx- 1.)*fppx(indexx) + ttx*(ttx*ttx - 1.)*fppx(indexx+1))*Deltax*Deltax/6.;
			}
		}
	    
		// interpolate in z
		SplineCoefficients(uz,z,uniformdz,fppz,TriTz,TriT2z,nzlow,nzhi);
		ans=CubicSpline(uz,z,fppz,zint,nzlow,nzhi,uniformdz,extrap);
	}
	return ans;
}

/***********************************************************/
/***********************************************************/

static void TriCubicSplineLoop(
//  x - loop
    const FAArray3Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
	FAArray1Ref<double>& xint,
    double yint,
    double zint,
	FAArray1Ref<double>& uint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
	int ilow,
	int ihi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    int extrap,
    FAArray3Ref<double>& fpp,
    FAArray1Ref<double>& TriTx,
    FAArray1Ref<double>& TriT2x,
    FAArray1Ref<double>& TriTy,
    FAArray1Ref<double>& TriT2y,
    FAArray1Ref<double>& TriTz,
    FAArray1Ref<double>& TriT2z
    )
{
    // tri cubic spline interpolation at a single point
	int i,j;

	// Auxiliary arrays
	FAArray1<double> ux(x.size0());
	FAArray1<double> fppx(x.size0());
	FAArray1<double> uy(y.size0());
	FAArray1<double> fppy(y.size0());

	// single data point
    if (nxlow==nxhi && nylow==nyhi && nzlow==nzhi) {
        for (i=ilow; i<=ihi; i++) {
            uint(i) = u(nxlow,nylow,nzlow);
        }
    }

    // locate point just to the left and compute interval fraction
	int locy = nylow;
	int ascendy = y(nyhi)>=y(nylow);
	int indexy = 0;
	char ErrorMsgy[] = "CubicSpline: Error - The interval between interpolation points is 0.";
	double tty, ttcy, Deltay;
	ComputeIntervalFraction(y,uniformdy,yint,nylow,nyhi,ascendy,extrap,&locy,&indexy,&tty,ErrorMsgy);
	Deltay = y(indexy + 1) - y(indexy);
	ttcy = 1. - tty;
	// locate point just to the left and compute interval fraction
    int locz = nzlow;
	int ascendz = z(nzhi)>=z(nzlow);
	int indexz = 0;
	char ErrorMsgz[] = "CubicSpline: Error - The interval between interpolation points is 0.";
	double ttz, ttcz, Deltaz;
	ComputeIntervalFraction(z,uniformdz,zint,nzlow,nzhi,ascendz,extrap,&locz,&indexz,&ttz,ErrorMsgz);
	Deltaz = z(indexz + 1) - z(indexz);
	ttcz = 1. - ttz;

	for (i=nxlow; i<=nxhi; i++) {
		for (j=nylow; j<=nyhi; j++) {
			// linear piece
			uy(j) = u(i,j,indexz) + ttz*(u(i,j,indexz+1) - u(i,j,indexz));
			// cubic spline correction
		    if (ttz>=0. && (nzhi-nzlow)>=2 && ttz<=1.) {
				uy(j)+= (ttcz*(ttcz*ttcz - 1.)*fpp(i,j,indexz) + ttz*(ttz*ttz - 1.)*fpp(i,j,indexz+1))*Deltaz*Deltaz/6.;
			}
		}	
	    
		// interpolate in x
		SplineCoefficients(uy,y,uniformdy,fppy,TriTy,TriT2y,nylow,nyhi);
		// linear piece
		ux(i) = uy(indexy) + tty*(uy(indexy+1) - uy(indexy));
	    // cubic spline correction
	    if (tty>=0. && (nyhi-nylow)>=2 && tty<=1.) {
			ux(i)+= (ttcy*(ttcy*ttcy- 1.)*fppy(indexy) + tty*(tty*tty - 1.)*fppy(indexy+1))*Deltay*Deltay/6.;
		}
	}
	    
	// interpolate in x
	SplineCoefficients(ux,x,uniformdx,fppx,TriTx,TriT2x,nxlow,nxhi);
	CubicSplineLoop(ux,x,fppx,xint,uint,nxlow,nxhi,ilow,ihi,uniformdx,extrap);
	return;
}

/***********************************************************/
/***********************************************************/

static void TriCubicSplineLoop(
//  y - loop
    const FAArray3Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
	double xint,
    FAArray1Ref<double>& yint,
    double zint,
	FAArray1Ref<double>& uint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
	int ilow,
	int ihi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    int extrap,
    FAArray3Ref<double>& fpp,
    FAArray1Ref<double>& TriTx,
    FAArray1Ref<double>& TriT2x,
    FAArray1Ref<double>& TriTy,
    FAArray1Ref<double>& TriT2y,
    FAArray1Ref<double>& TriTz,
    FAArray1Ref<double>& TriT2z
    )
{
	int i,j;

	// Auxiliary arrays 
	FAArray1<double> ux(x.size0());
	FAArray1<double> fppx(x.size0());
	FAArray1<double> uy(y.size0());
	FAArray1<double> fppy(y.size0());
    
	// single data point
    if (nxlow==nxhi && nylow==nyhi && nzlow==nzhi) {
        for (i=ilow; i<=ihi; i++) {
            uint(i) = u(nxlow,nylow,nzlow);
        }
    }

    // locate point just to the left and compute interval fraction
	int locx = nxlow;
	int ascendx = x(nxhi)>=x(nxlow);
	int indexx = 0;
	char ErrorMsgx[] = "CubicSpline: Error - The interval between interpolation points is 0.";
	double ttx, ttcx, Deltax;
	ComputeIntervalFraction(x,uniformdx,xint,nxlow,nxhi,ascendx,extrap,&locx,&indexx,&ttx,ErrorMsgx);
	Deltax = x(indexx + 1) - x(indexx);
	ttcx = 1. - ttx;
	// locate point just to the left and compute interval fraction
    int locz = nzlow;
	int ascendz = z(nzhi)>=z(nzlow);
	int indexz = 0;
	char ErrorMsgz[] = "CubicSpline: Error - The interval between interpolation points is 0.";
	double ttz, ttcz, Deltaz;
	ComputeIntervalFraction(z,uniformdz,zint,nzlow,nzhi,ascendz,extrap,&locz,&indexz,&ttz,ErrorMsgz);
	Deltaz = z(indexz + 1) - z(indexz);
	ttcz = 1. - ttz;

	for (j=nylow; j<=nyhi; j++) {
		for (i=nxlow; i<=nxhi; i++) {

			// linear piece
			ux(i) = u(i,j,indexz) + ttz*(u(i,j,indexz+1) - u(i,j,indexz));
			// cubic spline correction
		    if (ttz>=0. && (nzhi-nzlow)>=2 && ttz<=1.) {
				ux(i)+= (ttcz*(ttcz*ttcz - 1.)*fpp(i,j,indexz) + ttz*(ttz*ttz - 1.)*fpp(i,j,indexz+1))*Deltaz*Deltaz/6.;
			}
		}	
	    
		// interpolate in x
		SplineCoefficients(ux,x,uniformdx,fppx,TriTx,TriT2x,nxlow,nxhi);
		// linear piece
		uy(j) = ux(indexx) + ttx*(ux(indexx+1) - ux(indexx));
	    // cubic spline correction
	    if (ttx>=0. && (nxhi-nxlow)>=2 && ttx<=1.) {
			uy(j)+= (ttcx*(ttcx*ttcx- 1.)*fppx(indexx) + ttx*(ttx*ttx - 1.)*fppx(indexx+1))*Deltax*Deltax/6.;
		}
	}
	    
	// interpolate in y
	SplineCoefficients(uy,y,uniformdy,fppy,TriTy,TriT2y,nylow,nyhi);
	CubicSplineLoop(uy,y,fppy,yint,uint,nylow,nyhi,ilow,ihi,uniformdy,extrap);
	return;
}

/***********************************************************/
/***********************************************************/

static void TriCubicSplineLoop(
//  z - loop
    const FAArray3Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
	double xint,
    double yint,
    FAArray1Ref<double>& zint,
	FAArray1Ref<double>& uint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
	int ilow,
	int ihi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    int extrap,
    FAArray3Ref<double>& fpp,
    FAArray1Ref<double>& TriTx,
    FAArray1Ref<double>& TriT2x,
    FAArray1Ref<double>& TriTy,
    FAArray1Ref<double>& TriT2y,
    FAArray1Ref<double>& TriTz,
    FAArray1Ref<double>& TriT2z
    )
{
	int i,k;

	// Auxiliary arrays
	FAArray1<double> ux(x.size0());
	FAArray1<double> fppx(x.size0());
	FAArray1<double> uz(z.size0());
	FAArray1<double> fppz(z.size0());
    
	// single data point
    if (nxlow==nxhi && nylow==nyhi && nzlow==nzhi) {
        for (i=ilow; i<=ihi; i++) {
            uint(i) = u(nxlow,nylow,nzlow);
        }
    }

    // locate point just to the left and compute interval fraction
	int locx = nxlow;
	int ascendx = x(nxhi)>=x(nxlow);
	int indexx = 0;
	char ErrorMsgx[] = "CubicSpline: Error - The interval between interpolation points is 0.";
	double ttx, ttcx, Deltax;
	ComputeIntervalFraction(x,uniformdx,xint,nxlow,nxhi,ascendx,extrap,&locx,&indexx,&ttx,ErrorMsgx);
	Deltax = x(indexx + 1) - x(indexx);
	ttcx = 1. - ttx;
	// locate point just to the left and compute interval fraction
    int locy = nylow;
	int ascendy = y(nyhi)>=y(nylow);
	int indexy = 0;
	char ErrorMsgy[] = "CubicSpline: Error - The interval between interpolation points is 0.";
	double tty, ttcy, Deltay;
	ComputeIntervalFraction(y,uniformdy,yint,nylow,nyhi,ascendy,extrap,&locy,&indexy,&tty,ErrorMsgy);
	Deltay = y(indexy + 1) - y(indexy);
	ttcy = 1. - tty;

	for (k=nzlow; k<=nzhi; k++) {
		for (i=nxlow; i<=nxhi; i++) {

			// linear piece
			ux(i) = u(i,indexy,k) + tty*(u(i,indexy+1,k) - u(i,indexy,k));
			// cubic spline correction
		    if (tty>=0. && (nyhi-nylow)>=2 && tty<=1.) {
				ux(i)+= (ttcy*(ttcy*ttcy - 1.)*fpp(i,indexy,k) + tty*(tty*tty - 1.)*fpp(i,indexy+1,k))*Deltay*Deltay/6.;
			}
		}	
	    
		// interpolate in x
		SplineCoefficients(ux,x,uniformdx,fppx,TriTx,TriT2x,nxlow,nxhi);
		// linear piece
		uz(k) = ux(indexx) + ttx*(ux(indexx+1) - ux(indexx));
	    // cubic spline correction
	    if (ttx>=0. && (nxhi-nxlow)>=2 && ttx<=1.) {
			uz(k)+= (ttcx*(ttcx*ttcx- 1.)*fppx(indexx) + ttx*(ttx*ttx - 1.)*fppx(indexx+1))*Deltax*Deltax/6.;
		}
	}
	    
	// interpolate in z
	SplineCoefficients(uz,z,uniformdz,fppz,TriTz,TriT2z,nzlow,nzhi);
	CubicSplineLoop(uz,z,fppz,zint,uint,nzlow,nzhi,ilow,ihi,uniformdz,extrap);
	return;
}

/***********************************************************/
/**************** 4D interpolation *************************/
/*** currently only single point quadlinear & quadcubic ****/
/***********************************************************/

static double Quadlinear(
    const FAArray4Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
    const FAArray1Ref<double>& w,
    double xint,
    double yint,
    double zint,
	double wint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
    int nwlow,
    int nwhi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    double uniformdw,
    int extrap
    )
{
    // quadlinear interpolation at a single point
    // u:       ordinate
    // x:       x abscissa
	// ........
    // xint:    x value to interpolate at
    // ........
    // nxlow:   lower x abscissa index
    // nxhi:    upper x abscissa index
	// ........
    // uniformdx =0 if dx is nonuniform, else is the uniform dx
	// ........
    // extrap: =1(0): do(not) linearly extrapolate out of range xint,yint

    int locx,locy,locz,locw,ix,iy,iz,iw,ascendx,ascendy,ascendz,ascendw;
    double ttx,tty,ttcx,ttcy,ttz,ttcz,ttw,ttcw,u0,u1,uu0,uu1;
    char ErrorMsgx[] = "Quadlinear: Error - The interval between x interpolation points is 0.";
    char ErrorMsgy[] = "Quadlinear: Error - The interval between y interpolation points is 0.";
    char ErrorMsgz[] = "Quadlinear: Error - The interval between z interpolation points is 0.";
    char ErrorMsgw[] = "Quadlinear: Error - The interval between w interpolation points is 0.";
    
    // single data point
    if (nxlow==nxhi && nylow==nyhi && nzlow==nzhi && nwlow==nwhi) {
        return u(nxlow,nylow,nzlow,nwlow);
    }

    // find x interpolation interval
    locx = nxlow;
    ascendx = x(nxhi)>=x(nxlow);
    ComputeIntervalFraction(x,uniformdx,xint,nxlow,nxhi,ascendx,extrap,&locx,&ix,&ttx,ErrorMsgx);
    ttcx = 1.-ttx;

    // find y interpolation interval
    locy = nylow;
    ascendy = y(nyhi)>=y(nylow);
    ComputeIntervalFraction(y,uniformdy,yint,nylow,nyhi,ascendy,extrap,&locy,&iy,&tty,ErrorMsgy);
    ttcy = 1.-tty;
    
    // find z interpolation interval
    locz = nzlow;
    ascendz = z(nzhi)>=z(nzlow);
    ComputeIntervalFraction(z,uniformdz,zint,nzlow,nzhi,ascendz,extrap,&locz,&iz,&ttz,ErrorMsgz);
    ttcz = 1.-ttz;

    // find w interpolation interval
    locw = nwlow;
    ascendw = w(nwhi)>=w(nwlow);
    ComputeIntervalFraction(w,uniformdw,wint,nwlow,nwhi,ascendw,extrap,&locw,&iw,&ttw,ErrorMsgw);
    ttcw = 1.-ttw;

	u0 = ttcx*(ttcy*u(ix,iy,iz,iw)   + tty*u(ix,iy+1,iz,iw))   + ttx*(ttcy*u(ix+1,iy,iz,iw)   + tty*u(ix+1,iy+1,iz,iw));
    u1 = ttcx*(ttcy*u(ix,iy,iz+1,iw) + tty*u(ix,iy+1,iz+1,iw)) + ttx*(ttcy*u(ix+1,iy,iz+1,iw) + tty*u(ix+1,iy+1,iz+1,iw));
	uu0 = ttcz*u0 + ttz*u1;
	u0 = ttcx*(ttcy*u(ix,iy,iz,iw+1)   + tty*u(ix,iy+1,iz,iw+1))   + ttx*(ttcy*u(ix+1,iy,iz,iw+1)   + tty*u(ix+1,iy+1,iz,iw+1));
    u1 = ttcx*(ttcy*u(ix,iy,iz+1,iw+1) + tty*u(ix,iy+1,iz+1,iw+1)) + ttx*(ttcy*u(ix+1,iy,iz+1,iw+1) + tty*u(ix+1,iy+1,iz+1,iw+1));
	uu1 = ttcz*u0 + ttz*u1;

    return ttcw*uu0 + ttw*uu1;
}

/***********************************************************/
/***********************************************************/

static double QuadCubicCore(
    const FAArray4Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
    const FAArray1Ref<double>& w,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
    int nwlow,
    int nwhi,
	int indexx,
	int indexy,
	int indexz,
	int indexw,
	double ttx,
	double tty,
	double ttz,
	double ttw,
	FAArray1Ref<double>& ux,
	FAArray1Ref<double>& uy,
	FAArray1Ref<double>& uz
    )
{
    double ans;
	double ttcx,Deltax,Deltamx,Deltapx;
	double ttcy,Deltay,Deltamy,Deltapy;
	double ttcz,Deltaz,Deltamz,Deltapz;
	double ttcw,Deltaw,Deltamw,Deltapw;
	char ErrorMsgx[] = "Cubic: Error - The interval between interpolation points is 0.";
	char ErrorMsgy[] = "Cubic: Error - The interval between interpolation points is 0.";
	char ErrorMsgz[] = "Cubic: Error - The interval between interpolation points is 0.";
	char ErrorMsgw[] = "Cubic: Error - The interval between interpolation points is 0.";
	double fpp,fp0,fpm,fpp0,fpp1;

	if (indexy>nylow && (nyhi-nylow)>=3 && indexy<nyhi-1) {
		ttcy = 1. - tty;
		// cubic correction
		Deltamy = y(indexy) - y(indexy-1);
		Deltay  = y(indexy+1) - y(indexy);
		Deltapy = y(indexy+2) - y(indexy+1);
		if (Deltamy==0. || Deltay==0. || Deltapy==0) {
			throw new FAErrorException(ErrorMsgy,InterpolationDeltaError);
		}
	}
	
	if (indexz>nzlow && (nzhi-nzlow)>=3 && indexz<nzhi-1) {
		ttcz = 1. - ttz;
		// cubic correction
		Deltamz = z(indexz) - z(indexz-1);
		Deltaz  = z(indexz+1) - z(indexz);
		Deltapz = z(indexz+2) - z(indexz+1);
		if (Deltamz==0. || Deltaz==0. || Deltapz==0) {
			throw new FAErrorException(ErrorMsgz,InterpolationDeltaError);
		}
	}

	if (indexw>nwlow && (nwhi-nwlow)>=3 && indexw<nwhi-1) {
		ttcw = 1. - ttw;
		// cubic correction
		Deltamw = w(indexw) - w(indexw-1);
		Deltaw  = w(indexw+1) - w(indexw);
		Deltapw = w(indexw+2) - w(indexw+1);
		if (Deltamw==0. || Deltaw==0. || Deltapw==0) {
			throw new FAErrorException(ErrorMsgw,InterpolationDeltaError);
		}
	}

	int ilow,ihi,jlow,jhi,klow,khi;

	if (indexz<=nzlow || (nzhi-nzlow)<3 || indexz>=nzhi-1){
		klow=indexz; khi=indexz+1;
	}
	else {
		klow=indexz-1; khi=indexz+2;
	}

	if (indexy<=nylow || (nyhi-nylow)<3 || indexy>=nyhi-1){
		jlow=indexy; jhi=indexy+1;
	}
	else {
		jlow=indexy-1; jhi=indexy+2;
	}

	if (indexx<=nxlow || (nxhi-nxlow)<3 || indexx>=nxhi-1){
		ilow=indexx; ihi=indexx+1;
	}
	else {
		ilow=indexx-1; ihi=indexx+2;
	}
	
	for (int i=ilow; i<=ihi; i++){
		for (int j=jlow; j<=jhi; j++){
			for (int k=klow; k<=khi; k++) {
				// linear piece
				uz(k) = u(i,j,k,indexw) + ttw*(u(i,j,k,indexw+1) - u(i,j,k,indexw));
				if (indexw<=nwlow || (nwhi-nwlow)<3 || indexw>=nwhi-1) continue;
		
				fpm = (u(i,j,k,indexw) - u(i,j,k,indexw-1))/Deltamw;
				fp0 = (u(i,j,k,indexw+1) - u(i,j,k,indexw))/Deltaw;
				fpp = (u(i,j,k,indexw+2) - u(i,j,k,indexw+1))/Deltapw;
				fpp0 =  2.0*(fp0 - fpm) / (Deltaw + Deltamw);
				fpp1 =  2.0*(fpp - fp0) / (Deltapw + Deltaw);
				uz(k) += (ttcw*(ttcw*ttcw-1.)*fpp0 + ttw*(ttw*ttw-1.)*fpp1)*Deltaw*Deltaw/6.;
			}

			// linear piece
			uy(j) = uz(indexz) + ttz*(uz(indexz+1) - uz(indexz));
			if (indexz<=nzlow || (nzhi-nzlow)<3 || indexz>=nzhi-1) continue;
		
			fpm = (uz(indexz) - uz(indexz-1))/Deltamz;
			fp0 = (uz(indexz+1) - uz(indexz))/Deltaz;
			fpp = (uz(indexz+2) - uz(indexz+1))/Deltapz;
			fpp0 =  2.0*(fp0 - fpm) / (Deltaz + Deltamz);
			fpp1 =  2.0*(fpp - fp0) / (Deltapz + Deltaz);
			uy(j) += (ttcz*(ttcz*ttcz-1.)*fpp0 + ttz*(ttz*ttz-1.)*fpp1)*Deltaz*Deltaz/6.;
		}

		// linear piece
		ux(i) = uy(indexy) + tty*(uy(indexy+1) - uy(indexy));
		if (indexy<=nylow || (nyhi-nylow)<3 || indexy>=nyhi-1) continue;

	    fpm = (uy(indexy) - uy(indexy-1))/Deltamy;
		fp0 = (uy(indexy+1) - uy(indexy))/Deltay;
	    fpp = (uy(indexy+2) - uy(indexy+1))/Deltapy;
		fpp0 =  2.0*(fp0 - fpm) / (Deltay + Deltamy);
		fpp1 =  2.0*(fpp - fp0) / (Deltapy + Deltay);
	    ux(i) += (ttcy*(ttcy*ttcy-1.)*fpp0 + tty*(tty*tty-1.)*fpp1)*Deltay*Deltay/6.;
	}

    // linear piece
    ans = ux(indexx) + ttx*(ux(indexx+1) - ux(indexx));
    if (indexx<=nxlow || (nxhi-nxlow)<3 || indexx>=nxhi-1) return ans;

    ttcx = 1. - ttx;
    // cubic correction
    Deltamx = x(indexx) - x(indexx-1);
    Deltax  = x(indexx+1) - x(indexx);
    Deltapx = x(indexx+2) - x(indexx+1);
    if (Deltamx==0. || Deltax==0. || Deltapx==0) {
        throw new FAErrorException(ErrorMsgx,InterpolationDeltaError);
    }
    fpm = (ux(indexx) - ux(indexx-1))/Deltamx;
    fp0 = (ux(indexx+1) - ux(indexx))/Deltax;
    fpp = (ux(indexx+2) - ux(indexx+1))/Deltapx;
    fpp0 =  2.0*(fp0 - fpm) / (Deltax + Deltamx);
    fpp1 =  2.0*(fpp - fp0) / (Deltapx + Deltax);
    ans += (ttcx*(ttcx*ttcx-1.)*fpp0 + ttx*(ttx*ttx-1.)*fpp1)*Deltax*Deltax/6.;
    return ans;
}

/***********************************************************/
/***********************************************************/

static double QuadCubic(
    const FAArray4Ref<double>& u,
    const FAArray1Ref<double>& x,
    const FAArray1Ref<double>& y,
    const FAArray1Ref<double>& z,
    const FAArray1Ref<double>& w,
    double xint,
    double yint,
    double zint,
	double wint,
    int nxlow,
    int nxhi,
    int nylow,
    int nyhi,
    int nzlow,
    int nzhi,
    int nwlow,
    int nwhi,
    double uniformdx,
    double uniformdy,
    double uniformdz,
    double uniformdw,
    int extrap
    )
{
	double ans;
    // single data point
    if (nxlow==nxhi && nylow==nyhi && nzlow==nzhi && nwlow==nwhi) {
        return u(nxlow,nylow,nzlow,nwlow);
    }
	
	// precalculation in X direction
    int indexx,locx,ascendx;
    double ttx;
    char ErrorMsgx[] = "Cubic: Error - The interval between interpolation points is 0.";
    // locate point just to the left and compute interval fraction
    locx = nxlow;
    ascendx = x(nxhi)>=x(nxlow);
    ComputeIntervalFraction(x,uniformdx,xint,nxlow,nxhi,ascendx,extrap,&locx,&indexx,&ttx,ErrorMsgx);

	// precalculation in Y direction
	int indexy,locy,ascendy;
	double tty;
	char ErrorMsgy[] = "Cubic: Error - The interval between interpolation points is 0.";
    // locate point just to the left and compute interval fraction
	locy = nylow;
	ascendy = y(nyhi)>=y(nylow);
	ComputeIntervalFraction(y,uniformdy,yint,nylow,nyhi,ascendy,extrap,&locy,&indexy,&tty,ErrorMsgy);

	// precalculation in Z direction
	int indexz,locz,ascendz;
	double ttz;
	char ErrorMsgz[] = "Cubic: Error - The interval between interpolation points is 0.";
    // locate point just to the left and compute interval fraction
	locz = nzlow;
	ascendz = z(nzhi)>=z(nzlow);
	ComputeIntervalFraction(z,uniformdz,zint,nzlow,nzhi,ascendz,extrap,&locz,&indexz,&ttz,ErrorMsgz);

	// precalculation in W direction
	int indexw,locw,ascendw;
	double ttw;
	char ErrorMsgw[] = "Cubic: Error - The interval between interpolation points is 0.";
    // locate point just to the left and compute interval fraction
	locw = nwlow;
	ascendw = w(nwhi)>=w(nwlow);
	ComputeIntervalFraction(w,uniformdw,wint,nwlow,nwhi,ascendw,extrap,&locw,&indexw,&ttw,ErrorMsgw);

	FAArray1<double> uz(z.size0());
	FAArray1<double> uy(y.size0());
	FAArray1<double> ux(x.size0());
	
	ans = QuadCubicCore(u,x,y,z,w,nxlow,nxhi,nylow,nyhi,nzlow,nzhi,nwlow,nwhi,indexx,indexy,indexz,indexw,ttx,tty,ttz,ttw,ux,uy,uz);
	return ans;
}

/***********************************************************/
/***********************************************************/

#endif
