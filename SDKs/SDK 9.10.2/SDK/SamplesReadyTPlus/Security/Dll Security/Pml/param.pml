<?xml version="1.0" encoding="utf-8"?>

<template id="example" name="Example Template" description="Example Template For Easy Path to Dev Parameter management" version="12345">
  <fields>
     <choiceField id="trcOutput" name="Trace Output" defaultValue="1" type="SINGLE" access="READWRITE">
      <choiceValue label="telium" value="0"/>
      <choiceValue label="remoteDbg" value="1"/>
      <choiceValue label="internalFile" value="2"/>
      <choiceValue label="externalFileUsb" value="3"/>
      <choiceValue label="externalFileMmc" value="4"/>
      <choiceValue label="printer" value="5"/>
      <choiceValue label="udpIp" value="6"/>      
    </choiceField>   
    <dataField id="pinKey" description="Pin Key" defaultValue="BE272A9DB2272FDB" type="hexadecimal" minLength="8" maxLength="8" access="READWRITE" mandatory="true"/>    
    <dataField id="macKey" description="Pin Key" defaultValue="877DF21FC0A5700D" type="hexadecimal" minLength="8" maxLength="8" access="READWRITE" mandatory="true"/>    
    <dataField id="pinMasterKey" description="Pin Key" defaultValue="3B2C7C7E6829AEDA" type="hexadecimal" minLength="8" maxLength="8" access="READWRITE" mandatory="true"/>    
    <dataField id="macMasterKey" description="Pin Key" defaultValue="D197ED41E31815A0" type="hexadecimal" minLength="8" maxLength="8" access="READWRITE" mandatory="true"/>        
    <dataField id="rootKey" description="Root Key" defaultValue="9999999999999999" type="alphanumeric" minLength="16" maxLength="16" access="READWRITE"/>
    
    <structureField id="secConfig" description="Secure Part" access="READWRITE" mandatory="false" maxRows="3">
      <choiceField id="securePart" description="Secure Part Area" defaultValue="0" type="SINGLE" access="READWRITE">
        <choiceValue label="Pincode" value="0"/>
        <choiceValue label="Card" value="1"/>
        <choiceValue label="Ciphering" value="2"/>
        <choiceValue label="Keyboard" value="3"/>
        <choiceValue label="Display" value="4"/> 
      </choiceField>
      <choiceField id="terminalBooster" description="Booster used by the terminal" defaultValue="1" type="SINGLE" access="READWRITE">
        <choiceValue label="Booster1" value="0"/>
        <choiceValue label="Booster2" value="1"/>        
      </choiceField>
      <choiceField id="peripheralBooster" description="Peripheral Booster Type" defaultValue="0" type="SINGLE" access="READWRITE">
        <choiceValue label="iappDefName" value="0"/>
        <choiceValue label="iappUsbName" value="1"/>     
        <choiceValue label="iappUsbUsrName" value="2"/>        
      </choiceField>         
      <choiceField id="pinpadBooster" description="Booster used by the pinpad" defaultValue="1" type="SINGLE" access="READWRITE">
        <choiceValue label="Booster1" value="0"/>
        <choiceValue label="Booster2" value="1"/>        
      </choiceField>      
    </structureField>    
  </fields>
</template>
