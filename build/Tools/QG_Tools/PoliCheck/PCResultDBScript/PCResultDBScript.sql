GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
BEGIN
CREATE TABLE [dbo].[TaskInfo](
	[Task_Id] [bigint] IDENTITY(1,1) NOT NULL,
	[Task_Name] [nvarchar](500) NULL,
	[Task_LocalName] [nvarchar](500) NULL,
	[Root_Directory] [nvarchar](255) NULL,
	[Current_Version] [nvarchar](200) NULL,
 CONSTRAINT [PK_TaskInfo] PRIMARY KEY NONCLUSTERED 
(
	[Task_Id] ASC
) ON [PRIMARY]
) ON [PRIMARY]
END

/****** Object:  Table [dbo].[ScanLog]    Script Date: 12/11/2007 19:09:35 ******/
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
BEGIN
CREATE TABLE [dbo].[ScanLog](
	[Task_Id] [bigint] NOT NULL,
	[Target] [nvarchar](255) NULL,
	[Status] [nvarchar](100) NULL,
	[Issue_Count] [int] NULL
) ON [PRIMARY]
END
GO
ALTER TABLE [dbo].[ScanLog]  WITH CHECK ADD  CONSTRAINT [FK_ScanLog_TaskInfo] FOREIGN KEY([Task_Id])
REFERENCES [dbo].[TaskInfo] ([Task_Id])
GO
ALTER TABLE [dbo].[ScanLog] CHECK CONSTRAINT [FK_ScanLog_TaskInfo]
/****** Object:  Table [dbo].[PoliCheck_Results]    Script Date: 12/12/2007 10:58:46 ******/

GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[PoliCheck_Results](
	[Task_Id] [bigint] NOT NULL,
	[Target_File] [nvarchar](255) NULL,
	[Location] [nvarchar](100) NULL,
	[Term] [nvarchar](200) NULL,
	[TermTable] [nvarchar](200) NULL,
	[ContextInfo] [nvarchar](400) NULL,
	[Severity] [int] NULL,
	[TermClass] [nvarchar](250) NULL,
	[Replacement_Guideline] [nvarchar](1000) NULL,
	[Term_Translation] [nvarchar](1000) NULL,
	[Recommended_Term] [nvarchar](500) NOT NULL,
	[Issue_Type] [nvarchar](250) NULL,
	[Bug_No] [int] NULL,
	[Investigator] [nvarchar](250) NULL,
	[Version] [nvarchar](200) NULL,
	[Team_Name] [nvarchar](100) NULL,
	[Owner] [nvarchar](250) NULL,
	[IsSourceComment] [bit] NULL
) ON [PRIMARY]

GO
ALTER TABLE [dbo].[PoliCheck_Results]  WITH CHECK ADD  CONSTRAINT [FK_PoliCheck_Results_TaskInfo] FOREIGN KEY([Task_Id])
REFERENCES [dbo].[TaskInfo] ([Task_Id])
GO
ALTER TABLE [dbo].[PoliCheck_Results] CHECK CONSTRAINT [FK_PoliCheck_Results_TaskInfo]

-- =============================================
-- Author:		<v-swetas>
-- Create date: <13-12-2007>
-- Description:	<Creating Stored Proc to Insert task Info into the TaskInfo Table>
-- =============================================
set ANSI_NULLS ON
set QUOTED_IDENTIFIER ON
go

CREATE PROCEDURE [dbo].[insertTaskDet]
		(@Task_Name nvarchar(500)
           ,@Task_LocalName nvarchar(500)
           ,@Root_Directory nvarchar(255)
           ,@Current_Version nvarchar(200))
AS
BEGIN
	
Declare @Task_ID bigint

SELECT @Task_Id = dbo.FnGetTaskId(@Task_Name,@Task_LocalName)
	IF(@Task_Id = 0)
	BEGIN
		INSERT INTO [dbo].[TaskInfo]
				   ([Task_Name]
				   ,[Task_LocalName]
				   ,[Root_Directory]
				   ,[Current_Version])
			 VALUES
				 (@Task_Name 
				   ,@Task_LocalName 
				   ,@Root_Directory 
				   ,@Current_Version )
	END
		else 
Update [dbo].[TaskInfo] 
	set [Root_Directory]=@Root_Directory ,
		[Current_Version]=@Current_Version where [Task_Id]=@Task_Id

end

-- ================================================
--Creating Stored Proc to Insert Task details into the task_Info table
-- ================================================

-- =============================================
-- Author:		<v-swetas>
-- Create date: <13-12-2007>
-- Description:	<Creating Stored Proc to Insert Records into the PoliCheck_Results table>
-- =============================================
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
Create FUNCTION [dbo].[FnGetTaskId] 
(
	-- Add the parameters for the function here
	 @Task_Name NVARCHAR(250),
	 @Task_LocalName NVARCHAR(250)
)
RETURNS bigint
AS
BEGIN
	-- Declare the return variable here
