using System;
using System.IO;
using System.Linq;
using System.Threading;
using Microsoft.Win32;

namespace ValkyrieRepair {
public static class SelfTests {
    static int passed;
    static void Assert(bool ok, string name) { if(!ok) throw new Exception("FAILED: " + name); Console.WriteLine("PASS " + name); passed++; }
    static void WriteExe(string path) {
        byte[] b = new byte[512]; b[0]=0x4d; b[1]=0x5a; BitConverter.GetBytes(0x80).CopyTo(b,0x3c); b[0x80]=0x50; b[0x81]=0x45; b[0x82]=0; b[0x83]=0; b[0x84]=0x4c; b[0x85]=0x01;
        File.WriteAllBytes(path,b);
    }
    static string Install(string root, string name) {
        string dir=Path.Combine(root,name); Directory.CreateDirectory(dir); Directory.CreateDirectory(Path.Combine(dir,"data")); Directory.CreateDirectory(Path.Combine(dir,"models")); Directory.CreateDirectory(Path.Combine(dir,"audio","CONFIG")); Directory.CreateDirectory(Path.Combine(dir,"scripts"));
        WriteExe(Path.Combine(dir,"gta_sa.exe")); File.WriteAllText(Path.Combine(dir,"data","gta.dat"),"ok"); File.WriteAllText(Path.Combine(dir,"models","gta3.img"),"ok"); File.WriteAllText(Path.Combine(dir,"audio","CONFIG","BANKSLOT.DAT"),"ok");
        return Filesystem.Normalize(dir);
    }
    public static int Run(string rootArg) {
        string root = rootArg ?? Path.Combine(Path.GetTempPath(), "ValkyrieRepairTests-" + Guid.NewGuid().ToString("N"));
        if(Directory.Exists(root)) Directory.Delete(root,true); Directory.CreateDirectory(root);
        try {
            string a=Install(root,"A"), b=Install(root,"B");
            File.WriteAllText(Path.Combine(a,"III.VC.SA.WindowedMode.asi"),"windowed");
            File.WriteAllText(Path.Combine(a,"Sample.asi"),"plugin"); File.WriteAllText(Path.Combine(a,"scripts","Sample.asi"),"plugin");
            var installs=Discovery.Search(root,CancellationToken.None,s=>{});
            Assert(installs.Count==2, "detects multiple installations");
            var scan=Scanner.Scan(a,CancellationToken.None);
            Assert(!scan.Findings.Any(f=>f.Title.Contains("nullfix") || f.Payload=="valkyrie-crashfix.asi"), "SA scan offers no PE-only or separate Crashfix payload");
            Assert(scan.Findings.Any(f=>f.Title=="Install Doctor & Crashfix"), "offers combined ASI on stock GTA SA without PECore or CLEO");
            var installFix=scan.Findings.First(f=>f.Title=="Install Doctor & Crashfix");
            string doctorPath=Path.Combine(a,installFix.Relative);
            string installJournal=RepairEngine.Apply(a,installFix);
            Assert(File.Exists(doctorPath) && new FileInfo(doctorPath).Length>100000, "installs bundled Doctor ASI");
            RepairEngine.Undo(a,installJournal);
            Assert(!File.Exists(doctorPath), "undo removes unchanged bundled install");
            Assert(scan.Findings.Any(f=>f.Title.StartsWith("Optional: disable duplicate")), "suggests identical duplicate disable");
            var fix=scan.Findings.First(f=>f.Repairable && f.Action=="disable");
            string original=Path.Combine(a,fix.Relative);
            string journal=RepairEngine.Apply(a,fix);
            Assert(!File.Exists(original) && File.Exists(original + ".valkyrie-disabled-" + Path.GetFileName(Path.GetDirectoryName(journal))), "disables by rename");
            RepairEngine.Undo(a,journal);
            Assert(File.Exists(original), "undo restores renamed file");
            string ini=Path.Combine(a,"SA.Audio.ini"); File.WriteAllText(ini,"Volume=1\r\nRadioEx=true ; keep\r\n");
            var radioFinding=new Finding{Title="radio",Action="radio",Relative="SA.Audio.ini",ExpectedHash=Filesystem.Hash(ini)};
            journal=RepairEngine.Apply(a,radioFinding);
            Assert(File.ReadAllText(ini).Contains("RadioEx=false ; keep"), "radio repair preserves line");
            RepairEngine.Undo(a,journal);
            Assert(File.ReadAllText(ini).Contains("RadioEx=true ; keep"), "radio undo restores bytes");
            string exePath=Path.Combine(a,"gta_sa.exe"); string compatKey=@"Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers";
            using(var key=Registry.CurrentUser.CreateSubKey(compatKey))key.SetValue(exePath,"~ WIN7RTM",RegistryValueKind.String);
            var compatScan=Scanner.Scan(a,CancellationToken.None);var compatFix=compatScan.Findings.First(f=>f.Action=="compat-clear"&&f.Relative.EndsWith("gta_sa.exe",StringComparison.OrdinalIgnoreCase));
            string compatJournal=RepairEngine.Apply(a,compatFix);Assert(Registry.GetValue(@"HKEY_CURRENT_USER\"+compatKey,exePath,null)==null,"clears compatibility override");
            RepairEngine.Undo(a,compatJournal);Assert(Convert.ToString(Registry.GetValue(@"HKEY_CURRENT_USER\"+compatKey,exePath,null))=="~ WIN7RTM","undo restores compatibility override");
            using(var key=Registry.CurrentUser.OpenSubKey(compatKey,true))if(key!=null)key.DeleteValue(exePath,false);
            bool blocked=false; try { Filesystem.SafePath(a,@"..\B\gta_sa.exe"); } catch(IOException) { blocked=true; }
            Assert(blocked, "blocks paths outside selected install");
            Console.WriteLine("All " + passed + " tests passed.");
            return 0;
        } catch(Exception e) {
            Console.Error.WriteLine(e.ToString());
            return 1;
        } finally {
            try { Directory.Delete(root,true); } catch {}
        }
    }
}
}
