$settingsFile = Get-Content .\settings.properties
$executionPropsFile = Get-Content .\execution.properties

function getPropertyValue
{
	$global:property = $row.Split("=")[0]
	$global:value = $row.Split("=")[1]
}

function handleProperty
{
	switch ($property)
	{
		sdk.dir {setLocalProperties; break}
		target {$global:property = "targetSdkVersion"; $global:value = $value.Replace("android-", ""); setBuildGradleProperty; break}
		client.title {$global:appName = $value + ".apk"; setValueInStringXML "app_name" $value; break;}
		client.version.code {$global:property = "versionCode"; setBuildGradleProperty; break}
		client.version.name {$global:property = "versionName"; updateValueWithQuatationMarks; setBuildGradleProperty; break}
		package.name {$global:value = $value.toLower(); $global:property = "applicationId"; setApplicationId; break}
		key.store {$global:property = "storeFile file"; updateValueWithBracketsAndQuatationMarks; setBuildGradleProperty; break}
		key.store.password {$global:property = "storePassword"; updateValueWithQuatationMarks; setBuildGradleProperty; break}
		key.alias {$global:property = "keyAlias"; updateValueWithQuatationMarks; setBuildGradleProperty; break}
		key.alias.password {$global:property = "keyPassword"; updateValueWithQuatationMarks; setBuildGradleProperty; break}
		
		output.dir {$global:outputFolder = $value; break}
		build.dir {break}
		
		default {$errorMessage = "Unknown property: "; $errorMessage += $property; write-host $errorMessage}
	}
}

function setApplicationId
{
	setValueInStringXML "app_id" $value
	changePackageName
	$applicationAccountId = $value + ".account"
	updateValueWithQuatationMarks
	setBuildGradleProperty
	
	if ($global:isGenericUrl)
	{		
		setValueInStringXML "app_account" $applicationAccountId
	}
}

function changePackageName
{
	$packagePath = $value
	$packagePath = $packagePath -replace '\.', '\'
	$packagePath = '.\app\src\main\java\' + $packagePath
	New-Item -ItemType Directory -Force -Path $packagePath -erroraction 'silentlycontinue' | Out-Null
	Move-Item .\app\src\main\java\com\magicsoftware\magicdev\* $packagePath
	
	$files = Get-ChildItem $packagePath
	ForEach ($file in $files)
	{
		renamePackageNameInFile $file
	}
	$file = Get-Item '.\app\src\main\AndroidManifest.xml'
	renamePackageNameInFile ($file)
	$file = Get-Item '.\app\src\main\res\values\strings.xml'
	renamePackageNameInFile ($file)
	$file = Get-Item '.\app\src\main\res\xml\account_preferences.xml'
	renamePackageNameInFile ($file)
	$file = Get-Item '.\app\google-services.json'
	renamePackageNameInFile ($file)
}

function renamePackageNameInFile($file)
{
	Set-ItemProperty $file.FullName -name IsReadOnly -value $false
	$fileContent = Get-Content $file.FullName
	for ($i=0; $i -le $fileContent.count - 1; $i++)
	{
		if ($fileContent[$i].Contains("com.magicsoftware.magicdev"))
		{
			$fileContent[$i] = $fileContent[$i] -replace "com.magicsoftware.magicdev", $value
		}
	}
	Set-Content -path $file.FullName -value $fileContent 
}

function setLocalProperties
{
	#Create local.properties file containing the provided sdk folder
	Remove-Item -Force .\local.properties -erroraction 'silentlycontinue'
	New-Item -ItemType File -Force -Path .\local.properties -erroraction 'silentlycontinue' | Out-Null
	$newLine = 'sdk.dir=' + $value
	Add-Content -Path ".\local.properties" -Value $newLine
}

function setBuildGradleProperty
{
	$path = '.\app\build.gradle'
	sp $path IsReadOnly $false
	$buildGradle = Get-Content $path
	for ($i=0; $i -le $buildGradle.count - 1; $i++)
	{
		if ($buildGradle[$i].Contains($property))
		{
			$newValue = $property; $newValue += " "; $newValue += $value
			$newValue = $newValue.PadLeft($newValue.length + $buildGradle[$i].IndexOf($property), " ")
			$buildGradle[$i] = $newValue
		}
	}
	Set-Content -path $path -value $buildGradle 
}

function setValueInStringXML($key, $valueToSet)
{
	$path = '.\app\src\main\res\values\strings.xml'
	sp $path IsReadOnly $false
	$stringsXml = [xml](Get-Content $path)
	$node = $stringsXml.resources.string | where {$_.name -eq $key}
	$node.InnerText = $valueToSet
	$stringsXml.Save($path)
}

function updateValueWithQuatationMarks
{
	$newValue = '"'; $newValue += $value ; $newValue += '"'
	$global:value = $newValue
}

