#!/bin/bash
cd /root/camera
rm ./cgicc/postCamera.cpp
git pull
cd cgicc
chmod 777 postCamera.cpp
./build
./deploy
cd ../..
echo "Done!"
 
