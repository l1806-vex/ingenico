# dll_sec_017 : Data Ciphering - Create Secret Area

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
app.SendKeys('3')  #Choose Data Ciphering
app.Sleep(1.0)
app.Wait('20130509-105513-698000.png')  # Data ciphering Menu
app.Sleep(1.0)
app.SendKeys('1')  #Choose Create Secret Area
app.Sleep(1.0)
app.Wait('20130509-105439-391000.png') # TEST OK

# dll_sec_018 : Data Ciphering - List Secret Area

app.Sleep(1.0)
app.Wait('20130509-105513-698000.png')  # Data ciphering Menu
app.Sleep(1.0)
app.SendKeys('2')  #Choose List Secret Area
app.Sleep(1.0)
app.Wait('20130509-105439-391000.png') # TEST OK

# dll_sec_019 : Data Ciphering - Load Root Key

app.Sleep(1.0)
app.Wait('20130509-105513-698000.png')  # Data ciphering Menu
app.Sleep(1.0)
app.SendKeys('3')  #Choose Load Root Key
app.Sleep(1.0)
app.Wait('20130509-105439-391000.png') # TEST OK

# dll_sec_020 : Data Ciphering - Load MAC Key

app.Sleep(1.0)
app.Wait('20130509-105513-698000.png')  # Data ciphering Menu
app.Sleep(1.0)
app.SendKeys('4')  #Choose Load MAC Key
app.Sleep(1.0)
app.Wait('20130509-105439-391000.png') # TEST OK

# dll_sec_021 : Data Ciphering - MAC Calculation

app.Sleep(1.0)
app.Wait('20130509-105513-698000.png')  # Data ciphering Menu
app.Sleep(1.0)
app.SendKeys('5')  #Choose MAC Calculation
app.Sleep(1.0)
app.Wait('20130509-105439-391000.png') # TEST OK

# dll_sec_022 : Data Ciphering - Delete MAC Key

app.Sleep(1.0)
app.Wait('20130509-105513-698000.png')  # Data ciphering Menu
app.Sleep(1.0)
app.SendKeys('6')  #Choose Delete MAC Key
app.Sleep(1.0)
app.Wait('20130509-105439-391000.png') # TEST OK

# dll_sec_030 : Data Ciphering - Load MAC Key twice

app.Sleep(1.0)
app.Wait('20130509-105513-698000.png')  # Data ciphering Menu
app.Sleep(1.0)
app.SendKeys('4')  #Choose Load MAC Key
app.Sleep(1.0)
app.Wait('20130509-105439-391000.png') # TEST OK
app.Sleep(2.0)
app.SendKeys('4')  #Choose Load MAC Key again
app.Sleep(1.0)
app.Wait('20130509-105505-430000.png') # TEST FAILED

# dll_sec_031 : Data Ciphering -  Existing MAC Key Delete then Mac Calculate

app.Sleep(1.0)
app.Wait('20130509-105513-698000.png')  # Data ciphering Menu
app.Sleep(1.0)
app.SendKeys('6')  #Choose Delete MAC Key
app.Sleep(1.0)
app.Wait('20130509-105439-391000.png') # TEST OK
app.Sleep(2.0)
app.SendKeys('5')  #Choose MAC Calculate
app.Sleep(1.0)
app.Wait('20130509-105505-430000.png') # TEST FAILED

# dll_sec_032 : Data Ciphering -  No Loaded MAC Key, Delete MAC Key

app.Sleep(1.0)
app.Wait('20130509-105513-698000.png')  # Data ciphering Menu
app.Sleep(1.0)
app.SendKeys('6')  #Choose Delete MAC Key
app.Sleep(1.0)
app.Wait('20130509-105505-430000.png') # TEST FAILED

# dll_sec_033 : Load MAC, Restart, Load MAC

app.Sleep(1.0)
app.Wait('20130509-105513-698000.png')  # Data ciphering Menu
app.Sleep(1.0)
app.SendKeys('4')  #Choose Load MAC Key
app.Sleep(1.0)
app.Wait('20130509-105439-391000.png') # TEST OK
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
app.SendKeys('3')  #Choose Data Ciphering
app.Sleep(1.0)
app.Wait('20130509-105513-698000.png')  # Data ciphering Menu
app.Sleep(1.0)
app.SendKeys('4')  #Choose Load MAC key again
app.Sleep(1.0)
app.Wait('20130509-105505-430000.png') # TEST FAILED

# dll_sec_034 : MAC Key loaded, Restart, MAC Calculate

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
app.SendKeys('3')  #Choose Data Ciphering
app.Sleep(1.0)
app.Wait('20130509-105513-698000.png')  # Data ciphering Menu
app.Sleep(2.0)
app.SendKeys('5')  #Choose MAC Calculation
app.Sleep(1.0)
app.Wait('20130509-105439-391000.png') # TEST OK

# dll_sec_035 : MAC Key loaded, Restart, Delete MAC Key

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
app.SendKeys('3')  #Choose Data Ciphering
app.Sleep(1.0)
app.Wait('20130509-105513-698000.png')  # Data ciphering Menu
app.Sleep(2.0)
app.SendKeys('6')  #Choose Delete MAC key
app.Sleep(1.0)
app.Wait('20130509-105439-391000.png') # TEST OK

# dll_sec_036 : MAC Key deleted, Restart, Delete MAC Key 2nd time

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
app.SendKeys('3')  #Choose Data Ciphering
app.Sleep(1.0)
app.Wait('20130509-105513-698000.png')  # Data ciphering Menu
app.Sleep(2.0)
app.SendKeys('6')  #Choose Delete MAC key
app.Sleep(1.0)
app.Wait('20130509-105505-430000.png') # TEST FAILED
app.Sleep(2.0)
app.SendKeys('A')
app.Sleep(2.0)
app.SendKeys('A')
app.Sleep(2.0)
app.SendKeys('A')



