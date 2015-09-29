/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include<nits.h>
NitsSetup(DRT)
NitsEndSetup
NitsSetup(Common)
NitsEndSetup
NitsSetup(Linux)
NitsEndSetup
NitsSetup(IDX)
NitsEndSetup
NitsSetup(Feature)
NitsEndSetup
NitsSetup(Integration)
NitsEndSetup
NitsSetup(Milestone)
NitsEndSetup
//This header file is for setting the macros NitsDRTTest, NitsIDXTest etc. This is to enforce that prirorites are included in every DSC NITS test.
//Note that this approach of defining NitSetup will work only if each test dll has just one file(.cpp); if it has multiple of them this will lead to link errors saying the DRT setup is defined in multiple OBJs. 
//the way to get around that will be to use NitsDeclSetup/NitsDefSetup and split the declare and definition part into .h and .cpp and include the .obj of the common .cpp file which has NitsDefSetup into all your test dlls.
#define NitsDRTTest(testname) NitsTest1(testname, DRT, NitsEmptyValue)
#define NitsDRTCommonTest(testname) NitsTest2(testname, DRT, NitsEmptyValue, Common, NitsEmptyValue)
#define NitsDRTLinuxTest(testname) NitsTest2(testname, DRT, NitsEmptyValue, Linux, NitsEmptyValue)

#define NitsDRTTest1(testname, fixture1, fixture1init) NitsTest2(testname, fixture1, fixture1init, DRT, NitsEmptyValue)
#define NitsDRTCommonTest1(testname, fixture1, fixture1init) NitsTest3(testname, fixture1, fixture1init, DRT, NitsEmptyValue, Common, NitsEmptyValue)
#define NitsDRTLinuxTest1(testname, fixture1, fixture1init) NitsTest3(testname, fixture1, fixture1init, DRT, NitsEmptyValue, Linux, NitsEmptyValue)

#define NitsDRTTest2(testname, fixture1, fixture1init, fixture2, fixture2init) NitsTest3(testname, fixture1, fixture1init, fixture2, fixture2init, DRT, NitsEmptyValue)
#define NitsDRTCommonTest2(testname, fixture1, fixture1init, fixture2, fixture2init) NitsTest4(testname, fixture1, fixture1init, fixture2, fixture2init, DRT, NitsEmptyValue, Common, NitsEmptyValue)
#define NitsDRTLinuxTest2(testname, fixture1, fixture1init, fixture2, fixture2init) NitsTest4(testname, fixture1, fixture1init, fixture2, fixture2init, DRT, NitsEmptyValue, Linux, NitsEmptyValue)

#define NitsDRTTest3(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init) NitsTest4(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init, DRT, NitsEmptyValue)
#define NitsDRTCommonTest3(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init) NitsTest5(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init, DRT, NitsEmptyValue, Common, NitsEmptyValue)
#define NitsDRTLinuxTest3(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init) NitsTest5(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init, DRT, NitsEmptyValue, Linux, NitsEmptyValue)

#define NitsDRTTest4(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init,fixture4, fixture4init) NitsTest5(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init,fixture4, fixture4init, DRT, NitsEmptyValue)

#define NitsIntegrationTest(testname) NitsTest1(testname, Integration, NitsEmptyValue)
#define NitsIntegrationCommonTest(testname) NitsTest2(testname, Integration, NitsEmptyValue, Common, NitsEmptyValue)
#define NitsIntegrationLinuxTest(testname) NitsTest2(testname, Integration, NitsEmptyValue, Linux, NitsEmptyValue)

#define NitsIntegrationTest1(testname, fixture1, fixture1init) NitsTest2(testname, fixture1, fixture1init, Integration, NitsEmptyValue)
#define NitsIntegrationCommonTest1(testname, fixture1, fixture1init) NitsTest3(testname, fixture1, fixture1init, Integration, NitsEmptyValue, Common, NitsEmptyValue)
#define NitsIntegrationLinuxTest1(testname, fixture1, fixture1init) NitsTest3(testname, fixture1, fixture1init, Integration, NitsEmptyValue, Linux, NitsEmptyValue)

