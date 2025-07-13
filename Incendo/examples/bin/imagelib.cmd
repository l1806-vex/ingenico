@ECHO OFF

"%~dp0/launcher" -Doegw.activitylog.nodb=true -Doegw.log.dir="%~dp0/../log" -jar "%~dp0/../lib/oe-converter.jar" image/lib %*
