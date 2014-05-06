using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Xml.Xsl;

namespace ConvertToHtml
{
    public class Converter
    {
        #region Properties and Fields

        public enum TargetType
        {
            File,
            Folder
        }

        private TargetType ConverterTargetType { get; set; }

        /// <summary>
        ///     mcf xml log file name OR mcf xml logs folder name
        /// </summary>
        private string McfXmlLogs { get; set; }

        /// <summary>
        ///     mcf html logs folder name
        /// </summary>
        private string OutputFolderName { get; set; }

        /// <summary>
        ///     mcf html logs folder path
        /// </summary>
        public string OutputFolder 
        { 
            get
            {
                return Path.Combine(
                        AppDomain.CurrentDomain.BaseDirectory,
                        OutputFolderName);
            }
        }

        public bool NeedStatistics { private get; set; }

        private string McfLogTemplateName
        {
            get { return "MCFLogTemplate.xsl"; }
        }

        private readonly StatisticalWorker _statisticalWorker = new StatisticalWorker();

        #endregion

        #region Constructor

        private Converter(string src, string des)
        {
            McfXmlLogs = src;
            OutputFolderName = des;
        }

        public Converter(string src, string des, TargetType targetType): this(src, des)
        {
            ConverterTargetType = targetType;
        }

        #endregion

        #region Functions

        public bool Start()
        {
            if (ConverterTargetType == TargetType.File)
            {
                // Conver a single xml log to Html log
                ConvertFile(McfXmlLogs, AppDomain.CurrentDomain.BaseDirectory);
            }
            else if (ConverterTargetType ==  TargetType.Folder)
            {
                // Conver all xml logs of a folder to html logs
                ConvertFolder(McfXmlLogs, OutputFolder);

                if (NeedStatistics)
                {
                    _statisticalWorker.CreateStatisticsPage(McfXmlLogs);
                }
            }
            else
            {
                Console.WriteLine("xml log folder does not exist");
                return false;
            }

            return true;
        }

        private void ConvertFile(string fileFullName, string desFolder)
        {
            XslCompiledTransform transform = new XslCompiledTransform();
            
            transform.Load(Path.Combine(AppDomain.CurrentDomain.BaseDirectory, McfLogTemplateName));

            string desFullName = Path.Combine(desFolder, Path.GetFileNameWithoutExtension(fileFullName) + ".html");

            transform.Transform(fileFullName, desFullName);
        }

        private void ConvertFolder(string xmlLogsFolder, string htmlLogsFolder)
        {

            List<FileInfo> fileList = (new DirectoryInfo(xmlLogsFolder)).GetFiles().ToList();
            fileList.ForEach(
                file =>
                {
                    if (file.Name.EndsWith(".xml"))
                    {
                        ConvertFile(file.FullName, htmlLogsFolder);
                        Console.Write(".");
                    }
                }
                );
        }

        #endregion
    }
}
