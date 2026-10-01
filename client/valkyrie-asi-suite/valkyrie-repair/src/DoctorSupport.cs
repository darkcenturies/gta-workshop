using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
namespace ValkyrieRepair {
public static class DoctorSupport {
    public static void Check(ScanResult r,List<string> files) {
        var copies=files.Where(f=>Path.GetFileName(f).Equals("doctor-valkyrie.asi",StringComparison.OrdinalIgnoreCase) && !f.Substring(r.Root.Length).ToLowerInvariant().Contains("backup")).ToList();
        const string advice="Doctor and Crashfix share one GTA San Andreas ASI. Keep one active copy; review standalone Crashfix copies before restarting.";
        if(copies.Count==0){r.Findings.Add(new Finding{Title="Install Doctor & Crashfix",Severity="Suggested fix",Advice=advice,Evidence="No combined ASI found.",Relative="doctor-valkyrie.asi",Action="install",Payload="doctor-valkyrie.asi",ExpectedHash=""});return;}
        if(copies.Count>1){r.Findings.Add(new Finding{Title="Multiple Doctor copies found",Severity="Review",Evidence=String.Join("\r\n",copies),Advice=advice});return;}
        string file=copies[0];
        if(new FileInfo(file).Length>32*1024*1024)return;
        string text=Encoding.ASCII.GetString(File.ReadAllBytes(file));
        var match=Regex.Match(text,@"doctor-valkyrie (\d+\.\d+\.\d+)");
        Version version=match.Success?new Version(match.Groups[1].Value):null;
        string hash=Filesystem.Hash(file);
        string[] old={"C3A75A03D2025CC7230C7F4CCCC5448543B3673AA3CE4BCE85C0531E83303034","2B6D92C4DF841DBBFCEDBC4261359C178FEF6BD7551E8107CFF674C7E215A046","824610FEE21A75A49C4A496AAD2B84F955E9843DF833390790E632EC897BDA0F"};
        if(version==null && old.Contains(hash))version=new Version("0.3.2");
        if(version!=null && version<new Version("0.4.0"))r.Findings.Add(new Finding{Title="Update Doctor & Crashfix",Severity="Suggested fix",Evidence=file,Advice=advice,Relative=file.Substring(r.Root.Length),Action="replace",Payload="doctor-valkyrie.asi",ExpectedHash=hash});
        else r.Findings.Add(new Finding{Title=version==null?"Doctor version could not be identified":"Doctor "+version+" found",Severity="Review",Evidence=file,Advice=advice});
    }
}
}
