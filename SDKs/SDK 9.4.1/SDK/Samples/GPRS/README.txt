GSM/GPRS SAMPLE
---------------

To use this sample, please perform the following steps.


1- Set the GPRS facilty

Go in the menu GPRS (F/0: TELIUM Manager/3: Initialization /1: Parameters/Network Access).
Enter the parameters provided by your GPRS provider (APN, PPP login, PPP password).
Do not set the Gateway number (set to 0).

2 - Return to the idle screen.

3- Press the function key 'F' and enter the SAMPLE application. 
This one will automatically try to connect to the GPRS network.
It would ask the PIN code of the card if needed.
When the GPRS network is ready, the application displays its menu :

+---------------+
| 0 - PPP	|
| 1 - TCP/IP	|
| 2 - GSM	|
|		|
+---------------+

Form this menu, you can either perform a TCP/IP connection (through the GPRS network) 
or a GSM data connection.

3.1 - To perform a TCP/IP communication, you must first established a PPP connection.
Select the PPP item, and enter your PPP authentication (login and password). 
These parameters are generally the same than ones entered previously from the TELIUM
Manager menu. The following menu appears.

+-----------------+
| 0 - Connection  |
| 1 - Connection  |
|		  |
+-----------------+

Select connection. The PPP connection is in progress. In case of success, 
the application returns to the previous menu. The lift phone logo (with below : GPRS) 
indicates that the PPP connection is established. So, you can perform a TCP/IP connection.

To do that, please enter the TCP/IP menu of the application. Then, enter 
the informations of the TCP server (IP address and port). The IP address must be
resolved (for example : 217.12.3.11, instead of www.yahoo.fr).

FInally, the applications offers to process 3 tests.

+--------------------+
| 0 - WEB Iteration  |
| 1 - Echo Test      |
| 2 - Receive 100K   |
|		     |
+--------------------+


The "WEB Iteration" test connects an HTTP server and gets its HTML page.

The 2 other tests use a specific server : "IP Test Server". 
Please ask us to have access to this server. 

The "Echo" test echanges the same frame between the terminal and the server.
The "Receive 100K" test perform the transfer of 100 KBytes from the server to the terminal.


3.2 - To perform a GSM communication, please select the GSM menu.
Then enter the phone number of the remote server, and the modulation number :
( 
	4	: V22Bis - 2400,
	6 	: V32 - 4800,
	7 	: V32 - 9600,
	68	: V110 - 2400,
	70	: V110 - 4800,
	71	: V110 - 9600
)


And the RLP mode (0 or 1).  The RLP mode is the native protocol layer of GSM
to manage the error detection and correction).







 

