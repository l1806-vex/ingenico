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
    <dataField id="posKeyA" description="Key A" defaultValue="01020304050607080910111213141516" minLength="16" maxLength="16" type="hexadecimal" access="READWRITE"/>
    <dataField id="posKeyB" description="Key B" defaultValue="00112233445566778899AABBCCDDEEFF" minLength="16" maxLength="16" type="hexadecimal" access="READWRITE"/>
    <dataField id="posKeyC" description="Key C" defaultValue="ABCDEF012345678990817263545E740F" minLength="16" maxLength="16" type="hexadecimal" access="READWRITE"/>
  </fields>
</template>
