# dll_sec_010 : PIN Entry - Create Secret Area

app.SendKeys('F')
app.Sleep(2.0)
app.SendKeys('1')  #Choose DLL Sec
app.Sleep(1.0)
app.Wait('20130509-105210-661000.png')  # DLL Security Sample
app.Sleep(1.0)
app.SendKeys('2')  #Choose DLL Security Tests
app.Sleep(1.0)
app.Wait('20130509-105403-698000.png') # DLL Security Tests
app.Sleep(1.0)
app.SendKeys('2')  #Choose PIN Entry
app.Sleep(1.0)
app.Wait('20130509-105449-392000.png')  # PIN Entry Menu
app.Sleep(1.0)
app.SendKeys('1')  #Choose Create Secret Area
app.Sleep(1.0)
app.Wait('20130509-105439-391000.png') # TEST OK

# dll_sec_011 : PIN Entry - List Secret Area

app.Sleep(1.0)
app.Wait('20130509-105449-392000.png')  # PIN Entry Menu
app.Sleep(1.0)
app.SendKeys('2')  #Choose List Secret Area
app.Sleep(1.0)
app.Wait('20130509-105439-391000.png') # TEST OK

# dll_sec_012 : PIN Entry - Load Root Key

app.Sleep(1.0)
app.Wait('20130509-105449-392000.png')  # PIN Entry Menu
app.Sleep(1.0)
app.SendKeys('3')  #Choose Load Root Key
app.Sleep(1.0)
app.Wait('20130509-105439-391000.png') # TEST OK

# dll_sec_013 : PIN Entry - Load PIN Key

app.Sleep(1.0)
app.Wait('20130509-105449-392000.png')  # PIN Entry Menu
app.Sleep(1.0)
app.SendKeys('4')  #Choose Load PIN Key
app.Sleep(1.0)
app.Wait('20130509-105439-391000.png') # TEST OK

# dll_sec_014 : PIN Entry - PIN ENTRY

app.Sleep(1.0)
app.Wait('20130509-105449-392000.png')  # PIN Entry Menu
app.Sleep(1.0)
app.SendKeys('5')  #Choose PIN Entry
app.Sleep(1.0)
app.Wait('20130508-155420-984000.png') #PIN Entry prompt
app.Sleep(1.0)
app.Pin('1234') #enter PIN
app.Sleep(5.0)
app.Wait('20130509-105439-391000.png') # TEST OK

# dll_sec_015 : PIN Entry - Encipher PIN

app.Sleep(1.0)
app.Wait('20130509-105449-392000.png')  # PIN Entry Menu
app.Sleep(1.0)
app.SendKeys('6')  #Choose Encipher PIN
app.Sleep(1.0)
app.Wait('20130509-105439-391000.png') # TEST OK

# dll_sec_016 : PIN Entry - Delete PIN Key

app.Sleep(1.0)
app.Wait('20130509-105449-392000.png')  # PIN Entry Menu
app.Sleep(1.0)
app.SendKeys('7')  #Choose Delete PIN key
app.Sleep(1.0)
app.Wait('20130509-105439-391000.png') # TEST OK

# dll_sec_023 : PIN Entry - Load PIN Key twice

app.Sleep(1.0)
app.Wait('20130509-105449-392000.png')  # PIN Entry Menu
app.Sleep(1.0)
app.SendKeys('4')  #Choose Load PIN key
app.Sleep(1.0)
app.Wait('20130509-105439-391000.png') # TEST OK
app.Sleep(3.0)
app.SendKeys('4')  #Choose Load PIN key again
app.Sleep(1.0)
app.Wait('20130509-105505-430000.png') # TEST FAILED

# dll_sec_024 : PIN Entry - Existing Load PIN, Delete then Encipher

app.Sleep(1.0)
app.Wait('20130509-105449-392000.png')  # PIN Entry Menu
app.Sleep(2.0)
app.SendKeys('7')  #Choose Delete PIN key
app.Sleep(1.0)
app.Wait('20130509-105439-391000.png') # TEST OK
app.Sleep(2.0)
app.SendKeys('6')  #Choose Encipher PIN key
app.Sleep(1.0)
app.Wait('20130509-105505-430000.png') # TEST FAILED

# dll_sec_025 : PIN Entry - No Loaded PIN, Delete PIN

app.Sleep(1.0)
app.Wait('20130509-105449-392000.png')  # PIN Entry Menu
app.Sleep(1.0)
app.SendKeys('7')  #Choose Delete PIN key
app.Sleep(1.0)
app.Wait('20130509-105505-430000.png') # TEST FAILED

