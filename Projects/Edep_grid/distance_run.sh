#!/bin/bash

macfile="./run.mac"
mkdir ./data
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
    
    ../main $macfile && mv $filename ./data
done
