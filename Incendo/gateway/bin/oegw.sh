#!/bin/sh
dir=`dirname "$0"`
pushd "$dir/.." 1>/dev/null || exit 2
#use  in parameter to enable LDAP authentication
bin/launcher.sh -Djava.net.preferIPv4Stack=true -Doegw.log.dir="log" -jar lib/oegw.jar $*

exitcode=$?
popd 1>/dev/null
exit $exitcode
