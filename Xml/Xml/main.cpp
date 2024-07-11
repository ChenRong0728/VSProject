#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "tinyXml.h"
#include "platemoStr.h"
#include "engine.h"

#pragma comment(lib, "libeng.lib")
#pragma comment(lib, "libmx.lib")
#pragma comment(lib, "libmat.lib")

int main() {
	//解析xml文件
	TiXmlDocument doc("D:\\VS2017 Project\\Xml\\test.xml");
	if (!doc.LoadFile()) {
		std::cerr << "Failed to load file: " << doc.ErrorDesc() << std::endl;
		return 1;
	}
	TiXmlElement* root = doc.RootElement();
	if (!root) {
		std::cerr << "No root element." << std::endl;
		return 1;
	}
	//提取字符串
	platemoStr s;
	const char* platStr;
	platStr = s.constructPlatemo(root);
	//验证是否提取成功
	s.print();

	Engine* ep;
	if (!(ep = engOpen(NULL))) {
		fprintf(stderr, "\nCan't start MATLAB engine\n");
		return EXIT_FAILURE;
	}
	printf("Engine is OK!\n");

	// 设置输出缓冲区
	char buffer[256];
	buffer[0] = '\0';
	engOutputBuffer(ep, buffer, 256);

	// 发送命令以创建图形窗口
	//engEvalString(ep, "platemo('algorithm', @NSGAII,'problem', @WFG1,'M',5);");
	engEvalString(ep, platStr);
	//长久显示matlab页面
	engEvalString(ep, "uiwait;");
	// 打印缓冲区中的内容
	printf("%s", buffer);

	engClose(ep);

	return 0;
}