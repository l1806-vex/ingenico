# dll_sec_001 - dll_sec_009
# dll_sec_001 : Configuration - PIN Entry Keyboard - Terminal

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
app.SendKeys('1')  #Choose Configuration
app.Sleep(1.0)
app.Wait('20130509-105410-453000.png')  # Config Menu
app.Sleep(1.0)
app.SendKeys('1')  #Choose PIN ENTRY KEYBOARD
app.Sleep(1.0)
app.Wait('20130509-105432-246000.png')  # Booster option
app.Sleep(1.0)
app.SendKeys('1')  #Choose Terminal booster
app.Sleep(1.0)
app.Wait('20130509-105439-391000.png') # TEST OK

# dll_sec_002 : Configuration - PIN Entry Keyboard - Pinpad

app.Sleep(2.0)
app.Wait('20130509-105403-698000.png') # DLL Security Tests
app.Sleep(1.0)
app.SendKeys('1')  #Choose Configuration
app.Sleep(1.0)
app.Wait('20130509-105410-453000.png')  # Config Menu
app.Sleep(1.0)
app.SendKeys('1')  #Choose PIN ENTRY KEYBOARD
app.Sleep(1.0)
app.Wait('20130509-105432-246000.png')  # Booster option
app.Sleep(1.0)
app.SendKeys('2')  #Choose Pinpad booster
app.Sleep(1.0)
app.Wait('20130509-105439-391000.png') # TEST OK

# dll_sec_003 : Configuration - PIN Entry Keyboard - No Booster

app.Sleep(2.0)
app.Wait('20130509-105403-698000.png') # DLL Security Tests
app.Sleep(1.0)
app.SendKeys('1')  #Choose Configuration
app.Sleep(1.0)
app.Wait('20130509-105410-453000.png')  # Config Menu
app.Sleep(1.0)
app.SendKeys('1')  #Choose PIN ENTRY KEYBOARD
app.Sleep(1.0)
app.Wait('20130509-105432-246000.png')  # Booster option
app.Sleep(1.0)
app.SendKeys('{CANCEL}')  #Do not choose booster
app.Sleep(1.0)
app.Wait('20130509-105439-391000.png') # TEST OK

# dll_sec_004 : Configuration - CARD READER LOCATION - Terminal

app.Sleep(2.0)
app.Wait('20130509-105403-698000.png') # DLL Security Tests
app.Sleep(1.0)
app.SendKeys('1')  #Choose Configuration
app.Sleep(1.0)
app.Wait('20130509-105410-453000.png')  # Config Menu
app.Sleep(1.0)
app.SendKeys('2')  #Choose CARD READER LOCATION
app.Sleep(1.0)
app.Wait('20130509-105432-246000.png')  # Booster option
app.Sleep(1.0)
app.SendKeys('1')  #Choose Terminal booster
app.Sleep(1.0)
app.Wait('20130509-105439-391000.png') # TEST OK


# dll_sec_005 : Configuration - CARD READER LOCATION - Pinpad

app.Sleep(2.0)
app.Wait('20130509-105403-698000.png') # DLL Security Tests
app.Sleep(1.0)
app.SendKeys('1')  #Choose Configuration
app.Sleep(1.0)
app.Wait('20130509-105410-453000.png')  # Config Menu
app.Sleep(1.0)
app.SendKeys('2')  #Choose CARD READER LOCATION
app.Sleep(1.0)
app.Wait('20130509-105432-246000.png')  # Booster option
app.Sleep(1.0)
app.SendKeys('2')  #Choose Pinpad booster
app.Sleep(1.0)
app.Wait('20130509-105439-391000.png') # TEST OK

# dll_sec_006 : Configuration - CARD READER LOCATION - No Booster

app.Sleep(2.0)
app.Wait('20130509-105403-698000.png') # DLL Security Tests
app.Sleep(1.0)
app.SendKeys('1')  #Choose Configuration
app.Sleep(1.0)
app.Wait('20130509-105410-453000.png')  # Config Menu
app.Sleep(1.0)
app.SendKeys('2')  #Choose CARD READER LOCATION
app.Sleep(1.0)
app.Wait('20130509-105432-246000.png')  # Booster option
app.Sleep(1.0)
app.SendKeys('{CANCEL}')  #Do not choose booster
app.Sleep(1.0)
app.Wait('20130509-105439-391000.png') # TEST OK

# dll_sec_007 : Configuration - KEY FOR DATA CIPHERING - Terminal

app.Sleep(2.0)
app.Wait('20130509-105403-698000.png') # DLL Security Tests
app.Sleep(1.0)
app.SendKeys('1')  #Choose Configuration
app.Sleep(1.0)
app.Wait('20130509-105410-453000.png')  # Config Menu
app.Sleep(1.0)
app.SendKeys('3')  #Choose KEY FOR DATA CIPHERING
app.Sleep(1.0)
app.Wait('20130509-105432-246000.png')  # Booster option
app.Sleep(1.0)
app.SendKeys('1')  #Choose Terminal booster
app.Sleep(1.0)
app.Wait('20130509-105439-391000.png') # TEST OK


# dll_sec_008 : Configuration - KEY FOR DATA CIPHERING - Pinpad

app.Sleep(2.0)
app.Wait('20130509-105403-698000.png') # DLL Security Tests
app.Sleep(1.0)
app.SendKeys('1')  #Choose Configuration
app.Sleep(1.0)
app.Wait('20130509-105410-453000.png')  # Config Menu
app.Sleep(1.0)
app.SendKeys('3')  #Choose KEY FOR DATA CIPHERING
app.Sleep(1.0)
app.Wait('20130509-105432-246000.png')  # Booster option
app.Sleep(1.0)
app.SendKeys('2')  #Choose Pinpad booster
app.Sleep(1.0)
app.Wait('20130509-105439-391000.png') # TEST OK

# dll_sec_009 : Configuration - KEY FOR DATA CIPHERING - No Booster

app.Sleep(2.0)
app.Wait('20130509-105403-698000.png') # DLL Security Tests
app.Sleep(1.0)
app.SendKeys('1')  #Choose Configuration
app.Sleep(1.0)
app.Wait('20130509-105410-453000.png')  # Config Menu
app.Sleep(1.0)
app.SendKeys('3')  #Choose KEY FOR DATA CIPHERING
app.Sleep(1.0)
app.Wait('20130509-105432-246000.png')  # Booster option
app.Sleep(1.0)
app.SendKeys('{CANCEL}')  #Do not choose booster
app.Sleep(1.0)
app.Wait('20130509-105439-391000.png') # TEST OK

app.Sleep(2.0)
app.SendKeys('{CANCEL}')
app.Sleep(2.0)
app.SendKeys('{CANCEL}')
app.Sleep(2.0)
app.SendKeys('{CANCEL}')






