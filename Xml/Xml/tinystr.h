#ifndef TIXML_USE_STL

#ifndef TINYSTR_H
#define TINYSTR_H

#include <cassert>
#include <cstring>

#if defined(_MSC_VER) && (_MSC_VER >= 1200 )
// Microsoft visual studio, version 6 and higher.
#define TIXML_EXPLICIT explicit
#elif defined(__GNUC__) && (__GNUC__ >= 3 )
// GCC version 3 and higher.s
#define TIXML_EXPLICIT explicit
#else
#define TIXML_EXPLICIT
#endif


class TiXmlString 
{
private:
	typedef size_t size_type;
	//存储xml字符串
	struct Rep
	{
		size_type size, capacity;
		char str[1];
	};

	Rep * rep_;
	static Rep nullrep_;
	
	void init(size_type sz, size_type cap);//初始化Rep数据结构
	void init(size_type sz);
	void set_size(size_type sz);
	char* start() const;//返回指向str开头的指针
	char* finish() const;//返回指向str结尾的指针
	void quit();//释放内存
		
public:
	
	static const size_type npos;

	TiXmlString();
	TiXmlString(const TiXmlString & copy);
	TIXML_EXPLICIT TiXmlString(const char * copy);
	TIXML_EXPLICIT TiXmlString(const char * str, size_type len);
	~TiXmlString();

	TiXmlString& operator = (const char * str);
	TiXmlString& operator = (const TiXmlString & copy);
	TiXmlString& operator += (const char * suffix);
	TiXmlString& operator += (char single);
	TiXmlString& operator += (const TiXmlString & suffix);


	char * c_str() const { return rep_->str; }//将TiXmlString类转换为C字符串
	const char * data() const { return rep_->str; }//将TiXmlString类转换为char *
	size_type length() const { return rep_->size; }//返回TiXmlString的长度
	size_type size() const { return rep_->size; }//返回TiXmlString的长度
	size_type capacity() const { return rep_->capacity; }//返回TiXmlString的容量
	bool empty() const { return rep_->size == 0; }//判断TiXmlString是否为空

	const char& at(size_type index) const;
	char& operator [] (size_type index) const;//下标运算符
	size_type find(char lookup) const;
	size_type find(char tofind, size_type offset) const;
	void clear();//清空TiXmlString

	void reserve(size_type cap);//重置capacity
	TiXmlString& assign(const char* str, size_type len);//给TiXmlString赋值
	TiXmlString& append(const char* str, size_type len);//在TiXmlString拼接字符串
	void swap(TiXmlString& other);//交换两个TiXmlString

	friend TiXmlString operator + (const TiXmlString & a, const TiXmlString & b);
	friend TiXmlString operator + (const TiXmlString & a, const char* b);
	friend TiXmlString operator + (const char* a, const TiXmlString & b);
};

inline bool operator == (const TiXmlString & a, const TiXmlString & b);
inline bool operator < (const TiXmlString & a, const TiXmlString & b);


inline bool operator != (const TiXmlString & a, const TiXmlString & b) { return !(a == b); }
inline bool operator >  (const TiXmlString & a, const TiXmlString & b) { return b < a; }
inline bool operator <= (const TiXmlString & a, const TiXmlString & b) { return !(b < a); }
inline bool operator >= (const TiXmlString & a, const TiXmlString & b) { return !(a < b); }

inline bool operator == (const TiXmlString & a, const char* b) { return strcmp(a.c_str(), b) == 0; }
inline bool operator == (const char* a, const TiXmlString & b) { return b == a; }
inline bool operator != (const TiXmlString & a, const char* b) { return !(a == b); }
inline bool operator != (const char* a, const TiXmlString & b) { return !(b == a); }


class XmlOutStream : public TiXmlString
{
public:
	//重定向输入
	XmlOutStream & operator << (const TiXmlString & in)
	{
		*this += in;
		return *this;
	}

	XmlOutStream & operator << (const char * in)
	{
		*this += in;
		return *this;
	}
};
#endif	// TINYSTR_H
#endif	// TIXML_USE_STL
