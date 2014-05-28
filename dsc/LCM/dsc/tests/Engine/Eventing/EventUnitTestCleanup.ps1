if(Test-Path eventunitestdata)
{
    del eventunitestdata -Force -Recurse
}


#disable the log
wevtutil set-log Microsoft-Windows-DSC/Debug /e:false
wevtutil set-log Microsoft-Windows-DSC/Analytic /e:false
