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
	//�洢xml�ַ���
	struct Rep
	{
		size_type size, capacity;
		char str[1];
	};

	Rep * rep_;
	static Rep nullrep_;
	
	void init(size_type sz, size_type cap);//��ʼ��Rep���ݽṹ
	void init(size_type sz);
	void set_size(size_type sz);
	char* start() const;//����ָ��str��ͷ��ָ��
	char* finish() const;//����ָ��str��β��ָ��
	void quit();//�ͷ��ڴ�
		
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


	char * c_str() const { return rep_->str; }//��TiXmlString��ת��ΪC�ַ���
	const char * data() const { return rep_->str; }//��TiXmlString��ת��Ϊchar *
	size_type length() const { return rep_->size; }//����TiXmlString�ĳ���
	size_type size() const { return rep_->size; }//����TiXmlString�ĳ���
	size_type capacity() const { return rep_->capacity; }//����TiXmlString������
	bool empty() const { return rep_->size == 0; }//�ж�TiXmlString�Ƿ�Ϊ��

	const char& at(size_type index) const;
	char& operator [] (size_type index) const;//�±������
	size_type find(char lookup) const;
	size_type find(char tofind, size_type offset) const;
	void clear();//���TiXmlString

	void reserve(size_type cap);//����capacity
	TiXmlString& assign(const char* str, size_type len);//��TiXmlString��ֵ
	TiXmlString& append(const char* str, size_type len);//��TiXmlStringƴ���ַ���
	void swap(TiXmlString& other);//��������TiXmlString

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
	//�ض�������
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
