#!/bin/bash

if [ ! -x bin2c ]; then
  gcc -o bin2c bin2c.c
fi

SRC="sprite.glslv sprite.glslf"
HEADER="shaders.h"

rm -f ${HEADER}
for f in ${SRC}; do
  echo "const char ${f/./_}[] =" >>${HEADER}
  ./bin2c <${f} >>${HEADER}
  echo -e '\t"\\x00";' >>${HEADER}
done