function updateValueWithBracketsAndQuatationMarks
{
	$newValue = "("""; $newValue += $value ; $newValue += """)"
	$global:value = $newValue
}

function updateManifestIfNeeded
{
	$global:isGenericUrl = $false
	foreach ($row in $executionPropsFile)
	{
		if ($row.Contains("""URL""") -and $row.Contains("val="""""))
		{
			$global:isGenericUrl = $true
			break
		}
	}
	if (!($isGenericUrl))
	{
		$path = '.\app\src\main\AndroidManifest.xml'
		sp $path IsReadOnly $false
		$androidManifestXml = [xml](Get-Content $path)
		
		$node = $androidManifestXml.manifest.'uses-permission' | where {$_.name -eq 'android.permission.AUTHENTICATE_ACCOUNTS'}
		$node.ParentNode.RemoveChild($node)
		
		$node = $androidManifestXml.manifest.application.service | where {$_.name -eq 'AccountAuthenticatorService'}
		$node.ParentNode.RemoveChild($node)
		
		$node = $androidManifestXml.manifest.application.activity | where {$_.name -eq 'SettingsActivity'}
		$node.ParentNode.RemoveChild($node)
		
		$androidManifestXml.Save($path)
		
		# Update App account id with empty value, so that account will not be added
		setValueInStringXML "app_account" ""
	}
}

function updateCacheFolder
{
	# move the items to the cache folder and create a cachelist.txt
	Move-Item -path .\app\src\main\assets -destination .\app\src\main\assets_temp
	New-Item -ItemType Directory -Force -Path .\app\src\main\assets\cache -erroraction 'silentlycontinue' | Out-Null
	Move-Item -path .\app\src\main\assets_temp\* -destination .\app\src\main\assets\cache
	Remove-Item .\app\src\main\assets_temp
	
	New-item -Force -path .\app\src\main\assets -name cachelist.txt -type "file" | Out-Null
	# recurse through all files (exclude folder items) and add them to cachelist.txt
	$assetFiles = Get-ChildItem ".\app\src\main\assets\cache" -recurse | ?{ !$_.PSIsContainer }
	if ($assetFiles.length -gt 0)
	{
		$currentThread = [System.Threading.Thread]::CurrentThread
		
		$previousCulture = $currentThread.CurrentCulture
		$previousUICulture = $currentThread.CurrentUICulture    
	
		# Override the current culture to force the correct dateTimeFormat
		$currentThread.CurrentCulture = [System.Globalization.CultureInfo]::InvariantCulture
		$currentThread.CurrentUICulture = [System.Globalization.CultureInfo]::InvariantCulture
		
		try
		{
			foreach ($file in $assetFiles)
			{	
				$realtiveFilePath = $file | Resolve-Path -Relative
				$newLine = $realtiveFilePath.SubString(28) + ',' + $file.LastWriteTime.ToString("dd/MM/yyyy HH:mm:ss")
				Add-Content -Path ".\app\src\main\assets\cachelist.txt" -Value $newline
			}
		}
		finally
		{
			# restore the previous culture
			$currentThread.CurrentCulture = $previousCulture        
			$currentThread.CurrentUICulture = $previousUICulture    
		}
	}
}


#/////////////////////////////////////////////////////////////////////////////
#///////                  Script start                          //////////////
#/////////////////////////////////////////////////////////////////////////////

$host.ui.RawUI.WindowTitle = "Building Android Client"

Remove-Item -Force .\TEMP_BUILD_FOLDER -recurse -erroraction 'silentlycontinue'

#Copy all files to temporary build folder
New-Item -ItemType Directory -Force -Path .\TEMP_BUILD_FOLDER | Out-Null
Copy-Item -Exclude 'TEMP_BUILD_FOLDER' .\* -destination .\TEMP_BUILD_FOLDER -recurse
[environment]::CurrentDirectory = '.\TEMP_BUILD_FOLDER'
Set-Location .\TEMP_BUILD_FOLDER

Copy-Item execution.properties -destination .\app\src\main\res\raw -Force
Set-ItemProperty .\app\src\main\res\raw\execution.properties -name IsReadOnly -value $false
updateManifestIfNeeded
updateCacheFolder

# Iterate on all rows of the settings file, and handle each property
foreach ($row in $settingsFile)
{
	getPropertyValue
	if (![string]::IsNullOrEmpty($property))
	{
		handleProperty
	}
}

# Run the gradle build
Start-Process gradlew.bat 'assembleRelease' -NoNewWindow -Wait

# Copy the release apk to output folder
$outputFolder = '..\' + $outputFolder
Remove-Item -Force $outputFolder -recurse -erroraction 'silentlycontinue'
New-Item -ItemType Directory -Force -Path $outputFolder | Out-Null
Copy-Item .\app\build\outputs\apk\app-release.apk -destination $outputFolder
$apkPath = $outputFolder + "\app-release.apk"
Rename-Item -path $apkPath -newname $appName
$newApkPath = $outputFolder + "\" + $appName

if (!(Test-Path $newApkPath))
{
	Write-Host "Exiting with code -1" 
	exit -1
}

[environment]::CurrentDirectory = '..\'
Set-Location ..\
Remove-Item -Force .\TEMP_BUILD_FOLDER -recurse

break