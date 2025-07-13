# press any key during network info display
app.Sleep(1)                                        # recorded
app.SendKey('2')                                      # recorded
app.WaitText('Local Addr: 192.168.1.147')             # recorded
app.Sleep(1)                                        # recorded
app.SendKey('0')                                      # recorded
app.WaitText('Netmask: 255.255.255.0') 
app.Sleep(1)                                        # recorded
app.SendKey('8') 
  



