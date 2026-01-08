#!/bin/bash
mkdir Projects/$1
cd Projects/$1
pio project init --board disco_f407vg --project-option "framework=cmsis"