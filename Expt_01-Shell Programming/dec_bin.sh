#!/bin/bash
deci=100
BINARY=()
i=0
while [ $deci -gt 0 ]
do
	BINARY[$i]=$(($deci%2))
	deci=$(($deci/2))
	i=$(($i+1))
done
echo "Binary equivalent is: "
for (( j=$(($i-1));j>=0;j-- ))
do
	echo ${BINARY[$j]}
done
