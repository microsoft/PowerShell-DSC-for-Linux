Configuration nxFileExample1
{
	Import-DscResource -Module nx
	
	Node MyLinuxHostname
	{
		nxFile TestLinuxFile
		{
			Ensure = "Present"
			Type = "File"
			Contents = "testing nxFile\n"
			DestinationPath = "/tmp/test_linux_file.txt"
		}
	}
}

nxFileExample1