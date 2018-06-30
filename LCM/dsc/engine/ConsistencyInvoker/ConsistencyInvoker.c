/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <stdlib.h>

#define PYTHON_COMMAND "python"
#define PYTHON_SCRIPT_NAME "PerformRequiredConfigurationChecks.py"

int main(int argc, char *argv[])
{
    int fullCommandLength = strlen(PYTHON_COMMAND) + 1 + strlen(DSC_SCRIPT_PATH) + 1 + strlen(PYTHON_SCRIPT_NAME) + 1;
    char fullCommand[fullCommandLength];

    strcpy(fullCommand, PYTHON_COMMAND);
    strcat(fullCommand, " ");
    strcat(fullCommand, DSC_SCRIPT_PATH);
    strcat(fullCommand, "/");
    strcat(fullCommand, PYTHON_SCRIPT_NAME);

    int returnValue = system(fullCommand);
    return returnValue;
}
