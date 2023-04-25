#pragma once
#include <string>
#include <mysql.h>
#include <vector>
#include <iostream>
#include <thread>
#include <mutex>
#include <algorithm>
//incluir el gestor ini
class GestorMySQL
{
public:
	GestorMySQL();
	~GestorMySQL();
	GestorMySQL(std::string INI_file);
	
	bool isConnected();
	bool ExecuteNonQuery(std::string query);
	bool ExecuteSELECTQuery(std::string query, std::vector<std::vector<std::string>>* res);
	bool ExecuteSELECTQuery(std::string query, MYSQL_RES*& res);
	bool ExecuteSELECTQuery(std::vector<std::string> SelectedColumns, std::vector<std::vector<std::string>> SelectWhere, std::string table, std::vector<std::vector<std::string>>* res);
	std::string fetchFieldInRow(MYSQL_RES* res, MYSQL_ROW row, std::string field);
	
	bool sum(int a, int b, int* res);
private:
	//
	std::mutex mutex_;
	
	bool connect();
	bool disconnect();
	std::string INI_file;
	std::string user;
	std::string password;
	std::string server;
	std::string database;
	std::string port;
	MYSQL* conn;
};

