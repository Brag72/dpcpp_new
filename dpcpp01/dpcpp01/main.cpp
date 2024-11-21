#include "sql_query_builder.cpp"
#include <iostream>

int main()
{
    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumn("name").AddColumn("phone");
    query_builder.AddFrom("students");
    query_builder.AddWhere("id", "42").AddWhere("name", "John");
   
    std::cout << query_builder.BuildQuery();       
}