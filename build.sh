#!/bin/bash

type=${1:-debug}

rm main.a* main.b* main.f* main.o*
rm options.tex 1> /dev/null 2>&1
cp options_${type}.tex options.tex || exit 1

time latexmk -synctex=1 -interaction=nonstopmode -file-line-error -pdf -outdir=. ./main || exit 1

cp main.pdf main_${type}.pdf
