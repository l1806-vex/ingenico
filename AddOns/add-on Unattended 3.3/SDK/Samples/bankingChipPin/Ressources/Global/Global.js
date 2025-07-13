//----- Initialisation function : construct the list--------------------------
function GlobalInit()
	{
	//Get window height
	if(document.clientHeight)
	  height = document.clientHeight;		  
	else if (window.innerHeight)  //FF
	  height = window.innerHeight;
	
  //Get window width  
	if(document.clientWidth)
	  width = document.clientWidth;
	else if (window.innerWidth) //FF
	  width = window.innerWidth;
	  
	//height = 240; width = 320;    
  
  //Set size to the container      
  Element = document.getElementById("Container");      
  Element.style.width = width+"px";
  Element.style.height = height+"px";
  
  //Set Size for the Content
  Element = document.getElementById("Content");
  Element.style.height = height - 40 - 24 + "px";          
	Element.style.width = width+"px";
	
	if(typeof( window[ 'Strings' ] ) == "undefined" )
	 return
	 
	if(Strings[0] && Strings[0].length > 16)
    document.getElementById("CHeader").style.fontSize="20px";
    
	Element = document.getElementById("CHeader");
  if(Element && Strings)
    Element.innerHTML = Strings[0];
    
  Element = document.getElementById("FLeft");
  if(Element && Strings)
    Element.innerHTML = Strings[1];
    
  /*Element = document.getElementById("FCenter")
  if(Element && Strings)
    Element.innerHTML = Strings[2];*/
    
  Element = document.getElementById("FRight")
  if(Element && Strings)
    Element.innerHTML = Strings[3];
	}

