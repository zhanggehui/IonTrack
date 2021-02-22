#!/bin/bash

macfile="./run.mac"
mkdir ./data
for((i=1;i<31;i++)); do
    echo "------------------------  ${i}_th run ------------------------"
    beamnum=$((i*100))
    filename=beam_$beamnum.dat

    str1=beamOn
    str2="/run/beamOn $beamnum"
    sed -i "/$str1/c$str2" $macfile
    
    str1=dumpQuantityToFile
    str2="/score/dumpQuantityToFile boxMesh eDep $filename"
    sed -i "/$str1/c$str2" $macfile
    
    ../IonTrack $macfile && mv $filename ./data
done
