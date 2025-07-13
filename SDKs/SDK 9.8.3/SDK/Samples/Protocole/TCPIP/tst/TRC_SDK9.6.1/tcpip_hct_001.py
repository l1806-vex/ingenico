# test client - successful
app.Sleep(1)                                        # recorded
app.SendKey('4')                                      # recorded
app.WaitText('Launching Client Test.')                # recorded
app.WaitText('Creating socket...')                      # recorded
app.WaitText('Connec1ing to server.')                 # recorded
app.WaitText('Sending')                               # recorded
app.WaitText('Shutting down connection')              # recorded

