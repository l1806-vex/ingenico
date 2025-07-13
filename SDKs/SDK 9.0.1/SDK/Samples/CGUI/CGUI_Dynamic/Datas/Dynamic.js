//----- Initialisation function ------------------------------------------------
  function Init()
  {
    //Request category list
    SendRequest("Cat",0);
  }

//----- When selected category change ------------------------------------------
  function CatChange()
  {
    sel = document.getElementById("Category");
    SendRequest("Prod",sel.options[sel.selectedIndex].text)
  }

//----- When selected product change -------------------------------------------
  function ProdChange()
  {
    document.location.href = "app://Dynamic?Return=Exit"
  }
  
//----- Products display function ----------------------------------------------
  function DisplayProducts(Prod)
  {
    //get the product list object
    sel = document.getElementById("Product");
    
    //empty the list
    sel.innerHTML = "";
    
    for(i=0; i<Prod.List.length; i++)
    {
      opt = document.createElement("option");
      opt.text = Prod.List[i];
      opt.name = Prod.List[i];
      sel.appendChild(opt);
    }            
  }

//----- Categories display function --------------------------------------------
  function DisplayCategories(Cat)
  {
    //get the category list object
    sel = document.getElementById("Category");
    
    //empty the list
    sel.innerHTML = "";
    
    for(i=0; i<Cat.List.length; i++)
    {
      opt = document.createElement("option");
      opt.text = Cat.List[i];
      opt.name = Cat.List[i];
      sel.appendChild(opt);
    }
    
    SendRequest("Prod",sel.options[sel.selectedIndex].text)
    
  }  
//----- XHR callback function --------------------------------------------------
  function Change()
  {
    if(this.readyState == 4)
    {  
        obj = this.responseJSON     //only for CGUI JSON native function  
        if(obj.Type == "Cat")
          DisplayCategories(obj);
        else if(obj.Type == "Prod")
          DisplayProducts(obj);                            
    }    
  }

//----- XHR creation and data send ---------------------------------------------
  function SendRequest(Cat,Prod)
  {        
    var XHR = new XMLHttpRequest();    
    XHR.onreadystatechange = Change;
    XHR.open("GET","app://Dynamic?Type="+Cat+"&Value="+Prod,true);          
    XHR.send("");  
  }

//----- Modified remove function to avoid leak ---------------------------------
  function ModifiedRemoveChild(node)
  {
    document.body.removeChild(node)
    document.getElementById("TrashCan").appendChild(node)
    document.getElementById("TrashCan").innerHTML = ""
  }


