#!/bin/sh
dir=`dirname "$0"`
parent="$dir/.."
$dir/launcher.sh -cp "$parent/config:$parent/lib/oegw.jar" -Doegw.log.dir="$parent/log" com.ingenico.oegw.server.clear.RestoreTool $*
exitcode=$?
exit $exitcode