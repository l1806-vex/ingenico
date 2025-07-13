#!/bin/sh
dir=`dirname "$0"`
parent="$dir/.."
$dir/launcher.sh -cp "$parent/config:$parent/lib/oegw.jar" -Doegw.log.dir="$parent/log" com.ingenico.oegw.security.HashValidator $*
exitcode=$?
exit $exitcode