#ifndef PLATEMOSTR
#define PLATEMOSTR

#include "tinyXml.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <map>
#include <algorithm>
#include <iterator>



class platemoStr
{
	
private:
	std::map<std::string, std::string> str;
	std::string platemostr;
public:
	platemoStr();
	~platemoStr();

	//��ȡԪ�ؽڵ������ֵ
	const char* getNodeAttributes(TiXmlElement* element) const;
	//��ȡԪ�ؽڵ�ı�ǩ
	char* getNodeTagNames(TiXmlElement* element) const;
	//����ǩת��Ϊplatemo������׼��ǩ
	void transferTags(char * tags);
	//�жϽڵ��Ƿ�������ֵ
	bool isAttributes(TiXmlElement* element);
	//�洢�ڵ��ǩ��Ӧ������
	void saveAttributesAndTags(TiXmlElement* root);
	//���platemo()����������׼�ַ���platemo('-algorithm',@RVEA,'-problem',@WFG1,'-N',200,'-M',10);
	void getPlatemoStr();

	//�ⲿ�ӿ�
	const char* constructPlatemo(TiXmlElement* root);

	//��֤�Ƿ񱣴�ɹ�
	void print();
};

#endif // !PLATEMOSTR

