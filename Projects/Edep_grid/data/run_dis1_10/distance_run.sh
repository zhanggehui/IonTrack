#!/bin/bash

macfile="./$rundir/batch_run.mac"
mkdir ./$rundir/data
for((i=1;i<11;i++))
do
    length=$i
    filename=dis_${length}nm.dat

    str1=distance
    str2="/IonTrack/gun/distance $length nm"
    sed -i "/$str1/c$str2" $macfile
    
    str1=dumpQuantityToFile
    str2="/score/dumpQuantityToFile boxMesh eDep $filename"
    sed -i "/$str1/c$str2" $macfile
    
    ./RE03 $macfile && mv $filename ./$rundir/data/
done
