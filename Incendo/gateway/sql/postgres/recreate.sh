#!/bin/bash
dir=`dirname "$0"`
LOGDIR="$dir/../../log" 
[ -d $LOGDIR ] || mkdir $LOGDIR

echo `date +"%d/%m/%Y %T"` Postgres DB recreation script starting >> $LOGDIR/oegw.log

if [ "$1" = "--help" ];
  then echo recreate.sh [host] [login]
  exit 2
fi

uname="-U postgres"
dbhost="-h localhost"
if [ -n "$1" ]; then 
        dbhost="-h $1"
fi
if [ -n "$2" ]; then 
        uname="-U $2"
fi

function logAndExit() {
    if [ $1 = 0 ]
        then echo `date +"%d/%m/%Y %T"` Postgres DB recreation script finished successfully >> $LOGDIR/oegw.log
    else echo `date +"%d/%m/%Y %T"` Postgres DB recreation script finished with error >> $LOGDIR/oegw.log
    fi
    exit $1
}

dir=`dirname "$0"`
pushd "$dir" 1>/dev/null || logAndExit 2

function recreateDB () {
        psql $dbhost $uname -f all.sql
}

recreateDB 

exitcode=$?
popd 1>/dev/null
logAndExit $exitcode

