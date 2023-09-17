#!/bin/sh

printf "+ [INFO] Run make in bin folder.\n"
cd bin
make
printf "+ [INFO] Run znn.exe: \n"
./znn.exe 
printf "+ [INFO] Program ended successfully.\n"