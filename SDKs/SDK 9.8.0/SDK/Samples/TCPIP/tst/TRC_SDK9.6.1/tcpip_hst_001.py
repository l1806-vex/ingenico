# test server - successful
app.SendKey('3')                                      # recorded
app.WaitText('Launching Server Test...')              # recorded
app.WaitText('Creating socket...')                    # recorded
app.WaitText('Listening...')                          # listening message
app.WaitText('Accepted connection!')                  # Acception Connection
app.WaitText('Receiving')                             # recorded
app.WaitText('Sending')                               # listening message
app.WaitText('Listening...')  
app.Reset()                                           # recorded
app.WaitForReboot()
app.Sleep(9)
execfile(os.path.join(my_dir, "test_startupapp.py"))



