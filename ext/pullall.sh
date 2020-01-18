#!/bin/bash
for D in */; do cd $D; pwd; git checkout master; git pull; cd ..; done
