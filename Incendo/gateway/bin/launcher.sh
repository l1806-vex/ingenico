#!/bin/sh

JAVA_LAUNCHER="java -server"

test -e "jre/bin/java" && JAVA_LAUNCHER="jre/bin/java -server"

$JAVA_LAUNCHER $*