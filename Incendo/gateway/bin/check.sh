#!/bin/sh
dir=`dirname "$0"`
pushd "$dir/.." 1>/dev/null || exit 2
bin/launcher.sh -cp "lib/cfgmsrv.jar:lib/oegw.jar" -Djava.net.preferIPv4Stack=true -Doegw.log.dir="log" com.ingenico.oegw.connector.RemoteControl $*

exitcode=$?
popd 1>/dev/null
exit $exitcode
