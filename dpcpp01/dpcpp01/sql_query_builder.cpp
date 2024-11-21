#include "sql_query_builder.h"

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumn(std::string _name)
{
	Columns.push_back(_name);
	return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddFrom(std::string _name)
{
	Table = _name;
	return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(const std::string _Id, const std::string _name)
{
	Id_Name.insert(std::pair<std::string, std::string>(_Id, _name));
	return *this;
}

std::string SqlSelectQueryBuilder::BuildQuery() const
{
	std::string Query;

	if (Columns.empty())
	{
		Query = "SELECT *";
	}
	else
	{
		Query = "SELECT ";
	}
	for (int i = 0; i < Columns.size(); ++i)
	{
		if (i == Columns.size() - 1)
		{
			Query += Columns[i];
		}
		else
		{
			Query += Columns[i] + ", ";
		}
	}

	if (!Table.empty())
	{
		Query += " FROM " + Table;
	}

	if (!Id_Name.empty())
	{
		Query += " WHERE ";
		int count = 0;
		for (auto& [id, name] : Id_Name)
		{
			Query += id + "=" + name;
			if (++count < Id_Name.size())
			{
				Query += " AND ";
			}
		}
	}
	Query += ";";
	return Query;
}