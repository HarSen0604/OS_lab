#!/bin/bash
 
count=10
i=20
 
# until loop with single condition
until [ $i -lt $count ]; do
   echo "$i"
   #let i--
   i=$(($i-1))
done
