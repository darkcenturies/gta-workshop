using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Security.Cryptography;
using System.Security.Principal;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using System.Xml.Serialization;
using Microsoft.Win32;

namespace ValkyrieRepair {
public class Installation {
    public string Root;
    public string Kind { get { return "GTA San Andreas"; } }
    public override string ToString() { return Kind + "  —  " + Root; }
}
public class Finding {
    public string Title, Severity, Evidence, Advice, Relative, ExpectedHash, Action, Payload;
    public string State = "Review";
    public bool Repairable { get { return Action == "disable" || Action == "radio" || Action == "install" || Action == "replace" || Action == "compat-clear" || Action == "compat-admin"; } }
    public string Details { get { return Evidence + "\r\n\r\n" + Advice + (Repairable ? "\r\n\r\nProposed change: " + (Action == "disable" ? "Rename this file so the game no longer loads it." : (Action == "radio" ? "Change active RadioEx=true/1 settings to RadioEx=false, preserving all other bytes." : (Action == "install" || Action == "replace" ? "Install the bundled ASI at the selected path; preserve any replaced file for Undo." : (Action == "compat-clear" ? "Remove the current-user Windows compatibility override for this executable." : "Enable Run as administrator for this executable in the current user's Windows compatibility settings.")))) + "\r\nTarget: " + Relative + "\r\nAn Undo record is created only when you approve." : "\r\n\r\nGuidance only: no automatic change is available."); } }
}
public class ScanResult {
    public string Root;
    public List<Finding> Findings = new List<Finding>();
    public int Files, Logs, Rules;
    public bool Incomplete;
}
public class Rule {
    public Dictionary<string,string> Keys = new Dictionary<string,string>();
    public string Body = "", Source;
}
public static class Rules {
    public static List<Rule> All = Load();
    static List<Rule> Load() {
        var list = new List<Rule>();
        foreach (string name in new[]{"doctor-valkyrie.txt","CrashList.txt"}) {
            using (var stream = Assembly.GetExecutingAssembly().GetManifestResourceStream(name))
            using (var reader = new StreamReader(stream)) {
                Rule r = new Rule { Source = name };
                foreach (string raw in (reader.ReadToEnd()+"\n\n").Replace("\r", "").Split('\n')) {
                    string line = raw.Trim();
                    if (line.Length == 0) { if (r.Keys.Count > 0 && r.Body.Length > 0) list.Add(r); r = new Rule { Source = name }; continue; }
                    if (line.StartsWith("#") || line.StartsWith("//")) continue;
                    var m = Regex.Match(line,@"^(Error|Library|File|Module|Code):\s*(.*)$",RegexOptions.IgnoreCase);
                    if (m.Success) r.Keys[m.Groups[1].Value.ToLowerInvariant()] = m.Groups[2].Value;
                    else r.Body += line + "\r\n";
                }
            }
        }
        return list;
    }
    static string Capture(string text, string pattern) { return Regex.Match(text,pattern,RegexOptions.Multiline|RegexOptions.IgnoreCase).Groups[1].Value.Trim(); }
    public static Dictionary<string,string> Evidence(string text) {
        // Only the header is evidence. Addresses in backtraces and old diagnosis prose must never match.
        int end = text.IndexOf("Register dump:",StringComparison.OrdinalIgnoreCase);
        if (end >= 0) text = text.Substring(0,end);
        if (text.Length > 8192) text = text.Substring(0,8192);
        return new Dictionary<string,string> {
            {"error",Capture(text,@"^Unhandled exception at (0x[0-9a-f]+)\b")},
            {"code",Capture(text,@"^(0x[0-9a-f]{8}):")},
            {"library",Capture(text,@"^Last library loaded:\s*(.+)$")},
            {"file",Capture(text,@"^Last file loaded:\s*(.+)$")},
            {"module",Capture(text,@"^In module:\s*(.+)$")}
        };
    }
    public static List<Rule> Match(string text) {
        var ev = Evidence(text);
        return All.Where(r => r.Keys.All(k => {
            string actual = ev[k.Key].Replace('\\','/').ToLowerInvariant();
            if (actual.Length == 0) return false;
            if (k.Key == "error" || k.Key == "code") return Regex.Matches(k.Value,@"0x[0-9a-f]+",RegexOptions.IgnoreCase).Cast<Match>().Any(m => Convert.ToUInt64(m.Value.Substring(2),16) == Convert.ToUInt64(actual.Substring(2),16));
            if(k.Key=="module") return k.Value.Split(',','|').Any(v=> {
                string pattern=v.Trim().Replace('\\','/').ToLowerInvariant();
                var expected=Regex.Match(pattern,@"^(.+?)\+0x([0-9a-f]+)$");
                if(!expected.Success)return actual.Contains(pattern);
                var observed=Regex.Match(actual,@"^(.+?)\+0x([0-9a-f]+)\b");
                return observed.Success && observed.Groups[1].Value==expected.Groups[1].Value && Convert.ToUInt64(observed.Groups[2].Value,16)==Convert.ToUInt64(expected.Groups[2].Value,16);
            });
            return k.Value.Split(',','|').Any(v => actual.Contains(v.Trim().Replace('\\','/').ToLowerInvariant()));
        })).OrderByDescending(r => r.Keys.Count).ToList();
    }
}
public static class Filesystem {
    public static readonly string[] Exes = {"gta_sa.exe","gta-sa.exe"};
    public static bool IsInstall(string root) { return Exes.Any(n => File.Exists(Path.Combine(root,n))); }
    public static string Normalize(string root) { return Path.GetFullPath(root).TrimEnd(Path.DirectorySeparatorChar)+Path.DirectorySeparatorChar; }
    public static bool Link(string path) { return (File.GetAttributes(path)&FileAttributes.ReparsePoint)!=0; }
    public static string SafePath(string root, string relative) {
        root = Normalize(root);
        if (Path.IsPathRooted(relative)) throw new IOException("An absolute repair path is not allowed.");
        string full = Path.GetFullPath(Path.Combine(root,relative));
        if (!full.StartsWith(root,StringComparison.OrdinalIgnoreCase) || full == root.TrimEnd('\\')) throw new IOException("The repair path leaves this installation.");
        for (string p=full; !String.IsNullOrEmpty(p); p=Path.GetDirectoryName(p)) {
            if ((File.Exists(p)||Directory.Exists(p)) && Link(p)) throw new IOException("Repairs through a symbolic link or junction are not supported: " + p);
        }
        return full;
    }
    public static string Hash(string path) { using(var s=File.OpenRead(path)) using(var sha=SHA256.Create()) return BitConverter.ToString(sha.ComputeHash(s)).Replace("-", ""); }
    public static List<string> Walk(string root, int depth, int cap, CancellationToken token, Action<string> warn) {
        var result=new List<string>(); var queue=new Queue<Tuple<string,int>>(); queue.Enqueue(Tuple.Create(root,0)); int visited=0;
        while(queue.Count>0) {
            token.ThrowIfCancellationRequested(); var item=queue.Dequeue();
            if (++visited>cap) { warn("Folder limit reached; scan coverage is incomplete."); break; }
            try {
                if(Link(item.Item1)) { warn("Skipped linked folder: " + item.Item1); continue; }
                foreach(var f in Directory.EnumerateFiles(item.Item1)) { token.ThrowIfCancellationRequested(); if(result.Count>=100000) {warn("File limit reached; scan coverage is incomplete."); return result;} if(!Link(f)) result.Add(f); else warn("Skipped linked file: " + f); }
                foreach(var d in Directory.EnumerateDirectories(item.Item1)) {
                    if(Path.GetFileName(d).Equals(".valkyrie-repair",StringComparison.OrdinalIgnoreCase)) continue;
                    if(item.Item2>=depth) { warn("Depth limit reached: " + d); continue; }
                    queue.Enqueue(Tuple.Create(d,item.Item2+1));
                }
            } catch(UnauthorizedAccessException) {warn("Cannot read: " + item.Item1);} catch(IOException e) {warn(e.Message);}
        }
        return result;
    }
}
public static class Discovery {
    public static List<Installation> Search(string searchRoot, CancellationToken token, Action<string> progress) {
        var found=new Dictionary<string,Installation>(StringComparer.OrdinalIgnoreCase);
        Action<string> add = p => { try { if(!String.IsNullOrWhiteSpace(p) && Directory.Exists(p) && !Filesystem.Link(p) && Filesystem.IsInstall(p)) { p=Filesystem.Normalize(p); found[p]=new Installation{Root=p}; } } catch {} };
        var roots=new HashSet<string>(StringComparer.OrdinalIgnoreCase);
        if(searchRoot!=null) roots.Add(searchRoot);
        else {
            foreach(var drive in DriveInfo.GetDrives().Where(d=>d.IsReady && d.DriveType==DriveType.Fixed)) {
                add(drive.RootDirectory.FullName);
                foreach(var folder in new[]{"Games","SteamLibrary\\steamapps\\common","Steam\\steamapps\\common","GOG Games","Rockstar Games","GTA San Andreas"}) roots.Add(Path.Combine(drive.RootDirectory.FullName,folder));
                // Inspect drive-level custom installation folders without recursively walking Windows.
                try {foreach(var d in Directory.GetDirectories(drive.RootDirectory.FullName)) add(d);} catch {}
            }
            foreach(var basePath in new[]{Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles),Environment.GetFolderPath(Environment.SpecialFolder.ProgramFilesX86),Environment.GetFolderPath(Environment.SpecialFolder.Desktop),Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments)}) roots.Add(basePath);
            foreach(var hive in new[]{RegistryHive.LocalMachine,RegistryHive.CurrentUser}) foreach(var view in new[]{RegistryView.Registry32,RegistryView.Registry64}) {
                try {using(var key=RegistryKey.OpenBaseKey(hive,view)) {
                    using(var un=key.OpenSubKey(@"SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall")) if(un!=null) foreach(var name in un.GetSubKeyNames()) using(var sub=un.OpenSubKey(name)) { if(sub!=null) add(sub.GetValue("InstallLocation") as string); }
                    using(var gta=key.OpenSubKey(@"SOFTWARE\Rockstar Games\GTA San Andreas\Installation")) if(gta!=null) add(gta.GetValue("ExePath") is string ? Path.GetDirectoryName((string)gta.GetValue("ExePath")) : null);
                    using(var steam=key.OpenSubKey(@"SOFTWARE\Valve\Steam")) if(steam!=null) {
                        var p=(steam.GetValue("SteamPath")??steam.GetValue("InstallPath")) as string;
                        if(p!=null) {
                            roots.Add(Path.Combine(p,"steamapps","common"));
                            var vdf=Path.Combine(p,"steamapps","libraryfolders.vdf");
                            if(File.Exists(vdf)) foreach(Match m in Regex.Matches(File.ReadAllText(vdf),"\"path\"\\s+\"([^\"]+)\"")) roots.Add(Path.Combine(m.Groups[1].Value.Replace("\\\\","\\"),"steamapps","common"));
                        }
                    }
                }} catch {}
            }
        }
        int checkedDirs=0;
        foreach(string root in roots.Where(Directory.Exists)) {
            var queue=new Queue<Tuple<string,int>>(); queue.Enqueue(Tuple.Create(root,0));
            while(queue.Count>0 && checkedDirs<40000) {
                token.ThrowIfCancellationRequested(); var item=queue.Dequeue(); checkedDirs++;
                if(checkedDirs%100==0) progress("Searching installations · " + checkedDirs + " folders · " + found.Count + " found");
                try {
                    if(Filesystem.Link(item.Item1)) continue;
                    add(item.Item1); if(Filesystem.IsInstall(item.Item1)) continue;
                    if(item.Item2 >= (searchRoot==null ? 4 : 10)) continue;
                    foreach(var dir in Directory.GetDirectories(item.Item1)) {
                        string n=Path.GetFileName(dir).ToLowerInvariant();
                        if(new[]{"windows","appdata","node_modules",".git",".valkyrie-repair"}.Contains(n)) continue;
                        queue.Enqueue(Tuple.Create(dir,item.Item2+1));
                    }
                } catch(UnauthorizedAccessException) {} catch(IOException) {}
            }
        }
        progress("Search finished · " + found.Count + " installations. Search is bounded; use Add folder for any missing copy.");
        return found.Values.OrderBy(x=>x.Root).ToList();
    }
}
public static class Scanner {
    static void Add(ScanResult r,string title,string severity,string evidence,string advice) { r.Findings.Add(new Finding{Title=title,Severity=severity,Evidence=evidence,Advice=advice}); }
    static void Repair(ScanResult r,string title,string file,string action,string evidence,string advice) {
        try { Filesystem.SafePath(r.Root,file.Substring(r.Root.Length)); r.Findings.Add(new Finding{Title=title,Severity="Suggested fix",Evidence=evidence,Advice=advice,Relative=file.Substring(r.Root.Length),Action=action,ExpectedHash=Filesystem.Hash(file)}); }
        catch(Exception e) { Add(r,"Repair unavailable","Review",file,e.Message); }
    }
    static void Install(ScanResult r,string title,string relative,string payload,string evidence,string advice) {
        try {
            string file = Filesystem.SafePath(r.Root, relative);
            if(File.Exists(file)) return;
            r.Findings.Add(new Finding{Title=title,Severity="Suggested fix",Evidence=evidence,Advice=advice,Relative=relative,Action="install",Payload=payload,ExpectedHash=""});
        } catch(Exception e) { Add(r,"Install unavailable","Review",relative,e.Message); }
    }
    static void RegistryRepair(ScanResult r,string title,string exe,string action,string previous,string evidence,string advice) { try { Filesystem.SafePath(r.Root,exe.Substring(r.Root.Length)); r.Findings.Add(new Finding{Title=title,Severity="Suggested fix",Evidence=evidence,Advice=advice,Relative=exe.Substring(r.Root.Length),Action=action,Payload=previous??"",ExpectedHash=Filesystem.Hash(exe)}); } catch(Exception e) { Add(r,"Windows setting repair unavailable","Review",exe,e.Message); } }
    public static ScanResult Scan(string path,CancellationToken token) {
        var r=new ScanResult{Root=Filesystem.Normalize(path),Rules=Rules.All.Count};
        if(!Filesystem.IsInstall(r.Root)) throw new IOException("Select a folder containing gta_sa.exe or gta-sa.exe.");
        var warnings=new List<string>();
        var files=Filesystem.Walk(r.Root,12,20000,token,s=>{if(warnings.Count<10) warnings.Add(s); r.Incomplete=true;}); r.Files=files.Count;
        foreach(string exe in Filesystem.Exes.Select(n=>Path.Combine(r.Root,n)).Where(File.Exists)) {
            token.ThrowIfCancellationRequested();
            try { using(var br=new BinaryReader(File.OpenRead(exe))) {
                if(br.BaseStream.Length<64 || br.ReadUInt16()!=0x5A4D) throw new IOException("Missing DOS executable header.");
                br.BaseStream.Position=0x3c; int pe=br.ReadInt32(); if(pe<64 || pe>br.BaseStream.Length-24) throw new IOException("Invalid PE header offset.");
                br.BaseStream.Position=pe; if(br.ReadUInt32()!=0x4550) throw new IOException("Invalid PE signature.");
                if(br.ReadUInt16()!=0x14c) Add(r,"Executable is not x86","Problem",exe,"Classic GTA San Andreas expects a 32-bit executable. Restore the correct game release.");
                else Add(r,Path.GetFileName(exe)+" is a readable x86 executable","Checked","SHA-256: "+Filesystem.Hash(exe),"Architecture checked. Exact GTA release and binary integrity require a trusted version manifest; file size alone is not proof.");
            }} catch(Exception e) {Add(r,"Executable cannot be validated","Problem",exe,e.Message);}
        }
        string lowerRoot=r.Root.ToLowerInvariant();
        bool cloud=lowerRoot.Contains("\\onedrive\\") || lowerRoot.Contains("\\dropbox\\") || lowerRoot.Contains("\\google drive\\");
        if(cloud) Add(r,"Game is inside a cloud-synchronised folder","Problem",r.Root,"Move the complete game to a local folder such as C:\\Games\\GTA San Andreas. Sync clients can lock or partially replace files while the game is running.");
        else Add(r,"Game folder is local","Checked",r.Root,"No OneDrive, Dropbox or Google Drive path was detected.");
        bool programFiles=lowerRoot.Contains("\\program files\\") || lowerRoot.Contains("\\program files (x86)\\");
        if(programFiles) { Add(r,"Game is inside Program Files","Review",r.Root,"Repair available above: optionally enable Run as administrator for the launched executable. Moving the complete game to C:\\Games\\GTA San Andreas remains the cleanest long-term fix."); foreach(string exe in Filesystem.Exes.Select(n=>Path.Combine(r.Root,n)).Where(File.Exists)) { string old=Convert.ToString(Registry.GetValue(@"HKEY_CURRENT_USER\Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers",exe,null)); if(old.IndexOf("RUNASADMIN",StringComparison.OrdinalIgnoreCase)<0) RegistryRepair(r,"Optional: allow Program Files access for "+Path.GetFileName(exe),exe,"compat-admin",old,"The game is under Program Files and this executable is not configured to run elevated.","Adds only the current-user Run as administrator compatibility flag. Use this if the game cannot save settings or logs. Undo restores the previous setting."); } }
        if(lowerRoot.Contains("\\downloads\\") || lowerRoot.Contains("\\appdata\\local\\temp\\")) Add(r,"Game is running from a temporary or download folder","Review",r.Root,"Move the complete installation to a permanent local folder before repairing it.");
        if(r.Root.Length>180) Add(r,"Game folder path is unusually long","Review",r.Root,"Some older ASI/CLEO components fail on long paths. Move the installation closer to the drive root if loading fails.");
        if(r.Root.Any(c=>c>127)) Add(r,"Game folder contains non-ASCII characters","Review",r.Root,"Some legacy plugins only support ANSI paths. Use a simple Latin-character folder path if files fail to load.");
        try { bool elevated=new WindowsPrincipal(WindowsIdentity.GetCurrent()).IsInRole(WindowsBuiltInRole.Administrator); Add(r,"Repairer privilege level","Information",elevated?"Running as administrator":"Running as a standard user",elevated?"Administrator rights are available. They do not repair compatibility problems by themselves.":"Standard-user mode is preferred when the game folder is writable. Use administrator mode only for a confirmed access problem."); } catch {}
        string documents=Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);
        if(documents.IndexOf("OneDrive",StringComparison.OrdinalIgnoreCase)>=0) Add(r,"Documents is redirected through OneDrive","Review",documents,"GTA San Andreas saves and settings may be synchronised or blocked. Confirm that GTA San Andreas User Files is available locally and writable.");
        else Add(r,"Documents folder is local","Checked",documents,"No OneDrive redirection was detected for Documents.");
        try { if((File.GetAttributes(r.Root)&FileAttributes.ReadOnly)!=0) Add(r,"Game folder has the Read-only attribute","Review",r.Root,"Clear Read-only in folder Properties and apply it to contained files if the game cannot save settings or create logs."); } catch {}
        foreach(string exe in Filesystem.Exes.Select(n=>Path.Combine(r.Root,n)).Where(File.Exists)) {
            try { string userLayers=Convert.ToString(Registry.GetValue(@"HKEY_CURRENT_USER\Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers",exe,null)); string machineLayers=Convert.ToString(Registry.GetValue(@"HKEY_LOCAL_MACHINE\Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers",exe,null)); if(!String.IsNullOrEmpty(userLayers) && !(programFiles && userLayers.Trim().Equals("~ RUNASADMIN",StringComparison.OrdinalIgnoreCase))) { Add(r,"Windows compatibility settings are enabled", "Review",Path.GetFileName(exe)+": "+userLayers,"Repair available above: clear the current-user compatibility override. GTA San Andreas's verified startup guidance recommends compatibility mode off."); RegistryRepair(r,"Clear compatibility mode for "+Path.GetFileName(exe),exe,"compat-clear",userLayers,"Current-user compatibility flags: "+userLayers,"Removes the current-user override. Undo restores the exact previous flags."); } if(!String.IsNullOrEmpty(machineLayers)) Add(r,"Machine-wide compatibility settings are enabled","Review",Path.GetFileName(exe)+": "+machineLayers,"This machine-wide setting requires administrator review in Properties > Compatibility > Change settings for all users; Valkyrie will not silently alter a machine-wide policy."); if(String.IsNullOrEmpty(userLayers)&&String.IsNullOrEmpty(machineLayers)) Add(r,Path.GetFileName(exe)+" has no compatibility override","Checked",exe,"No per-user or machine AppCompat layer was found."); } catch {}
            try { long size=new FileInfo(exe).Length; if(size>4*1024*1024 && size<7*1024*1024) Add(r,Path.GetFileName(exe)+" resembles a later GTA release","Problem",size+" bytes","GTA San Andreas requires a complete GTA San Andreas 1.0 base. Verify or downgrade the installation before applying the mod."); else if(size>60L*1024*1024) Add(r,Path.GetFileName(exe)+" resembles Definitive Edition","Problem",size+" bytes","GTA San Andreas cannot run on Definitive Edition; use classic GTA San Andreas 1.0."); } catch {}
        }
        string sys32=Environment.GetFolderPath(Environment.SpecialFolder.SystemX86); if(String.IsNullOrEmpty(sys32))sys32=Environment.SystemDirectory;
        if(!File.Exists(Path.Combine(sys32,"d3dx9_43.dll"))) Add(r,"Legacy DirectX component was not found","Review",Path.Combine(sys32,"d3dx9_43.dll"),"Install the DirectX End-User Runtime supplied with GTA San Andreas. Modern DirectX alone does not include every legacy D3DX9 component.");
        foreach(string relative in new[]{@"data\gta.dat",@"models\gta3.img",@"audio\CONFIG\BANKSLOT.DAT"}) {
            var f=Path.Combine(r.Root,relative);
            if(!File.Exists(f) || new FileInfo(f).Length==0) Add(r,"Missing or empty base-game file","Problem",relative,"Restore this file from your matching, complete game installation or original installer. Repair does not download or guess replacement game assets.");
        }
        DoctorSupport.Check(r,files);
        foreach(var file in files.Where(f=>CrashfixSupport.Candidate(r.Root,f)))
            Repair(r,"Optional: retire standalone Crashfix",file,"disable","Doctor now includes Crashfix; leaving both active can cause competing patches.","Close the game, disable this legacy copy, then install the combined ASI. Undo restores the original copy.");
        var plugins=files.Where(f=>new[]{".asi",".cleo",".cs"}.Contains(Path.GetExtension(f).ToLowerInvariant())).ToList();
        foreach(var group in plugins.GroupBy(Path.GetFileName,StringComparer.OrdinalIgnoreCase).Where(g=>g.Count()>1)) {
            var copies=group.OrderBy(f=>DuplicateScore(r.Root,f)).ThenBy(f=>f.Length).ToList(); string keep=copies[0];
            Add(r,"Potential duplicate: "+group.Key,"Review",String.Join("\r\n",copies.Select(f=>f.Substring(r.Root.Length))),"Repair available above: Valkyrie keeps the most likely active copy and offers every other copy as a reversible disable choice. Copies inside backup or documentation folders normally do not load, so disabling those is optional cleanup.");
            foreach(var copy in copies.Skip(1)) Repair(r,"Optional: disable duplicate "+group.Key,copy,"disable","Keep: "+keep.Substring(r.Root.Length)+"\r\nDisable: "+copy.Substring(r.Root.Length)+(Filesystem.Hash(keep)==Filesystem.Hash(copy)?"\r\nThe files are byte-identical.":"\r\nThe files differ; compare versions before applying."),"Renames only this extra copy so loaders cannot treat it as an ASI/CLEO plugin. Undo restores its original name.");
        }
        var logs=files.Where(f=>Path.GetFileName(f).StartsWith("doctor-valkyrie_",StringComparison.OrdinalIgnoreCase)&&Path.GetExtension(f).Equals(".log",StringComparison.OrdinalIgnoreCase)).OrderByDescending(File.GetLastWriteTimeUtc).Take(10).ToList();

