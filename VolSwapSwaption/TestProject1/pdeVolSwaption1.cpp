/* RKS/pdeVolSwaption1.s

   
(* pdeVolSwaption1.s *)

PDE[];  CrankNicholson;
Region[xMin<=x1<=xMax && xMin<=x2<=xMax && yMin<=y<=yMax && 0<=tau<=TMax,
       GeneralCoordinates[{x1,x2,y},tau]];
       OldCoordinates[{{S,Sp,vari},t}];
       S==Spot Exp[x1];  
       Sp==Spot Exp[x2];
       vari==variBar Sinh[y];
       t==tau;

When[Interior, BlackScholes1D[]];
When[Boundary, AutomaticBC; OneSidedDifference[1]];
When[max[tau], V==payoff];
vol==Sqrt[A vari];
payoff==Max[vol - K, 0];

(* simple CEV-style local vol *)
sigma==sigma0 (S/S0)^(beta-1);
sigmatyp==sigma0;

DiscreteEvents[
     Exercise[functions[{if[t>=FirstExDate, V>=payoff]}],
          tsample==RDates],
     Path[direction[Sp], function[Sp==SumOf[S-Sp]],
          tsample==RDates, InterpolateLinear],
     Path[direction[vari], function[vari==SumOf[
              ((S/Sp-1)^2 - vari) / (iret+nsampSoFar)]],
          tsample==RDates, CubicSpline]];
ReadArray[RDates, {iret,1,nsampToGo}, "RDates.dat"];

Default[TaggedInputFile["volswap.dat"]];
Output[V, "atSpot.out", CubicSpline,
       S==Spot && Sp==Sp0 && vari==vari0];

ReadOrCompute[{xMin,xMax,yMin,yMax}];
    stddevs==Max[4 sigmatyp Sqrt[TMax], 0.1];
    xMin==-stddevs - r TMax;
    xMax== stddevs + D0 TMax;
    variBar==sigmatyp^2/A;
    yMin==0;
    yMax==2;
ReadOrCompute[{iMax,kMax,nMax}];
    delx==Min[xMax-xMin,4]/100;
    iMax0==Round[(xMax-xMin)/delx];
    ndiff==Round[(sigmatyp/delx)^2 TMax /10];
    nconv==Round[2 Abs[r-D0]/delx TMax];
    nMax0==Max[40, Max[ndiff, nconv]];
    kMax0==20;
    iMax==Round[iMax0 Sqrt[Accuracy]];
    kMax==Round[kMax0 Sqrt[Accuracy]];
    nMax==Max[Round[nMax0 Sqrt[Accuracy]],2 nsampToGo];
GridSize[{{iMax,iMax,kMax},nMax}];
MInteger[{nsampTot,nsampSoFar}];
nsampTot==nsampToGo+nsampSoFar;
A==(nsampTot/TContract);
TMax==RDates[nsampToGo];


  Macros expanded by specification were: 
    RKS/PDE.s
(* :HelpText: PDE[] is a specification macro that invokes a
    collection of specifications frequently used in generating 
    option pricing models in C.*)
(* :HelpLongText: We set the default memory allocation method 
    to DynamicAllocation, the default solver to TriDiagonal, 
    and the default time evolution algorithm to EvolveFixed.
    We specify that time should run backwards, that Microsoft
    C is the target language, and that double precision is to
    be used for all real numbers.  We suppress tensor order
    and physical units checking to reduce synthesis time. *)
(* :FileName: PDE.s *)

BeginAtFinalTime;
NoTensorOrderChecks;
NoUnitChecks;
Default[EvolveFixed, DynamicAllocation, msC];
AllDouble;

    RKS/BlackScholes1D.eqn
(* :FileName: BlackScholes1D.eqn *)
(* :HelpText: Equation Generator for the 1D Black-Scholes  Equation with greeks *)
(* :HelpLongText:  The equation generator for the 1D Black-Scholes Equation for option valuation, and optionally, equations for the greeks Vega and Rho.  (Delta, Gamma, and Theta can be derived by differentiation of value V.)  See Paul Wilmott, Jeff Dewynne, Sam Howison,  "Option Pricing"   Oxford Financial Press, 1993. *)

(*
   der[V,t] + (1/2)sigma^2 S^2 der[V,{S,2}] +
                            (r-D0) S der[V,S] - r V == 0

   in price (S) coordinates and backward time (t).  

   Defines the variables:
   Variable[V,     Scalar, Dollars,      "option value"];
   Variable[sigma, Scalar, Time^(-1/2),  "volatility"];
   Variable[r,     Scalar, Time^(-1),    "interest rate"];
   Variable[D0,    Scalar, Time^(-1),    
                   "continuous dividend yield"]; *)

(* :HelpSyntax: BlackScholes1D[] | BlackScholes1D[Keywords->{<subset of {Vega,Rho}>}, <var>->value] *)
(* :HelpExamples:
    BlackScholes1D[Keywords->{Vega,Rho}]
    BlackScholes1D[D0->0]
    BlackScholes1D[Keywords->{Vega,Rho}, D0->0] *)

PhysicalMeaning[S,Dollars];

(* Create the Dependent Variables *)
   Variable[V,     Scalar, Dollars,      "option value"];
   Variable[sigma, Scalar, Time^(-1/2),  "volatility"];
   Variable[r,     Scalar, Time^(-1),    "interest rate"];
   Variable[D0,    Scalar, Time^(-1),    
                   "continuous dividend yield"];

(* Create and name Black-Scholes Equation for option value V *)
   Equation[der[V,t] + (1/2)sigma^2 S^2 der[V,{S,2}] +
                               (r-D0) S der[V,S] - r V == 0,
     BuildSymbol[V,"Eqn"]];

 (* Create and name the equation for Vega=der[V,sigma] *)
   IsAKeyWord[Vega,
       Variable[Vega, Scalar, Dollars Time^(1/2), "Vega"];
       Equation[Greek[BuildSymbol[V, "Eqn"],{Vega,der[V,sigma]}],
       BuildSymbol[Vega,"Eqn"]];
       (* Create and name the equation for Volga=der[Vega,sigma] *)
       IsAKeyWord[Volga,
           Variable[Volga, Scalar, Dollars Time^(1/2), "Volga"];
           Equation[Greek[BuildSymbol[Vega, "Eqn"],{Volga,der[Vega,sigma]}],
           BuildSymbol[Volga,"Eqn"]]
   ]];

 (* Create and name the equation for Volga=der[Vega,sigma]
   IsAKeyWord[Volga,
       Variable[Volga, Scalar, Dollars Time^(1/2), "Volga"];
       Equation[Greek[BuildSymbol[Vega, "Eqn"],{Volga,der[Vega,sigma]}],
       BuildSymbol[Volga,"Eqn"]]
   ]; *)

(* Create and name the equation for Rho=der[V,r] *)
   IsAKeyWord[Rho,
       Variable[Rho, Scalar, Dollars Time, "Rho"];
       Equation[Greek[BuildSymbol[V, "Eqn"],{Rho,der[V,r]}],
       BuildSymbol[Rho,"Eqn"]]
   ];

(* Create and name the equation for RhoD=der[V,D0] *)
   IsAKeyWord[RhoD,
       Variable[RhoD, Scalar, Dollars Time, "RhoD"];
       Equation[Greek[BuildSymbol[V, "Eqn"],{RhoD,der[V,D0]}],
        BuildSymbol[RhoD,"Eqn"]]
   ];

 */

