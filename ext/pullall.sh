#!/bin/bash
for D in */; do cd $D; git pull; cd ..; done
