; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "MellowPlayer"
#define MyAppVersion "@MellowPlayer_VERSION@"
#define MyAppPublisher "Colin Duquesnoy"
#define MyAppURL "https://github.com/ColinDuquesnoy/MellowPlayer"
#define MyAppExeName "MellowPlayer.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{A638A43D-A82A-4CEA-A0D8-65F3F4258925}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
AllowNoIcons=yes
LicenseFile=..\LICENSE
OutputDir=dist
OutputBaseFilename=MellowPlayer_Setup
SetupIconFile=..\src\mellowplayer.ico
Compression=lzma
SolidCompression=yes
ChangesAssociations=yes
ArchitecturesInstallIn64BitMode=x64

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Types]
Name: full;    Description: "Full installation"
Name: compact; Description: "Compact installation"
Name: custom;  Description: "Custom installation"; Flags: iscustom

[Components]
Name: app;  Description: "MellowPlayer";  Types: full compact custom; Flags: fixed
Name: flash; Description: "Flash Player PPAPI";  Types: full; Flags: disablenouninstallwarning;
Name: vcredist; Description: "MSVC 2015 Redist";  Types: full; Flags: disablenouninstallwarning;

[Files]
Source: "bin\*"; DestDir: "{app}"; Flags: recursesubdirs createallsubdirs; Components: app
Source: "..\scripts\packaging\windows\libeay32.dll"; DestDir: "{app}"; Components: app
Source: "..\scripts\packaging\windows\ssleay32.dll"; DestDir: "{app}"; Components: app
Source: "..\scripts\packaging\windows\vc_redist.x64.exe"; DestDir: "{tmp}"; Components: vcredist
Source: "..\scripts\packaging\windows\flashplayer26pp_fb_install.exe"; DestDir: "{tmp}"; Components: flash

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; Components: app;
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 0,6.1; Components: app;

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Components: app;
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"; Components: app;
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon; Components: app;
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: quicklaunchicon; Components: app;

[Run]
Filename: "{tmp}\vc_redist.x64.exe"; Components: vcredist;
Filename: "{tmp}\flashplayer26pp_fb_install.exe"; Components: flash;
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent; Components: app;
