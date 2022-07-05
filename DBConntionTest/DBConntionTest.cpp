// DBConntionTest.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "SQLConnection.h"
#include "SQLCommand.h"
#include "SQLReader.h"
#include "SQLTranstaction.h"
#include <chrono>
#include <atltime.h>


using namespace NetworkCommon::DBConnection;
using namespace std::chrono;

int main()
{

    std::cout << "Hello World!\n";

	try
	{

		SQLHDBC m_connHanlde;
		SQLHENV m_envHandle;

		if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_envHandle) == SQL_ERROR)
		{
			throw SQLException("Unable to allocate an environment handle");
		}


		SQLRETURN retCode = SQLSetEnvAttr(m_envHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
		retCode = SQLSetEnvAttr(NULL, SQL_ATTR_CONNECTION_POOLING, (SQLPOINTER)SQL_CP_ONE_PER_DRIVER, SQL_IS_INTEGER);


		retCode = SQLAllocHandle(SQL_HANDLE_DBC, m_envHandle, &m_connHanlde);

		SQLConnection sqlConn("DRIVER={ODBC Driver 17 for SQL Server};SERVER=localhost,1433;DATABASE=Imas_GameDB;UID=Sin;PWD=skfnxh59835;", m_connHanlde, m_envHandle);

		SQLConnection sqlConn2("DRIVER={ODBC Driver 17 for SQL Server};SERVER=localhost,1433;DATABASE=Imas_GameDB;UID=Sin;PWD=skfnxh59835;", m_connHanlde, m_envHandle);

		sqlConn.Open();
		sqlConn2.Open();
		
		std::cout << "connect sucess " << std::endl;

		SQLCommand command(&sqlConn, L"Proc_LoadPlayer ?, ?");
		//SQLCommand command(&sqlConn, L"Proc_SingUpPlayer ?, ?, ? ,?, ?, ?");
		//SQLTranstaction sqlTrans(&sqlConn);

		//sqlTrans.BegionTrans();

		std::string id = "sky598351";
		std::string pw = "skfnxh598351";
		std::string nickname = "nick name";
		tm st_now;
		CTime now = CTime::GetCurrentTime();
		now.GetLocalTm(&st_now);
		INT64 playerID = 0;
		INT32 outputResult = 0;

		command.AddParameterWithValue("@pID", SQL_VARCHAR, id);
		command.AddParameterWithValue("@pPassword", SQL_VARCHAR, pw);
		//command.AddParameterWithValue("@pNickName", SQL_VARCHAR, nickname);
		//command.AddParameterWithValue("@pCreateTime", SQL_DATETIME, st_now);
		//command.AddOutputParameter("@pOutPlayerID", SQL_BIGINT);
		//command.AddOutputParameter("@pOutResult", SQL_INTEGER);

		SQLReader reader = command.Execute();
		

		while (reader.Next())
		{
			std::string result_id = reader.GetValue<std::string>("ID");
			std::string result_pw = reader.GetValue<std::string>("PW");
			tm result_createTime = reader.GetValue<tm>("CreateTime");

			std::cout << "id : " << result_id << " / value : " << result_pw.c_str() << std::endl;
		}

		//reader.GetValue("@pOutPlayerID")

		auto result = command.GetParameterOutputValue<int>("@pOutPlayerID");;

		//sqlTrans.Commit();
		//sqlTrans.Rollback();
		sqlConn.Close();

		std::cout << "disconnect sucess" << std::endl;
	}
	catch (SQLException ex)
	{
		std::cout << "fail : " << ex.GetMessageW() << std::endl;
	}
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
