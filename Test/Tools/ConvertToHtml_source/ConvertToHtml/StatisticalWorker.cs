using System;
using System.Globalization;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;
using System.Xml;
using System.Xml.Xsl;

namespace ConvertToHtml
{
    public class StatisticalWorker
    {
        private string StatisticsTemplateName
        {
            get { return "StatisticsTemplate.xslt"; }
        }

        /// <summary>
        ///     Compiled Regex object
        /// </summary>
        private readonly Regex _compiledRegex = new Regex("\\d+", RegexOptions.Compiled);

        #region private enum

        /// <summary>
        ///     The type of Result in generated single Htmllogs
        /// </summary>
        private enum ResultType
        {
            TotalType = 1,
            PassType = 2,
            FailType = 3,
            PassWithBugIdType = 4,
            FailWithBugIdType = 5,
            AbortedType = 6,
            GrpsFailedType = 7,
            GrpsAbortedType = 8,
            UnsupportedType = 9,
            NotRunType = 10,
            ManualType = 11,
            UnknownType = 12
        }
        #endregion

        /// <summary>
        ///     Get xml writer setting
        /// </summary>
        /// <returns></returns>
        private XmlWriterSettings getXMLSetting()
        {
            XmlWriterSettings xws = new XmlWriterSettings
            {
                Indent = true,
                Encoding = Encoding.GetEncoding("utf-8")
            };
            return xws;
        }

