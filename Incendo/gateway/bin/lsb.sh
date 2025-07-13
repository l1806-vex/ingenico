#!/bin/sh
dir=`dirname "$0"`
pushd "$dir/.." 1>/dev/null || exit 2
#use -Djava.security.auth.login.config=config/jaas.conf in parameter to enable LDAP authentication
bin/launcher.sh -cp "lib/cfgmsrv.jar:lib/oegw.jar" -Djava.net.preferIPv4Stack=true -Doegw.log.dir="log" com.ingenico.cfgsrv.oegwmm.lsb.Lsb $*

exitcode=$?
popd 1>/dev/null
exit $exitcode