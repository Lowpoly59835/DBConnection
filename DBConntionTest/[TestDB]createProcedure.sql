use TestDB;

IF EXISTS (SELECT object_id FROM SYS.OBJECTS WHERE name = N'Proc_LoadRanking' AND type = N'P')
DROP PROCEDURE DBO.Proc_LoadRanking
GO

CREATE PROCEDURE DBO.Proc_LoadRanking
@pID INT
AS
	SET NOCOUNT ON
	SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED

	SELECT * FROM _RefRanking where ID = @pID
GO