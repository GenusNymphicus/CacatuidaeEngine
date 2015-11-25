#include "Utility/Profiler.h"

#include "Utility/Time.h"

#include <iostream>
#include <fstream>

cac::Profiler::Profiler()
{
    setMaxSampleSize(100);
}

cac::Profiler* cac::Profiler::instance()
{
    static Profiler profiler;
    return &profiler;
}


void cac::Profiler::stop(std::string sectionName)
{
    if( trackedSections[sectionName] != 0 && sectionResults[sectionName].size() < maxSampleSize)
    {
	sectionResults[sectionName].push_back(cac::Time::getTimeInMs() - trackedSections[sectionName]);
    }
    trackedSections[sectionName] = 0;
}

void cac::Profiler::track(std::string sectionName)
{
    if(sectionResults[sectionName].size() < maxSampleSize)
    {
	trackedSections[sectionName] = cac::Time::getTimeInMs();
    }
}

void cac::Profiler::saveAs(std::string fileName)
{
    std::string buffer = "";
    for(auto sectionResult : sectionResults)
    {
	buffer += "\n";
	buffer += sectionResult.first + ": \n";
	for(auto results : sectionResult.second)
	{
	    buffer += "    "+ std::to_string(results/1000.0f)+"s\n";
	}
    }
    
    std::fstream file(fileName, std::ios::out);
    file << buffer;

}

std::map<std::string, std::vector<unsigned int>> cac::Profiler::getResults() 
{ 
    return sectionResults; 
    
} 

void cac::Profiler::setMaxSampleSize(int n)
{
    maxSampleSize = n;
}