DECLARE @Task_Id bigint
IF NOT EXISTS (SELECT [Task_Id] FROM dbo.TaskInfo WHERE  Task_LocalName = @Task_LocalName and Task_Name =@Task_Name)
	SET @Task_Id = 0
ELSE
	SELECT @Task_Id = [Task_Id] FROM dbo.TaskInfo WHERE  Task_LocalName = @Task_LocalName and Task_Name =@Task_Name
	RETURN @Task_Id
END

go
set ANSI_NULLS ON
set QUOTED_IDENTIFIER ON
go


Create PROCEDURE [dbo].[insertResults]
	-- Add the parameters for the stored procedure here
           (@Task_Name nvarchar(500)
           ,@Task_LocalName nvarchar(500)
           ,@Target_File nvarchar(255)
           ,@Location nvarchar(100)
           ,@Term nvarchar(200)
           ,@TermTable nvarchar(200)
           ,@ContextInfo nvarchar(400)
           ,@Severity int
           ,@TermClass nvarchar(250)
           ,@Replacement_Guideline nvarchar(1000)
           ,@Term_Translation nvarchar(1000)
           ,@Recommended_Term nvarchar(500)
           ,@Issue_Type nvarchar(250)
           ,@Bug_No bigint
           ,@Investigator nvarchar(250)
           ,@Version bigint
           ,@Team_Name nvarchar(100)
           ,@Owner nvarchar(250)
           ,@IsSourceComment bit)


as 
BEGIN
Declare @Task_Id bigint

-- Get Task ID 
SELECT @Task_Id = dbo.FnGetTaskId(@Task_Name,@Task_LocalName)

	IF (@Task_Id != 0)
--insert records
	BEGIN
		INSERT INTO [dbo].[PoliCheck_Results]
           ([Task_Id]
           ,[Target_File]
           ,[Location]
           ,[Term]
           ,[TermTable]
           ,[ContextInfo]
           ,[Severity]
           ,[TermClass]
           ,[Replacement_Guideline]
           ,[Term_Translation]
           ,[Recommended_Term]
           ,[Issue_Type]
           ,[Bug_No]
           ,[Investigator]
           ,[Version]
           ,[Team_Name]
           ,[Owner]
           ,[IsSourceComment])
		VALUES
           (@Task_Id
           ,@Target_File
           ,@Location
           ,@Term
           ,@TermTable
           ,@ContextInfo
           ,@Severity
           ,@TermClass
           ,@Replacement_Guideline
           ,@Term_Translation
           ,@Recommended_Term
           ,@Issue_Type
           ,@Bug_No
           ,@Investigator
           ,@Version
           ,@Team_Name
           ,@Owner
           ,@IsSourceComment)
	end 
END

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<v-swetas>
-- Create date: <14/12/2007>
-- Description:	<Delete Results>
-- =============================================
CREATE PROCEDURE [dbo].[deleteResults] 
	@Task_Name nvarchar(500),
	@Task_LocalName nvarchar(500)
AS
BEGIN

	DECLARE @Task_Id bigint

-- Get Task ID 
		SELECT @Task_Id = dbo.FnGetTaskId(@Task_Name,@Task_LocalName)

		IF (@Task_Id != 0)
			BEGIN 

		--Delete dbo.ScanLog
				DELETE FROM dbo.ScanLog 
					WHERE Task_Id = @Task_Id

		--Delete dbo.PoliCheck_Results
				DELETE FROM dbo.PoliCheck_Results
					WHERE Task_Id = @Task_Id
		--Delete dbo.TaskInfo
				--DELETE FROM dbo.TaskInfo
				--	WHERE Task_Id = @Task_Id
		END 

END

set ANSI_NULLS ON
set QUOTED_IDENTIFIER ON
go

CREATE Procedure [dbo].[insertScanLog] 
		@TaskdetailXMLdoc  nText,
		@Task_Name nvarchar(500),
		@Task_LocalName nvarchar(500)
as 
begin 

DECLARE @iTaskDetailXMLdoc int,
		@Task_Id bigint

EXEC sp_xml_preparedocument @iTaskDetailXMLdoc   OUTPUT, @TaskdetailXMLdoc

SELECT @Task_Id = dbo.FnGetTaskId(@Task_Name,@Task_LocalName)

	IF(@Task_Id != 0)
	
	BEGIN

SELECT	@Task_Id "Task_Id", Target "Target", Status "Status", [Issue Count] as "Issue_Count" into #temp	FROM    
				OPENXML (@iTaskDetailXMLdoc, N'/ScanLogInformation/ScanLog',1)
				with
					(
						Target varchar(255),
						Status varchar(255),
						[Issue Count] nvarchar(200) )


Update  #temp 
set Issue_Count = null
where rtrim(ltrim(Issue_Count)) ='N/A'

insert into ScanLog select Task_Id,Target,Status,Issue_Count from #temp

DROP table #temp

	END
END
