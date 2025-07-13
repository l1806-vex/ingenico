<?xml version="1.0" encoding="UTF-8"?>
<DAL xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="http://www.ingenico.com/schemas/dal/1_0">
	<version DAL_version="01.00" this_version="01.00" />
	<goal name="StepFooter">
		<window>
			<children>
				<layout>
					<children>
						<label>
							<text>Information</text>
							<item>
								<column>0</column>
								<row>0</row>
							</item>
							<backcolor>0xFF800080</backcolor>
							<forecolor>0xFFFFFFFF</forecolor>
							<expand>width</expand>
						</label>
						<layout>
							<item>
								<column>0</column>
								<row>2</row>
							</item>
							<children>
								<button>
									<text>OK</text>
									<item>
										<column>0</column>
										<row>0</row>
									</item>
								</button>
								<button>
									<text>Cancel</text>
									<item>
										<column>1</column>
										<row>0</row>
									</item>
								</button>
							</children>
						</layout>
					</children>
				</layout>
			</children>
		</window>
	</goal>
</DAL>
