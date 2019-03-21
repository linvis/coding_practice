#!/bin/bash

FILE=$1

if [ ! -d "build" ]
then
    mkdir build
fi

if [ ! -f $FILE ]
then
    echo "File is not exist"
    exit
fi

cd build
cmake ../ -DSOURCE_FILE=$FILE
make
cp test_pthread.o ../
