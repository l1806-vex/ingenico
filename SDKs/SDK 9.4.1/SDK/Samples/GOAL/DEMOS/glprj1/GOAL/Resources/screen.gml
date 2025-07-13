<DAL xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
	xsi:noNamespaceSchemaLocation="http://www.ingenico.com/schemas/dal/1_0">

	<version DAL_version="01.00" this_version="01.00" />
	<goal name="inputDetailsScreen">
		<window>
			<children>
				<layout>
					<children>
						<list>
							<items>
								<label>
									<text>Name</text>
									<backalign>left</backalign>
									<idname>../widgetMappings.iml#ID_LABEL_NAME</idname>
								</label>
								<edit>
									<text>Santa-Clauss</text>
									<textalign>left</textalign>
									<idname>../widgetMappings.iml#ID_EDIT_NAME</idname>
								</edit>
								<label>
									<text>Birthday</text>
									<idname>../widgetMappings.iml#ID_LABEL_AGE</idname>
								</label>
								<edit>
									<mask>/d/d/d/d/./d/d/./d/d/</mask>
									<textalign>left</textalign>
									<text>1898.12.05</text>
									<idname>../widgetMappings.iml#ID_EDIT_AGE</idname>
								</edit>
								<radiobutton>
									<text>Female</text>
									<backalign>left</backalign>
									<state>unchecked</state>
									<idname>../widgetMappings.iml#ID_RADIO_FEMALE</idname>
								</radiobutton>
								<radiobutton>
									<text>Male</text>
									<backalign>right</backalign>
									<state>checked</state>
									<idname>../widgetMappings.iml#ID_RADIO_MALE</idname>
								</radiobutton>

								<checkbutton>
									<text>Married</text>
									<idname>../widgetMappings.iml#ID_CHECK_MARITAL</idname>
								</checkbutton>

								<label>
									<text>ZIP Code</text>
									<idname>../widgetMappings.iml#ID_LABEL_ZIP</idname>
								</label>
								<edit>
									<text>07263</text>
									<mask>/d/d/d/d/d</mask>
									<idname>../widgetMappings.iml#ID_EDIT_ZIP</idname>
								</edit>
								<label>
									<text>City</text>
									<idname>../widgetMappings.iml#ID_LABEL_CITY</idname>
								</label>
								<edit>
									<text>North Pole</text>
									<idname>../widgetMappings.iml#ID_EDIT_CITY</idname>
								</edit>
							</items>
						</list>

						<button>
							<backalign>left</backalign>
							<grow>width</grow>
							<text>Cancel</text>
							<item>
								<column>0</column>
								<row>1</row>
							</item>
							<margins>
								<left>10</left>
								<bottom>1</bottom>
								<right>1</right>
								<top>1</top>
								<unit>%</unit>
							</margins>
							<idname>../widgetMappings.iml#ID_BUTTON_CANCEL</idname>
						</button>
						<button>
							<grow>width</grow>
							<backalign>right</backalign>
							<text>OK</text>

							<item>
								<column>0</column>
								<row>1</row>
							</item>
							<idname>../widgetMappings.iml#ID_BUTTON_OK</idname>
							<margins>
								<right>10</right>
								<unit>%</unit>
							</margins>
						</button>
					</children>
				</layout>
			</children>
			<position>
				<y>0</y>
				<x>0</x>
				<unit>%</unit>
			</position>
			<size>
				<width>100</width>
				<unit>%</unit>
				<height>100</height>
			</size>
		</window>

	</goal>
</DAL>
