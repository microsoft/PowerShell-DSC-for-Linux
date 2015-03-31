configuration nxPackage {
param (
    [Parameter(Mandatory)]
    [String]$Name,
    [ValidateSet('Present','Absent')]
    [String]$Ensure = 'Present'
)
#     Import-DscResource -ModuleName nx

    nxScript "Package-$Name" {
        GetScript = @'
#!/bin/bash
yum info {0}
'@ -f $Name
        TestScript = @'
#!/bin/bash
case {1} in
    Present)
        yum list installed {0} > /dev/null 2>&1 || exit 1 && exit 0;;
    Absent)
        yum list installed {0} > /dev/null 2>&1 || exit 0 && exit 1;;
esac
'@ -f $Name, $Ensure
        SetScript = @'
#!/bin/bash
case {1} in
    Present)
        yum -y install {0};;
    Absent)
        yum -y erase {0};;
esac
'@ -f $Name, $Ensure
    }

}
