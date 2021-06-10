using UnrealBuildTool;

public class ZipPlatformFileEd : ModuleRules
{
	public ZipPlatformFileEd(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			});

        PrivateDependencyModuleNames.AddRange(new string[] {
			"Settings",
			"ZipPlatformFile",
		});
	}
}
