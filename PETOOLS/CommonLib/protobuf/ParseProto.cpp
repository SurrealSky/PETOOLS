#include "stdafx.h"
#include "ParseProto.h"
#include<sstream>
#include<CodedConvert.h>
#include"test.pb.h"

ParseProto::ParseProto()
{
}


ParseProto::~ParseProto()
{
}

bool ParseProto::LoadProtoFromFile(const std::string& proto_filename)
{
	strProtoFile = proto_filename;
	int ipos = proto_filename.find_last_of('\\');
	if (ipos == -1)
	{
		ipos = proto_filename.find_last_of('/');
	}
	std::string path = proto_filename.substr(0,ipos);
	std::string file = proto_filename.substr(ipos+1);
	SurrealConvert::CodedConvert mCodedConvert;
	path = mCodedConvert.AsciiToUtf8(path.c_str());
	google::protobuf::compiler::DiskSourceTree sourceTree;
	sourceTree.MapPath("", path);
	google::protobuf::compiler::Importer mImport((google::protobuf::compiler::SourceTree*)(&sourceTree), NULL);
	const google::protobuf::FileDescriptor* pFileDescriptor = mImport.Import(file);
	if (pFileDescriptor == NULL) return false;
	Clear();
	for (int i = 0; i < pFileDescriptor->message_type_count(); i++)
	{
		std::string name = pFileDescriptor->message_type(i)->full_name();
		messagelist.push_back(name);
	}
	return true;
}

std::vector<std::string>& ParseProto::GetMessageList()
{
	return messagelist;
}

void ParseProto::PrintDataFile(const std::string& message_name,const unsigned char *buffer,const unsigned int size, std::map<std::string, std::string> &mapresult)
{
	if (size) {
		std::string strdebug = PrintDebugString(buffer,size);
		mapresult.insert(std::pair<std::string, std::string>(message_name, strdebug));
		int ipos = strProtoFile.find_last_of('\\');
		if (ipos == -1)
		{
			ipos = strProtoFile.find_last_of('/');
		}
		std::string path = strProtoFile.substr(0, ipos);
		std::string file = strProtoFile.substr(ipos + 1);
		SurrealConvert::CodedConvert mCodedConvert;
		path=mCodedConvert.AsciiToUtf8(path.c_str());
		google::protobuf::compiler::DiskSourceTree sourceTree;
		sourceTree.MapPath("", path);
		google::protobuf::compiler::Importer mImport((google::protobuf::compiler::SourceTree*)(&sourceTree), NULL);
		const google::protobuf::FileDescriptor* pFileDescriptor = mImport.Import(file);
		if (pFileDescriptor)
		{
			const google::protobuf::Descriptor *p=mImport.pool()->FindMessageTypeByName(message_name);
			if (p == NULL) return;
			google::protobuf::DynamicMessageFactory factory;
			google::protobuf::Message *msg = factory.GetPrototype(p)->New();
			msg->ParseFromArray(buffer, size);
			msg->DiscardUnknownFields();
			TraversalFieldDescript(*msg, mapresult);
			delete msg;

		}
	}
}

bool ParseProto::TraversalFieldDescript(const google::protobuf::Message& message, std::map<std::string,std::string>& result)
{
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::Reflection* reflection = message.GetReflection();
	if (NULL == descriptor) {
		return false;
	}
	//遍历所有的字段，包括空字段
	//for (int i = 0; i < descriptor->field_count(); i++)
	//{
	//	DoTraversalFieldDescript(message, descriptor->field(i), reflection,result);
	//}
	//只遍历非空字段
	std::vector<const google::protobuf::FieldDescriptor*> fields;
	reflection->ListFields(message, &fields);
	for (int i = 0; i < fields.size(); i++)
	{
		DoTraversalFieldDescript(message,fields[i], reflection, result);
	}
	return true;
}

