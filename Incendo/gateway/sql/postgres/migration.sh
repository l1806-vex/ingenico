#!/bin/bash
dir=`dirname "$0"`
LOGDIR="$dir/../../log" 
[ -d $LOGDIR ] || mkdir $LOGDIR

echo `date +"%d/%m/%Y %T"` Postgres DB migration script starting >> $LOGDIR/oegw.log

if [ "$1" = "--help" ];
  then echo migration.sh [host] [login] [sql file]
  exit 2
fi
if [ -z "$1" ];
  then echo migration.sh [host] [login] [sql file]
  exit 2
fi
uname="-U postgres"
dbhost="-h localhost"
dbscript="$1"
if [ -n "$2" ]; then 
        dbhost="-h $2"
fi
if [ -n "$3" ]; then 
        uname="-U $3"
fi

function logAndExit() {
    if [ $1 = 0 ]
        then echo `date +"%d/%m/%Y %T"` Postgres DB migration script finished successfully >> $LOGDIR/oegw.log
    else echo `date +"%d/%m/%Y %T"` Postgres DB migration script finished with error >> $LOGDIR/oegw.log
    fi
    exit $1
}

dir=`dirname "$0"`
pushd "$dir" 1>/dev/null || logAndExit 2

function migrationDB () {
        psql $dbhost -d oegw $uname -f $dbscript
}

migrationDB 

exitcode=$?
popd 1>/dev/null
logAndExit $exitcode

