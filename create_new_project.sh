#!/bin/bash
mkdir $1
cd $1
pio project init --board disco_f407vg --project-option "framework=cmsis"