        foreach(var log in logs) {
            token.ThrowIfCancellationRequested();
            try {
                if(new FileInfo(log).Length>8*1024*1024) {Add(r,"Crash log skipped","Review",log,"Log exceeds the 8 MB read limit.");r.Incomplete=true;continue;}
                string text=File.ReadAllText(log); r.Logs++; var matches=Rules.Match(text);
                if(matches.Count>0) {
                    var best=matches[0]; Add(r,"Crash guidance: "+Path.GetFileName(log),"Log evidence","Saved "+File.GetLastWriteTime(log).ToString("g")+" · "+best.Source+"\r\n"+String.Join("\r\n",Rules.Evidence(text).Where(k=>k.Value.Length>0).Select(k=>k.Key+": "+k.Value)),best.Body+"\r\nThis is historical evidence; the problem may already be fixed.");
                } else Add(r,"No rule matched this crash header","Review",log,"Keep the full Doctor report for investigation. Unmatched evidence does not mean the game is healthy.");
            } catch(Exception e) {r.Incomplete=true;Add(r,"Crash log could not be read","Review",log,e.Message);}
        }
        var cleo=Path.Combine(r.Root,"cleo.log");
        if(File.Exists(cleo)) {try {if(new FileInfo(cleo).Length<=8*1024*1024 && File.ReadAllText(cleo).IndexOf("Script suspended",StringComparison.OrdinalIgnoreCase)>=0) Add(r,"CLEO recorded a suspended script","Log evidence",cleo,"Review the script name and adjacent error in cleo.log. The entry can be old; no script is automatically disabled from this message alone.");}catch(Exception e){r.Incomplete=true;Add(r,"CLEO log unreadable","Review",cleo,e.Message);}}
        if(r.Logs==0) Add(r,"No saved Doctor crash reports found","Information","Searched this installation, including its crash subfolders.","Doctor is installed or offered above. Run the game normally; if it crashes, the next scan will read the new report automatically.");
        if(warnings.Count>0) Add(r,"Some scan locations were skipped","Review",String.Join("\r\n",warnings),"Results cover only files that could be read. Linked folders are excluded to keep repairs inside the selected installation.");
        Add(r,"Scan coverage","Information",r.Files+" files · "+r.Logs+" recent crash reports · "+r.Rules+" embedded rules","Checks executable structure, selected base files, Doctor/core presence, potential duplicate plugins, known repair candidates and crash headers. Full asset integrity, loaded-module conflicts, drivers, saves and runtime behaviour are not verified.");
        return r;
    }
    static int DuplicateScore(string root,string file) { string relative=file.Substring(root.Length).ToLowerInvariant(); if(String.Equals(Path.GetDirectoryName(file)+"\\",root,StringComparison.OrdinalIgnoreCase))return 0;if(String.Equals(Path.GetDirectoryName(file),Path.Combine(root,"scripts"),StringComparison.OrdinalIgnoreCase))return 1;if(relative.Contains("backup")||relative.Contains("\\doc")||relative.Contains("old"))return 9;return 4; }
}
public class Journal {
    public string Root, Relative, OriginalHash, AfterHash, Action, DisabledRelative, Status, Title, CreatedUtc, Payload;
}
public static class RepairEngine {
    static readonly Regex Radio = new Regex(@"(?im)^(\s*RadioEx\s*=\s*)(true|1)(\s*(?:[;#].*)?\r?$)");
    const string CompatKey = @"Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers";
    static Encoding ByteEncoding = Encoding.GetEncoding(28591);
    public static bool HasRadio(byte[] bytes) {return Array.IndexOf(bytes,(byte)0)<0 && Radio.IsMatch(ByteEncoding.GetString(bytes));}
    static byte[] RadioBytes(byte[] bytes) {if(!HasRadio(bytes)) throw new IOException("The radio setting is absent or uses an unsupported encoding. Rescan.");return ByteEncoding.GetBytes(Radio.Replace(ByteEncoding.GetString(bytes),"${1}false${3}"));}
    public static void CheckClosed() {
#if VALKYRIE_TEST
        // The separate test executable operates only on its generated fixtures.
        // Never compiled into the shipping GUI executable.
        return;
#else
        CheckGameProcessesClosed();
#endif
    }
    static void CheckGameProcessesClosed() {foreach(string name in new[]{"gta_sa","gta-sa"}) {var processes=Process.GetProcessesByName(name);try {if(processes.Length>0) throw new IOException("Close all GTA / GTA San Andreas games and S&SMP launchers before applying or undoing repairs.");}finally {foreach(var p in processes)p.Dispose();}}}
    static void WriteJournal(string path,Journal j) {var temp=path+".tmp";using(var f=new FileStream(temp,FileMode.Create,FileAccess.Write,FileShare.None)){new XmlSerializer(typeof(Journal)).Serialize(f,j);f.Flush(true);}if(File.Exists(path))File.Replace(temp,path,null);else File.Move(temp,path);}
    public static Journal ReadJournal(string path) {using(var f=File.OpenRead(path))return (Journal)new XmlSerializer(typeof(Journal)).Deserialize(f);}
    static byte[] PayloadBytes(string name) {
        if(String.IsNullOrEmpty(name) || name.IndexOfAny(Path.GetInvalidFileNameChars())>=0) throw new IOException("Invalid bundled payload name.");
        using(var stream=Assembly.GetExecutingAssembly().GetManifestResourceStream(name)) {
            if(stream==null) throw new IOException("Bundled payload is missing: " + name);
            using(var ms=new MemoryStream()) { stream.CopyTo(ms); return ms.ToArray(); }
        }
    }
    public static string Apply(string root,Finding finding) {
        CheckClosed(); if(!finding.Repairable || finding.State!="Review") throw new IOException("This finding is not awaiting approval.");
        root=Filesystem.Normalize(root);string file=Filesystem.SafePath(root,finding.Relative);bool registry=finding.Action=="compat-clear"||finding.Action=="compat-admin";
        if(finding.Action!="install" && Filesystem.Hash(file)!=finding.ExpectedHash) throw new IOException("The file changed after the scan. Rescan before approving.");
        if(finding.Action=="install" && File.Exists(file)) throw new IOException("The destination file already exists. Rescan before approving.");
        byte[] changed=finding.Action=="radio"?RadioBytes(File.ReadAllBytes(file)):((finding.Action=="install" || finding.Action=="replace")?PayloadBytes(finding.Payload):null);
        string id=DateTime.UtcNow.ToString("yyyyMMdd-HHmmss")+"-"+Guid.NewGuid().ToString("N");
        string dir=Filesystem.SafePath(root,Path.Combine(".valkyrie-repair",id));Directory.CreateDirectory(dir);
        string backup=Path.Combine(dir,"original.bin"), journalPath=Path.Combine(dir,"repair.xml");
        if(finding.Action=="install"||registry) File.WriteAllBytes(backup,new byte[0]);
        else {File.Copy(file,backup);if(Filesystem.Hash(backup)!=finding.ExpectedHash) throw new IOException("File changed while backing up. No repair applied.");}
        var j=new Journal{Root=root,Relative=finding.Relative,OriginalHash=finding.ExpectedHash,Action=finding.Action,Payload=finding.Payload,DisabledRelative=finding.Relative+".valkyrie-disabled-"+id,Status="Prepared",Title=finding.Title,CreatedUtc=DateTime.UtcNow.ToString("o")};
        string staged=Path.Combine(dir,"replacement.bin");
        if(changed!=null) {File.WriteAllBytes(staged,changed);j.AfterHash=Filesystem.Hash(staged);}else j.AfterHash=j.OriginalHash;
        WriteJournal(journalPath,j);
        // Revalidate immediately before committing. File.Replace / File.Move are atomic on the local volume.
        file=Filesystem.SafePath(root,finding.Relative);
        if(j.Action!="install" && Filesystem.Hash(file)!=finding.ExpectedHash) throw new IOException("File changed before the repair. No repair applied.");
        if(j.Action=="install" && File.Exists(file)) throw new IOException("The destination file appeared before the repair. No repair applied.");
        if(j.Action=="disable") File.Move(file,Filesystem.SafePath(root,j.DisabledRelative)); else if(j.Action=="install") File.Move(staged,file); else if(j.Action=="radio" || j.Action=="replace") File.Replace(staged,file,null); else {using(var key=Registry.CurrentUser.CreateSubKey(CompatKey)){if(key==null)throw new IOException("Windows compatibility settings could not be opened.");if(j.Action=="compat-clear")key.DeleteValue(file,false);else{string next=String.IsNullOrWhiteSpace(j.Payload)?"~ RUNASADMIN":j.Payload+" RUNASADMIN";key.SetValue(file,next,RegistryValueKind.String);}}}
        j.Status="Applied";WriteJournal(journalPath,j);finding.State="Applied";return journalPath;
    }
    public static void Undo(string root,string journalPath) {
        CheckClosed();root=Filesystem.Normalize(root);
        string fullJournal=Path.GetFullPath(journalPath);
        if(!fullJournal.StartsWith(root,StringComparison.OrdinalIgnoreCase)) throw new IOException("Repair history is outside this installation.");
        string journalRelative=fullJournal.Substring(root.Length);
        if(!journalRelative.StartsWith(".valkyrie-repair\\",StringComparison.OrdinalIgnoreCase)) throw new IOException("Repair history is outside this installation.");
        journalPath=Filesystem.SafePath(root,journalRelative);var j=ReadJournal(journalPath);
        if(!String.Equals(root,j.Root,StringComparison.OrdinalIgnoreCase) || (j.Status!="Applied"&&j.Status!="Prepared"))throw new IOException("This repair cannot be undone here.");
        string file=Filesystem.SafePath(root,j.Relative),backup=Filesystem.SafePath(root,Path.Combine(Path.GetDirectoryName(journalRelative),"original.bin"));
        bool registry=j.Action=="compat-clear"||j.Action=="compat-admin";
        if(j.Action!="install" && !registry && Filesystem.Hash(backup)!=j.OriginalHash)throw new IOException("Backup integrity check failed.");
        if(j.Action=="disable") {
            string disabled=Filesystem.SafePath(root,j.DisabledRelative);
            if(File.Exists(file)) {if(j.Status=="Prepared" && Filesystem.Hash(file)==j.OriginalHash && !File.Exists(disabled)){j.Status="Not applied";WriteJournal(journalPath,j);return;}throw new IOException("The original path now contains a file. Undo will not overwrite it.");}
            if(Filesystem.Hash(disabled)!=j.AfterHash)throw new IOException("Disabled file changed. Undo will not overwrite changes.");File.Move(disabled,file);
        } else if(j.Action=="radio" || j.Action=="replace") {
            var hash=Filesystem.Hash(file);
            if(j.Status=="Prepared"&&hash==j.OriginalHash){j.Status="Not applied";WriteJournal(journalPath,j);return;}
            if(hash!=j.AfterHash)throw new IOException("Configuration changed since repair. Undo will not overwrite your changes.");
            string temp=Path.Combine(Path.GetDirectoryName(backup),"restore.bin");File.Copy(backup,temp,true);File.Replace(temp,file,null);
        } else if(j.Action=="install") {
            if(!File.Exists(file)) {j.Status="Not applied";WriteJournal(journalPath,j);return;}
            if(Filesystem.Hash(file)!=j.AfterHash)throw new IOException("Installed file changed. Undo will not delete it.");
            File.Delete(file);
        } else if(registry) {
            using(var key=Registry.CurrentUser.CreateSubKey(CompatKey)){if(key==null)throw new IOException("Windows compatibility settings could not be opened.");if(String.IsNullOrEmpty(j.Payload))key.DeleteValue(file,false);else key.SetValue(file,j.Payload,RegistryValueKind.String);}
        } else throw new IOException("Unknown repair type.");
        j.Status="Undone";WriteJournal(journalPath,j);
    }
    public static List<string> History(string root) {
        var dir=Filesystem.SafePath(root,".valkyrie-repair");if(!Directory.Exists(dir))return new List<string>();
        return Directory.GetDirectories(dir).Where(d=>!Filesystem.Link(d)).Select(d=>Path.Combine(d,"repair.xml")).Where(File.Exists).OrderByDescending(x=>x).ToList();
    }
}
}
