#!/bin/bash

n=2000

for(( i=n ; i>=0 ; i-- ))
do
	a[i]=$i
done

for(( i=1; i<n; i++ ))
do
	for(( j=0; j<n-i; j++ ))
	do
		if [ ${a[$j]} -gt ${a[$j+1]} ]
		then
			t=${a[$j]}
			a[$j]=${a[$j+1]}
			a[$j+1]=$t
		fi
	done
done

s=16
l=0
c=0
u=$(($n-1))

while [ $l -le $u ]
do

	mid=$(((( $l+$u ))/2 ))

	if [ $s -eq ${a[$mid]} ]
	then
		c=1
		break
	elif [ $s -lt ${a[$mid]} ]
	then
		u=$(($mid-1))
	else
	l=$(($mid+1))
	fi
done

if [ $c -eq 1 ]
then
	echo Element $s found at position $(($mid+1))
else
	echo Element not found
fi
