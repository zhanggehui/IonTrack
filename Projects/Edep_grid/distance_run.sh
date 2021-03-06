#!/bin/bash

macfile="./run.mac"
mkdir ./data
for((i=0;i<15;i++)); do
    echo "------------------------  ${i}_th run ------------------------"
    length=`echo "2*$i" | bc`
    filename=dis_${length}nm.dat

    str1=distance
    str2="/IonTrack/gun/distance $length nm"
    sed -i "/$str1/c$str2" $macfile
    
    str1=dumpQuantityToFile
    str2="/score/dumpQuantityToFile boxMesh eDep $filename"
    sed -i "/$str1/c$str2" $macfile
    
    ../IonTrack $macfile && mv $filename ./data
done
