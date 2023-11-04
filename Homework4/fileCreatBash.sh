#!/bin/bash

if [$# -ne 2];then
	echo "invalid arguments"
	exit 1
fi
mkdir ./Nfiles
i=0
N=$1
ARR=$2
while ((i < N))
do
	touch ./Nfiles/files_$i.txt
	echo $ARR $i >> ./Nfiles/files_$i.txt
	((i+=1))
done
