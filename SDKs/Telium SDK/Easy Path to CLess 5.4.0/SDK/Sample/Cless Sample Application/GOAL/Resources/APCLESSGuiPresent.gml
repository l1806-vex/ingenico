<?xml version="1.0" encoding="UTF-8"?>
<!-- ============================================================ -->
<!-- SEPCGuiPresent.gml                              -->
<!-- ============================================================ -->
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
<!-- The uniqueness of each <idname> is automatically checked     -->
<!-- (in the editor and at build time).                           -->
<!-- ============================================================ -->
<DAL xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="http://www.ingenico.com/schemas/dal/1_0">
  <version DAL_version="01.00" this_version="01.00"/>
  <goal name="APCLESSGuiPresent">
    <window>
      <borders>
        <left>0</left>
        <top>0</top>
        <right>0</right>
        <bottom>0</bottom>
        <unit>pixel</unit>
        <color>0xFF000000</color>
      </borders>
      <children>
        <picture>
          <idname>../widgetMappings.iml#ID_PICTURE_CLESS</idname>
          <backalign>center</backalign>
          <size>
            <width>134</width>
            <height>80</height>
            <unit>pixel</unit>
          </size>
          <source>LOGO.png</source>
        </picture>
        <label>
          <idname>../widgetMappings.iml#ID_LABEL_AMOUNT</idname>
          <backalign>top</backalign>
          <text>AMOUNT</text>
          <font>
            <style>bold</style>
            <size>
              <height>LARGE</height>
            </size>
          </font>
        </label>
        <label>
          <idname>../widgetMappings.iml#ID_LABEL_PRESENT</idname>
          <backalign>bottom</backalign>
          <text>PRESENT CARD</text>
          <font>
            <style>bold</style>
            <size>
              <height>LARGE</height>
            </size>
          </font>
        </label>
      </children>
    </window>
  </goal>
</DAL>