#define NitsIntegrationTest2(testname, fixture1, fixture1init, fixture2, fixture2init) NitsTest3(testname, fixture1, fixture1init, fixture2, fixture2init, Integration, NitsEmptyValue)
#define NitsIntegrationCommonTest2(testname, fixture1, fixture1init, fixture2, fixture2init) NitsTest3(testname, fixture1, fixture1init, fixture2, fixture2init, Integration, NitsEmptyValue, Common, NitsEmptyValue)
#define NitsIntegrationLinuxTest2(testname, fixture1, fixture1init, fixture2, fixture2init) NitsTest3(testname, fixture1, fixture1init, fixture2, fixture2init, Integration, NitsEmptyValue, Linux, NitsEmptyValue)

#define NitsIntegrationTest3(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init) NitsTest4(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init, Integration, NitsEmptyValue)
#define NitsIntegrationCommonTest3(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init) NitsTest5(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init, Integration, NitsEmptyValue, Common, NitsEmptyValue)
#define NitsIntegrationLinuxTest3(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init) NitsTest5(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init, Integration, NitsEmptyValue, Linux, NitsEmptyValue)

#define NitsIntegrationTest4(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init,fixture4, fixture4init) NitsTest5(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init,fixture4, fixture4init, Integration, NitsEmptyValue)


#define NitsIDXTest(testname) NitsTest1(testname, IDX, NitsEmptyValue)
#define NitsIDXCommonTest(testname) NitsTest2(testname, IDX, NitsEmptyValue, Common, NitsEmptyValue)
#define NitsIDXLinuxTest(testname) NitsTest2(testname, IDX, NitsEmptyValue, Linux, NitsEmptyValue)

#define NitsIDXTest1(testname, fixture1, fixture1init) NitsTest2(testname, fixture1, fixture1init, IDX, NitsEmptyValue)
#define NitsIDXCommonTest1(testname, fixture1, fixture1init) NitsTest3(testname, fixture1, fixture1init, IDX, NitsEmptyValue, Common, NitsEmptyValue)
#define NitsIDXLinuxTest1(testname, fixture1, fixture1init) NitsTest3(testname, fixture1, fixture1init, IDX, NitsEmptyValue, Linux, NitsEmptyValue)

#define NitsIDXTest2(testname, fixture1, fixture1init, fixture2, fixture2init) NitsTest3(testname, fixture1, fixture1init, fixture2, fixture2init, IDX, NitsEmptyValue)
#define NitsIDXCommonTest2(testname, fixture1, fixture1init, fixture2, fixture2init) NitsTest4(testname, fixture1, fixture1init, fixture2, fixture2init, IDX, NitsEmptyValue, Common, NitsEmptyValue)
#define NitsIDXLinuxTest2(testname, fixture1, fixture1init, fixture2, fixture2init) NitsTest4(testname, fixture1, fixture1init, fixture2, fixture2init, IDX, NitsEmptyValue, Linux, NitsEmptyValue)


#define NitsIDXTest3(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init) NitsTest4(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init, IDX, NitsEmptyValue)
#define NitsIDXCommonTest3(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init) NitsTest5(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init, IDX, NitsEmptyValue, Common, NitsEmptyValue)
#define NitsIDXLinuxTest3(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init) NitsTest5(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init, IDX, NitsEmptyValue, Linux, NitsEmptyValue)

#define NitsIDXTest4(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init,fixture4, fixture4init) NitsTest5(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init,fixture4, fixture4init, IDX, NitsEmptyValue)

#define NitsFeatureTest(testname) NitsTest1(testname, Feature, NitsEmptyValue)
#define NitsFeatureCommonTest(testname) NitsTest2(testname, Feature, NitsEmptyValue, Common, NitsEmptyValue)
#define NitsFeatureLinuxTest(testname) NitsTest2(testname, Feature, NitsEmptyValue, Linux, NitsEmptyValue)

