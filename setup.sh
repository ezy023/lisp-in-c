#!/bin/bash


echo "Installing Valgrind"
sudo apt-get install -y valgrind --fix-missing --quiet
echo "Valgrind COMPLETED"

echo "Installing libedit-dev"
sudo apt-get install libedit-dev -y --quiet
echo "libedit-dev COMPLETED"

echo "Installying make"
sudo apt-get install make --quiet
echo "make COMPLETED"