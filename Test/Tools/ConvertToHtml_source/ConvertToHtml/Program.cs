using System;
using System.IO;
using System.Linq;

namespace ConvertToHtml
{
    static class ConvertToHtml
    {
        /// <summary>
        ///     Usage: ConvertToHtml xmlLog [childFolder]
        ///     xmlLog: xml log name OR xml logs folder
        ///    [childFolder]: optional, if not given, will save html logs to current folder
        /// </summary>
        /// <param name="args"></param>
        /// <returns></returns>
        static int Main(string[] args)
        {
            if (args.Length > 3 || args.Length == 0 )
            {
                PrintBanner();
                return 1;
            }

            #region Prepare the instance of Converter

            bool isFileToConvert = args[0].EndsWith(".xml");
            bool isFolderToConvert = Directory.Exists(Path.Combine(AppDomain.CurrentDomain.BaseDirectory, args[0]));
            string convertSrc = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, args[0]);
            string convertDes = string.Empty;

            Converter mcfLogConverter = null;
            
            if (args.Length == 1)
            {
                if (!isFileToConvert)
                {
                    PrintBanner();
                    return 1;
                }

                mcfLogConverter = new Converter(convertSrc, convertDes, Converter.TargetType.File);
            }                        
            
            if (args.Length >= 2)
            {
                if (!isFolderToConvert)
                {
                    PrintBanner();
                    return 1;
                }

                convertDes = args[1];
                mcfLogConverter = new Converter(convertSrc, convertDes, Converter.TargetType.Folder);

                if (!Directory.Exists(mcfLogConverter.OutputFolder))
                {
                    Directory.CreateDirectory(mcfLogConverter.OutputFolder);
                }
                else
                {
                    DirectoryInfo di = new DirectoryInfo(mcfLogConverter.OutputFolder);
                    di.GetFiles().ToList().ForEach(
                        r => r.Delete());
                }

                if (args.Length == 3 && args[2] == "/s")
                {
                    mcfLogConverter.NeedStatistics = true;
                }
            }

            #endregion

            // now start to convert
            if (mcfLogConverter == null)
            {
                Console.WriteLine("Convert aborted, no instance of Converter is created");
                return 1;
            }

            if (mcfLogConverter.Start())
            {
                Console.WriteLine("Finished! All xml logs have been converted to Html");
            }
            
            return 0;
        }

        private static void PrintBanner()
        {
            Console.WriteLine("This tool will convert: ");
            Console.WriteLine("\t \"mcf xml log(s)\" ==> \"html log(s)\"");
            Console.WriteLine("\t , also can create a statistics page \n \n");
            Console.WriteLine("Please enter a string argument:");
            Console.WriteLine("Usage: ConvertToHtml xmlLog/{xmlLogFolder desHtmlFolder [/s]}");
            Console.WriteLine("\t xmlLog: xml log name, the converted html log will be saved to current folder");
            Console.WriteLine("\t xmlLogFolder: relative path which hold the source mcf xml logs");
            Console.WriteLine("\t desHtmlFolder: relative path which will hold all converted html logs");
            Console.WriteLine("\t /s: create statistics page");
        }
    }
}