void ParseProto::DoTraversalFieldDescript(const google::protobuf::Message& message,const google::protobuf::FieldDescriptor* field, const google::protobuf::Reflection * reflection, std::map<std::string, std::string>& result)
{
	if (field == NULL) return;
	if (field->label() == google::protobuf::FieldDescriptor::LABEL_REPEATED)
	{
		//repeated message
		int count = reflection->FieldSize(message, field);
		std::string repeatedstr = "";
		for (int i = 0; i < count; i++)
		{
			//const google::protobuf::Message &m = reflection->GetRepeatedMessage(message, field, i);
			//const google::protobuf::Reflection * ref = m.GetReflection();
			//const google::protobuf::FieldDescriptor *f = (const google::protobuf::FieldDescriptor *)(m.GetDescriptor());
			//DoTraversalFieldDescript(m, field->message_type()->field(i), ref, result);
			//result.insert(std::pair<std::string, std::string>("repeated message", "not support"));
			const google::protobuf::Message &msg = reflection->GetRepeatedMessage(message, field, i);
			repeatedstr.append(msg.DebugString());
		}
		result.insert(std::pair<std::string, std::string>(field->full_name(), repeatedstr));
		return;
	}
	switch (field->type())
	{
		case google::protobuf::FieldDescriptor::TYPE_FIXED64:
		case google::protobuf::FieldDescriptor::TYPE_INT64:
		{
			long long l = reflection->GetInt64(message, field);
			std::ostringstream stream;
			stream << l;
			result.insert(std::pair<std::string, std::string>(field->full_name(), stream.str()));
			break;
		}

		case google::protobuf::FieldDescriptor::TYPE_UINT64:
		{
			unsigned long long l1 = reflection->GetUInt64(message, field);
			std::ostringstream stream;
			stream << l1;
			result.insert(std::pair<std::string, std::string>(field->full_name(), stream.str()));
			break;
		}


		case google::protobuf::FieldDescriptor::TYPE_FIXED32:
		{
			int i = reflection->GetUInt32(message, field);
			std::ostringstream stream;
			stream << i;
			result.insert(std::pair<std::string, std::string>(field->full_name(), stream.str()));
			break;
		}
		case google::protobuf::FieldDescriptor::TYPE_INT32:
		{
			int i = reflection->GetInt32(message, field);
			std::ostringstream stream;
			stream << i;
			result.insert(std::pair<std::string, std::string>(field->full_name(), stream.str()));
			break;
		}
		case google::protobuf::FieldDescriptor::TYPE_UINT32:
		{
			unsigned int i1 = reflection->GetUInt32(message, field);
			std::ostringstream stream;
			stream << i1;
			result.insert(std::pair<std::string, std::string>(field->full_name(), stream.str()));
			break;
		}

		case google::protobuf::FieldDescriptor::TYPE_STRING:
		{
			std::string s = reflection->GetString(message, field);
			result.insert(std::pair<std::string, std::string>(field->full_name(), s));
			break;
		}

		case google::protobuf::FieldDescriptor::TYPE_DOUBLE:
		{
			double d = reflection->GetDouble(message, field);
			std::ostringstream stream;
			stream << d;
			result.insert(std::pair<std::string, std::string>(field->full_name(), stream.str()));
			break;
		}
		case google::protobuf::FieldDescriptor::TYPE_FLOAT:
		{
			float f = reflection->GetFloat(message, field);
			std::ostringstream stream;
			stream << f;
			result.insert(std::pair<std::string, std::string>(field->full_name(), stream.str()));
			break;
		}
		case google::protobuf::FieldDescriptor::TYPE_BOOL:
		{
			bool b = reflection->GetBool(message, field);
			std::ostringstream stream;
			stream << b;
			result.insert(std::pair<std::string, std::string>(field->full_name(), stream.str()));
			break;
		}
		case google::protobuf::FieldDescriptor::TYPE_MESSAGE:
		{
			//嵌套
			const google::protobuf::Message& current_msg = reflection->GetMessage(message, field);
			//std::string sd= current_msg.SerializeAsString();
			const google::protobuf::Descriptor* descriptor_temp = current_msg.GetDescriptor();
			const google::protobuf::Reflection* reflection_temp = current_msg.GetReflection();
			if (NULL == descriptor_temp)
			{
				break;
			}
			//遍历所有字段，包含空字段
			//for (int i = 0; i < descriptor_temp->field_count(); i++)
			//{
			//	DoTraversalFieldDescript(current_msg, descriptor_temp->field(i), reflection_temp, result);
			//}
			//只遍历非空字段
			std::vector<const google::protobuf::FieldDescriptor*> fields;
			reflection_temp->ListFields(current_msg, &fields);
			for (int i = 0; i < fields.size(); i++)
			{
				DoTraversalFieldDescript(current_msg, fields[i], reflection_temp, result);
			}
		}break;
		case google::protobuf::FieldDescriptor::TYPE_GROUP:
		{
			result.insert(std::pair<std::string, std::string>(field->full_name(), "not support type"));
		}break;
		case google::protobuf::FieldDescriptor::TYPE_BYTES:
		{
			std::string s = reflection->GetString(message, field);
			result.insert(std::pair<std::string, std::string>(field->full_name(), s));
		}break;
		case google::protobuf::FieldDescriptor::TYPE_ENUM:
		{
			result.insert(std::pair<std::string, std::string>(field->full_name(), "not support type"));
		}break;
		default:
		{
			result.insert(std::pair<std::string, std::string>(field->full_name(), "not support type"));
		}
	}
}

std::string ParseProto::PrintDebugString(const unsigned char *buffer, const unsigned int size)
{
	std::string ret;
	//google::protobuf::OneofDescriptorProto proto;
	//proto.ParseFromArray(buffer, size);
	//ret = proto.DebugString();
	//google::protobuf::DescriptorProto proto;
	//proto.ParseFromArray(buffer, size);
	//ret=proto.Utf8DebugString();
	//ret = proto.DebugString();
	test::test testmsg;
	testmsg.ParseFromArray(buffer, size);
	ret = testmsg.Utf8DebugString();
	return ret;
}