/**************  ARRAY FORMAT INSTRUCTIONS **************

Please use the following information to check carefully the formats
  of your arrays.  Although all arrays are dimensioned from 0,
  ReadArray arrays are filled from 0 unless specified otherwise.
  ReadFile arrays are filled from 1; ReadTable arrays, from 0.
  ReadTable files contain a maximum *index* (not number of items) count.

If you modify the code to input arrays directly, please check
  that the initializations fill from 0 or 1 as appropriate.

                          ****

   The table for RDates in file "RDates.dat" has maximum index
      nsampToGo, 
     with minimum index 1.
      The index bounds are not read from this file.
        Following should be the nsampToGo elements,
      to be stored in RDates(1..nsampToGo).


******************* END FORMAT INSTRUCTIONS *******************/


#include "FACommonLib.h"
#include "FAArrayN.h"
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "FAInterpLib.h"
#include "TaggedInput.h"

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
#define BrentConvergenceFailure 39
#define MCFAOldSobolOverflow 40
#define MCFASobolOverflow2 38
#define FANormalFlag 0
#define MaxErrorLength 128
#define MaxMessages 10
/* Define macro to check errors on opening file for writing */
#undef openfilepdeVolSwaption1MW
#define openfilepdeVolSwaption1MW(stream, file) \
   (stream) = fopen((file), "w");\
   if ((stream) == NULL)\
       {\
	throw new FAFileException(FileOpenError, "%s%s%s",\
	"Cannot open file ", (file), " for writing.");\
       }

/* Define macro to check errors on opening file for reading */
#undef openfilepdeVolSwaption1MR
#define openfilepdeVolSwaption1MR(stream, file) \
   (stream) = fopen((file), "r");\
   if ((stream) == NULL)\
       {\
	throw new FAFileException(FileOpenError, "%s%s%s",\
	"Cannot open file ", (file), " for reading.");\
       }