#define NitsFeatureTest1(testname, fixture1, fixture1init) NitsTest2(testname, fixture1, fixture1init, Feature, NitsEmptyValue)
#define NitsFeatureCommonTest1(testname, fixture1, fixture1init) NitsTest3(testname, fixture1, fixture1init, Feature, NitsEmptyValue, Common, NitsEmptyValue)
#define NitsFeatureLinuxTest1(testname, fixture1, fixture1init) NitsTest3(testname, fixture1, fixture1init, Feature, NitsEmptyValue, Linux, NitsEmptyValue)

#define NitsFeatureTest2(testname, fixture1, fixture1init, fixture2, fixture2init) NitsTest3(testname, fixture1, fixture1init, fixture2, fixture2init, Feature, NitsEmptyValue)
#define NitsFeatureCommonTest2(testname, fixture1, fixture1init, fixture2, fixture2init) NitsTest4(testname, fixture1, fixture1init, fixture2, fixture2init, Feature, NitsEmptyValue, Common, NitsEmptyValue)
#define NitsFeatureLinuxTest2(testname, fixture1, fixture1init, fixture2, fixture2init) NitsTest4(testname, fixture1, fixture1init, fixture2, fixture2init, Feature, NitsEmptyValue, Linux, NitsEmptyValue)

#define NitsFeatureTest3(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init) NitsTest4(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init, Feature, NitsEmptyValue)
#define NitsFeatureCommonTest3(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init) NitsTest5(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init, Feature, NitsEmptyValue, Common, NitsEmptyValue)
#define NitsFeatureLinuxTest3(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init) NitsTest5(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init, Feature, NitsEmptyValue, Linux, NitsEmptyValue)

#define NitsFeatureTest4(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init,fixture4, fixture4init) NitsTest5(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init,fixture4, fixture4init, Feature, NitsEmptyValue)

#define NitsMilestoneTest(testname) NitsTest1(testname, Milestone, NitsEmptyValue)
#define NitsMilestoneCommonTest(testname) NitsTest2(testname, Milestone, NitsEmptyValue, Common, NitsEmptyValue)
#define NitsMilestoneLinuxTest(testname) NitsTest2(testname, Mileston, NitsEmptyValue, Linux, NitsEmptyValue)

#define NitsMilestoneTest1(testname, fixture1, fixture1init) NitsTest2(testname, fixture1, fixture1init, Milestone, NitsEmptyValue)
#define NitsMilestoneCommonTest1(testname, fixture1, fixture1init) NitsTest3(testname, fixture1, fixture1init, Milestone, NitsEmptyValue, Common, NitsEmptyValue)
#define NitsMilestoneLinuxTest1(testname, fixture1, fixture1init) NitsTest3(testname, fixture1, fixture1init, Milestone, NitsEmptyValue, Linux, NitsEmptyValue)

#define NitsMilestoneTest2(testname, fixture1, fixture1init, fixture2, fixture2init) NitsTest3(testname, fixture1, fixture1init, fixture2, fixture2init, Milestone, NitsEmptyValue)
#define NitsMilestoneCommonTest2(testname, fixture1, fixture1init, fixture2, fixture2init) NitsTest4(testname, fixture1, fixture1init, fixture2, fixture2init, Milestone, NitsEmptyValue, Common, NitsEmptyValue)
#define NitsMilestoneLinuxTest2(testname, fixture1, fixture1init, fixture2, fixture2init) NitsTest4(testname, fixture1, fixture1init, fixture2, fixture2init, Milestone, NitsEmptyValue, Linux, NitsEmptyValue)

#define NitsMilestoneTest3(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init) NitsTest4(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init, Milestone, NitsEmptyValue)
#define NitsMilestoneCommonTest3(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init) NitsTest5(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init, Milestone, NitsEmptyValue, Common, NitsEmptyValue)
#define NitsMilestoneLinuxTest3(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init) NitsTest5(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init, Milestone, NitsEmptyValue, Linux, NitsEmptyValue)

#define NitsMilestoneTest4(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init,fixture4, fixture4init) NitsTest5(testname, fixture1, fixture1init, fixture2, fixture2init, fixture3, fixture3init,fixture4, fixture4init, Milestone, NitsEmptyValue)

