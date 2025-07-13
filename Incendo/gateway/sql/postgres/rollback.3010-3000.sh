#!/bin/sh
basedir=$(dirname $0)
$basedir/migration.sh $basedir/migration/rollback3010.sql $* 
exitcode=$?
exit $exitcode