        /// <summary>
        ///     Create Staticstics Page
        /// </summary>
        /// <param name="logsFolder"></param>
        public void CreateStatisticsPage(string logsFolder)
        {
            DirectoryInfo di = new DirectoryInfo(logsFolder);
            FileInfo[] fis = di.GetFiles("*.xml");

            string xmlName = DateTime.Now.ToString("yyyy-MM-dd-HH-mm-ss") + ".xml";
            XmlWriter xw = XmlWriter.Create(xmlName, getXMLSetting());
            xw.WriteStartElement("Root");

            int totalNumber = 0;
            int passNumber = 0;
            int failedNumber = 0;
            int abortedNumber = 0;
            int passWithBugIdNumber = 0;
            int failWithBugIdNumber = 0;
            int grpFailedNumber = 0;
            int grpAbortedNumber = 0;
            int unsupportedNumber = 0;
            int notRunNumber = 0;
            int manualNumber = 0;
            int unknownNumber = 0;
            
            foreach (FileInfo xml in fis)
            {
                string bugId = string.Empty;
                int i = 0;
                int activityFaildNumber = 0;

                xw.WriteStartElement("Activity");
                xw.WriteStartAttribute("Name");
                xw.WriteString((Path.GetFileNameWithoutExtension(xml.Name)).Replace("_VarMap.log", string.Empty));
                xw.WriteEndAttribute();

                XmlReader xr = XmlReader.Create(xml.FullName);
                while (xr.Read())
                {
                    if (xr.NodeType == XmlNodeType.Element && xr.LocalName.Equals("Result"))
                    {
                        if (xr.MoveToAttribute("BugId"))
                        {
                            if (bugId.IndexOf(xr.Value, StringComparison.Ordinal) == -1)
                            {
                                bugId += xr.Value + ",";
                            }
                        }
                    }
                    if (xr.NodeType == XmlNodeType.Element && xr.LocalName.Equals("Counter"))
                    {
                        if (xr.Read() && xr.NodeType == XmlNodeType.Text)
                        {
                            i++;

                            string matchNumberString = _compiledRegex.Match(xr.Value).Value;

                            xw.WriteElementString("Result" + i, matchNumberString);

                            ResultType resultType = (ResultType)Enum.Parse(typeof(ResultType), i.ToString(CultureInfo.InvariantCulture));

                            switch (resultType)
                            {
                                case ResultType.TotalType:
                                    totalNumber += int.Parse(matchNumberString);
                                    break;
                                case ResultType.PassType:
                                    passNumber += int.Parse(matchNumberString);
                                    break;
                                case ResultType.FailType:
                                    failedNumber += int.Parse(matchNumberString);
                                    activityFaildNumber += int.Parse(matchNumberString);
                                    break;
                                case ResultType.PassWithBugIdType:
                                    passWithBugIdNumber += int.Parse(matchNumberString);
                                    //add passwithbugid number into pass number
                                    passNumber += int.Parse(matchNumberString);
                                    break;
                                case ResultType.FailWithBugIdType:
                                    failWithBugIdNumber += int.Parse(matchNumberString);
                                    activityFaildNumber += int.Parse(matchNumberString);
                                    //add failedwithbugid number into failed number
                                    failedNumber += int.Parse(matchNumberString);
                                    break;
                                case ResultType.AbortedType:
                                    abortedNumber += int.Parse(matchNumberString);
                                    break;
                                case ResultType.GrpsFailedType:
                                    grpFailedNumber += int.Parse(matchNumberString);
                                    break;
                                case ResultType.GrpsAbortedType:
                                    grpAbortedNumber += int.Parse(matchNumberString);
                                    break;
                                case ResultType.UnsupportedType:
                                    unsupportedNumber += int.Parse(matchNumberString);
                                    break;
                                case ResultType.NotRunType:
                                    notRunNumber += int.Parse(matchNumberString);
                                    break;
                                case ResultType.ManualType:
                                    manualNumber += int.Parse(matchNumberString);
                                    break;
                                case ResultType.UnknownType:
                                    unknownNumber += int.Parse(matchNumberString);
                                    break;
                            }
                        }
                    }
                }
                xw.WriteElementString("TotalFail", activityFaildNumber.ToString(CultureInfo.InvariantCulture));
                xw.WriteElementString("BugID", string.IsNullOrEmpty(bugId) ? bugId : bugId.Remove(bugId.Length - 1, 1));
                xw.WriteEndElement();

                Console.Write('.');
            }

            xw.WriteStartElement("Summary");
            xw.WriteElementString("Total", (totalNumber-unsupportedNumber).ToString(CultureInfo.InvariantCulture));
            xw.WriteElementString("Pass", passNumber.ToString(CultureInfo.InvariantCulture));
            xw.WriteElementString("Fail", failedNumber.ToString(CultureInfo.InvariantCulture));
            xw.WriteElementString("PassWithBugID", passWithBugIdNumber.ToString(CultureInfo.InvariantCulture));
            xw.WriteElementString("FailWithBugID", failWithBugIdNumber.ToString(CultureInfo.InvariantCulture));
            xw.WriteElementString("NotRun", abortedNumber.ToString(CultureInfo.InvariantCulture));
            xw.WriteElementString("Unsupported", unsupportedNumber.ToString(CultureInfo.InvariantCulture));
            xw.WriteElementString("PassRate", CalculatePassRateStr(passNumber,(totalNumber-unsupportedNumber)));
            xw.WriteEndElement();
            xw.WriteEndElement();

            xw.Flush();
            xw.Close();

            XmlTransform(xmlName);
        }

        /// <summary>
        ///     Calculate PassRate string according passNumber and totalNumber
        /// </summary>
        /// <param name="passNum">pass number</param>
        /// <param name="totalNum">total number</param>
        /// <returns></returns>
        private string CalculatePassRateStr(int passNum, int totalNum)
        {
            string passRateStr = passNum < totalNum ? string.Format("{0}%", ((passNum * 1.00 / totalNum) * 100).ToString(CultureInfo.InvariantCulture).Substring(0, 5)) : string.Format("{0}%", 100);
            return passNum > 0 ? passRateStr : "0%";
        }

        /// <summary>
        ///     Generate XML according to StatisticsTemplate.xslt file
        /// </summary>
        /// <param name="xmlName"></param>
        private void XmlTransform(string xmlName)
        {
            XslCompiledTransform xct = new XslCompiledTransform();
            xct.Load(StatisticsTemplateName);
            xct.Transform(xmlName, xmlName.Replace(".xml", ".html"));

            // clean environment
            try
            {
                if (File.Exists(xmlName))
                {
                    File.Delete(xmlName);
                }
            }
            catch (IOException ex)
            {
                // now no log mechanism here.
                Console.WriteLine("File " + xmlName + " delete failed: " + ex);
            }
        }
    }
}
