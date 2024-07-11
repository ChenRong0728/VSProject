#include "platemoStr.h"

platemoStr::platemoStr():platemostr("")
{
	
}

platemoStr::~platemoStr()
{
}

const char* platemoStr::getNodeAttributes(TiXmlElement * element) const
{
	if (!element) {
		return 0;
	}
	// 遍历元素的所有属性
	for (TiXmlAttribute* attr = element->FirstAttribute(); attr; attr = attr->Next())
		return attr->Value();

}

char * platemoStr::getNodeTagNames(TiXmlElement * element) const
{
	if (!element) {
		return NULL;
	}
	// 获取并打印当前节点的标签名称
	return element->Value();
}

void platemoStr::transferTags(char* tags)
{
	if (strcmp(tags, "Algorithm") == 0)
		strcpy_s(tags, strlen("algorithm") + 1, "algorithm");
	else if (strcmp(tags, "RunNumber") == 0)
		strcpy_s(tags, strlen("run") + 1, "run");
	else if (strcmp(tags, "NumberOfSavePopulation") == 0)
		strcpy_s(tags, strlen("save") + 1, "save");
	else if (strcmp(tags, "Problem") == 0)
		strcpy_s(tags, strlen("problem") + 1, "problem");
	else if (strcmp(tags, "PopulationSize") == 0)
		strcpy_s(tags, strlen("N") + 1, "N");
	else if (strcmp(tags, "NumberOfObjectives") == 0)
		strcpy_s(tags, strlen("M") + 1, "M");
	else if (strcmp(tags, "NumberOfVariables") == 0)
		strcpy_s(tags, strlen("D") + 1, "D");
	else if (strcmp(tags, "MaxNumberOfEvaluations") == 0)
		strcpy_s(tags, strlen("maxFE") + 1, "maxFE");
	else if (strcmp(tags, "MaxRuntime") == 0)
		strcpy_s(tags, strlen("maxRuntime") + 1, "maxRuntime");
}

bool platemoStr::isAttributes(TiXmlElement * element)
{
	TiXmlAttribute* attr = element->FirstAttribute();
	if (attr)
		return true;
	else
		return false;
}

void platemoStr::saveAttributesAndTags(TiXmlElement * root)
{
	if (root)
	{
		if (isAttributes(root))
		{
			char* tags = getNodeTagNames(root);
			transferTags(tags);
			const char* value = getNodeAttributes(root);
			str.insert(std::make_pair(tags, value));
		}
		for (TiXmlElement* child = root->FirstChildElement(); child; child = child->NextSiblingElement())
			saveAttributesAndTags(child);  // 递归遍历子元素
	}
}

void platemoStr::getPlatemoStr()
{
	platemostr += "'algorithm',@";
	platemostr += str["algorithm"];
	platemostr += ",";

	platemostr += "'problem',@";
	platemostr += str["problem"];

	for (auto iter = str.begin(); iter != str.end(); ++iter)
	{
		if (!(iter->first == "algorithm" || iter->first == "problem"))
		{
			platemostr += ",";
			platemostr += "'";
			platemostr += iter->first;
			platemostr += "',";
			platemostr += iter->second;
		}
	}
}

const char* platemoStr::constructPlatemo(TiXmlElement * root)
{
	saveAttributesAndTags(root);
	getPlatemoStr();
	platemostr = "platemo(" + platemostr;
	platemostr = platemostr + ")";
	return platemostr.c_str();
}

void platemoStr::print()
{
	for (auto p = str.begin(); p != str.end(); ++p)
		std::cout << p->first << " " << p->second << std::endl;

	std::cout << std::endl;
	std::cout << platemostr << std::endl;
}
