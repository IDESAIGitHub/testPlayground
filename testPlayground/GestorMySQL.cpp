#include "GestorMySQL.h"

GestorMySQL::GestorMySQL()
{
	//para pruebas
	this->user = "root";
	this->password = "root";
	this->server = "localhost";
	this->database = "guillen";
	this->port = "3306";
	//quita el conect despues de las pruebas
	connect();
}

GestorMySQL::GestorMySQL(std::string INI_file)
{
	//incluir el gestor ini
}

GestorMySQL::~GestorMySQL()
{
	disconnect();
}

bool GestorMySQL::connect()
{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, server.c_str(), user.c_str(), password.c_str(), database.c_str(), std::stoi(port), NULL, 0);
	if (conn) {
		return true;
	}
	return false;
}

bool GestorMySQL::disconnect()
{
	try
	{
		mysql_close(conn);
		return true;
	}
	catch (const std::exception&)
	{
		//log disconnect err
	}
	return true;
}

bool GestorMySQL::isConnected()
{
	return true;
}

bool GestorMySQL::ExecuteNonQuery(std::string query)
{
	//Para evitar que se ejecuten dos consultas a la vez
	std::lock_guard<std::mutex> lock(mutex_);
	
	int qstate = 0;
	qstate = mysql_query(conn, query.c_str());
	if (!qstate) {
		return true;
	}
	return false;
}

bool GestorMySQL::ExecuteSELECTQuery(std::string query, MYSQL_RES*& res)
{
	//Para evitar que se ejecuten dos consultas a la vez
	std::lock_guard<std::mutex> lock(mutex_);

	int qstate = 0;
	qstate = mysql_query(conn, query.c_str());
	if (!qstate)
	{
		res = mysql_store_result(conn);
		return true;
	}
	return false;
}

bool GestorMySQL::ExecuteSELECTQuery(std::vector<std::string> SelectedColumns, std::vector<std::vector<std::string>> SelectWhere, std::string table, MYSQL_RES*& res) {
	//create the query
	{
		std::string query = "SELECT ";
		for (int i = 0; i < SelectedColumns.size(); i++)
		{
			query += SelectedColumns[i];
			if (i != SelectedColumns.size() - 1)
			{
				query += ", ";
			}
		}
		query += " FROM " + table;
		if (SelectWhere.size() > 0)
		{
			query += " WHERE ";
			for (int i = 0; i < SelectWhere.size(); i++)
			{
				query += SelectWhere[i][0] + " = " + SelectWhere[i][1];
				if (i != SelectWhere.size() - 1)
				{
					query += " AND ";
				}
			}
		}
		return ExecuteSELECTQuery(query, res);
	}
}

std::string GestorMySQL::fetchFieldInRow(MYSQL_RES* res, MYSQL_ROW& row, std::string field)
{
	// convert field name to lowercase
	std::transform(field.begin(), field.end(), field.begin(), ::tolower);

	MYSQL_FIELD* fields = mysql_fetch_fields(res);
	for (int i = 0; i < mysql_num_fields(res); i++)
	{
		// convert column name to lowercase and compare
		std::string column = fields[i].name;
		std::transform(column.begin(), column.end(), column.begin(), ::tolower);
		if (column == field)
		{
			return row[i];
		}
	}
	return "";
}