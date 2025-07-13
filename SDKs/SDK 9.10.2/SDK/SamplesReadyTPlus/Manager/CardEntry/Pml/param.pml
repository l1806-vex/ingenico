<?xml version="1.0" encoding="utf-8"?>

<template id="cardEntry" name="Card Entry Parameter" description="SDK Sample Card Entry Parameter management" version="1">
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
    <choiceField id="periph" description="Output Display for Card Entry" defaultValue="0" type="SINGLE" access="READWRITE">
      <choiceValue label="Display" value="0"/>
      <choiceValue label="Ppr" value="1"/>
      <choiceValue label="C30" value="2"/>
    </choiceField>
    <choiceField id="cardEntry" description="Flag to enable or disable custom card entry message" defaultValue="1" type="SINGLE" access="READWRITE">
      <choiceValue label="Off" value="0"/>
      <choiceValue label="On" value="1"/>
    </choiceField>
    <choiceField id="amountEntry" description="Flag to enable or disable custom amount entry message" defaultValue="1" type="SINGLE" access="READWRITE">
      <choiceValue label="Off" value="0"/>
      <choiceValue label="On" value="1"/>
    </choiceField>
    <choiceField id="clessSupport" description="Flag to enable or disable cless support" defaultValue="1" type="SINGLE" access="READWRITE">
      <choiceValue label="Off" value="0"/>
      <choiceValue label="On" value="1"/>
    </choiceField>
    <choiceField id="checkBmp" description="Flag to enable or disable bitmap display for check transactions" defaultValue="1" type="SINGLE" access="READWRITE">
      <choiceValue label="Off" value="0"/>
      <choiceValue label="On" value="1"/>
    </choiceField>
    <choiceField id="tpassBmp" description="Flag to enable or disable bitmap display for tpass transactions" defaultValue="1" type="SINGLE" access="READWRITE">
      <choiceValue label="Off" value="0"/>
      <choiceValue label="On" value="1"/>
    </choiceField>
    <choiceField id="pp2Lines" description="Flag to enable or disable 2 lines display on pinpad" defaultValue="0" type="SINGLE" access="READWRITE">
      <choiceValue label="Off" value="0"/>
      <choiceValue label="On" value="1"/>
    </choiceField>
    <choiceField id="ppGraphic" description="Flag to enable or disable pinpad graphic support" defaultValue="1" type="SINGLE" access="READWRITE">
      <choiceValue label="Off" value="0"/>
      <choiceValue label="On" value="1"/>
    </choiceField>
    <choiceField id="c30" description="Flag to enable or disable tpass or vending pass terminal support" defaultValue="1" type="SINGLE" access="READWRITE">
      <choiceValue label="Off" value="0"/>
      <choiceValue label="On" value="1"/>
    </choiceField>
    <choiceField id="bwHeader" description="Flag to enable or disable header on black and white terminal" defaultValue="1" type="SINGLE" access="READWRITE">
      <choiceValue label="Off" value="0"/>
      <choiceValue label="On" value="1"/>
    </choiceField>
  </fields>
</template>
