<?xml version="1.0" encoding="utf-8"?>

<template id="DUALSIM" name="Dual Sim Parameter" description="SDK Sample DUAL SIM Parameter management" version="1">
<fields>
<structureField id="T_GPRS_TEST_SETTINGS"  description="Gprs setting structure" access="READWRITE"  maxRows="2">
<dataField id="nameStr" name="stringname" description="operator name string" type="alphanumeric" minLength="1" defaultValue="orange" maxLength="40" access="READWRITE" mandatory="true"/>
<dataField id="nSlotId" name="Slot Id" description="Slot Identifier" type="numeric" defaultValue="0" access="READWRITE" mandatory="true"/>
<dataField id="szPinCode" name="Pin Code" description="Pin Code" type="alphanumeric" defaultValue="00" minLength="1"  maxLength="40" access="READWRITE" mandatory="true"/>
<dataField id="szAPn" name="Slot Id" description="Slot Identifier" type="alphanumeric" minLength="1"  maxLength="100" access="READWRITE" />
<dataField id="nPort" name="portNum" description="port number" type="numeric" defaultValue="80" access="READWRITE" />
<dataField id="szHostName" name="HostName" description="Host Name String" type="alphanumeric" defaultValue="host" minLength="1" maxLength="100" access="READWRITE" mandatory="true"/> 
</structureField>
</fields>
</template>



