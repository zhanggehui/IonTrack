#!/bin/bash

macfile="./$rundir/batch_run.mac"
mkdir ./$rundir/data
for((i=1;i<31;i++))
do
    beamnum=$((i*100))
    filename=beam_$beamnum.dat

    str1=beamOn
    str2="/run/beamOn $beamnum"
    sed -i "/$str1/c$str2" $macfile
    
    str1=dumpQuantityToFile
    str2="/score/dumpQuantityToFile boxMesh eDep $filename"
    sed -i "/$str1/c$str2" $macfile
    
    ./RE03 $macfile && mv $filename ./$rundir/data/
done
