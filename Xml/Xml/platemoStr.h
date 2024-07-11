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

	//获取元素节点的属性值
	const char* getNodeAttributes(TiXmlElement* element) const;
	//获取元素节点的标签
	char* getNodeTagNames(TiXmlElement* element) const;
	//将标签转化为platemo函数标准标签
	void transferTags(char * tags);
	//判断节点是否有属性值
	bool isAttributes(TiXmlElement* element);
	//存储节点标签对应的属性
	void saveAttributesAndTags(TiXmlElement* root);
	//输出platemo()函数参数标准字符串platemo('-algorithm',@RVEA,'-problem',@WFG1,'-N',200,'-M',10);
	void getPlatemoStr();

	//外部接口
	const char* constructPlatemo(TiXmlElement* root);

	//验证是否保存成功
	void print();
};

#endif // !PLATEMOSTR

