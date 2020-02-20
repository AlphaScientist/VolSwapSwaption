(* pdeVolSwap1.s *)

PDE;  CrankNicolson;
Region[xMin<=x1<=xMax && xMin<=x2<=xMax && 0<=y<=1
       && 0<=tau<=TMax, GeneralCoordinates[{x1,x2,y},tau]];
       OldCoordinates[{{S,Sp,A},t}];
       S ==Spot Exp[x1];          Sp==Spot Exp[x2];
       A==AMin + (AMax-AMin) y;   t==tau;
When[Interior, BlackScholes1D[]];
When[Boundary, AutomaticBC; OneSidedDifference[1]];
When[min[x1]||max[x1], der[V,S]==0];
When[max[tau], V==Vol - K];
Vol==Sqrt[Max[0, (A - (Log[S/S0]/nsampTot)^2)/dTAve]];
dTAve==(TContract/nsampTot);

DiscreteEvents[
     Path[direction[Sp],
          function[Sp==SumOf[S-Sp]],
          tsample==RDates, nsample==nsampToGo,
          InterpolateLinear],
     Path[direction[A],
          function[
              A==SumOf[(Log[S/Sp]^2-A)/(isamp + nsampSoFar)]],
          tsample==RDates, nsample==nsampToGo,
          CubicSpline]];
ReadArray[RDates, {isamp,1,nsampToGo}, "RDates.dat"];

Default[TaggedInputFile["volswap.dat"], Labelled];
Output[V, "VofA.out",   CubicSpline, S==Spot && Sp==SpSpot];
Output[V, "atSpot.out", CubicSpline, S==Spot && Sp==SpSpot && A==ASpot];

ReadOrCompute[{xMin,xMax,AMin,AMax}];
    stddevs==Max[4 sigma Sqrt[TMax], 0.1];
    xMin==-stddevs - r TMax;
    xMax== stddevs + D0 TMax;
    AMin==0.25 sigma^2 dTAve;
    AMax==4 sigma^2 dTAve;
ReadOrCompute[{iMax,kMax,nMax}];
    delx==Min[xMax-xMin,4]/100;
    iMax0==Round[(xMax-xMin)/delx];
    kMax0==20;
    ndiff==Round[(sigma/delx)^2 TMax /10];
    nconv==Round[2 Abs[r-D0]/delx TMax];
    nMax0==Max[20, Max[ndiff, nconv]];
    iMax==Round[iMax0 Sqrt[Accuracy]];
    nMax==Round[nMax0 Sqrt[Accuracy]];
    kMax==Round[kMax0 Sqrt[Accuracy]];
    nsampTot==nsampSoFar+nsampToGo;
    TMax==RDates[nsampToGo];
MInteger[{nsampSoFar,nsampTot}];
GridSize[{{iMax,iMax,kMax},nMax}];
