<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:msxsl="urn:schemas-microsoft-com:xslt" exclude-result-prefixes="msxsl"
>
    <xsl:output method="html" indent="yes"/>

    <xsl:template match="/">
      <html>
        <head>
          <title>
    Mcf Log Report
          </title>
          <style type="text/css">

            p.MsoNormal
            {margin-bottom:.0001pt;
            font-size:11.0pt;
            font-family:"Calibri","sans-serif";
            margin-left: 0in;
            margin-right: 0in;
            margin-top: 0in;
            }
            table.MsoNormalTable
            {font-size:10.0pt;
            font-family:"Times New Roman","serif";
            }
          </style>
        </head>
        <body>
          <table border="0" cellpadding="0" cellspacing="0" class="MsoNormalTable"
              style="border-collapse:collapse;mso-yfti-tbllook:1184;mso-padding-alt:0in 0in 0in 0in">
            <tr style="mso-yfti-irow:0;mso-yfti-firstrow:yes; padding:8px;">
              <td style="width:164.65pt;border-top:solid #4F81BD 1.0pt;
  border-left:none;border-bottom:solid #4F81BD 1.0pt;border-right:none;
  padding:0in 5.4pt 0in 5.4pt" valign="top" width="220">
                <p class="MsoNormal" align="center">
                  <b>
                    <span style="color:#365F91;mso-fareast-language:JA">
                     
                      Activity Name
                    </span>
                  </b>
                </p>
              </td>
              <td style="width:67.05pt;border-top:solid #4F81BD 1.0pt;
  border-left:none;border-bottom:solid #4F81BD 1.0pt;border-right:none;
  padding:0in 5.4pt 0in 5.4pt" valign="top" width="89">
                <p align="center" class="MsoNormal" style="text-align:center; width:90px;">
                  <b>
                    <span style="color:#365F91;mso-fareast-language:JA">
                      Total Cases
                    </span>
                  </b>
                </p>
              </td>
              <td style="width:48.0pt;border-top:solid #4F81BD 1.0pt;
  border-left:none;border-bottom:solid #4F81BD 1.0pt;border-right:none;
  padding:0in 5.4pt 0in 5.4pt" valign="top" width="64">
                <p align="center" class="MsoNormal" style="text-align:center">
                  <b>
                    <span style="color:#365F91;mso-fareast-language:JA">
                      Pass
                    </span>
                  </b>
                </p>
              </td>
              <td style="width:48.0pt;border-top:solid #4F81BD 1.0pt;
  border-left:none;border-bottom:solid #4F81BD 1.0pt;border-right:none;
  padding:0in 5.4pt 0in 5.4pt" valign="top" width="80">
                <p align="center" class="MsoNormal" style="text-align:center">
                  <b>
                    <span style="color:#365F91;mso-fareast-language:JA">
                      Fail
                    </span>
                  </b>
                </p>
              </td>
              <!--<td style="border-top:solid #4F81BD 1.0pt;
  border-left:none;border-bottom:solid #4F81BD 1.0pt;border-right:none;
  padding:0in 5.4pt 0in 5.4pt" valign="top" width="80">
                <p align="center" class="MsoNormal" style="text-align:center; width:80px;">
                  <b>
                    <span style="color:#365F91;mso-fareast-language:JA">
                      Pass(bug id)
                    </span>
                  </b>
                </p>
              </td>
              <td style="border-top:solid #4F81BD 1.0pt;
  border-left:none;border-bottom:solid #4F81BD 1.0pt;border-right:none;
  padding:0in 5.4pt 0in 5.4pt" valign="top" width="80">
                <p align="center" class="MsoNormal" style="text-align:center;width:80px;">
                  <b>
                    <span style="color:#365F91;mso-fareast-language:JA">
                      Fail(bug id)
                    </span>
                  </b>
                </p>
              </td>-->
              <td style="border-top:solid #4F81BD 1.0pt;
  border-left:none;border-bottom:solid #4F81BD 1.0pt;border-right:none;
  padding:0in 5.4pt 0in 5.4pt" valign="top" width="100">
                <p align="center" class="MsoNormal" style="text-align:center">
                  <b>
                    <span style="color:#365F91;mso-fareast-language:JA">
                      Unsupported
                    </span>
                  </b>
                </p>
              </td>
              <td style="width:95.55pt;border-top:solid #4F81BD 1.0pt;
  border-left:none;border-bottom:solid #4F81BD 1.0pt;border-right:none;
  padding:0in 5.4pt 0in 5.4pt" valign="top" width="127">
                <p align="center" class="MsoNormal" style="text-align:center; width:120px;">
                  <b>
                    <span style="color:#365F91;mso-fareast-language:JA">
                      Aborted
                    </span>
                  </b>
                </p>
              </td>
              <td style="width:169.5pt;border-top:solid #4F81BD 1.0pt;
  border-left:none;border-bottom:solid #4F81BD 1.0pt;border-right:none;
  padding:0in 5.4pt 0in 5.4pt" valign="top" width="226">
                <p align="center" class="MsoNormal" style="text-align:center">
                  <b>
                    <span style="color:#365F91;mso-fareast-language:JA">
                      Aborted Reason
                    </span>
                  </b>
                </p>
              </td>
            </tr>

            <xsl:for-each select="/Root/Activity">
              <xsl:choose>
                <xsl:when test="position() mod 2=1">
                  <tr style="mso-yfti-irow:1;background: #D3DFEE; padding:5px;">

                    <td style="width: 164.65pt;  padding: 0in 5.4pt 0in 5.4pt"
                        valign="top" width="220">
                      <p align="center" class="MsoNormal" style="text-align:center">
                        <b>
                          <span style="color:#365F91;mso-fareast-language:JA">
                            <xsl:value-of select="@Name"/>

                          </span>
                        </b>
                      </p>
                    </td>
                    <td style="width: 67.05pt;  padding: 0in 5.4pt 0in 5.4pt"
                        valign="top" width="89">
                      <p align="center" class="MsoNormal" style="text-align:center">
                        <span style="color:#365F91;mso-fareast-language:JA">
                          <xsl:value-of select="Result1 - Result9"/>
                        </span>
                      </p>
                    </td>
                    <td style="width: 48.0pt;  padding: 0in 5.4pt 0in 5.4pt"
                        valign="top" width="64">
                      <p align="center" class="MsoNormal" style="text-align:center">
                        <span style="color:#00B050;mso-fareast-language:JA">
                          <xsl:value-of select="Result2+Result4"/>
                        </span>
                      </p>
                    </td>
                    <td style="width: 48.0pt;  padding: 0in 5.4pt 0in 5.4pt"
                        valign="top" width="64">
                      <p align="center" class="MsoNormal" style="text-align:center">
                        <span style="color:red;mso-fareast-language:JA">
                          <xsl:value-of select="Result3+Result5"/>
                        </span>
                      </p>
                    </td>
                    <!--<td style="padding: 0in 5.4pt 0in 5.4pt"
                      valign="top" width="80">
                      <p align="center" class="MsoNormal" style="text-align:center;">
                        <span style="color:red;mso-fareast-language:JA">
                          <xsl:value-of select="Result4"/>
                        </span>
                      </p>
                    </td>
                    <td style="padding: 0in 5.4pt 0in 5.4pt"
                      valign="top" width="80">
                      <p align="center" class="MsoNormal" style="text-align:center">
                        <span style="color:red;mso-fareast-language:JA">
                          <xsl:value-of select="Result5"/>
                        </span>
                      </p>
                    </td>-->
                    <td style="padding: 0in 5.4pt 0in 5.4pt"
                        valign="top" width="100">
                      <p align="center" class="MsoNormal" style="text-align:center">
                        <span style="color:#4F81BD;mso-fareast-language:JA">
                          <xsl:value-of select="Result9"/>
                        </span>
                      </p>
                    </td>
                    <td style="width: 95.55pt;  padding: 0in 5.4pt 0in 5.4pt"
                        valign="top" width="127">
                      <p align="center" class="MsoNormal" style="text-align:center">
                        <span style="color:#7030A0;mso-fareast-language:JA">
                          <xsl:value-of select="Result6"/>
                        </span>
                      </p>
                    </td>
                    <td style="width: 169.5pt;  padding: 0in 5.4pt 0in 5.4pt"
                        valign="top" width="226">
                    </td>
                  </tr>
                  </xsl:when>
                <xsl:otherwise>
                  <tr style="mso-yfti-irow:1;background: #ffffff; padding:5px;">

                    <td style="width: 164.65pt;padding: 0in 5.4pt 0in 5.4pt"
                        valign="top" width="220">
                      <p align="center" class="MsoNormal" style="text-align:center">
                        <b>
                          <span style="color:#365F91;mso-fareast-language:JA">
                            <xsl:value-of select="@Name"/>

                          </span>
                        </b>
                      </p>
                    </td>
                    <td style="width: 67.05pt;  padding: 0in 5.4pt 0in 5.4pt"
                        valign="top" width="89">
                      <p align="center" class="MsoNormal" style="text-align:center">
                        <span style="color:#365F91;mso-fareast-language:JA">
                          <xsl:value-of select="Result1 - Result9"/>
                        </span>
                      </p>
                    </td>
                    <td style="width: 48.0pt;  padding: 0in 5.4pt 0in 5.4pt"
                        valign="top" width="64">
                      <p align="center" class="MsoNormal" style="text-align:center">
                        <span style="color:#00B050;mso-fareast-language:JA">
                          <xsl:value-of select="Result2+Result4"/>
                        </span>
                      </p>
                    </td>
                    <td style="width: 48.0pt;  padding: 0in 5.4pt 0in 5.4pt"
                        valign="top" width="64">
                      <p align="center" class="MsoNormal" style="text-align:center">
                        <span style="color:red;mso-fareast-language:JA">
                          <xsl:value-of select="Result3+Result5"/>
                        </span>
                      </p>
                    </td>
                    <!--<td style="padding: 0in 5.4pt 0in 5.4pt"
                     valign="top" width="80">
                      <p align="center" class="MsoNormal" style="text-align:center">
                        <span style="color:red;mso-fareast-language:JA">
                          <xsl:value-of select="Result4"/>
                        </span>
                      </p>
                    </td>
                    <td style="padding: 0in 5.4pt 0in 5.4pt"
                      valign="top" width="80">
                      <p align="center" class="MsoNormal" style="text-align:center">
                        <span style="color:red;mso-fareast-language:JA">
                          <xsl:value-of select="Result5"/>
                        </span>
                      </p>
                    </td>-->
                    <td style="padding: 0in 5.4pt 0in 5.4pt"
                        valign="top" width="100">
                      <p align="center" class="MsoNormal" style="text-align:center">
                        <span style="color:#4F81BD;mso-fareast-language:JA">
                          <xsl:value-of select="Result9"/>
                        </span>
                      </p>
                    </td>
                    <td style="width: 95.55pt;  padding: 0in 5.4pt 0in 5.4pt"
                        valign="top" width="127">
                      <p align="center" class="MsoNormal" style="text-align:center">
                        <span style="color:#7030A0;mso-fareast-language:JA">
                          <xsl:value-of select="Result6"/>
                        </span>
                      </p>
                    </td>
                    <td style="width: 169.5pt;  padding: 0in 5.4pt 0in 5.4pt"
                        valign="top" width="226">
                    </td>
                  </tr>
                </xsl:otherwise>
                
              </xsl:choose>
             
          
              </xsl:for-each>

            <tr style="mso-yfti-irow:1;background: #ffffff; padding:5px;">

              <td style="border-bottom: solid #4F81BD 1.0pt;"
                  valign="top" width="220">
                <p align="center" class="MsoNormal" style="text-align:center">
                  <b>
                    <span style="color:#365F91;mso-fareast-language:JA">
                      Total
                    </span>
                  </b>
                </p>
              </td>
              <td style="border-bottom: solid #4F81BD 1.0pt;"
                  valign="top" width="89">
                <p align="center" class="MsoNormal" style="text-align:center">
                  <span style="color:#365F91;mso-fareast-language:JA">
                    <xsl:value-of select="/Root/Summary/Total"/>
                  </span>
                </p>
              </td>
              <td style="border-bottom: solid #4F81BD 1.0pt;"
                  valign="top" width="64">
                <p align="center" class="MsoNormal" style="text-align:center">
                  <span style="color:#00B050;mso-fareast-language:JA">
                    <xsl:value-of select="/Root/Summary/Pass"/>
                  </span>
                </p>
              </td>
              <td style="border-bottom: solid #4F81BD 1.0pt;"
                  valign="top" width="64">
                <p align="center" class="MsoNormal" style="text-align:center">
                  <span style="color:red;mso-fareast-language:JA">
                    <xsl:value-of select="/Root/Summary/Fail"/>
                  </span>
                </p>
              </td>
              <!--<td style="border-bottom: solid #4F81BD 1.0pt;"
               valign="top" width="80">
                <p align="center" class="MsoNormal" style="text-align:center">
                  <span style="color:red;mso-fareast-language:JA">
                    <xsl:value-of select="/Root/Summary/PassWithBugID"/>
                  </span>
                </p>
              </td>
              <td style="border-bottom: solid #4F81BD 1.0pt;"
                valign="top" width="80">
                <p align="center" class="MsoNormal" style="text-align:center">
                  <span style="color:red;mso-fareast-language:JA">
                    <xsl:value-of select="/Root/Summary/FailWithBugID"/>
                  </span>
                </p>
              </td>-->
              <td style="border-bottom: solid #4F81BD 1.0pt;"
                  valign="top" width="100">
                <p align="center" class="MsoNormal" style="text-align:center">
                  <span style="color:#4F81BD;mso-fareast-language:JA">
                    <xsl:value-of select="/Root/Summary/Unsupported"/>
                  </span>
                </p>
              </td>
              <td style=" border-bottom: solid #4F81BD 1.0pt;"
                  valign="top" width="127">
                <p align="center" class="MsoNormal" style="text-align:center">
                  <span style="color:#7030A0;mso-fareast-language:JA">
                    <xsl:value-of select="/Root/Summary/NotRun"/>
                  </span>
                </p>
              </td>
              <td style="border-bottom: solid #4F81BD 1.0pt;"
                  valign="top" width="226">
                <span style="color:#365F91;mso-fareast-language:JA; font-weight:bolder;font-size:14pt;">
                  Pass Rate:<xsl:value-of select="/Root/Summary/PassRate"/>
                </span>
              </td>
            </tr>
            
          </table>
        </body>
      </html>

    </xsl:template>
</xsl:stylesheet>
