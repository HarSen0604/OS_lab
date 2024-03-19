#!/bin/bash
n=2000

for (( i=0; i<=n; i++ ))
do
    a[$i]=$i
done

item=21

j=0
while [ $j -lt $n -a $item -ne ${a[$j]} ]
do
    j=$(($j + 1))
done

if [ $item -eq ${a[$j]} ]
then
    echo $item is present at location $(($j+1))
else
    echo "$item is not present in the array."
fi
