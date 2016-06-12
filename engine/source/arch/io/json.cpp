//=================================================================================//
//                                                                                 //
//  ArchEngine                                                                     //
//                                                                                 //
//  Copyright (C) 2011-2016 Terry                                                  //
//                                                                                 //
//  This file is a portion of the ArchEngine. It is distributed under the MIT      //
//  License, available in the root of this distribution and at the following URL.  //
//  http://opensource.org/licenses/mit-license.php                                 //
//                                                                                 //
//=================================================================================//

#include <arch/utility.h>
#include <arch/string.h>
#include <arch/io/json.h>
#include <arch/io/text.h>

using namespace arch;
using namespace arch::json;

class value::impl
{
private:
	struct parse_object
	{
	public:
		char read()
		{
			char c = '\0';
			if (size > position)
			{
				c = data[position];
				position++;
			}
			return c;
		}

		void seek(char key)
		{
			while (size > position)
			{
				if (data[position] == key)
				{
					position++;
					break;
				}
				position++;
			}
		}

		bool eof() const
		{
			return size <= position;
		}

	public:
		const char* data;
		size_t size;
		size_t position;
	};

public:
	void clear()
	{
		m_value.clear();
		m_objects.clear();
		m_array.clear();
	}

	void read(const std::string& filepath)
	{
		text::reader reader(filepath);
		if (!reader)
		{
			return;
		}

		std::string string;
		reader.read_contents(string);
		if (string.empty())
		{
			return;
		}

		deserialize(string);
	}

	bool write(const std::string& filepath)
	{
		std::string data = serialize();

		text::writer writer(filepath);
		if (!writer)
		{
			return false;
		}

		writer.write(data);

		return true;
	}


	std::string serialize()
	{
		std::string _data;
		write_objects(_data, m_objects);
		return std::move(_data);
	}

	void deserialize(const std::string& _string)
	{
		clear();

		parse_object _data;
		_data.data = &_string[0];
		_data.size = _string.size();
		_data.position = 0;

		_data.seek('{');
		read_objects(_data, m_objects);
	}

private:
	char read_value(parse_object& _data, value& _value)
	{
		char c;
		bool loop = true;
		while (loop)
		{
			c = _data.read();
			switch (c)
			{
			case ' ':
				break;

			case '"':
				_value.pimpl->m_value = read_string(_data);
				break;

			case '{':
				read_objects(_data, _value.pimpl->m_objects);
				break;

			case '[':
				read_array(_data, _value.pimpl->m_array);
				break;

			case '}':
			case ']':
			case ',':
			case '\0':
				loop = false;
				break;

			default:
				_value.pimpl->m_value += c;
				break;
			}
		}
		return c;
	}

	std::string read_string(parse_object& _data)
	{
		std::string str;
		while (1)
		{
			char c = _data.read();
			if (c == '"' || c == '\0')
			{
				break;
			}
			else if (c == '\\')
			{
				c = _data.read();
				switch (c)
				{
				case 'b':	c = '\b';	break;
				case 'f':	c = '\f';	break;
				case 'n':	c = '\n';	break;
				case 'r':	c = '\r';	break;
				case 't':	c = '\t';	break;
				default:
					return std::move(str);
				}
			}
			str += c;
		}
		return std::move(str);
	}

	void read_array(parse_object& _data, array& _array)
	{
		char c = '\0';
		while (c != ']')
		{
			value v;
			c = read_value(_data, v);
			if (c == '\0')
			{
				return;
			}
			_array.push_back(std::move(v));
		}
	}

	void read_objects(parse_object& _data, std::map<std::string, value>& _object)
	{
		char c = '\0';
		while (c != '}')
		{
			_data.seek('"');
			std::string name = read_string(_data);
			_data.seek(':');

			value v;
			c = read_value(_data, v);

			_object.insert(std::make_pair(name, v));
		}
	}
	
	void write_value(std::string& _data, value& _value)
	{
		if (!_value.pimpl->m_value.empty())
		{
			write_string(_data, _value.pimpl->m_value);
			return;
		}

		if (!_value.pimpl->m_array.empty())
		{
			write_array(_data, _value.pimpl->m_array);
			return;
		}

		if (!_value.pimpl->m_objects.empty())
		{
			write_objects(_data, _value.pimpl->m_objects);
			return;
		}
	}

	void write_string(std::string& _data, const std::string& _value)
	{
		_data += '"';
		for (auto& c : _value)
		{
			switch (c)
			{
			case '\b':	_data += "\\b"; break;
			case '\f':	_data += "\\f"; break;
			case '\n':	_data += "\\n"; break;
			case '\r':	_data += "\\r";	break;
			case '\t':	_data += "\\t"; break;
			default:	_data += c;		break;
			}
		}
		_data += '"';
	}

	void write_array(std::string& _data, array& _array)
	{
		_data += '[';
		for (auto itr = _array.begin(); itr != _array.end(); itr++)
		{
			if (itr != _array.begin())
			{
				_data += ',';
			}
			write_value(_data, *itr);
		}
		_data += ']';
	}

	void write_objects(std::string& _data, std::map<std::string, value>& _objects)
	{
		_data += '{';
		for (auto itr = _objects.begin(); itr != _objects.end(); itr++)
		{
			if (itr != _objects.begin())
			{
				_data += ',';
			}


			write_string(_data, itr->first);
			_data += ':';
			write_value(_data, itr->second);
		}
		_data += '}';
	}

public:
	std::string m_value;
	array m_array;
	std::map<std::string, value>	m_objects;
};


value::value()
: pimpl(std::make_shared<impl>())
{
}

value::value(const value& _value)
: pimpl(_value.pimpl)
{
}

value::~value()
{
}

bool value::read(const std::string& _filepath)
{
	pimpl->read(_filepath);
	return true;
}

bool value::write(const std::string& _filepath) const
{
	pimpl->write(_filepath);
	return true;
}

void value::set(const std::string& _value)
{
	pimpl->m_array.clear();
	pimpl->m_objects.clear();
	pimpl->m_value = _value;
}

template<> void value::set<array>(const array& _value)
{
	pimpl->m_value.clear();
	pimpl->m_objects.clear();
	pimpl->m_array = _value;
}

template<> void	value::set<bool>(const bool& _value)
{
	set<std::string>(_value ? "true" : "false");
}

std::string value::get() const
{
	return pimpl->m_value;
}

template<> array value::get<array>() const
{
	return pimpl->m_array;
}

template<> bool value::get<bool>() const
{
	return pimpl->m_value == "true";
}

bool value::is_array() const
{
	return !pimpl->m_array.empty();
}

bool value::empty() const
{
	return pimpl->m_value.empty() && pimpl->m_array.empty() && pimpl->m_objects.empty();
}

value& value::operator[](const std::string& _key)
{
	auto itr = pimpl->m_objects.find(_key);
	if(itr != pimpl->m_objects.end())
	{
		return itr->second;
	}

	value v;
	return pimpl->m_objects.insert(std::make_pair(_key, v)).first->second;
}
