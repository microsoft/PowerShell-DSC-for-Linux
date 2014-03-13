Configuration LinuxFileTest1
{
	Import-DscResource -Module Linux
	
	Node johnkord64-rhel6-01
	{
		Linux_File TestLinuxFile
		{
			Ensure = "Present" # You can also set Ensure to "Absent“
			Type = "File" # Default is “File”
			Contents = "testing Linux_File\n"
			DestinationPath = "/tmp/testing_linux_file.txt"
		}
	}
}

LinuxFileTest1