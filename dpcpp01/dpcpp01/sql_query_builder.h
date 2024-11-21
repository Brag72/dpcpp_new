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
	
	std::string BuildQuery() const;
};