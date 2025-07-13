del html\search\*.* /q
del html\*.html
del html\*.png
del html\*.php
del html\*.hh?
del html\*.css
del html\*.gif
del html\*.idx
del html\*.ttf
del html\installdox
del doxlog.txt
del errors.txt
del *.chm

copy images\*.gif html
copy images\*.png html
copy intro\*.html html
copy intro\*.htm html
copy doxparam\*.gif html
copy doxparam\*.png html
copy doxparam\*.html html
copy doxparam\*.htm html
W:\Tools\ExternalTools\Doxygen\1.7.4\bin\doxygen GPRS.dox > doxlog.txt 2>errors.txt
pause 1