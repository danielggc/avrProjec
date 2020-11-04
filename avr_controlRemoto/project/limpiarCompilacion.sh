#!/bin/bash
 
if  test -e target $1; then
    mv *.o target
	if test -e ../scr/main.hex $1; then 
        rm ../scr/main.elf 
        rm ../scr/main.hex
    else 
        if test ../scr/main.elf $1; then
            rm ../scr/main.elf
        fi
    fi 
	rm -rf target
    echo " \n Hemos terminado la compilacion y el montado Bien =) ";
else
    mkdir target
    mv *.o target
	if test -e ../scr/main.hex $1; then 
        rm ../scr/main.elf 
        rm ../scr/main.hex
    else 
        if test ../scr/main.elf $1; then
            rm ../scr/main.elf 
        fi
    fi
	rm -rf target
    echo " \n Hemos terminado la compilacion y el montado Bien =) ";
fi
 
