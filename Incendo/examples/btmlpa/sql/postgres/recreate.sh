#!/bin/bash

if [ "$1" = "--help" ];
  then echo recreate.sh [login]
  exit 2
fi

# By default run scripts for user 'postgres':
uname="-U postgres"
# Do not force password prompt (which is default):
#passwd="-W"
if [ -n "$1" ]; then 
        uname="-U $1"
fi

dir=`dirname "$0"`
pushd "$dir" 1>/dev/null || exit 2

function recreateDB () {
        psql -h localhost $uname $passwd -f all.sql
}

recreateDB 

exitcode=$?
popd 1>/dev/null
exit $exitcode

