#!/bin/sh
basedir=$(dirname $0)
$basedir/migration.sh $basedir/migration/3020.sql $* 
exitcode=$?
exit $exitcode