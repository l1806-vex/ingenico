# EMV Contact card entry
                                  
app.SendKeys('1')                                      # recorded
app.Sleep(2)                                          # recorded
app.SendKeys('2')                                      # recorded
app.Sleep(2)                                          # recorded
app.SendKeys('3')
app.Sleep(2)                                          # recorded
app.SendKeys('4')
app.Sleep(2)                                          # recorded
app.SendKeys('{ENTER}') 
app.Sleep(2)
app.InsertCard()
app.Sleep(1.0)
app.RemoveCard()

