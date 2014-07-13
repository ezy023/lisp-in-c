#!/bin/bash

cc -std=c99 -Wall parsing.c lib/mpc.c -ledit -lm -o parsing