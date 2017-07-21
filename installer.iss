#define MyAppName "ChipAnnotator"
#define MyAppVersion "1.0.0"
#define MyAppPublisher "Stilla Technologies"
#define MyAppPublisherShort "Stilla"
#define MyAppURL "http://www.stilla.fr/"
#define MyAppExeName "ChipAnnotator.exe"

; Machine dependent directories
#define BuildDirectory "C:\Users\Julien\Documents\Dev\build-ChamberAnnotater-Clone_de_Desktop_Qt_5_7_0_MSVC2015_64bit-Release\release"
#define PreprocessorBuildDirectory "C:\Users\Julien\Documents\Dev\crystalminer\build_vs2015\chip_annotator_preprocessor\Release"
#define OutputDirectory "C:\Users\Julien\Documents\crystalminer_intaller"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{D00026E9-1EEE-4CB4-AD99-A36559E6FAB0}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppPublisherShort}\{#MyAppName}
DisableProgramGroupPage=yes
OutputDir={#OutputDirectory}
OutputBaseFilename=SetupChipAnnotator
Compression=lzma
SolidCompression=yes
ArchitecturesAllowed=x64
ArchitecturesInstallIn64BitMode=x64        

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Files]
Source: "{#BuildDirectory}\ChipAnnotator.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#PreprocessorBuildDirectory}\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs

; Add the app dir to the Path variable
[Registry]
Root: HKLM; SubKey: "SYSTEM\CurrentControlSet\Control\Session Manager\Environment\"; ValueType: string; ValueName: "Path"; ValueData: "{reg:HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Environment\,Path};{app}"; Check: NeedsAddPath()

[Setup]
; Tell Windows Explorer to reload the environment
ChangesEnvironment=yes   

[Code]
// Do note insert install dir to Path if its already there
function NeedsAddPath(): boolean;
var
  OrigPath: string;
  ParamExpanded: string;
begin
  OrigPath := ExpandConstant('{app}');
  //expand the setup constants like {app} from Param
  ParamExpanded := ExpandConstant('{app}');
  if not RegQueryStringValue(HKEY_LOCAL_MACHINE,
    'SYSTEM\CurrentControlSet\Control\Session Manager\Environment',
    'Path', OrigPath)
  then begin
    Result := True;
    exit;
  end;
  // look for the path with leading and trailing semicolon and with or without \ ending
  // Pos() returns 0 if not found
  Result := Pos(';' + UpperCase(ParamExpanded) + ';', ';' + UpperCase(OrigPath) + ';') = 0;  
  if Result = True then
     Result := Pos(';' + UpperCase(ParamExpanded) + '\;', ';' + UpperCase(OrigPath) + ';') = 0; 
end;


//Remvoe install dir from Path at unistall
procedure CurUninstallStepChanged(CurUninstallStep: TUninstallStep);
var
  Path, AppDir: string;
  Index: Integer;
begin
  if CurUninstallStep = usUninstall then
  begin
    if RegQueryStringValue(HKEY_LOCAL_MACHINE,
      'SYSTEM\CurrentControlSet\Control\Session Manager\Environment\',
      'Path', Path) then
    begin
      AppDir := ExpandConstant('{app}');
      Index := Pos(AppDir, Path);
      Delete(Path, Index-1, Length(AppDir)+1);
      RegWriteStringValue(HKEY_LOCAL_MACHINE,
        'SYSTEM\CurrentControlSet\Control\Session Manager\Environment\',
        'Path', Path);
    end;
  end;
end;

