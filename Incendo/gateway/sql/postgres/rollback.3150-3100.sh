#!/bin/sh
basedir=$(dirname $0)
$basedir/migration.sh $basedir/migration/rollback3150.sql $* 
exitcode=$?
exit $exitcode