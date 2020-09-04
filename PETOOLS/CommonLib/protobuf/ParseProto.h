#pragma once
#include"stdafx.h"

class ParseProto
{
public:
	ParseProto();
	virtual ~ParseProto();
private:
	std::vector<std::string> messagelist;
	std::string strProtoFile;
private:
	bool TraversalFieldDescript(const google::protobuf::Message& message, std::map<std::string, std::string>& result);
	void DoTraversalFieldDescript(const google::protobuf::Message& message, const google::protobuf::FieldDescriptor* descriptor, const google::protobuf::Reflection * reflection, std::map<std::string, std::string>& result);
public:
	void Clear(){ messagelist.clear(); };
	bool LoadProtoFromFile(const std::string& data_filename);
	void PrintDataFile(const std::string& message_name, const unsigned char *buffer, const unsigned int size, std::map<std::string, std::string> &);
	std::vector<std::string> &GetMessageList();
	std::string PrintDebugString(const unsigned char *buffer, const unsigned int size);
};

