#pragma once
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/prettywriter.h"


namespace Thomas {

	class Rapidjson {

	public:
		bool DeserialiseFromFile(const std::string& filePath);
		bool SerialiseToFile(const std::string& filePath);

		virtual std::string Serialise() const;
		virtual bool Deserialise(const std::string& s);
		virtual bool Deserialise(const rapidjson::Value& obj) = 0;
		virtual bool Serialise(rapidjson::Writer<rapidjson::StringBuffer>* writer) const = 0;
	};
	
}

