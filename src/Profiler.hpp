#pragma once

#include<fstream>
#include<chrono>
#include<mutex>
#include<string>
#include<algorithm>
#include <bits/std_thread.h>

// #define PROFILING 1
#ifdef PROFILING
    #define PROFILE_SCOPE(name) \
        ProfileTimer timer##__LINE__(name)
    #define PROFILE_FUNCTION() \
        PROFILE_SCOPE(__FUNCTION__)
#else
    #define PROFILE_SCOPE(name)
    #define PROFILE_FUNCTION()
#endif

struct ProfileResult {
    std::string name    = "Default";
    long long start     = 0;
    long long end       = 0;
    size_t threadID     = 0;
};

class Profiler {
    std::string     m_outputFile    = "results.json";
    size_t          m_profileCount  = 0;
    std::ofstream   m_outPutStream;
    std::mutex      m_lock;           
    
    Profiler() {
        m_outPutStream = std::ofstream(m_outputFile);
        //writes JSON header
        writeHeader();
    };

    void writeHeader() { m_outPutStream << "{\"otherData\": {},\"traceEvents\":[";}
    void writeFooter() { m_outPutStream << "]}"; }

public:
    static Profiler & Instance() {
        static Profiler instance;
        return instance;
    }

    void writeProfile(const ProfileResult &result){
        //write result in JSON
        std::lock_guard<std::mutex> lock(m_lock);

        if(m_profileCount++ > 0) {m_outPutStream << ",";}

        std::string name = result.name;
        std::replace(name.begin(),name.end(), '"', '\'');

        m_outPutStream << "\n{";
        m_outPutStream << "\"cat\":\"function\",";
        m_outPutStream << "\"dur\":" << (result.end - result.start) <<',';
        m_outPutStream << "\"name\":\"" << result.name <<"\",";
        m_outPutStream << "\"ph\":\"X\",";
        m_outPutStream << "\"pid\":0,";
        m_outPutStream << "\"tid\":" << result.threadID << ",";
        m_outPutStream << "\"ts\":" << result.start;
        m_outPutStream << "}";
    }

    ~Profiler() {
        //write JSON footer
        writeFooter();
    }
};

class ProfileTimer {
    typedef std::chrono::time_point<std::chrono::high_resolution_clock> ClockType;

    ProfileResult m_result;
    ClockType m_startTimepoint;
    bool m_stopped = false;

public:
    //construct the profiler
    ProfileTimer(const std::string& name): m_result({name, 0, 0, 0}) {
        start();
    }

    ~ProfileTimer() {
        stop();
    }

    //this set the start time
    //there is some issue in chrome::tracing for identical start times
    //so here we add 1 unit of time when ever identical start times are possible (nasty workaround)
    void start() {
        //a static variable to store the last start time recorded
        static long long lastStartTime = 0;

        m_startTimepoint = std::chrono::high_resolution_clock().now();
        m_result.start = std::chrono::time_point_cast<std::chrono::microseconds>
            (m_startTimepoint).time_since_epoch().count();

        m_result.start += (lastStartTime == m_result.start ? 1:0);

        lastStartTime = m_result.start;
        m_stopped = false;
    }

    void stop() {
        if(m_stopped) {return;}
       
        auto endTimepoint = std::chrono::high_resolution_clock::now();

        m_result.start=std::chrono::time_point_cast<std::chrono::microseconds>
        (m_startTimepoint).time_since_epoch().count();
    
        m_result.end=std::chrono::time_point_cast<std::chrono::microseconds>
        (endTimepoint).time_since_epoch().count();

        m_result.threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());

        Profiler::Instance().writeProfile(m_result);
        m_stopped = true;
    }
};