<?xml version="1.0" encoding="utf-8"?>

<template id="NULLPROTOCOL" name="NULL PROTOCOL Parameter" description="SDK Sample NULL PROTOCOL Parameter management" version="1">
  <fields>
<choiceField id="portNum" description="number of com port" type="SINGLE" defaultValue="0" access="READONLY">
<choiceValue label="COM0_PORT" value="0"/>
<choiceValue label="COM1_PORT" value="1"/> 
<choiceValue label="COM2_PORT" value="2"/> 
</choiceField>
<choiceField id="portSpeed" description="Speed of com port" type="SINGLE" defaultValue="9600" access="READONLY">
<choiceValue label="SPEED_1200" value="1200"/> 
<choiceValue label="SPEED_2400" value="2400"/> 
<choiceValue label="SPEED_4800" value="4800"/> 
<choiceValue label="SPEED_9600" value="9600"/> 
<choiceValue label="SPEED_19200" value="19200"/> 
<choiceValue label="SPEED_38400" value="38400"/> 
<choiceValue label="SPEED_57600" value="57600"/> 
<choiceValue label="SPEED_152000" value="152000"/> 
</choiceField>
</fields>
</template>
