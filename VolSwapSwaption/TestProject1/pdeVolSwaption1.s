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
