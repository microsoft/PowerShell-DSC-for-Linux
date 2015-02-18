@ECHO OFF

REM =======================================================================
REM
REM    INPUTS:   This CMD file takes 2 command line parameters:
REM
REM       1) Server Name - Server on which the PoliCheck user wants the History Database 
REM       2) Database Name ("dbname")
REM
REM    OUTPUTS : At the end of this run, the DB will be setup for use.
REM
REM =======================================================================
REM          Change History
REM 	 Date 		Author   	Description  
REM	02/16/2006	v-gowram	Creation of the CMD file to automate the process
REM=======================================================================

REM Processing cmd line parameters here...
SET Server=%1
SET DBName=%2

REM Checking cmd line parameters

if "%1" == "" echo Usage - HistoryDatabase ^<dbservername^> ^<dbname^> & GOTO END
if "%2" == "" echo Usage - HistoryDatabase ^<dbservername^> ^<dbname^> & GOTO END

REM Log filename variables...
SET log=HistoryDatabase.log

ECHO Starting setup.... > %log%
ECHO Starting setup....

REM Echo variable settings to log
ECHO **** Server Name      : %Server%        >> %log%
ECHO **** Server Name      : %Server%  
ECHO **** Database Name    : %DBName%        >> %log%
ECHO **** Database Name    : %DBName%

REM =========================================================================

		REM Exiting batch program if History Database already exists.

REM =========================================================================

osql -E -b -S %Server% -d master -Q "IF EXISTS(SELECT * FROM sysdatabases WHERE name = '%DBName%') RAISERROR('Database %DBName% already exists choose another name and try again', 16, 1)" 
IF ERRORLEVEL 1 set errmsg=Database already exists & goto ERROR

REM =========================================================================

		ECHO **** Creating History Database >> %log%
		ECHO **** Creating History Database 

REM =========================================================================

osql -E -S %Server% -d master -Q "CREATE DATABASE [%DBName%]" >> %log%

REM =========================================================================

		REM Set ARITHABORT option before excuting SQL queries

REM =========================================================================

osql -E -S %Server% -d %DBName% -Q "ALTER DATABASE [%DBName%] SET ARITHABORT ON" >> %log%

REM =========================================================================

REM =========================================================================

		ECHO **** Executing SQL Queries to create tables, views and stored procedures >> %log%
		ECHO **** Executing SQL Queries to create tables, views and stored procedures

REM =========================================================================

osql -E -S %Server% -d %DBName% -i "PC_HistoryManagement.sql" -n >> %log%

GOTO END

:ERROR
ECHO **** ERROR. EXITING >> %log%

:END
ECHO **** CMD File processing Ends >> %log% 
ECHO **** CMD File processing Ends