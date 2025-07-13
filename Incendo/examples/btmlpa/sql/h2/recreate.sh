#!/bin/sh
LOGDIR=./../../log
[ -d $LOGDIR ] || mkdir $LOGDIR

echo `date +"%d/%m/%Y %T"` H2 DB recreation script starting >> $LOGDIR/oegw.log

if [ "$1" = "--help" ];
  then echo recreate.sh [login [password]]
  exit 2
fi

CLASSPATH=h2.jar
CLASS=org.h2.tools.RunScript
JDBC_URL=jdbc:h2:tcp://localhost/~/btmlpa

# By default run scripts for root without password
uname=-user sa
passwd=-password ""
if [ -n "$1" ]; then 
	uname=-user $1
fi
if [ -n "$2" ]; then
	passwd=-password $2
fi

function logAndExit() {
    if [ $1 = 0 ]
        then echo `date +"%d/%m/%Y %T"` H2 DB recreation script finished successfully >> $LOGDIR/oegw.log
    else echo `date +"%d/%m/%Y %T"` H2 DB recreation script finished with error >> $LOGDIR/oegw.log
    fi
    exit $1
}

dir=`dirname "$0"`
pushd "$dir" 1>/dev/null || logAndExit 2

function recreateDB () {
  java -cp $CLASSPATH $CLASS $uname $passwd $JDBC_URL -f oegw/cred.ddl.sql  || return
  java -cp $CLASSPATH $CLASS $uname $passwd $JDBC_URL -f oegw/crebas.ddl.sql  || return
  java -cp $CLASSPATH $CLASS $uname $passwd $JDBC_URL -f oegw/crebas.dml.sql  || return
}

recreateDB 

exitcode=$?
popd 1>/dev/null
logAndExit $exitcode

