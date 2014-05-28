sd edit ..\..\mof\MSFT_DSCMetaConfiguration.mof
sd edit ..\..\mof\MSFT_DSCMetaConfiguration.mfl
mofcomp -mof:..\..\mof\MSFT_DSCMetaConfiguration.mof -mfl:..\..\mof\MSFT_DSCMetaConfiguration.mfl -amendment:MS_409 .\MSFT_DSCMetaConfiguration.mof
