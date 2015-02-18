CustomBuildNumberTask is a .net assembly which contains the MSBuild custom 
task "CustomBuildNumber".

The CustomBuildNumber task will update the build number for the currently in 
progress TFS build job (as well as the drop location) but if it detects that 
there will be a collision with an existing build number then it will increment 
the build revision number (or tack on a build revision number, starting at .1
if one did not previously exist) up to a maximum of 20 times until a free 
build number is found. The actual build number is returned as an output, if 
no free build number exists in the range attempted then the task will throw an
exception of type BuildNumberAlreadyExistsException.

To use the task in an MSBuild project it's necessary to first reference the 
assembly:

  <UsingTask TaskName="CustomBuildNumberTask.CustomBuildNumber" AssemblyFile="Path\to\Assembly\CustomBuildNumberTask.dll" />

Then use it within a target.

<Target>
    <CustomBuildNumber TFSServerURI="$(TeamFoundationServerUrl)" BuildURI="$(BuildUri)" RequestedBuildNumber="$(BuildNumber)" >
        <Output TaskParameter="BuildNumber" PropertyName="BuildNumber" />
    </CustomBuildNumber>
</Target>


The sources for this task are currently checked into http://vstfpg05:8080/tfs 
under the CDM TPC at $/Sandbox/private/SCXTools/CustomBuildNumber