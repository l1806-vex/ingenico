var Pos = 0;

//----- Initialisation function : Set table height ---------------------------
function PinInit()
{
	//Get window height
	if(document.clientHeight)
		height = document.clientHeight;
	else if (window.innerHeight)  //FF
		height = window.innerHeight;

	//display the title or remove the header
	if(typeof( window[ 'Title' ] ) != "undefined" )
	{
		height -= 40;
		document.getElementById("CHeader").innerHTML = Title;
	}
	else
	{
		document.getElementById("Header").style.display = 'none';
	}

	Content = document.getElementById("Content");
	Content.style.height = height + "px";

	Cell = document.getElementById("Cell1");
	Cell.style.height = (0.3*height) + "px";
	Cell = document.getElementById("Cell2");
	Cell.style.height = (0.2*height) + "px";
	Cell = document.getElementById("Cell3");
	Cell.style.height = (0.5*height) + "px";
}

function KeyPressed(event)
{
	if(event.which)
		keyCode = event.which //ff non function key
	else
		keyCode = event.keyCode

	//document.getElementById("Cell1").innerHTML = keyCode;
	if(keyCode == 8)
	{
		if(Pos > 1)
		{
			Pos--;
			document.getElementById("Cell2").innerHTML = document.getElementById("Cell2").innerHTML.substr(0,(Pos*2)-1);
		}
		else
		{
			document.getElementById("Cell2").innerHTML = "&nbsp;";
			Pos = 0;
		}
	}
	else if(keyCode == 42)
	{
		if(Pos == 0)
		{
			document.getElementById("Cell2").innerHTML = "*";
			Pos++;
		}
		else if(Pos < 12)
		{
			document.getElementById("Cell2").innerHTML += " *";
			Pos++;
		}
	}
}
