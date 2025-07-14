# Ingenico
My personal research about known data about TeliumOS (version 1 and 2) and Ingenico terminals based on it.

## Why?
Since 2 years this topic has bothered me, I was really keen on exploring this topic more. There is a lot of data hidden behind developer portals that cannot be accessed, so this repo can help someone develop some kind of fun stuff that can be done on those PoS devices.

## TeliumOS PoS terminals
TeliumOS has been developed since 2004 and has been discontinued in 2018, since 2018 Ingenico PoS terminals run Tetra (extended TeliumOS)

<div style="display: flex; gap: 40px; flex-wrap: wrap;">

  <div>
    <h3>🔹 Telium 1</h3>
    <table>
      <tr><th>Model</th><th>Timespan</th></tr>
      <tr><td>Ingenico EFT930</td><td>2004–2009</td></tr>
      <tr><td>Ingenico EFT930G</td><td>2005–2009</td></tr>
      <tr><td>Ingenico EFT930B</td><td>2005–2009</td></tr>
      <tr><td>Ingenico EFT930P</td><td>2005–2009</td></tr>
      <tr><td>Ingenico i5100</td><td>2003–2008</td></tr>
      <tr><td>Ingenico i7910</td><td>2006–2009</td></tr>
      <tr><td>Ingenico Elite 730</td><td>2004–2008</td></tr>
      <tr><td>Ingenico 510</td><td>2003–2007</td></tr>
      <tr><td>Ingenico 570</td><td>2004–2008</td></tr>
      <tr><td>Ingenico 650</td><td>2005–2008</td></tr>
      <tr><td>Ingenico 670</td><td>2005–2008</td></tr>
    </table>
  </div>

  <div>
    <h3>🔹 Telium 2</h3>
    <table>
      <tr><th>Model</th><th>Timespan</th></tr>
      <tr><td>Ingenico iCT220</td><td>2009–2018</td></tr>
      <tr><td>Ingenico iCT250</td><td>2009–2018</td></tr>
      <tr><td>Ingenico iWL220</td><td>2010–2018</td></tr>
      <tr><td>Ingenico iWL250</td><td>2010–2018</td></tr>
      <tr><td>Ingenico iWL280</td><td>2011–2018</td></tr>
      <tr><td>Ingenico iPP320</td><td>2010–2018</td></tr>
      <tr><td>Ingenico iPP350</td><td>2010–2018</td></tr>
      <tr><td>Ingenico iPP280</td><td>2011–2018</td></tr>
    </table>
  </div>

</div>


## Device states
Those devices are made with tamper proof mechanisms that successively cuts off any modifications that can be done to the device

