/*
 Poisson Disc Sampler 0.0.1
 -----
 
*/
using System.IO;
using System.Collections;
using UnrealBuildTool;

public class PoissonDiscSamplerPlugin: ModuleRules
{
    public PoissonDiscSamplerPlugin(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "Engine"
            });

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                
            });

        string ThirdPartyPath = Path.Combine(ModuleDirectory, "../../ThirdParty");

        // -- PDSGen include and lib path

        string PDSGenPath = Path.Combine(ThirdPartyPath, "pdsgenerator");
        string PDSGenInclude = Path.Combine(PDSGenPath, "include");
        string PDSGenLib = Path.Combine(PDSGenPath, "lib");

        PublicIncludePaths.Add(Path.GetFullPath(PDSGenInclude));
        PublicLibraryPaths.Add(Path.GetFullPath(PDSGenLib));

        PublicAdditionalLibraries.Add("PDSGenerator.lib");
    }
}
