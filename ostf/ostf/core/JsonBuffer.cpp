#include "JsonBuffer.h"

void ostf::JsonBuffer::write_int(std::string m, int v)
{
	_jsonBuffer[m] = v;
}

void ostf::JsonBuffer::read_int(std::string m, int & v)
{
	v = _jsonBuffer[m];
}

void ostf::JsonBuffer::write_float(std::string m, float v)
{
	_jsonBuffer[m] = v;
}

void ostf::JsonBuffer::read_float(std::string m, float & v)
{
	v = _jsonBuffer[m];
}

void ostf::JsonBuffer::write_bool(std::string m, bool v)
{
	_jsonBuffer[m] = v;
}

void ostf::JsonBuffer::read_bool(std::string m, bool & v)
{
	v = _jsonBuffer[m];
}

void ostf::JsonBuffer::write_string(std::string m, std::string & v)
{
	_jsonBuffer[m] = v;
}

void ostf::JsonBuffer::read_string(std::string m, std::string & value)
{
	value = _jsonBuffer[m].get<std::string>();
}

ostf::Buffer & ostf::JsonBuffer::create_child(std::string c)
{
	// first thing to do is to manipulate the json obj to match
	_jsonBuffer[c] = nlohmann::json::object();

	// now we create an internal json buffer to match the one we already have
	// and give that the reference to the json child we just created
	auto b = new JsonBuffer(_jsonBuffer[c]);
	_buffer.insert_or_assign(c, b);

	return read_child(c);
}

ostf::Buffer & ostf::JsonBuffer::read_child(std::string c)
{
	// get buf, ensure that it isn't null
	JsonBuffer* buf = _buffer[c];

	// if buf is null, check if we have a child in the json buffer
	if (buf == nullptr) {
		if (!_jsonBuffer[c].is_null()) {
			// we have a child in the json buffer, create one to match
			buf = new JsonBuffer(_jsonBuffer[c]);
			_buffer[c] = buf;
		}
		else
			throw std::invalid_argument("JsonBuffer::read_child(c) was called, but the child did not exist.");
	}

	return *buf;
}