<table>
  <tr><th>State</th><th>What it means</th></tr>
  <tr><td>Normal state</td><td>Device is fully functional and can create charges, all applications can be used normally, no banner is displayed. At the start a happy emoji is shown :-)</td></tr>
  <tr><td>Alert irruption!!!</td><td>Device tamper-proof mechanism has worked and wiped the secret keys used for payment processing and accept any kind of application/OS updates. Alphanumerical keyboard is disabled. At the start a sad emoji is shown - :-(</td></tr>
  <tr><td>Unauthorized</td><td>The device tamper mechanism has been reset but device does not have any secret keys and it cannot be used until Ingenico Recovery Tools are used to restore the original secret keys. At the start a sad emoji is shown - :-(</td></tr>
  <tr><td>Do not use for payment</td><td>It means that the Ingenico device has been provided to a developer and it cannot make live charges, can only be used to develop apps.</td></tr>
</table>

In 3 last cases there is a red/black banner stating the information.

## Files type in Telium
Provided file formats are being used in TeliumOS and TeliumOS 2
<table ><thead><tr><th>File Type</th><th>File Extension</th><th>Filetype ID</th><th>Description</th></tr></thead><tbody><tr><td>Application</td><td>.AGN</td><td>1</td><td>Used for Telium Manager (M2OS) and third-party applications installed on the device.</td></tr><tr><td>Library</td><td>.LGN</td><td>2</td><td>Contains shared functionality for multiple applications, such as graphics or communication protocols.</td></tr><tr><td>Driver</td><td>.DGN</td><td>3</td><td>Includes essential low-level components like the operating system, USB interface, or file system.</td></tr><tr><td>Key</td><td>.KGN</td><td>4</td><td>Holds cryptographic public keys used for secure communications and operations.</td></tr><tr><td>Signed File</td><td>.SGN</td><td>N/A</td><td>Generic signed file type not specific to any single purpose.</td></tr><tr><td>Parameter</td><td>.PGN</td><td>0</td><td>This file type is largely undocumented, making it difficult to understand or use effectively.</td></tr></tbody></table>

## Device modes
<table>
  <tr><th>Mode</th><th>What it does</th></tr>
  <tr><td>Normal mode</td><td>Device is operational at TeliumOS level</td></tr>
  <tr><td>LLT mode</td><td>Local Loading Tool is a Windows tool created by Ingenico used to load Applets, Images, Drivers and other things to the device. Every file has to be signed by Ingenico to operate in Telium. In this repositorium there are 2 versions of LLT <a href="https://github.com/l1806-vex/ingenico/tree/main/Tools/LLT%204.5.2">4.5.2</a> (Older) and <a href="https://github.com/l1806-vex/ingenico/tree/main/Tools/LLT%205.2.4">5.2.4</a> (Newer)</td></tr>
  <tr><td>Wiping mode (****)</td><td>**** is meant to wipe all data stored on the device, it will not boot up if no data is on it, it will go always into LLT mode. <strong>DO NOT WIPE YOUR DEVICE IF ITS IN ANY OTHER STATE THAN NORMAL, IT WILL BE BRICKED TILL THE SECRET KEYS ARE RESTORED.</strong></td></tr>
  <tr><td>Trace mode (before patch)</td><td>In 2020 researchers discovered a special mode in Telium devices called a Trace mode, this mode allowed developers to track apps performance in real time. It was given the <strong>CVE-2018-17772</strong> number, and was later on patched by Ingenico. Detailed information can be found under the training course which is included in this repo. <a href="https://github.com/l1806-vex/ingenico/tree/main/Training%20Courses/TELIUM%20TDS%20-Training_Course_23-11-2010_jp2">Click here.</a></td></tr>
</table>

## Keypad shortcuts
<table>
  <tr><th>Shortcut</th><th>What it does</th></tr>
  <tr><td>Yellow Button (Retry) + Dot (.)</td><td>Restart the PoS terminal</td></tr>
  <tr><td>F1 Hold at restart</td><td>Allows to enter combinations such as F1, F4, F2, F3 to enter the **** Wiping mode</td></tr>
  <tr><td>F2 Hold at restart</td><td>Shows a SYSTEM menu, if Tailum is installed.</td></tr>
  <tr><td>F4 Hold at restart</td><td>Enters a USB storage mode where data can be moved the same method as LLT but without a computer.</td></tr>
  <tr><td>Arrow up hold at restart</td><td>Opens up the LLT menu and later on the connection.</td></tr>
</table>

## Trace mode
This mode only applies to the device that were not updated and patched. <br><br>
<strong>Steps:</strong>
1. Enter the LLT mode 
2. Create an `SYSTEM.CFG` with content:
```
TRACE_DEV=5
LDBG_DEV=0
```
Make sure that it is disoverable via LLT tool

3. Upload the file to `/SWAP` folder.
4. Restart the PoS terminal

Now when the device is connected via serial, thru a tool like PuTTY it will display more data thru monitors like DMM (Device monitoring studio). Although it is in hexadecimal form it can be made in to some kind of structure.

## Trace mode data structure
<table><thead><tr><th>Field</th><th>Length (bytes)</th><th>Description</th><th>Example (hex)</th></tr></thead><tbody><tr><td>Header</td><td>2</td><td>Specifies the message type</td><td>0508</td></tr><tr><td>Payload length</td><td>1</td><td>Indicates the combined length of the last two fields</td><td>05</td></tr><tr><td>Time</td><td>4</td><td>9-digit decimal showing seconds (first 4 digits), milliseconds (next 3), and microseconds (last 3) since device start</td><td>09bba9f4</td></tr><tr><td>Payload (ASCII)</td><td>0+</td><td>Contains the data</td><td>68</td></tr></tbody></table>

## LLT modes
<table>
  <tr><th>Mode</th><th>What it does</th></tr>
  <tr><td>Download</td><td>Loading local resources and signed parameters</td></tr>
  <tr><td>Diagnostic</td><td>Allows to extract the .DIA files for troubleshooting</td></tr>
  <tr><td>Maintenance</td><td>Allows to write configuration data (.CFG) to the device</td></tr>
</table>

## How does the LLT connection work?
The LLT connection works via Windows PBK, RAS Dialer and thru PPPD (Point-To-Point Daemon), First the connection is created via RAS phone dialer, when is connects, the PPPD IP gets assigned and then a FTP port is opened where it can be accessed thru LLT tool. <br><br>
This was disclosed via `CVE-2018-17771`, that app has hardcoded PPPD credentials which were
```
Username: pppuser
Password: 123456 
```
The FTP server behind most of the Telium devices is NexGenREMOTE FTP server in version 1.0 as it states in banner.

^ This might not be accurate since it is not publiclly disclosed about how it works.

# WIP
more detailed info coming soon.
