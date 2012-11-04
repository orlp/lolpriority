[Setup]
AppName=lolpriority
AppVersion=1.0
DefaultDirName={pf}\lolpriority
DefaultGroupName=lolpriority
UninstallDisplayIcon={app}\lolpriority.exe
Compression=lzma2
AppMutex=lolpriority.exe
SolidCompression=yes

[Files]
Source: "lolpriority.exe"; DestDir: "{app}"

[Registry]
Root: HKCU; Subkey: "SOFTWARE\Microsoft\Windows\CurrentVersion\Run"; ValueType: string; ValueName: "lolpriority"; ValueData: """{app}\lolpriority.exe"""; Flags: uninsdeletevalue

[Icons]
Name: "{group}\Uninstall lolpriority"; Filename: "{uninstallexe}"

[Run]
Filename: "{app}\lolpriority.exe"; Flags: nowait;

[Code]
function InitializeSetup(): Boolean;
var
ErrorCode: Integer;
begin
ShellExec('open',
'taskkill.exe',
'/f /im lolpriority.exe','', SW_HIDE, ewNoWait, ErrorCode);
ShellExec('open',
'tskill.exe',
' lolpriority','',SW_HIDE, ewNoWait, ErrorCode);
result := True;
end;

function InitializeUninstall(): Boolean;
var
ErrorCode: Integer;
begin
ShellExec('open',
'taskkill.exe',
'/f /im lolpriority.exe','',SW_HIDE,ewNoWait,ErrorCode);
ShellExec('open',
'tskill.exe',
' lolpriority','',SW_HIDE,ewNoWait,ErrorCode);
result := True;
end;