/* Define macro to check errors on reading input line */
#undef fscanf$pdeVolSwaption1M
#define fscanf$pdeVolSwaption1M(file, format, numvars, vars) \
   if (fscanf((file), (format), spreadargs##numvars vars) != (numvars))\
       {\
        throw new FAErrorException(fscanfError, \
            "%s%s%s%s\n","Input error while reading ", #vars,\
              " from ", #file);\
       }


#undef spreadargs1
#define spreadargs1(a1) a1


static void ComputeIndStencils1(
    double D0,
    double dx1,
    int iMax,
    const FAArray1Ref<double>& J11,
    int kMax,
    double r,
    const FAArray1Ref<double>& S,
    FAArray2Ref<double>& SA0,
    FAArray2Ref<double>& SB0,
    const FAArray1Ref<double>& sigma
    );
static void ComputeStencils1(
    double dtau,
    double dtaum1,
    int iMax,
    int kMax,
    FAArray2Ref<double>& SA,
    const FAArray2Ref<double>& SA0,
    FAArray2Ref<double>& SB,
    const FAArray2Ref<double>& SB0
    );
static void CreateGrids1(
    double dx1,
    double dx2,
    double dy,
    int iMax,
    int kMax,
    FAArray1Ref<double>& S,
    FAArray1Ref<double>& Sp,
    double Spot,
    FAArray1Ref<double>& vari,
    double variBar,
    double xMin,
    double yMin
    );
static int CRound(
    double delx
    );
static int pdeVolSwaption1fn(
    double Accuracy,
    double beta,
    double D0,
    double FirstExDate,
    int iMax,
    double K,
    int kMax,
    int nMax,
    int nsampSoFar,
    int nsampToGo,
    double r,
    FAArray1Ref<double>& RDates,
    double S0,
    double sigma0,
    double Sp0,
    double Spot,
    double TContract,
    double vari0,
    double xMax,
    double xMin,
    double yMax,
    double yMin,
    double *VOutp
    );
static int pdeVolSwaption1fnC(
    double Accuracy,
    double beta,
    double D0,
    double FirstExDate,
    int iMax,
    double K,
    int kMax,
    int nMax,
    int nsampSoFar,
    int nsampToGo,
    double r,
    double *RDatesC,
    double S0,
    double sigma0,
    double Sp0,
    double Spot,
    double TContract,
    double vari0,
    double xMax,
    double xMin,
    double yMax,
    double yMin,
    double *VOutp
    );
static void SetDateIndices1(
    const FAArray1Ref<double>& RDates,
    FAArray1Ref<double>& RDates1,
    int nsampToGo,
    int *iretminp,
    int *nsampToGo1p,
    double TMax,
    double ttest,
    int arraymin
    );
static void TriDiag(
    const FAArray3Ref<double>& g,
    const FAArray2Ref<double>& SA,
    FAArray3Ref<double>& V,
    int iMax,
    int kMax,
    FAArray1Ref<double>& TriTa,
    FAArray1Ref<double>& TriTb
    );
static void ValidateArraySorted1(
    const FAArray1Ref<double>& RDates,
    int nsampToGo
    );
static void VectorMatrixMultiply4(
    const FAArray2Ref<double>& SB,
    const FAArray3Ref<double>& V,
    FAArray3Ref<double>& g,
    int iMax,
    int kMax
    );

int main()
{
    int iMax,itvar1,kMax,nMax,nsampSoFar,nsampToGo;
    double Accuracy,beta,D0,FirstExDate,K,r,S0,sigma0,Sp0,Spot,TContract
       ,vari0,VOut,xMax,xMin,yMax,yMin;
    FILE *IOUNIT,*IOUNIT1,*IOUNIT2;
    ArgumentRecord volswapInputTable[21];
    
    /* *** Key to program variables: *** */
    /* Accuracy, beta, FirstExDate, K, nsampSoFar, RDates, S0, sigma0,  
       Sp0, Spot, TContract, vari0: solution variable */
    /* D0: continuous dividend yield */
    /* iMax: number of grid cells for x2 */
    /* IOUNIT, IOUNIT1, IOUNIT2: I/O channel */
    /* kMax: number of grid cells for y */
    /* nMax: number of grid cells for tau */
    /* nsampToGo: array maximum for RDates */
    /* r: interest rate */
    /* VOut: interpolated value of VOut (option value)  */
    /* xMax: maximum physical value in dimension x2 */
    /* xMin: minimum physical value in dimension x2 */
    /* yMax: maximum physical value in dimension y */
    /* yMin: minimum physical value in dimension y */
    try {
    /* Read Tagged Input File */
    openfilepdeVolSwaption1MR(IOUNIT1,"volswap.dat");
    setupargs(volswapInputTable, 0, 
       "Accuracy", Accuracy, READINPUTSDOUBLE);
    setupargs(volswapInputTable, 1, "beta", beta, READINPUTSDOUBLE);
    setupargs(volswapInputTable, 2, "D0", D0, READINPUTSDOUBLE);
    setupargs(volswapInputTable, 3, 
       "FirstExDate", FirstExDate, READINPUTSDOUBLE);
    setupargs(volswapInputTable, 4, "iMax", iMax, READINPUTSINTEGER);
    setupargs(volswapInputTable, 5, "K", K, READINPUTSDOUBLE);
    setupargs(volswapInputTable, 6, "kMax", kMax, READINPUTSINTEGER);
    setupargs(volswapInputTable, 7, "nMax", nMax, READINPUTSINTEGER);
    setupargs(volswapInputTable, 8, 
       "nsampSoFar", nsampSoFar, READINPUTSINTEGER);
    setupargs(volswapInputTable, 9, 
       "nsampToGo", nsampToGo, READINPUTSINTEGER);
    setupargs(volswapInputTable, 10, "r", r, READINPUTSDOUBLE);
    setupargs(volswapInputTable, 11, "S0", S0, READINPUTSDOUBLE);
    setupargs(volswapInputTable, 12, 
       "sigma0", sigma0, READINPUTSDOUBLE);
    setupargs(volswapInputTable, 13, "Sp0", Sp0, READINPUTSDOUBLE);
    setupargs(volswapInputTable, 14, "Spot", Spot, READINPUTSDOUBLE);
    setupargs(volswapInputTable, 15, 
       "TContract", TContract, READINPUTSDOUBLE);
    setupargs(volswapInputTable, 16, "vari0", vari0, READINPUTSDOUBLE);
    setupargs(volswapInputTable, 17, "xMax", xMax, READINPUTSDOUBLE);
    setupargs(volswapInputTable, 18, "xMin", xMin, READINPUTSDOUBLE);
    setupargs(volswapInputTable, 19, "yMax", yMax, READINPUTSDOUBLE);
    setupargs(volswapInputTable, 20, "yMin", yMin, READINPUTSDOUBLE);
    if (ReadInputs(IOUNIT1,volswapInputTable,21)!=0)
        {
        fclose(IOUNIT1);
        throw new FAErrorException(		
           "ReadInput failed",TaggedInputError);
        }
    fclose(IOUNIT1);
    /* Read RDates from file */
    FAArray1<double>RDates(nsampToGo + 1);
    if (nsampToGo>=1)
        {
        openfilepdeVolSwaption1MR(IOUNIT2,"RDates.dat");
        for (itvar1=1; itvar1<=nsampToGo; itvar1++) {
            fscanf$pdeVolSwaption1M(IOUNIT2,
               "%lg",1,((&RDates(itvar1))));
        }
        fclose(IOUNIT2);
        }
    /*                            */
    /* Call the computation function. */
    pdeVolSwaption1fnC(Accuracy,beta,D0,FirstExDate,iMax,K,kMax,nMax,
       nsampSoFar,nsampToGo,r,RDates.array(),S0,sigma0,Sp0,Spot,
       TContract,vari0,xMax,xMin,yMax,yMin,&VOut);
    /*                            */
    /* Writing collected output to file atSpot.out from ResultEqc. */
    openfilepdeVolSwaption1MW(IOUNIT,"atSpot.out");
    fprintf(IOUNIT, " %18.8e\n", VOut);
    fprintf(IOUNIT, "\n");
    fclose(IOUNIT);
    return 0;
    /* end try */
    }
    catch(FAErrorException* ex1)
	{
	// Handle exceptions thrown by SF core code
	printf
       (
       "%s\n"
       , ex1->getMessage());
	int rc = ex1->getErrorType();
	delete ex1;
       
	return rc;
	}
    catch(FAException* ex2)
	{
	// Handle any exceptions thrown by call-backs
	printf
       ("%s\n", ex2->getMessage());
	delete ex2;
	return -1;
	}
    return 0;
}

static int pdeVolSwaption1fnC(
    double Accuracy,
    double beta,
    double D0,
    double FirstExDate,
    int iMax,
    double K,
    int kMax,
    int nMax,
    int nsampSoFar,
    int nsampToGo,
    double r,
    double *RDatesC,
    double S0,
    double sigma0,
    double Sp0,
    double Spot,
    double TContract,
    double vari0,
    double xMax,
    double xMin,
    double yMax,
    double yMin,
    double *VOutp
    )
{
    
    /* *** Key to program variables: *** */
    /* Accuracy, beta, FirstExDate, K, nsampSoFar, RDates, S0, sigma0,  
       Sp0, Spot, TContract, vari0: solution variable */
    /* D0: continuous dividend yield */
    /* iMax: number of grid cells for x2 */
    /* kMax: number of grid cells for y */
    /* nMax: number of grid cells for tau */
    /* nsampToGo: array maximum for RDates */
    /* r: interest rate */
    /* VOutp: interpolated value of VOut (option value)  */
    /* xMax: maximum physical value in dimension x2 */
    /* xMin: minimum physical value in dimension x2 */
    /* yMax: maximum physical value in dimension y */
    /* yMin: minimum physical value in dimension y */
    FAArray1Ref<double> RDates(RDatesC, nsampToGo + 1);
    /* Call FAArray C++ Spreadsheet function  */
    pdeVolSwaption1fn(Accuracy,beta,D0,FirstExDate,iMax,K,kMax,nMax,
       nsampSoFar,nsampToGo,r,RDates,S0,sigma0,Sp0,Spot,TContract,vari0,
       xMax,xMin,yMax,yMin,VOutp);
    return 1;
}

static int pdeVolSwaption1fn(
    double Accuracy,
    double beta,
    double D0,
    double FirstExDate,
    int iMax,
    double K,
    int kMax,
    int nMax,
    int nsampSoFar,
    int nsampToGo,
    double r,
    FAArray1Ref<double>& RDates,
    double S0,
    double sigma0,
    double Sp0,
    double Spot,
    double TContract,
    double vari0,
    double xMax,
    double xMin,
    double yMax,
    double yMin,
    double *VOutp
    )
{
    int i,iMax0,iretmin,isamp1,j,k1,n,nconv,ndiff,nsampToGo1,nsampTot;
    double A,delx,dtau,dtaum1,dx1,dx2,dy,eps,kMax0,nMax0,savedt,sigmatyp
       ,stddevs,tau,temp15,temp16,temp17,temp21,tend,TMax,ttest,variBar,
       VOut;
    
    /* *** Key to program variables: *** */
    /* A, Accuracy, beta, delx, FirstExDate, iMax0, J11, K, kMax0,      
       nconv, ndiff, nMax0, nsampSoFar, nsampTot, payoff, RDates, S, S0,
       sigma0, sigmatyp, slicetmp1, Sp, Sp0, Spot, stddevs, TContract,  
       vari, vari0, variBar, vol: solution variable */
    /* D0: continuous dividend yield */
    /* dtau: step size for tau */
    /* dtaum1: value for dtau 1 time steps ago */
    /* dx1: step size for x1 */
    /* dx2: step size for x2 */
    /* dy: step size for y */
    /* eps: machine epsilon */
    /* fpp1, fpp4: second derivative temporary array */
    /* g: right hand side of the linear system; the y in Ax=y. */
    /* i: index variable for x1 */
    /* iMax: number of grid cells for x2 */
    /* iretmin: Minimum of Exercise array */
    /* isamp1: Index for Path array */
    /* j: index variable for x2 */
    /* k1: index variable for y */
    /* kMax: number of grid cells for y */
    /* n: index variable for tau */
    /* nMax: number of grid cells for tau */
    /* nsampToGo: array maximum for RDates */
    /* nsampToGo1: Maximum of Exercise array */
    /* r: interest rate */
    /* RDates1: Auxiliary array for Exercise sample array */
    /* SA: stencil array of the system; the A in Ax=y. */
    /* SA0: part of SA that is proportional to dt. */
    /* savedt: saved value of dt */
    /* SB: coefficients for right hand side of the linear system */
    /* SB0: part of SB that is proportional to dt */
    /* sigma: volatility */
    /* tau: time variable */
    /* temp15, temp16, temp17, temp21: common subexpression temporary */
    /* tend: time to save results */
    /* TMax: minimum physical value in dimension tau */
    /* TriT1i1, TriT1j1, TriT1k11, TriT2i1, TriT2j1, TriT2k11: spline   
       temporary array */
    /* TriTa, TriTb: temporary, same size as diagonal */
    /* ttest: minimal size test */
    /* V: option value */
    /* VOut, VOutp: interpolated value of VOut (option value)  */
    /* xMax: maximum physical value in dimension x2 */
    /* xMin: minimum physical value in dimension x2 */
    /* xnew, xnew1: updated var */
    /* yi1, yi2: adjusted for discrete events */
    /* yMax: maximum physical value in dimension y */
    /* yMin: minimum physical value in dimension y */
    /* Compute machine epsilon. */
    eps = 1.;
    while (1.!=eps + 1.) {
        eps = eps*0.5;
    }
    eps = eps*2.;
    kMax0 = 20.;
    /* Initialize geometric parameter */
    if (kMax==-999)
        {
        kMax = CRound(sqrt(Accuracy)*kMax0);
        }
    if (yMax==-999.)
        {
        yMax = 2.;
        }
    if (yMin==-999.)
        {
        yMin = 0.;
        }
    TMax = RDates(nsampToGo);
    /* Compute the value for nsampTot; formula is nsampTot == nsampSoFar
       + nsampToGo; discretization methods are Implicit[1/2] and        
       CentralSpaceDifference[2]; truncation error is 0; Eq23c. */
    nsampTot = nsampSoFar + nsampToGo;
    /* Compute the value for A; formula is A == nsampTot/TContract;     
       discretization methods are Implicit[1/2] and                     
       CentralSpaceDifference[2]; truncation error is 0; Eq24c. */
    A = nsampTot / TContract;
    sigmatyp = sigma0;
    FAArray1<double>xnew1(kMax + 1);
    FAArray1<double>yi2(kMax + 1);
    FAArray1<double>fpp4(kMax + 1);
    FAArray1<double>TriT1k11(kMax + 1);
    FAArray1<double>TriT2k11(kMax + 1);
    FAArray1<double>vari(kMax + 1);
    /* Initialize step size */
    dy = (yMax - yMin) / (double)(kMax);
    dtaum1 = TMax;
    ttest = max(fabs(TMax),0.)*max(eps*100.,1.e-12);
    FAArray1<double>RDates1(nsampToGo + 1);
    ValidateArraySorted1(RDates,nsampToGo);
    SetDateIndices1(RDates,RDates1,nsampToGo,&iretmin,&nsampToGo1,TMax,
       ttest,1);
    /* Compute the value for stddevs; formula is stddevs == Max[0.1,    
       4*sigmatyp*Sqrt[TMax]]; discretization methods are Implicit[1/2] 
       and CentralSpaceDifference[2]; truncation error is 0; Eq8c. */
    stddevs = max(4*sigmatyp*sqrt(TMax),0.1);
    /* Compute the value for variBar; formula is variBar ==             
       sigmatyp^2/A; discretization methods are Implicit[1/2] and       
       CentralSpaceDifference[2]; truncation error is 0; Eq11c. */
    variBar = (sigmatyp*sigmatyp) / A;
    /* Initialize geometric parameter */
    if (xMax==-999.)
        {
        xMax = stddevs + D0*TMax;
        }
    if (xMin==-999.)
        {
        xMin = -stddevs - r*TMax;
        }
    /* Compute the value for delx; formula is delx == Min[4, xMax -     
       xMin]/100; discretization methods are Implicit[1/2] and          
       CentralSpaceDifference[2]; truncation error is 0; Eq14c. */
    delx = min(xMax - xMin,4.) / 100.;
    /* Compute the value for iMax0; formula is iMax0 == CRound[(xMax -  
       xMin)/delx]; discretization methods are Implicit[1/2] and        
       CentralSpaceDifference[2]; truncation error is 0; Eq15c. */
    iMax0 = CRound((xMax - xMin) / delx);
    /* Initialize geometric parameter */
    if (iMax==-999)
        {
        iMax = CRound(sqrt(Accuracy)*iMax0);
        }
    temp21 = (xMax - xMin) / (double)(iMax);
    /* Compute the value for nconv; formula is nconv ==                 
       CRound[(2*TMax*Abs[D0 - r])/delx]; discretization methods are    
       Implicit[1/2] and CentralSpaceDifference[2]; truncation error is 
       0; Eq17c. */
    nconv = CRound((2*TMax*fabs(D0 - r)) / delx);
    /* Compute the value for ndiff; formula is ndiff ==                 
       CRound[(sigmatyp^2*TMax)/(10*delx^2)]; discretization methods are
       Implicit[1/2] and CentralSpaceDifference[2]; truncation error is 
       0; Eq16c. */
    ndiff = CRound((sigmatyp*sigmatyp*TMax) / (10.*delx*delx));
    FAArray3<double>g(iMax + 1, iMax + 1, kMax + 1);
    FAArray2<double>SA(iMax + 1, 3);
    FAArray2<double>SA0(iMax + 1, 3);
    FAArray2<double>SB(iMax + 1, 3);
    FAArray2<double>SB0(iMax + 1, 3);
    FAArray1<double>slicetmp1(iMax + 1);
    FAArray1<double>TriTa(iMax + 1);
    FAArray1<double>TriTb(iMax + 1);
    FAArray1<double>xnew(iMax + 1);
    FAArray1<double>yi1(iMax + 1);
    /* Initialize step size */
    dx1 = temp21;
    dx2 = temp21;
    FAArray3<double>fpp1(iMax + 1, iMax + 1, kMax + 1);
    FAArray1<double>Sp(iMax + 1);
    FAArray1<double>TriT1i1(iMax + 1);
    FAArray1<double>TriT1j1(iMax + 1);
    FAArray1<double>TriT2i1(iMax + 1);
    FAArray1<double>TriT2j1(iMax + 1);
    FAArray3<double>V(iMax + 1, iMax + 1, kMax + 1);
    /* Compute the value for nMax0; formula is nMax0 == Max[40, nconv,  
       ndiff]; discretization methods are Implicit[1/2] and             
       CentralSpaceDifference[2]; truncation error is 0; Eq18c. */
    nMax0 = max((double)(max(nconv,40)),(double)(ndiff));
    /* Initialize geometric parameter */
    if (nMax==-999)
        {
        nMax = max(2*nsampToGo,CRound(sqrt(Accuracy)*nMax0));
        }
    /* Initialize step size */
    dtau = -(TMax / (double)(nMax));
    FAArray1<double>S(iMax + 1);
    /* Initialize coordinate arrays for S, Sp, vari */
    CreateGrids1(dx1,dx2,dy,iMax,kMax,S,Sp,Spot,vari,variBar,xMin,yMin);
    FAArray1<double>J11(iMax + 1);
    /* Compute the value for J11 on the interior; formula is J11 ==     
       der[S, {x1, 1}]; discretization methods are Explicit; truncation 
       error is Ord[dx1^2]; GCEq1. */
    for (i=0; i<=iMax - 1; i++) {
        J11(i) = (S(i + 1) - S(i)) / dx1;
    }
    FAArray1<double>vol(kMax + 1);
    /* Compute the value for vol on the interior; formula is vol ==     
       Sqrt[A*vari]; discretization methods are Implicit[1/2] and       
       CentralSpaceDifference[2]; truncation error is 0; Eq4c. */
    for (k1=0; k1<=kMax; k1++) {
        vol(k1) = sqrt(A*vari(k1));
    }
    FAArray1<double>payoff(kMax + 1);
    /* Compute the value for payoff on the interior; formula is payoff  
       == Max[0, -K + vol]; discretization methods are Implicit[1/2] and
       CentralSpaceDifference[2]; truncation error is 0; Eq5c. */
    for (k1=0; k1<=kMax; k1++) {
        payoff(k1) = max(vol(k1) - K,0.);
    }
    FAArray1<double>sigma(iMax + 1);
    /* Compute the value for sigma on the interior; formula is sigma == 
       (S/S0)^(-1 + beta)*sigma0; discretization methods are            
       Implicit[1/2] and CentralSpaceDifference[2]; truncation error is 
       0; Eq6c. */
    for (i=0; i<=iMax; i++) {
        sigma(i) = sigma0*pow(S(i) / S0,beta - 1);
    }
    SplineForwardSweep(vari,0.,TriT1k11,TriT2k11,0,kMax);
    savedt = dtau;
    tau = TMax;
    /* Initialize local loop counter */
    n = 0;
    /* Initialize time-dependent equations */
    /* Initial value for V from IVEqc. */
    for (i=0; i<=iMax; i++) {
        for (k1=0; k1<=kMax; k1++) {
            for (j=0; j<=iMax; j++) {
                V(i,j,k1) = payoff(k1);
            }
        }
    }
    /* Reset discrete indexes. */
    isamp1 = nsampToGo1;
    /* Loop-independent part of: Take a time step. */
    ComputeIndStencils1(D0,dx1,iMax,J11,kMax,r,S,SA0,SB0,sigma);
    while (fabs(tau)>ttest) {
        tend = 0.;
        /* Discrete event initializations. */
        if (isamp1>=iretmin)
            {
            tend = max(tend,RDates1(isamp1));
            }
        while (fabs(tend - tau)>ttest) {
            dtau = max(savedt,tend - tau);
            /* Take a time step. */
            /* Interior discretization methods are CrankNicholson and   
               CentralSpaceDifference[2]. */
            /* Boundary discretization methods are CrankNicholson and   
               OneSidedDifference[1]. */
            /* Total truncation error is bounded by C*(dtau^2 + dx1 +   
               dx1^2). */
            ComputeStencils1(dtau,dtaum1,iMax,kMax,SA,SA0,SB,SB0);
            VectorMatrixMultiply4(SB,V,g,iMax,kMax);
            TriDiag(g,SA,V,iMax,kMax,TriTa,TriTb);
            /* Discrete event updates for DiscreteSystem1 on V. */
            /* update for Exercise[functions[if[(t >= FirstExDate), (V  
               >= payoff)]], tsample==RDates] */
            if ((isamp1>=iretmin&&dtau + tau>=FirstExDate&&fabs(RDates1(
               isamp1) - tend)<ttest&&fabs(tend - tau - dtau)<=ttest))
                {
                for (i=0; i<=iMax; i++) {
                    for (k1=0; k1<=kMax; k1++) {
                        for (j=0; j<=iMax; j++) {
                            V(i,j,k1) = max(payoff(k1),V(i,j,k1));
                        }
                    }
                }
                }
            /* Update time variables  */
            if (tau>=ttest - dtau)
                {
                dtaum1 = dtau;
                }
            /* Update time */
            tau = dtau + tau;
            if (fabs(tau)<max(100*eps,1.e-12)*max(fabs(TMax),0.))
                {
                tau = 0.;
                }
            /* Update local loop counter */
            n++;
        }
        /* End-loop discrete event updates. */
        if ((isamp1>=iretmin&&fabs(RDates1(isamp1) - tend)<ttest))
            {
            /* update for Path[direction[Sp], function[Sp==SumOf[(S -   
               Sp)]], tsample==RDates, InterpolateLinear] */
            for (k1=0; k1<=kMax; k1++) {
                for (i=0; i<=iMax; i++) {
                    for (j=0; j<=iMax; j++) {
                        xnew(j) = S(i);
                    }
                    for (j=0; j<=iMax; j++) {
                        slicetmp1(j) = V(i,j,k1);
                    }
                    InterpolateLinearLoop(slicetmp1,Sp,xnew,yi1,0,iMax,0
                       ,iMax,0.,1);
                    for (j=0; j<=iMax; j++) {
                        V(i,j,k1) = yi1(j);
                    }
                }
            }
            /* update for Path[direction[vari],                         
               (function[vari==SumOf[(((-1 + (S Sp^-1))^2 - vari) (iret 
               + nsampSoFar)^-1)]]), tsample==RDates, CubicSpline] */
            temp16 = 1. / (double)(isamp1 + nsampSoFar);
            for (j=0; j<=iMax; j++) {
                temp17 = 1. / Sp(j);
                for (i=0; i<=iMax; i++) {
                    SplineCoefficients(V(i,j),vari,0.,fpp4,TriT1k11,
                       TriT2k11,0,kMax);
                    temp15 = (temp17*S(i) - 1)*(temp17*S(i) - 1);
                    for (k1=0; k1<=kMax; k1++) {
                        xnew1(k1) = temp16*(temp15 - vari(k1)) + vari(k1
                           );
                    }
                    CubicSplineLoop(V(i,j),vari,fpp4,xnew1,yi2,0,kMax,0,
                       kMax,0.,1);
                    for (k1=0; k1<=kMax; k1++) {
                        V(i,j,k1) = yi2(k1);
                    }
                }
            }
            isamp1--;
            }
    }
    SplineForwardSweep(S,0.,TriT1i1,TriT2i1,0,iMax);
    SplineForwardSweep(Sp,0.,TriT1j1,TriT2j1,0,iMax);
    TriCubicSplineCoefficients(V,S,Sp,vari,0.,0.,0.,fpp1,TriT1i1,TriT2i1
       ,TriT1j1,TriT2j1,TriT1k11,TriT2k11,0,iMax,0,iMax,0,kMax,1);
    VOut = TriCubicSpline(V,S,Sp,vari,Spot,Sp0,vari0,0,iMax,0,iMax,0,
       kMax,0.,0.,0.,1,1,fpp1,TriT1i1,TriT2i1,TriT1j1,TriT2j1,TriT1k11,
       TriT2k11);
    *VOutp = VOut;
    return 1;
}

static void ComputeIndStencils1(
    double D0,
    double dx1,
    int iMax,
    const FAArray1Ref<double>& J11,
    int kMax,
    double r,
    const FAArray1Ref<double>& S,
    FAArray2Ref<double>& SA0,
    FAArray2Ref<double>& SB0,
    const FAArray1Ref<double>& sigma
    )
{
    int i;
    double jtemp1,jtemp2,temp1,temp11,temp2,temp4,temp5,temp6,temp7,
       temp8,temp9;
    
    /* *** Key to program variables: *** */
    /* D0: continuous dividend yield */
    /* dx1: step size for x1 */
    /* i: index variable for x1 */
    /* iMax: number of grid cells for x2 */
    /* J11, S: solution variable */
    /* jtemp1, jtemp2, temp1, temp11, temp2, temp4, temp5, temp6, temp7,
       temp8, temp9: common subexpression temporary */
    /* kMax: number of grid cells for y */
    /* r: interest rate */
    /* SA0: part of SA that is proportional to dt. */
    /* SB0: part of SB that is proportional to dt */
    /* sigma: volatility */
    /* Loop-independent part of: Set up and solve system for V. */
    /* assign SA0 */
    temp2 = ((r - D0)*0.25) / dx1;
    temp1 = 0.25 / (dx1*dx1);
    temp7 = ((D0 - r)*0.5) / dx1;
    temp6 = temp7*S(0);
    temp5 = temp7*S(iMax);
    SA0(0,1) = temp6 / J11(0) - r*0.5;
    SA0(0,2) = -(temp6 / J11(0));
    SA0(iMax,0) = temp5 / J11(iMax - 1);
    SA0(iMax,1) = -(r*0.5) - temp5 / J11(iMax - 1);
    for (i=1; i<=iMax - 1; i++) {
        jtemp1 = 2. / (J11(i - 1) + J11(i));
        temp4 = temp1*S(i)*S(i)*sigma(i)*sigma(i);
        SA0(i,0) = jtemp1*(temp4 / J11(i - 1) - temp2*S(i));
        SA0(i,1) = -(temp4*2.) / (J11(i)*J11(i - 1)) - r*0.5;
        SA0(i,2) = jtemp1*(temp4 / J11(i) + temp2*S(i));
    }
    /* assign SB0 */
    temp9 = ((D0 - r)*0.25) / dx1;
    temp8 = 0.5 / (dx1*dx1);
    SB0(0,1) = r*0.5 - temp6 / J11(0);
    SB0(0,2) = temp6 / J11(0);
    SB0(iMax,0) = -(temp5 / J11(iMax - 1));
    SB0(iMax,1) = temp5 / J11(iMax - 1) + r*0.5;
    for (i=1; i<=iMax - 1; i++) {
        jtemp2 = 2. / (J11(i - 1) + J11(i));
        temp11 = temp8*S(i)*S(i)*sigma(i)*sigma(i);
        SB0(i,0) = jtemp2*(-(temp11*0.5) / J11(i - 1) - temp9*S(i));
        SB0(i,1) = temp11 / (J11(i)*J11(i - 1)) + r*0.5;
        SB0(i,2) = jtemp2*0.25*(-(temp11*2.) / J11(i) + temp9*S(i)*4.);
    }
    return;
}

static void ComputeStencils1(
    double dtau,
    double dtaum1,
    int iMax,
    int kMax,
    FAArray2Ref<double>& SA,
    const FAArray2Ref<double>& SA0,
    FAArray2Ref<double>& SB,
    const FAArray2Ref<double>& SB0
    )
{
    int i;
    double eps;
    
    /* *** Key to program variables: *** */
    /* dtau: step size for tau */
    /* dtaum1: value for dtau 1 time steps ago */
    /* eps: machine epsilon */
    /* i: index variable for x1 */
    /* iMax: number of grid cells for x2 */
    /* kMax: number of grid cells for y */
    /* SA: stencil array of the system; the A in Ax=y. */
    /* SA0: part of SA that is proportional to dt. */
    /* SB: coefficients for right hand side of the linear system */
    /* SB0: part of SB that is proportional to dt */
    /* Compute machine epsilon. */
    eps = 1.;
    while (1.!=eps + 1.) {
        eps = eps*0.5;
    }
    eps = eps*2.;
    /* Set up and solve system for V. */
    if (!(fpequal(dtau,dtaum1,1000*eps)))
        {
        /* assign SA */
        SA(0,1) = dtau*SA0(0,1) + 1.;
        SA(0,2) = dtau*SA0(0,2);
        SA(iMax,0) = dtau*SA0(iMax,0);
        SA(iMax,1) = dtau*SA0(iMax,1) + 1.;
        for (i=1; i<=iMax - 1; i++) {
            SA(i,0) = dtau*SA0(i,0);
            SA(i,2) = dtau*SA0(i,2);
            SA(i,1) = dtau*SA0(i,1) + 1.;
        }
        /* assign SB */
        SB(0,1) = dtau*SB0(0,1) + 1.;
        SB(0,2) = dtau*SB0(0,2);
        SB(iMax,0) = dtau*SB0(iMax,0);
        SB(iMax,1) = dtau*SB0(iMax,1) + 1.;
        for (i=1; i<=iMax - 1; i++) {
            SB(i,0) = dtau*SB0(i,0);
            SB(i,2) = dtau*SB0(i,2);
            SB(i,1) = dtau*SB0(i,1) + 1.;
        }
        }
    return;
}

static void CreateGrids1(
    double dx1,
    double dx2,
    double dy,
    int iMax,
    int kMax,
    FAArray1Ref<double>& S,
    FAArray1Ref<double>& Sp,
    double Spot,
    FAArray1Ref<double>& vari,
    double variBar,
    double xMin,
    double yMin
    )
{
    int i,j,k1;
    
    /* *** Key to program variables: *** */
    /* dx1: step size for x1 */
    /* dx2: step size for x2 */
    /* dy: step size for y */
    /* i: index variable for x1 */
    /* iMax: number of grid cells for x2 */
    /* j: index variable for x2 */
    /* k1: index variable for y */
    /* kMax: number of grid cells for y */
    /* S, Sp, Spot, vari, variBar: solution variable */
    /* xMin: minimum physical value in dimension x2 */
    /* yMin: minimum physical value in dimension y */
    /* Initialize coordinate arrays for S, Sp, vari */
    /* Computing S from equation Eqc on interior; formula is S ==       
       E^x1*Spot; discretization methods are Implicit[1/2] and          
       CentralSpaceDifference[2]; truncation error is 0. */
    for (i=0; i<=iMax; i++) {
        S(i) = Spot*exp(dx1*i + xMin);
    }
    /* Computing Sp from equation Eq1c on interior; formula is Sp ==    
       E^x2*Spot; discretization methods are Implicit[1/2] and          
       CentralSpaceDifference[2]; truncation error is 0. */
    for (j=0; j<=iMax; j++) {
        Sp(j) = Spot*exp(dx2*j + xMin);
    }
    /* Computing vari from equation Eq2c on interior; formula is vari ==
       variBar*Sinh[y]; discretization methods are Implicit[1/2] and    
       CentralSpaceDifference[2]; truncation error is 0. */
    for (k1=0; k1<=kMax; k1++) {
        vari(k1) = variBar*sinh(dy*k1 + yMin);
    }
    return;
}

static int CRound(
    double delx
    )
{
    
    /* *** Key to program variables: *** */
    /* delx: solution variable */
    if (delx>=0.)
        {
        return (int)(delx + 0.5);
        }
    else
        {
        return -(int)(0.5 - delx);
        }
}

static void SetDateIndices1(
    const FAArray1Ref<double>& RDates,
    FAArray1Ref<double>& RDates1,
    int nsampToGo,
    int *iretminp,
    int *nsampToGo1p,
    double TMax,
    double ttest,
    int arraymin
    )
{
    int i12,iretmin,lower,nsampToGo1,upper;
    
    /* *** Key to program variables: *** */
    /* arraymin: temp arg for number */
    /* i12: local loop variable */
    /* iretmin, iretminp: Minimum of Exercise array */
    /* lower: lowest significant array value */
    /* nsampToGo: array maximum for RDates */
    /* nsampToGo1, nsampToGo1p: Maximum of Exercise array */
    /* RDates: solution variable */
    /* RDates1: Auxiliary array for Exercise sample array */
    /* TMax: minimum physical value in dimension tau */
    /* ttest: minimal size test */
    /* upper: greatest significant array value */
    lower = arraymin;
    upper = arraymin - 1;
    if (arraymin<=nsampToGo)
        {
        while ((lower<=nsampToGo&&-(5*ttest)>RDates(lower))) {
            RDates1(lower) = RDates(lower);
            lower++;
        }
        upper = nsampToGo;
        while ((upper>=arraymin&&TMax + 5*ttest<RDates(upper))) {
            RDates1(upper) = RDates(upper);
            upper--;
        }
        for (i12=lower; i12<=upper; i12++) {
            RDates1(i12) = max(min(TMax - 5*ttest,RDates(i12)),0.);
        }
        }
    iretmin = lower;
    nsampToGo1 = upper;
    *iretminp = iretmin;
    *nsampToGo1p = nsampToGo1;
    return;
}

static void TriDiag(
    const FAArray3Ref<double>& g,
    const FAArray2Ref<double>& SA,
    FAArray3Ref<double>& V,
    int iMax,
    int kMax,
    FAArray1Ref<double>& TriTa,
    FAArray1Ref<double>& TriTb
    )
{
    int i,j,k1;
    
    /* *** Key to program variables: *** */
    /* g: right hand side of the linear system; the y in Ax=y. */
    /* i: index variable for x1 */
    /* iMax: number of grid cells for x2 */
    /* j: index variable for x2 */
    /* k1: index variable for y */
    /* kMax: number of grid cells for y */
    /* SA: stencil array of the system; the A in Ax=y. */
    /* TriTa, TriTb: temporary, same size as diagonal */
    /* V: option value */
    TriTa(0) = 1. / SA(0,1);
    TriTb(0) = -(TriTa(0)*SA(0,2));
    for (i=1; i<=iMax; i++) {
        TriTa(i) = 1. / (TriTb(i - 1)*SA(i,0) + SA(i,1));
        TriTb(i) = -(TriTa(i)*SA(i,2));
    }
    for (k1=0; k1<=kMax; k1++) {
        for (j=0; j<=iMax; j++) {
            V(0,j,k1) = TriTa(0)*g(0,j,k1);
            for (i=1; i<=iMax; i++) {
                V(i,j,k1) = TriTa(i)*(g(i,j,k1) - SA(i,0)*V(i - 1,j,k1
                   ));
            }
            for (i=iMax - 1; i>=0; i--) {
                V(i,j,k1) = V(i,j,k1) + TriTb(i)*V(i + 1,j,k1);
            }
        }
    }
    return;
}

static void ValidateArraySorted1(
    const FAArray1Ref<double>& RDates,
    int nsampToGo
    )
{
    int i1;
    
    /* *** Key to program variables: *** */
    /* i1: index for sample arrays */
    /* nsampToGo: array maximum for RDates */
    /* RDates: solution variable */
    /* see that the sample array is sorted */
    for (i1=1; i1<=nsampToGo - 1; i1++) {
        if (RDates(i1)>=RDates(i1 + 1))
            {
            throw new FAErrorException(		
               "pdeVolSwaption1: The sample array for your discrete event is not properly sorted."
               ,UnsortedSampleArray);
            }
    }
    return;
}

static void VectorMatrixMultiply4(
    const FAArray2Ref<double>& SB,
    const FAArray3Ref<double>& V,
    FAArray3Ref<double>& g,
    int iMax,
    int kMax
    )
{
    int i,j,k1;
    
    /* *** Key to program variables: *** */
    /* g: right hand side of the linear system; the y in Ax=y. */
    /* i: index variable for x1 */
    /* iMax: number of grid cells for x2 */
    /* j: index variable for x2 */
    /* k1: index variable for y */
    /* kMax: number of grid cells for y */
    /* SB: coefficients for right hand side of the linear system */
    /* V: option value */
    for (j=0; j<=iMax; j++) {
        for (k1=0; k1<=kMax; k1++) {
            g(0,j,k1) = SB(0,1)*V(0,j,k1) + SB(0,2)*V(1,j,k1);
            g(iMax,j,k1) = SB(iMax,0)*V(iMax - 1,j,k1) + SB(iMax,1)*V(
               iMax,j,k1);
            for (i=1; i<=iMax - 1; i++) {
                g(i,j,k1) = SB(i,0)*V(i - 1,j,k1) + SB(i,1)*V(i,j,k1) + 
                   SB(i,2)*V(i + 1,j,k1);
            }
        }
    }
    return;
}




