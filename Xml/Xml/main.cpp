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
	//����xml�ļ�
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
	//��ȡ�ַ���
	platemoStr s;
	const char* platStr;
	platStr = s.constructPlatemo(root);
	//��֤�Ƿ���ȡ�ɹ�
	s.print();

	Engine* ep;
	if (!(ep = engOpen(NULL))) {
		fprintf(stderr, "\nCan't start MATLAB engine\n");
		return EXIT_FAILURE;
	}
	printf("Engine is OK!\n");

	// �������������
	char buffer[256];
	buffer[0] = '\0';
	engOutputBuffer(ep, buffer, 256);

	// ���������Դ���ͼ�δ���
	//engEvalString(ep, "platemo('algorithm', @NSGAII,'problem', @WFG1,'M',5);");
	engEvalString(ep, platStr);
	//������ʾmatlabҳ��
	engEvalString(ep, "uiwait;");
	// ��ӡ�������е�����
	printf("%s", buffer);

	engClose(ep);

	return 0;
}