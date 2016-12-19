#!/bin/bash
vmd -dispdev text -e visualization/vmd/movie-maker.tcl 
TACHYONBIN=/usr/local/lib/vmd/tachyon_LINUXAMD64 
let "iter=0"
for i in animate.*
do  
   $TACHYONBIN $i -format PPM -o ${i}.ppm
   let "iter+=1"
done
let "iter-=1"
printf -v VAR "%'.04d" ${iter}
sed -r -e "/^END_INPUT/i\animate.*.ppm [0000-${VAR}]" visualization/vmd/tompeg.sh > tompeg.par
ppmtompeg tompeg.par
rm -rf animate.*
rm -rf tompeg.par
mv -f output.mpg visualization/vmd/movie.mpg
xdg-open visualization/vmd/movie.mpg
