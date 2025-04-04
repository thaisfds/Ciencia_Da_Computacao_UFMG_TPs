#!/bin/bash
set -u

i=6

gcc -g -std=gnu99 -Wall -c fs.c &>> gcc.log
gcc -g -std=gnu99 -Wall -I. tests/test$i.c fs.o -o test$i &>> gcc.log
if [ ! -x test$i ] ; then
    echo "[$i] compilation error"
    exit 1 ;
fi

if ! ./test$i > test$i.out 2> test$i.err ; then
    echo "[$i] error"
    exit 1
fi

rm -f test$i test$i.out test$i.err
exit 0
