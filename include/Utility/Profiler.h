#ifndef CACATUIDAE_UTILITY_PROFILER_H
#define CACATUIDAE_UTILITY_PROFILER_H

#include <string>
#include <map>
#include <vector>

namespace cac 
{
    class Profiler 
    {
    public:
	
	static Profiler* instance() ;
	void setMaxSampleSize(int n);
	std::map<std::string, std::vector<unsigned int>> getResults(); 
	void stop(std::string sectionName);
	void track(std::string sectionName);
	void saveAs(std::string fileName);
	
    private:
	Profiler();
	
	std::map<std::string, unsigned int> trackedSections;
	std::map<std::string, std::vector<unsigned int>> sectionResults;
	
	int maxSampleSize;
    };
}
#endif
