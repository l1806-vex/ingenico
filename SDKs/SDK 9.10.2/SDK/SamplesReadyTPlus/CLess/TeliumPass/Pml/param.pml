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
    <dataField id="aidOption101" description="AID Option 101 (Partial AID and Zero amount)" defaultValue="05030000" minLength="4" maxLength="8" type="hexadecimal" access="READWRITE"/>
    <dataField id="aidPaywaveSmall" description="Paywave AID" defaultValue="A000000003" minLength="4" maxLength="8" type="hexadecimal" access="READWRITE"/>
    <dataField id="aidPaypassSmall" description="Paypass AID" defaultValue="A000000004" minLength="4" maxLength="8" type="hexadecimal" access="READWRITE"/>
    <dataField id="amtBin15" description="Amount binary 15" defaultValue="000005DC" minLength="4" maxLength="4" type="hexadecimal" access="READWRITE"/>
    <dataField id="amtNum25" description="Amount numeric 25" defaultValue="000000002500" minLength="6" maxLength="6" type="hexadecimal" access="READWRITE"/>
    <dataField id="amtNum20" description="Amount numeric 20" defaultValue="000000002000" minLength="6" maxLength="6" type="hexadecimal" access="READWRITE"/>
    <dataField id="amtNum10" description="Amount numeric 10" defaultValue="000000001000" minLength="6" maxLength="6" type="hexadecimal" access="READWRITE"/>
    <dataField id="apduOption" description="AID Options" defaultValue="01100000" minLength="4" maxLength="8" type="hexadecimal" access="READWRITE"/>
    <dataField id="selectPPSE" description="APDU Select PPSE" defaultValue="05030000" minLength="4" maxLength="8" type="hexadecimal" access="READWRITE"/>
    <dataField id="apduSW9000" description="APDU SW 9000" defaultValue="0900" minLength="2" maxLength="2" type="hexadecimal" access="READWRITE"/>
    <dataField id="kernelPaypass" description="Paypass Kernel" defaultValue="0002" minLength="2" maxLength="2" type="hexadecimal" access="READWRITE"/>
    <dataField id="kernelVisa" description="Visa kernel" defaultValue="0003" minLength="2" maxLength="2" type="hexadecimal" access="READWRITE"/>
    <dataField id="propId1" description="Proprietary ID 1" defaultValue="12345678" minLength="4" maxLength="8" type="hexadecimal" access="READWRITE"/>
    <dataField id="propId2" description="Proprietary ID 2" defaultValue="11223344" minLength="4" maxLength="8" type="hexadecimal" access="READWRITE"/>
    <dataField id="ttqNoOption" description="TTQ No Option" defaultValue="B2000000" minLength="4" maxLength="8" type="hexadecimal" access="READWRITE"/>
  </fields>
</template>
