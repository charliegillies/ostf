#pragma once

#include "Buffer.h"
#include "json.hpp"
#include <map>

namespace ostf
{
	class JsonBuffer : public Buffer
	{
	private:
		// json buffer
		nlohmann::json& _jsonBuffer;
		// internal buffer to match
		std::map<std::string, JsonBuffer*> _buffer;

	public:
		JsonBuffer(nlohmann::json& buffer) : _jsonBuffer(buffer) { }
		
		~JsonBuffer() {
			// delete all our json buffer ptrs
			for (auto pair : _buffer)
				delete pair.second;
		}

		// Inherited via Buffer
		virtual void write_int(std::string m, int v) override;
		virtual void read_int(std::string m, int & v) override;

		virtual void write_float(std::string m, float v) override;
		virtual void read_float(std::string m, float & v) override;
		
		virtual void write_bool(std::string m, bool v) override;
		virtual void read_bool(std::string m, bool & v) override;
		
		virtual void write_string(std::string m, std::string & v) override;
		virtual void read_string(std::string m, std::string & value) override;

		virtual Buffer& create_child(std::string c) override;
		virtual Buffer& read_child(std::string c) override;
	};
}