#!/bin/sh

if [ "$1" = "--help" ];
  then echo recreate.sh login password
  exit 2
fi

login=btmlpa
pswd=ingenico

if [ -n "$1" ]; then 
	uname=$1
fi
if [ -n "$2" ]; then
	passwd=$2
fi

pushd `dirname $0` 1>/dev/null || exit 2

function recreateDB () {
        sqlplus $uname/$passwd < crebas.ddl.sql    || return
        sqlplus $login/$pswd   < crebas.dml.sql    || return
}

recreateDB 

exitcode=$?
popd 1>/dev/null
exit $exitcode

