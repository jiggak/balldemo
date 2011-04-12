#!/bin/bash

path2cname() {
  f=$(basename $1)
  echo ${f/./_}
}

if [ ! -x bin2c ]; then
  gcc -o bin2c bin2c.c
fi

SRC="sprite.glslv sprite.glslf"
HEADER="shaders.h"

rm -f ${HEADER}
for f in ${SRC}; do
  name=$(path2cname $f)
  echo -e "const char ${name}[] =" >>${HEADER}
  ./bin2c <${f} >>${HEADER}
  echo -e '\t"\\x00";' >>${HEADER}
done
