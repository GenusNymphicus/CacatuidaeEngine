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
	
	void enabled(bool enable);
	bool enabled();
    private:
	Profiler();
	bool enable = true;
	std::map<std::string, unsigned int> trackedSections;
	std::map<std::string, std::vector<unsigned int>> sectionResults;
	
	unsigned int maxSampleSize;
    };
}
#endif
