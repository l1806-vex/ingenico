<?xml version="1.0" encoding="UTF-8"?>
<DAL xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="http://www.ingenico.com/schemas/dal/1_0">
  <version DAL_version="01.00" this_version="01.00"/>
  <goal name="usecalculator">
    <window>
      <children>
        <layout>
          <children>
            <include>
              <item>
                <column>0</column>
                <row>0</row>
              </item>
              <filename>Calculator.wml#calculator</filename>
            </include>
            <include>
              <item>
                <column>0</column>
                <row>1</row>
              </item>
              <filename>Calculator.wml#calculator</filename>
            </include>
            <button>
              <idname>../widgetMappings.iml#GL_ID_OK</idname>
              <item>
                <column>0</column>
                <row>3</row>
              </item>
              <text>Ok</text>
            </button>
          </children>
        </layout>
      </children>
    </window>
  </goal>
</DAL>