#pragma once

#include <string>
#include <map>
#include <vector>

class SqlSelectQueryBuilder
{
	std::string Table;
	std::vector<std::string> Columns;
	std::map<std::string, std::string> Id_Name;

public:
	SqlSelectQueryBuilder& AddColumn(std::string _name);
	SqlSelectQueryBuilder& AddFrom(std::string _name);
	SqlSelectQueryBuilder& AddWhere(const std::string _Id, const std::string _name);

	SqlSelectQueryBuilder& Add_Where(const std::map<std::string, std::string>& kv) noexcept;
	SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept;

	std::string BuildQuery() const;
};