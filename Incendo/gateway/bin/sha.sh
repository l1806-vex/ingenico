#!/bin/sh
dir=`dirname "$0"`
parent="$dir/.."
$dir/launcher.sh -cp "$parent/config:$parent/lib/iutil.jar:$parent/lib/common/commons-codec-1.3.jar:$parent/lib/common/log4j-1.2.16.jar" -Doegw.log.dir="$parent/../log" com.ingenico.util.byte_utils.DigestUtilityLancher $*
exitcode=$?
exit $exitcode