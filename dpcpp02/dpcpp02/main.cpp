#include "sql_query_builder.h"
#include <iostream>

int main()
{
    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumn("name").AddColumn("phone");
    query_builder.AddFrom("students");
    query_builder.AddWhere("id", "42").AddWhere("name", "John");

    query_builder.Add_Where(std::map<std::string, std::string>{{ "id", "42" }, { "name", "John" }});
    query_builder.AddColumns({ "name" , "phone" });

    std::cout << query_builder.BuildQuery();
}