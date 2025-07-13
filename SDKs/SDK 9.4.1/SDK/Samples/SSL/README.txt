SSL SAMPLE
---------------

This sample must be only executed on Internet terminals (Ethernet terminals : EFT30+ or Smart+,
or GPRS terminals : ETF930G, EFT930B ).

It shows :
	- how to manage the SSL configuration profiles.
	- how to display the content of a X509 certificate.
	- how to perform a SSL connection with mutual authentication.


From the idle screen, press the 'F' key and select the item "Sample TCP/IP" 
to enter the application.

It displays the folowing menu

+-----------------------+
| 0 - GPRS		|
| 1 - SSL		|
|			|
|			|
+-----------------------+


0 - GPRS

This function connects the GPRS network. It allows the input of the needed parameters :
APN, PPP login and password.

1 - SSL

This item displays the folowing menu.

+-----------------------+
| 0 - Profiles		|
| 1 - Connection	|
|			|
|			|
+-----------------------+

1.0 - Profiles

This function allows to monitor the SSL configuration profiles. It allows to create a new profile and to display all the profiles.
It shows also how to get the information contained in a certificate.

It displays the following menu

+-----------------------+
| 0 - Add		|
| 1 - List		|
|			|
|			|
+-----------------------+

1.0.0 - Add

This item creates a new profile configured for mutual authentication. 
The new profile uses the following files :

"/SYSTEM/CLIENT_KEY.PEM"	: the RSA keys of the terminal
"/SYSTEM/CLIENT.CRT"	: the client certificate
"/SYSTEM/CA.CRT" 	: the CA certificate

These files must be previously loaded in the terminal to make the profile operational.
(Cf. section 2 below)



1.0.1 - List

This functions displays all the profiles contained in the terminal. For each profile, it displays information 
about its certificates : the validity period, the common name (CN)...


1.1 - Connection

This function performs a SSL connection. It displays the input screens to enter the parameters of the connection (TCP/IP address and port)
and the profile used for the connection.

To select the profile, please use the "Up" and "Down" arrow key to scroll the list in the combobox.


2 - To generate the keys and the certificates


Here are the OpenSSL commands, to generate the files needed by the terminal and the server.


CA certiticate :
	- Key generation
		openssl genrsa -out ca_key.pem 1024
	- Certificat generation, auto-signed.
		openssl req -config openssl.cnf -new -x509 -key ca_key.pem -out ca.crt

Server certificate :
	Generation of the Key and of the Certificate Signature Request (CSR)
		openssl req -config openssl.cnf -newkey rsa:1024 -keyout server_key.pem -out server.csr -nodes

	Signature of the certificate by the CA
		openssl ca -config openssl.cnf -keyfile ca_key.pem -cert ca.crt -in server.csr -out server.crt -notext

Client certificate (terminal) :
	Generation of the Key and of the Certificate Signature Request (CSR)
		openssl req -config openssl.cnf -newkey rsa:1024 -keyout client_key.pem -out client.csr -nodes

	Signature of the certificate by the CA
		openssl ca -config openssl.cnf -keyfile ca_key.pem -cert ca.crt -in client.csr -out client.crt -notext

To launch the test server provided with OpenSsl (listening on port 2000)

	openssl s_server -accept 2000 -cert server.crt -key server_key.pem -state -ssl3 -CAfile ca.crt -Verify 1


The openssl.cnf file is the configuration file of OpenSll

The 3 files to load into the terminal :
	client.crt			// Client certificate
	client_key.pem		// Client RSA keys 
	ca.crt		        // CA certificates

When you will load this file using LLT, their name are automatically changed in uppercase.


