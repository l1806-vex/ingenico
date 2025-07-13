//----- Keypress event handler called on the body ------------------------------

var RED_KEY = 0x1B;     //telium red key code 
var GREEN_KEY = 0x0D;   //telium green key code

function keypress(event)
{

  //See the code of the key pressed
  switch(event.keyCode)
  {
    //Cancel form and signal application that we canceled
    case RED_KEY:
      document.location.href="app://Retrieve?Return=Cancel";
      break;
    
    //Submit the form
    case GREEN_KEY:
      document.getElementById('form').submit();
      break;
  }   
}
