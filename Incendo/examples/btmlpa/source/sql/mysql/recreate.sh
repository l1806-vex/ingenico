#!/bin/sh

if [ "$1" = "--help" ];
  then echo recreate.sh [login [password]]
  exit 2
fi

# By default run scripts for root without password
uname=-uroot
passwd=
if [ -n "$1" ]; then 
	uname=-u$1
fi
if [ -n "$2" ]; then
	passwd=-p$2
fi

pushd `dirname $0` 1>/dev/null || exit 2

function recreateDB () {
	mysql $uname $passwd           < crebas.ddl.sql 	|| return
	mysql $uname $passwd -D btmlpa < crebas.dml.sql 	|| return
}

recreateDB 

exitcode=$?
popd 1>/dev/null
exit $exitcode

