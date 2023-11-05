#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include <filesystem>
#include <chrono>

#include <Windows.h>
// LogManager class
// Version 1.0
// Versión guarra con el Sleep

struct LogEntry {
    std::chrono::system_clock::time_point TimeStamp;
    std::string _message;

    LogEntry(std::chrono::system_clock::time_point timeStamp, std::string message) : TimeStamp(timeStamp), _message(message) {}
};

class CLogManager {
public:
    std::string LogName;
    std::queue<LogEntry> LogEntries;
    int DaysToKeepLogs = 7;
    std::string LogFullPath;
   

    //constructor
    CLogManager(std::string _logName, std::string _logFolderPath, int _daysToKeepLogs) : LogName(_logName), DaysToKeepLogs(_daysToKeepLogs) {
        LogEntries = std::queue<LogEntry>();

        //create log name with date
        auto now = std::chrono::system_clock::now();
        time_t now_c = std::chrono::system_clock::to_time_t(now);
        struct tm time_info;
        localtime_s(&time_info, &now_c);
        char buffer[80];
        strftime(buffer, 80, "%Y-%m-%d", &time_info);
        LogName = std::string(buffer) + "_" + LogName + ".txt";

        this->LogFullPath = _logFolderPath + LogName;
        CreateLogFile(_logFolderPath);
        DeleteOldLogs(_logFolderPath);

        _logThread = std::thread(&CLogManager::LogThread, this);
    }
    
    ~CLogManager() {
        FinalizeLogManager();
    }
    
    void CreateLogFile(std::string _logFolderPath) {
        //create log folder if it doesn't exist
        if (!std::filesystem::exists(_logFolderPath)) {
            std::filesystem::create_directory(_logFolderPath);
        }
        //create the file if it doesn't exist
        if (!std::filesystem::exists(LogFullPath)) {
            std::ofstream file(LogFullPath);
            file.close();
        }
    }

    void DeleteOldLogs(std::string _logFolderPath) {
        //delete logs older than N days
        for (const auto& entry : std::filesystem::directory_iterator(_logFolderPath)) {
            if (entry.is_regular_file()) {
                auto filePath = entry.path();
                std::filesystem::file_time_type fileTime = std::filesystem::last_write_time(filePath);
                std::chrono::system_clock::time_point fileTime_time_point = std::chrono::clock_cast<std::chrono::system_clock>(fileTime);
                std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
                auto daysAgo = std::chrono::duration_cast<std::chrono::days>(now - fileTime_time_point).count();
                if (daysAgo > DaysToKeepLogs && filePath.filename().string().find(LogName) != std::string::npos) {
                    std::filesystem::remove(filePath);
                }
            }
        }
    }

    void AddEntry(std::string _message) {
        std::unique_lock<std::mutex> lock(_lock);
        LogEntries.push(LogEntry(std::chrono::system_clock::now(), _message));
    }

    void SaveLog() {
        std::ofstream sw(LogFullPath, std::ios::app);
        std::queue<LogEntry> logEntriesCopy;
        {
			std::unique_lock<std::mutex> lock(_lock);
            while (!LogEntries.empty()) {
                LogEntry logEntry = LogEntries.front();
                LogEntries.pop();
                logEntriesCopy.push(logEntry);
            }
        }
        while (!logEntriesCopy.empty()) {
            LogEntry logEntry = logEntriesCopy.front();
            logEntriesCopy.pop();
            auto now_c = std::chrono::system_clock::to_time_t(logEntry.TimeStamp);
            struct tm time_info;
            localtime_s(&time_info, &now_c);
            char buffer[80];
            strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", &time_info);
            sw << buffer << " " << logEntry._message << std::endl;
        }
    }

    void LogThread() {
        do {
            SaveLog();
			Sleep(150);
        } while (!s_FinalizeLogManager);
    }

    void FinalizeLogManager() {
        s_FinalizeLogManager = true;
        if (_logThread.joinable()) {
            _logThread.join();
        }
    }
    
private:
    std::mutex _lock;
    std::condition_variable _cv;
    bool _awake = false;
    std::thread _logThread;
    bool s_FinalizeLogManager = false;
};
