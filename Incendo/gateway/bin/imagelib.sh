#!/bin/sh

dir=`dirname $0`
$dir/launcher.sh -cp "$dir/../config:$dir/../lib/oe-converter.jar" -Doegw.activitylog.nodb=true -Doegw.log.dir="$dir/../log" com.ingenico.oegw.conv.Converter image/lib $*


