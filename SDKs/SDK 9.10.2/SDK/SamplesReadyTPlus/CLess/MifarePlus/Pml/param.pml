<?xml version="1.0" encoding="utf-8"?>

<template id="mifare" name="Mifare Parameter" description="SDK Sample Card Entry Parameter management" version="1">
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
  </fields>
</template>
