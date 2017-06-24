<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="14008000">
	<Item Name="My Computer" Type="My Computer">
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="Arduino Reader" Type="Folder">
			<Item Name="ArduinoReader.vi" Type="VI" URL="../ArduinoReader.vi"/>
		</Item>
		<Item Name="Plate Reader" Type="Folder">
			<Property Name="NI.SortType" Type="Int">3</Property>
			<Item Name="SubVIs" Type="Folder">
				<Item Name="Event Handlers" Type="Folder">
					<Item Name="EventHandleCommandCompleted.vi" Type="VI" URL="../EventHandleCommandCompleted.vi"/>
					<Item Name="EventHandleCommandCompletedData.ctl" Type="VI" URL="../EventHandleCommandCompletedData.ctl"/>
					<Item Name="EventHandleErrorReport.vi" Type="VI" URL="../EventHandleErrorReport.vi"/>
					<Item Name="EventHandleErrorReportData.ctl" Type="VI" URL="../EventHandleErrorReportData.ctl"/>
					<Item Name="EventHandleInstrumentStatusChanged.vi" Type="VI" URL="../EventHandleInstrumentStatusChanged.vi"/>
					<Item Name="EventHandleInstrumentStatusChangedData.ctl" Type="VI" URL="../EventHandleInstrumentStatusChangedData.ctl"/>
				</Item>
				<Item Name="AdvanceNextColumn.vi" Type="VI" URL="../AdvanceNextColumn.vi"/>
				<Item Name="AnalyzeColumnData.vi" Type="VI" URL="../AnalyzeColumnData.vi"/>
				<Item Name="CommandReadActiveColumn.vi" Type="VI" URL="../CommandReadActiveColumn.vi"/>
				<Item Name="ConvertTimestamp.vi" Type="VI" URL="../ConvertTimestamp.vi"/>
				<Item Name="DelayForReadStart.vi" Type="VI" URL="../DelayForReadStart.vi"/>
				<Item Name="DestructSMPAutomationClient.vi" Type="VI" URL="../DestructSMPAutomationClient.vi"/>
				<Item Name="DetectChange.vi" Type="VI" URL="../DetectChange.vi"/>
				<Item Name="DisconnectEventHandlers.vi" Type="VI" URL="../DisconnectEventHandlers.vi"/>
				<Item Name="GetDataCopy.vi" Type="VI" URL="../GetDataCopy.vi"/>
				<Item Name="GetDataFromPreviousRead.vi" Type="VI" URL="../GetDataFromPreviousRead.vi"/>
				<Item Name="GetPosition.vi" Type="VI" URL="../GetPosition.vi"/>
				<Item Name="GetTimingProfileValues.vi" Type="VI" URL="../GetTimingProfileValues.vi"/>
				<Item Name="HandleErrorReport.vi" Type="VI" URL="../HandleErrorReport.vi"/>
				<Item Name="HandleLabVIEWErrors.vi" Type="VI" URL="../HandleLabVIEWErrors.vi"/>
				<Item Name="InitializeSMPAutomationClient.vi" Type="VI" URL="../InitializeSMPAutomationClient.vi"/>
				<Item Name="LogColumnData.vi" Type="VI" URL="../LogColumnData.vi"/>
				<Item Name="ParseRawResult.vi" Type="VI" URL="../ParseRawResult.vi"/>
				<Item Name="ReconnectToInstrument.vi" Type="VI" URL="../ReconnectToInstrument.vi"/>
				<Item Name="RespondToStopButton.vi" Type="VI" URL="../RespondToStopButton.vi"/>
				<Item Name="RestartSMP.vi" Type="VI" URL="../RestartSMP.vi"/>
				<Item Name="SelectActiveColumn.vi" Type="VI" URL="../SelectActiveColumn.vi"/>
				<Item Name="UpdateGrid.vi" Type="VI" URL="../UpdateGrid.vi"/>
				<Item Name="ValidateTiming.vi" Type="VI" URL="../ValidateTiming.vi"/>
				<Item Name="WaitForNextReadTriggerTime.vi" Type="VI" URL="../WaitForNextReadTriggerTime.vi"/>
				<Item Name="WaitForReadCompletion.vi" Type="VI" URL="../WaitForReadCompletion.vi"/>
			</Item>
			<Item Name="Typedefs" Type="Folder">
				<Item Name="ReadSpecifications.ctl" Type="VI" URL="../ReadSpecifications.ctl"/>
				<Item Name="PlateReaderState.ctl" Type="VI" URL="../PlateReaderState.ctl"/>
				<Item Name="ColumnData.ctl" Type="VI" URL="../ColumnData.ctl"/>
				<Item Name="MasterCluster.ctl" Type="VI" URL="../MasterCluster.ctl"/>
				<Item Name="RPMUpdateData.ctl" Type="VI" URL="../RPMUpdateData.ctl"/>
				<Item Name="TimingProfile.ctl" Type="VI" URL="../TimingProfile.ctl"/>
			</Item>
			<Item Name="PlateReaderV1.vi" Type="VI" URL="../PlateReaderV1.vi"/>
			<Item Name="PlateReaderV2.vi" Type="VI" URL="../PlateReaderV2.vi"/>
			<Item Name="PlateReaderGlobal.vi" Type="VI" URL="../PlateReaderGlobal.vi"/>
		</Item>
		<Item Name="SoftMax Pro 6.5.1 Automation SDK" Type="Folder"/>
		<Item Name="Utilities" Type="Folder">
			<Item Name="LogTimeDataExtract.vi" Type="VI" URL="../LogTimeDataExtract.vi"/>
			<Item Name="PlateReaderTest.vi" Type="VI" URL="../PlateReaderTest.vi"/>
			<Item Name="PlateReaderTimeTest.vi" Type="VI" URL="../PlateReaderTimeTest.vi"/>
		</Item>
		<Item Name="BioServeSquareLogo.ico" Type="Document" URL="../BioServeSquareLogo.ico"/>
		<Item Name="Clinostat.aliases" Type="Document" URL="../Clinostat.aliases"/>
		<Item Name="Clinostat.lvlps" Type="Document" URL="../Clinostat.lvlps"/>
		<Item Name="CloseSMPDocument.vi" Type="VI" URL="../CloseSMPDocument.vi"/>
		<Item Name="ConvertTimeStampToHHMMSS.vi" Type="VI" URL="../ConvertTimeStampToHHMMSS.vi"/>
		<Item Name="GenerateExcelHeader.vi" Type="VI" URL="../GenerateExcelHeader.vi"/>
		<Item Name="GenerateWellCoordinates.vi" Type="VI" URL="../GenerateWellCoordinates.vi"/>
		<Item Name="GetLogRefnums.vi" Type="VI" URL="../GetLogRefnums.vi"/>
		<Item Name="LogColumnDataToExcel.vi" Type="VI" URL="../LogColumnDataToExcel.vi"/>
		<Item Name="PadZeroes.vi" Type="VI" URL="../PadZeroes.vi"/>
		<Item Name="PlateSize.ctl" Type="VI" URL="../PlateSize.ctl"/>
		<Item Name="ReadBackup.vi" Type="VI" URL="../ReadBackup.vi"/>
		<Item Name="WriteBackup.vi" Type="VI" URL="../WriteBackup.vi"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="List Directory and LLBs.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/libraryn.llb/List Directory and LLBs.vi"/>
				<Item Name="NI_AALBase.lvlib" Type="Library" URL="/&lt;vilib&gt;/Analysis/NI_AALBase.lvlib"/>
				<Item Name="Open Sessions.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/visa.llb/Open Sessions.vi"/>
				<Item Name="Recursive File List.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/libraryn.llb/Recursive File List.vi"/>
				<Item Name="Space Constant.vi" Type="VI" URL="/&lt;vilib&gt;/dlg_ctls.llb/Space Constant.vi"/>
				<Item Name="System Exec.vi" Type="VI" URL="/&lt;vilib&gt;/Platform/system.llb/System Exec.vi"/>
				<Item Name="VISA Configure Serial Port" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port"/>
				<Item Name="VISA Configure Serial Port (Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Instr).vi"/>
				<Item Name="VISA Configure Serial Port (Serial Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Serial Instr).vi"/>
			</Item>
			<Item Name="lvanlys.dll" Type="Document" URL="/&lt;resource&gt;/lvanlys.dll"/>
			<Item Name="mscorlib" Type="VI" URL="mscorlib">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="SoftMaxPro.AutomationClient.dll" Type="Document" URL="../../../../Program Files (x86)/Molecular Devices/SoftMax Pro 6.5.1 Automation SDK/SoftMaxPro.AutomationClient.dll"/>
		</Item>
		<Item Name="Build Specifications" Type="Build">
			<Item Name="ArduinoReader" Type="EXE">
				<Property Name="App_copyErrors" Type="Bool">true</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{40986970-390E-43D7-BBC0-9494CDF50F20}</Property>
				<Property Name="App_INI_GUID" Type="Str">{91416850-99D1-4DDA-B5AB-989453AB74CF}</Property>
				<Property Name="App_serverConfig.httpPort" Type="Int">8002</Property>
				<Property Name="Bld_autoIncrement" Type="Bool">true</Property>
				<Property Name="Bld_buildCacheID" Type="Str">{C2866FF8-7179-47F8-A99D-D583161FE821}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">ArduinoReader</Property>
				<Property Name="Bld_excludeInlineSubVIs" Type="Bool">true</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../Builds/ArduinoReader</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToProject</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{3F149307-54A4-4753-9DD1-6912716A29B6}</Property>
				<Property Name="Bld_version.build" Type="Int">1</Property>
				<Property Name="Bld_version.major" Type="Int">1</Property>
				<Property Name="Destination[0].destName" Type="Str">ArduinoReader.exe</Property>
				<Property Name="Destination[0].path" Type="Path">../Builds/ArduinoReader/ArduinoReader.exe</Property>
				<Property Name="Destination[0].path.type" Type="Str">relativeToProject</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">Support Directory</Property>
				<Property Name="Destination[1].path" Type="Path">../Builds/ArduinoReader/data</Property>
				<Property Name="Destination[1].path.type" Type="Str">relativeToProject</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Exe_iconItemID" Type="Ref">/My Computer/BioServeSquareLogo.ico</Property>
				<Property Name="Source[0].itemID" Type="Str">{B75EC566-3416-455E-A27D-F97EBE6C5632}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/My Computer/Arduino Reader/ArduinoReader.vi</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="SourceCount" Type="Int">2</Property>
				<Property Name="TgtF_fileDescription" Type="Str">ArduinoReader</Property>
				<Property Name="TgtF_internalName" Type="Str">ArduinoReader</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">Copyright © 2016 </Property>
				<Property Name="TgtF_productName" Type="Str">ArduinoReader</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{57145456-7325-4274-85DA-DF4D6571D2EF}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">ArduinoReader.exe</Property>
			</Item>
			<Item Name="PlateReader" Type="EXE">
				<Property Name="App_copyErrors" Type="Bool">true</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{D51DC175-FA1A-44D1-8FC1-8313D7B374BF}</Property>
				<Property Name="App_INI_GUID" Type="Str">{90801F0E-0519-4797-945B-268132CC13B8}</Property>
				<Property Name="App_serverConfig.httpPort" Type="Int">8002</Property>
				<Property Name="Bld_autoIncrement" Type="Bool">true</Property>
				<Property Name="Bld_buildCacheID" Type="Str">{554F27E8-CF0E-4192-A4ED-85C98A4FC73C}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">PlateReader</Property>
				<Property Name="Bld_excludeInlineSubVIs" Type="Bool">true</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../Builds/PlateReader</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToProject</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{DF44FF6B-C2F7-4ACF-8B49-53EA3CA94A2C}</Property>
				<Property Name="Bld_version.build" Type="Int">89</Property>
				<Property Name="Bld_version.major" Type="Int">1</Property>
				<Property Name="Destination[0].destName" Type="Str">PlateReader.exe</Property>
				<Property Name="Destination[0].path" Type="Path">../Builds/PlateReader/PlateReader.exe</Property>
				<Property Name="Destination[0].path.type" Type="Str">relativeToProject</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">Support Directory</Property>
				<Property Name="Destination[1].path" Type="Path">../Builds/PlateReader/data</Property>
				<Property Name="Destination[1].path.type" Type="Str">relativeToProject</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Exe_iconItemID" Type="Ref">/My Computer/BioServeSquareLogo.ico</Property>
				<Property Name="Source[0].itemID" Type="Str">{EA524C32-C438-4278-9039-A00F3311EC56}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/My Computer/Arduino Reader/ArduinoReader.vi</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="Source[2].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[2].itemID" Type="Ref">/My Computer/Plate Reader/PlateReaderV2.vi</Property>
				<Property Name="Source[2].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[2].type" Type="Str">VI</Property>
				<Property Name="SourceCount" Type="Int">3</Property>
				<Property Name="TgtF_companyName" Type="Str">BioServe Space Technologies</Property>
				<Property Name="TgtF_fileDescription" Type="Str">ArduinoReader</Property>
				<Property Name="TgtF_internalName" Type="Str">ArduinoReader</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">Copyright © 2016 </Property>
				<Property Name="TgtF_productName" Type="Str">ArduinoReader</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{A0EDC48A-4698-43FF-AD66-BCCAEBD2134D}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">PlateReader.exe</Property>
			</Item>
		</Item>
	</Item>
</Project>
