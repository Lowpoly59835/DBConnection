// Reflection.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <type_traits>
#include <map>
#include <cassert>
#include <list>

using namespace std;

/*
enum EType
{
	None = 0,
	Integer,
	Floating,
	String,
	Class
};

struct st_metadata
{
	template<typename T>
	static auto GetType()
	{
		st_metadata metaData;

		if (std::disjunction<
			std::is_same<char*, typename std::decay_t<T>>,
			std::is_same<const char*, typename std::decay_t<T>>,
			std::is_same<std::string, typename std::decay_t<T>>>::value)
		{
			metaData.type = EType::String;
		}
		else if (std::disjunction <
			std::is_same<int, typename std::decay_t<T>>,
			std::is_same<int64_t, typename std::decay_t<T>>>::value)
		{
			metaData.type = EType::Integer;
		}
		else if (std::disjunction <
			std::is_same<float, typename std::decay_t<T>>,
			std::is_same<double, typename std::decay_t<T>>>::value)
		{
			metaData.type = EType::Floating;
		}
		else if (std::is_class<T>::value)
		{
			metaData.type = EType::Class;
		}
		else
		{
			return metaData;
		}
	}

public:
	template<typename T>
	void Init(T& value)
	{
		type = GetType();
	}

private:
	EType type;
	string name;
}typedef MetaData, CMetaData;


template<typename T>
class CRuntimeObject
{
public:
	CRuntimeObject() 
	{
		m_metaData.Init(this);
	}

private:
	static map<string, CMetaData> m_managetData;
	CMetaData m_metaData;
};

class Test : public CRuntimeObject<Test>
{
public:

};

template<typename T>
EType GetType(T& value)
{
	//std::cout << st_type<T>::type << std::endl;
	st_metadata<T> _type;
	return _type.type;
}
*/

//template<typename T, typename std::enable_if<std::is_class<T>::value::type* = nullptr>
//void GetResult(T* value)
//{
//	static_assert("invalid type");
//}

template<typename T>
struct check_type
	: std::false_type
{
};


template<>
struct check_type<int>
	: std::true_type
{ // determine whether T is type that we want
};

template<>
struct check_type<float>
	: std::true_type
{ // determine whether T is type that we want
};


template<>
struct check_type<std::string>
	: std::true_type
{ // determine whether T is type that we want
};



#define PROPERT_GET(_get) _declspec(property(get = _get))
#define PROPERT_SET(_set) _declspec(property(set = _set))
#define PROPERTY(_get, _set) _declspec(property(get = _get, put = _set))

#define PROPERT_MAKE_GET(value, type, name) type Get##name() { return value; }
#define PROPERT_MAKE_SET(value, type, name) void Set##name(type _value) { value = _value; }
#define PROPERT_MAKE(value, type, name) PROPERT_MAKE_GET(value, type, name) PROPERT_MAKE_SET(value, type, name)


#define PROPERT_GETEX(value, type, name) PROPERT_MAKE_GET(value, type, name) PROPERT_GET(Get##name) type name;
#define PROPERT_SETEX(value, type, name) PROPERT_MAKE_SET(value, type, name) PROPERT_GET(Get##name) type name;

template<typename T>
class DBRecord
{
public:
	DBRecord()
	{
		static_assert(check_type<T>::value, "DB Record type error!!");
	}

private:
	T _value;
	PROPERT_GETEX(_value, T, value)
};

struct test
{
	int num;
};

class DBTable
{
private:
	DBRecord<int> m_value;
};

class tempClass
{
public:
	tempClass(int _num)
		:num(_num)
	{
		cout << "hello world" << endl;
	}

	~tempClass()
	{
		cout << "end!!" << endl;
	}

	tempClass(tempClass*) = delete;

	tempClass(tempClass&&) = delete;
	tempClass(tempClass&) = delete;
	tempClass(const tempClass&) = delete;
	tempClass(const tempClass&&) = delete;

	tempClass operator=(tempClass& other) = delete;
	tempClass operator=(tempClass&& other) = delete;

	tempClass operator=(const tempClass& other) = delete;
	tempClass operator=(const tempClass&& other) = delete;

	int num;
};

tempClass&& TestFunc()
{
	return tempClass(100);
}

int main() 
{
	tempClass&& test = TestFunc();

	cout << test.num << endl;

	return 0;
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
