#pragma once

#include <string>

namespace ostf
{
	/*
		Helps with the io of incoming and outgoing packets/events.
	*/
	class Buffer
	{
		virtual void write_int(std::string m, int v) = 0;

		virtual void read_int(std::string m, int& v) = 0;


		virtual void write_float(std::string m, float v) = 0;
		
		virtual void read_float(std::string m, float& v) = 0;


		virtual void write_bool(std::string m, bool v) = 0;

		virtual void read_bool(std::string m, bool& v) = 0;


		virtual void write_string(std::string m, std::string& v) = 0;

		virtual void read_string(std::string m, std::string& value) = 0;
	};
}