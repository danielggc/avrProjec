#!/bin/bash
 
if  test -e target $1; then
    mv *.o target
	if test -e ../src/main.hex $1; then 
        rm ../src/main.elf 
        rm ../src/main.hex
    else 
        if test ../src/main.elf $1; then
            rm ../src/main.elf
        fi
    fi 
	rm -rf target
    echo " \n Hemos terminado la compilacion y el montado Bien =) ";
else
    mkdir target
    mv *.o target
	if test -e ../src/main.hex $1; then 
        rm ../src/main.elf 
        rm ../src/main.hex
    else 
        if test ../src/main.elf $1; then
            rm ../src/main.elf 
        fi
    fi
	rm -rf target
    echo " \n Hemos terminado la compilacion y el montado Bien =) ";
fi
 
