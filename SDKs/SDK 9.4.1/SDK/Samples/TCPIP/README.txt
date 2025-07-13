TCP/IP SAMPLE
---------------

This sample must be only executed on Ethernet terminal (EFT30+ or Smart+).

It shows :
	- how to retreive the Ethernet information (local address, netmask..).
	- how to implement a TCP/IP server.
	- how to implement a TCP/IP client.


From the idle screen, press the 'F' key and select the item "Sample TCP/IP" 
to enter the application.

It displays the following menu

+-----------------------+
| 0 - Infos		|
| 1 - HTTP Server	|
| 2 - HTTP Client	|
|			|
|			|
+-----------------------+


0 - Infos.

This function prints the local address of the terminal and its network mask.
Be careful, in DHCP, the systems requires few seconds to get these parameters
from the network.

1 - HTTP Server

This function launchs a HTTP server listening on the port 80 of the terminal.
The server can return some pages from the 'HOST' flash disk.


2 - HTTP Client.

This function connects a HTTP server and perform an HTTP GET request.
It shows how to resolve a DNS name (call to the function "gethostbyname_r").
