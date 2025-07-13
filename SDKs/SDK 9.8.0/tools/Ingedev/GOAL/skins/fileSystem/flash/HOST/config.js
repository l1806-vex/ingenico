{
	"X":0,"Y":0,   // RB
	//~ "X":320, "Y":0, // NT
	//~ "X":-900,"Y":-130,
	//~ "X":0, "Y":100, // RB2
	"default":2,
	"viewers":
	[
		{ "title":"iCT220 128x64" , "terminal":"iCT220", "X":"$X", "Y":"$Y", "x":320, "y":480, "width":128, "height":64,  "color": 1, "scale":2, "touch":false},
		{ "title":"iCT250 320x240", "terminal":"iCT250", "X":"$X", "Y":"$Y", "x":0,   "y":480, "width":320, "height":240, "color":16, "scale":1, "touch":false},
		{ "title":"iWL280 240x320", "terminal":"iWL280", "X":"$X", "Y":"$Y", "x":320, "y":608, "width":240, "height":320, "color":32, "scale":1, "touch":true },
		{ "title":"iWL350 320x480", "terminal":"iWL350", "X":"$X", "Y":"$Y", "x":0,   "y":720, "width":320, "height":480, "color":32, "scale":1, "touch":true },
		{ "title":"iSC250 480x272", "terminal":"iSC250", "X":"$X", "Y":"$Y", "x":320, "y":928, "width":480, "height":272, "color":32, "scale":1, "touch":true },
		{ "title":"iSC350 640x480", "terminal":"iSC350", "X":"$X", "Y":"$Y", "x":0,   "y":0,   "width":640, "height":480, "color":32, "scale":1, "touch":true },
        { "title":"iSC480 800x480", "terminal":"iSC480", "X":"$X", "Y":"$Y", "x":640, "y":0,   "width":800, "height":480, "color":32, "scale":1, "touch":true },
	],
	
	// Win32 allocation manager
	"win32":
	{
		// Allocation break point 
		//~ "break":1144,
		
		// Allocation statistic 
		//~ "stat" :true,
		
		// Allocation trace
		//~ "trace":true,
	},
	
	// Telium allocation manager
	"telium":
	{
		// Allocation break point 
		//~ "break":2746,
	}
}