<?xml version="1.0" encoding="UTF-8"?>
<!-- ============================================================ -->
<!-- dateScreen.gml                                               -->
<!-- ============================================================ -->
<!-- NOTE: You can optionally associate an "<idname>" element to  -->
<!-- any of the widgets.                                          -->
<!-- The "<idname>" element is required if the application        -->
<!-- business part (written in "C" code) needs to interact with   -->
<!-- the widget.                                                  -->
<!-- The value inside the "<idname>" element must be one of the   -->
<!-- "idname" attributes declared in the "widgetMappings.iml"     -->
<!-- file (located at project root). Please complete this file    -->
<!-- if needed.                                                   -->
<!-- The uniqueness of each ID is automatically checked (in the   -->
<!-- editor and at build time).                                   -->
<!-- ============================================================ -->
<DAL xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
  xsi:noNamespaceSchemaLocation="http://www.ingenico.com/schemas/dal/1_0">

  <version DAL_version="01.00" this_version="01.00" />

  <!-- Declare a new GOAL screen (this name is used when calling -->
  <!-- 'GL_GraphicLib_ReadResource' in order to render this      -->
  <!-- resource file). See 'Menu.c' source file.                 -->
  <goal name="dateScreen">

    <!-- Create a window -->
    <window>
      <!-- ==================== -->
      <!-- Window configuration -->
      <!-- ==================== -->
      <!-- Set no border to window --> 
      <borders>
        <left>0</left>
        <top>0</top>
        <right>0</right>
        <bottom>0</bottom>
      </borders>
      
      <!-- Set window position:                         --> 
      <!-- vertical and horizontal values in percentage -->
      <position>
        <unit>%</unit>
        <y>0</y>
        <x>0</x>
      </position>

      <!-- Set window size:                      -->
      <!-- width and height values in percentage -->
      <size>        
        <width>100</width>
        <height>100</height>
        <unit>%</unit>
      </size>

      <!-- Add children to window -->
      <children>
        <!-- ============================ -->
        <!-- Add a picture item to window -->
        <!-- ============================ -->
        <picture>
          <!-- Set picture source -->
          <source>background.jpg</source>
        </picture>

        <!-- ============================ -->
        <!-- Add a layout child to window -->
        <!-- to arrange widgets location  -->
        <!-- ============================ -->
        <layout>
          <!-- Add children to layout -->
          <children>
            <!-- ===================== -->
            <!-- Add label to children -->
            <!-- (this is the title)   -->
            <!-- ===================== -->
            <label>
              <!-- Set label item position: -->
              <!-- column and row           -->
              <item>
                <column>0</column>
                <row>0</row>
              </item>
              
              <!-- Set label expand mode (width) -->
              <expand>width</expand>

              <!-- Set label background color (blue) -->
              <backcolor>0xF00000A0</backcolor>

              <!-- Set label text color (white) -->
              <forecolor>0xFFFFFFFF</forecolor>

              <!-- Set label size:            -->
              <!-- height value in percentage -->
              <size>
                <unit>%</unit>
                <height>25</height>
              </size>

              <!-- Set label text -->
              <text>Goal Resource Sample</text>

              <!-- Set label font size:             -->
              <!-- height predefined value (MEDIUM) -->
              <font>
                <size>
                  <height>MEDIUM</height>
                </size>
              </font>

            </label>

            <!-- ====================== -->
            <!-- Add label to children  -->
            <!-- (this is the label for -->
            <!-- the edit field)        -->
            <!-- ====================== -->
            <label>
              <!-- Set label item position: -->
              <!-- column and row           -->
              <item>
                <column>0</column>
                <row>1</row>
              </item>

              <!-- Set label alignment (center) -->
              <backalign>center</backalign>

              <!-- Set label margins:                               -->
              <!-- left, top, right and bottom values in percentage -->
              <margins>
                <left>0</left>
                <top>3</top>
                <right>0</right>
                <bottom>3</bottom>
                <unit>%</unit>
              </margins>

              <!-- Set label background color (blue) -->
              <backcolor>0xF00000A0</backcolor>

              <!-- Set label text color (white) -->
              <forecolor>0xFFFFFFFF</forecolor>

              <!-- Set label text -->
              <text>Enter a date (YYYY/MM/DD):</text>

              <!-- Set label font size:             -->
              <!-- height predefined value (XSMALL) -->
              <font>
                <size>
                  <height>XSMALL</height>
                </size>
              </font>
            </label>

            <!-- ======================== -->
            <!-- Add edit field to layout -->
            <!-- (ask to enter a date)    -->
            <!-- ======================== -->
            <edit>
              <!-- Set the edit field id     -->
              <!-- ======== WARNING ======== -->
              <!-- This idname               -->
              <!-- DATE_SCREEN_EDIT_DATE     -->
              <!-- must be declared in       -->
              <!-- widgetMappings.iml        -->
              <!-- ======== WARNING ======== -->
              <idname>../widgetMappings.iml#DATE_SCREEN_EDIT_DATE</idname>

              <!-- Set edit item position: -->
              <!-- column and row          -->
              <item>
                <column>0</column>
                <row>2</row>
              </item>

              <!-- Set edit expand mode (all is expanded) -->
              <expand>all</expand>

              <!-- Set edit text alignment (left) -->
              <textalign>left</textalign>

              <!-- Set edit state (focused) -->
              <state>focused</state>

              <!-- Set edit mask -->
              <mask>/d/d/d/d///d/d///d/d/</mask>
            </edit>

            <!-- ================================== -->
            <!-- Add a layout child to main layout  -->
            <!-- to arrange button widgets location -->
            <!-- ================================== -->
            <layout>
              <!-- Set layout item position: -->
              <!-- column and row            -->
              <item>
                <column>0</column>
                <row>3</row>
              </item>

              <!-- Add children to layout -->
              <children>
                <!-- ========================== -->
                <!-- Add button field to layout -->
                <!-- (the 'Ok' button)          -->
                <!-- ========================== -->
                <button>
                  <!-- Set the button field id   -->
                  <!-- ======== WARNING ======== -->
                  <!-- This idname               -->
                  <!-- DATE_SCREEN_BUTTON_OK     -->
                  <!-- must be declared in       -->
                  <!-- widgetMappings.iml        -->
                  <!-- ======== WARNING ======== -->
	              <idname>../widgetMappings.iml#DATE_SCREEN_BUTTON_OK</idname>

                  <!-- Set button item position: -->
                  <!-- column and row            -->
                  <item>
                    <column>0</column>
                    <row>0</row>
                  </item>
                  
                  <!-- Set button margins:                              -->
                  <!-- left, top, right and bottom values in percentage -->
                  <margins>
                    <left>0</left>
                    <top>0</top>
                    <right>5</right>
                    <bottom>5</bottom>
                    <unit>%</unit>
                  </margins>

                  <!-- Set button alignment (bottom right) -->
                  <backalign>bottom,right</backalign>

                  <!-- Set button background color (green) -->
                  <backcolor>0xFF00FF00</backcolor>

                  <!-- keyboard shortcut to the validate key -->
                  <shortcut>KEY_VALID</shortcut>                  

                  <!-- Set button minimal size:              -->
                  <!-- width and height values in percentage -->
                  <minsize>
                    <unit>%</unit>
                    <width>30</width>
                    <height>0</height>
                  </minsize>

                  <!-- Set button text -->
                  <text>Ok</text>
               </button>

                <!-- ========================== -->
                <!-- Add button field to layout -->
                <!-- (the 'Cancel' button)      -->
                <!-- ========================== -->
                <button>
                  <!-- Set the button field id   -->
                  <!-- ======== WARNING ======== -->
                  <!-- This idname               -->
                  <!-- GENERIC_BUTTON_CANCEL     -->
                  <!-- must be declared in       -->
                  <!-- widgetMappings.iml        -->
                  <!-- ======== WARNING ======== -->
                  <idname>../widgetMappings.iml#GENERIC_BUTTON_CANCEL</idname>

                  <!-- Set button item position: -->
                  <!-- column and row            -->
                  <item>
                    <column>1</column>
                    <row>0</row>
                  </item>

                  <!-- Set button alignment (bottom left) -->
                  <backalign>bottom,left</backalign>

                  <!-- Set button margins:                              -->
                  <!-- left, top, right and bottom values in percentage -->
                  <margins>
                    <left>5</left>
                    <top>0</top>
                    <right>0</right>
                    <bottom>5</bottom>
                    <unit>%</unit>
                  </margins>

                  <!-- Set button background color (red) -->
                  <backcolor>0xFFFF0000</backcolor>

                  <!-- keyboard shortcut to the cancel key -->
                  <shortcut>KEY_CANCEL</shortcut>

                  <!-- Set button minimal size:              -->
                  <!-- width and height values in percentage -->
                  <minsize>
                    <unit>%</unit>
                    <width>30</width>
                    <height>0</height>
                  </minsize>

                  <!-- Set button text -->
                  <text>Cancel</text>
                </button>
              </children>
            </layout>
          </children>
        </layout>
      </children>
    </window>
  </goal>
</DAL>