# dll_sec_026 : PIN Entry - Load PIN, Restart, Load PIN

app.Sleep(1.0)
app.Wait('20130509-105449-392000.png')  # PIN Entry Menu
app.Sleep(1.0)
app.SendKeys('4')  #Choose Load PIN key
app.Sleep(1.0)
app.Wait('20130509-105439-391000.png') # TEST OK
app.Reset()                                           # recorded
app.WaitForReboot()
app.Sleep(10)
app.SendKeys('F')
app.Sleep(2.0)
app.SendKeys('1')  #Choose DLL Sec
app.Sleep(1.0)
app.Wait('20130509-105210-661000.png')  # DLL Security Sample
app.Sleep(1.0)
app.SendKeys('2')  #Choose DLL Security Tests
app.Sleep(1.0)
app.Wait('20130509-105403-698000.png') # DLL Security Tests
app.Sleep(1.0)
app.SendKeys('2')  #Choose PIN Entry
app.Sleep(1.0)
app.Wait('20130509-105449-392000.png')  # PIN Entry Menu
app.Sleep(1.0)
app.SendKeys('4')  #Choose Load PIN Key again
app.Sleep(1.0)
app.Wait('20130509-105505-430000.png') # TEST FAILED

# dll_sec_027 : PIN Entry - PIN loaded, Restart, Encipher PIN

app.Sleep(1.0)
app.Reset()                                           # recorded
app.WaitForReboot()
app.Sleep(10)
app.SendKeys('F')
app.Sleep(2.0)
app.SendKeys('1')  #Choose DLL Sec
app.Sleep(1.0)
app.Wait('20130509-105210-661000.png')  # DLL Security Sample
app.Sleep(1.0)
app.SendKeys('2')  #Choose DLL Security Tests
app.Sleep(1.0)
app.Wait('20130509-105403-698000.png') # DLL Security Tests
app.Sleep(1.0)
app.SendKeys('2')  #Choose PIN Entry
app.Sleep(1.0)
app.Wait('20130509-105449-392000.png')  # PIN Entry Menu
app.Sleep(1.0)
app.SendKeys('6')  #Choose Encipher PIN
app.Sleep(1.0)
app.Wait('20130509-105505-430000.png') # TEST FAILED

# dll_sec_028 : PIN Entry - PIN loaded, Restart, Delete PIN Key

app.Sleep(1.0)
app.Reset()                                           # recorded
app.WaitForReboot()
app.Sleep(10)
app.SendKeys('F')
app.Sleep(2.0)
app.SendKeys('1')  #Choose DLL Sec
app.Sleep(1.0)
app.Wait('20130509-105210-661000.png')  # DLL Security Sample
app.Sleep(1.0)
app.SendKeys('2')  #Choose DLL Security Tests
app.Sleep(1.0)
app.Wait('20130509-105403-698000.png') # DLL Security Tests
app.Sleep(1.0)
app.SendKeys('2')  #Choose PIN Entry
app.Sleep(1.0)
app.Wait('20130509-105449-392000.png')  # PIN Entry Menu
app.Sleep(1.0)
app.SendKeys('7')  #Choose Delete PIN Key
app.Sleep(1.0)
app.Wait('20130509-105439-391000.png') # TEST OK

# dll_sec_029 : PIN Entry - Deleted PIN, Restart, Delete PIN Key Again

app.Sleep(1.0)
app.Reset()                                           # recorded
app.WaitForReboot()
app.Sleep(10)
app.SendKeys('F')
app.Sleep(2.0)
app.SendKeys('1')  #Choose DLL Sec
app.Sleep(1.0)
app.Wait('20130509-105210-661000.png')  # DLL Security Sample
app.Sleep(1.0)
app.SendKeys('2')  #Choose DLL Security Tests
app.Sleep(1.0)
app.Wait('20130509-105403-698000.png') # DLL Security Tests
app.Sleep(1.0)
app.SendKeys('2')  #Choose PIN Entry
app.Sleep(1.0)
app.Wait('20130509-105449-392000.png')  # PIN Entry Menu
app.Sleep(1.0)
app.SendKeys('7')  #Choose Delete PIN Key
app.Sleep(1.0)
app.Wait('20130509-105505-430000.png') # TEST FAILED
app.Sleep(2.0)
app.SendKeys('A')
app.Sleep(2.0)
app.SendKeys('A')
app.Sleep(2.0)
app.SendKeys('A')





