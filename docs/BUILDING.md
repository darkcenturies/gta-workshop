# Building GTA mods in their implementation owner

GTA Workshop explains the methods; it contains no build recipes or mod source.
Select the [source owner](REPOSITORIES.md) before running commands.

## Native Valkyrie mods

Doctor/Crashfix, Map and Repair are maintained in private
[valkyrie-workshop](https://github.com/darkcenturies/valkyrie-workshop).
Read its instructions and component recipes. Typical suite commands, run from
that owner's canonical checkout on Windows:

```powershell
./client/valkyrie-asi-suite/build.ps1 -Release -OnlyTarget doctor-valkyrie
./client/valkyrie-asi-suite/build.ps1 -Release -OnlyTarget valkyrie-map
```

Install MSVC C++ Build Tools with Desktop development with C++ and a Windows
SDK. Select x86 for classic GTA SA plugins. An ASI is a Windows DLL loaded by
the game's ASI loader; changing the extension does not establish compatibility.

Doctor and Crashfix share one artwork-free ASI. Repair is a C# application
using the .NET Framework compiler; follow its private component recipe.
Preserve GPL guard notices and all applicable diagnostic-resource terms.

## Public Phone

In the existing [valkyrie-phone](https://github.com/darkcenturies/valkyrie-phone)
checkout:

```powershell
git submodule update --init --recursive
./valkyrie-asi-suite/build.ps1 -Release
```

Its pinned SDK/ImGui dependencies and reviewed shared source build independently.
Maps needs tiles from the player's installation. Optional browser pages need
the separately supplied/generated page pack. Follow its packaging instructions;
do not assume optional content is present because the ASI compiled.

## Validation and publication

Build only the affected owner target without installation. Run meaningful
existing component tests. Report builds, tests, package integrity and in-game
behavior separately. Never install mods or deploy services merely to validate
a guide. A package release uses its owner's reviewed revision and process,
not files copied out of this knowledge repository.

Return the exact target, source revision, commands/results, failures and limits
here using [the finding template](../research/finding-template.md).
