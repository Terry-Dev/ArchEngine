#include <fstream>
#include <vector>
#include "arch/csv_file.h"

class csv_reader::impl
{
public:
	void parse(const char* _data, size_t _size);
	void add_rows();

	std::vector<std::vector<std::string>> table;
};

void csv_reader::impl::parse(const char* _data, size_t _size)
{
	table.push_back(std::vector<std::string>());

	size_t pos = 0;
	std::string value;
	while (pos < _size)
	{
		if (_data[pos] == '\n')
		{
			table.back().push_back(std::move(value));
			add_rows();
		}
		else if (_data[pos] == ',')
		{
			table.back().push_back(std::move(value));
		}
		else
		{
			value += _data[pos];
		}
		pos++;
	}
}

void csv_reader::impl::add_rows()
{
	table.push_back(std::vector<std::string>());
}


csv_reader::csv_reader()
: pimpl(std::make_shared<impl>())
{
}

csv_reader::csv_reader(const std::string& _path)
: csv_reader()
{
	std::ifstream stream = std::ifstream(_path);
	if (!stream)
	{
		return;
	}

	auto pos = stream.seekg(0, std::ios::end).tellg();
	stream.seekg(0, std::ios::beg);
	size_t file_size = static_cast<size_t>(pos);

	std::string data;
	data.resize(file_size);
	stream.read(&data[0], data.size());
	pimpl->parse(data.data(), data.size());
}

csv_reader::csv_reader(const void* _data, size_t _size)
: csv_reader()
{
	if (_data == nullptr || _size == 0)
	{
		return;
	}

	pimpl->parse(reinterpret_cast<const char*>(_data), _size);
}

csv_reader::~csv_reader()
{
}

uint32_t csv_reader::rows() const
{
	return pimpl->table.size();
}

uint32_t csv_reader::columns(uint32_t _rows) const
{
	return pimpl->table[_rows].size();
}

std::string csv_reader::get(uint32_t _rows, uint32_t _columns) const
{
	return pimpl->table[_rows][_columns];
}