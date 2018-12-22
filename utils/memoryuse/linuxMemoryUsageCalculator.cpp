#include <fstream>
#include <string>
#include <unistd.h>
#include <iostream>

#include "core/utils/global.h"
#include "linuxMemoryUsageCalculator.h"

void LinuxMemoryUsageCalculator::getMemoryUsageImpl()
{
    using std::ios_base;
    using std::ifstream;
    using std::string;

    mVirtualSize = 0.0;
    mResidentSize = 0.0;

    // 'file' stat seems to give the most reliable results
    ifstream stat_stream("/proc/self/stat",ios_base::in);

    // dummy vars for leading entries in stat that we don't care about
    string pid, comm, state, ppid, pgrp, session, tty_nr;
    string tpgid, flags, minflt, cminflt, majflt, cmajflt;
    string utime, stime, cutime, cstime, priority, nice;
    string O, itrealvalue, starttime;

    // the two fields we want
    unsigned long vsize;
    long rss;

    stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr
                >> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt
                >> utime >> stime >> cutime >> cstime >> priority >> nice
                >> O >> itrealvalue >> starttime >> vsize >> rss; // don't care about the rest

    stat_stream.close();

    long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
    mVirtualSize     = vsize / 1024.0 / 1024.0;
    mResidentSize = rss * page_size_kb / 1024.0;
}

void LinuxMemoryUsageCalculator::getTotalMemoryImpl()
{
    std::ifstream f;
    f.open("/proc/meminfo", std::ios_base::in);
    double mem = 2400;
    std::string tag, units;
    double value;
    while (f)
    {
        f >> tag >> value >> units;
        if (tag != "MemTotal:")
            continue;
        CORE_ASSERT_TRUE_S(units == "kB"); // LoL
        mem = value / 1024.0;
        break;
    }
    mTotalMemory = mem;
}
