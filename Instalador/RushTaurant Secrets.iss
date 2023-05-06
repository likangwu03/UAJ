; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "RushTaurant Secrets"
#define MyAppVersion "1.1"
#define MyAppPublisher "Nightmare Dogs"
#define MyAppURL "https://ucm-fdi-disia.github.io/Nightmare-Dogs/"
#define MyAppExeName "RushTaurantSecrets.exe"
#define MyAppAssocName MyAppName + " File"
#define MyAppAssocExt ".myp"
#define MyAppAssocKey StringChange(MyAppAssocName, " ", "") + MyAppAssocExt

[Setup]
; NOTE: The value of AppId uniquely identifies this application. Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
<<<<<<<< HEAD:Instalador/RushTaurant Secrets.iss
AppId={{299778B9-1D70-4D43-86E5-3B1679E1D048}
========
AppId={{447B8A11-AED3-4775-B355-2F10EC112A20}
>>>>>>>> 103cd26dabc59715debf0b5a0c5efb43e87902e4:Instalador/Nightmare Dogs.iss
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={autopf}\{#MyAppName}
ChangesAssociations=yes
DisableProgramGroupPage=yes
; Uncomment the following line to run in non administrative install mode (install for current user only.)
;PrivilegesRequired=lowest
OutputDir=RushTaurant Secrets
OutputBaseFilename=RushTaurant Secrets
SetupIconFile=C:\Users\likan\Desktop\proyecto2\Nightmare-Dogs\RushTaurantSecrets\RushTaurant_Icon1.ico
Compression=lzma
SolidCompression=yes
WizardStyle=modern

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "spanish"; MessagesFile: "compiler:Languages\Spanish.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "..\RushTaurantSecrets\x64\Release\{#MyAppExeName}"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\likan\Desktop\Nueva carpeta\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "..\RushTaurantSecrets\RushTaurant_Icon1.ico"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\RushTaurantSecrets\SDL2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\RushTaurantSecrets\SDL2_image.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\RushTaurantSecrets\SDL2_mixer.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\RushTaurantSecrets\SDL2_net.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\RushTaurantSecrets\SDL2_ttf.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\RushTaurantSecrets\tmxlite.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\RushTaurantSecrets\tmxlite-d.dll"; DestDir: "{app}"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Registry]
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocExt}\OpenWithProgids"; ValueType: string; ValueName: "{#MyAppAssocKey}"; ValueData: ""; Flags: uninsdeletevalue
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocKey}"; ValueType: string; ValueName: ""; ValueData: "{#MyAppAssocName}"; Flags: uninsdeletekey
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocKey}\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\{#MyAppExeName},0"
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocKey}\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\{#MyAppExeName}"" ""%1"""
Root: HKA; Subkey: "Software\Classes\Applications\{#MyAppExeName}\SupportedTypes"; ValueType: string; ValueName: ".myp"; ValueData: ""

[Icons]
Name: "{autoprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; IconFilename:"{app}\RushTaurant_Icon1.ico"; Tasks: desktopicon;

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

