#ifndef UTILS_H_
#define UTILS_H_
/**
 * \file utils.h
 * \brief This calss conatins CPP helper functions
 *
 *
 *
 * \ingroup cppcorefiles
 * \date Apr 14, 2010
 * \author alexander
 */

#include <type_traits>
#include <string>
#include <vector>
#include <iostream>
#include <vector>
#include <unordered_map>

#include "core/utils/global.h"


namespace corecvs {

//@{
/**
 * This is a helper
 * meta-programming template to represent binary constants.
 *
 * For example:
 *         9 == binary<1001>::value
 *
 *
 **/
template <unsigned long int N>
class binary
{
public:
    const static unsigned value = (binary<N / 10>::value * 2) + ((N % 10 == 0) ? 0 : 1);
};

template <>
class binary<0>
{
    const static unsigned value = 0;
};

//@}

/** Useful class for some tasty things
 */
namespace HelperUtils
{
    using std::string;
    using std::istream;
    using std::vector;

    bool            startsWith(const string &str, const string &prefix);
    bool            endsWith  (const string &str, const string &postfix);
    istream&        getlineSafe(istream& is, string& str);

    std::string     removeLeading(const string &str, const string &symbols = " ");

    void            stringSplit(const string &s, char delim, vector<string> &elems);
    vector<string>  stringSplit(const string &s, char delim);

    string          escapeString  (const string &s, const std::unordered_map<char, char> &symbols, const std::string &escape);
    string          unescapeString(const string &s, const std::unordered_map<char, char> &symbols, char guard);


    string          stringCombine(vector<string> parts, char delim);

    string          toNativeSlashes(const string& str);

    string          getEnvDirPath(cchar *envVarName);       // returns path to dir with slash at the end
    string          getEnvVar(cchar *envVarName);
    string          getFullPath(const string& envDirPath, cchar* path, cchar* filename = NULL);

    inline string   getFullPath(cchar *envVarName, cchar* path, cchar* filename = NULL)
    {
        return  getFullPath(getEnvDirPath(envVarName), path, filename);
    }

    inline string   getFileNameFromFilePath(const string &filePath)
    {
        size_t pos = filePath.find_last_of("/\\");
        return filePath.substr(pos == string::npos ? 0 : (pos + 1));
    }

    inline string   getPathWithoutFilename(const string &filePath)
    {
        return filePath.substr(0, filePath.find_last_of("/\\") + 1);
    }

    inline string   getFullPathWithoutExt(const string &filePath)
    {
        return filePath.substr(0, filePath.find_last_of("."));
    }

    inline string   getFullPathWithNewExt(const string &filePath, const string &newExt)
    {
        return getFullPathWithoutExt(filePath) + newExt;
    }

    /// Add suffix to file name before extension: filename.ext -> filenameSuffix.ext
    inline string   getFilePathWithSuffixAtName(const string& filePath, const string& suffix)
    {
        size_t pos = filePath.find_last_of(".");
        return filePath.substr(0, pos) + suffix + (pos == string::npos ? "" : filePath.substr(pos));
    }

    /* these wrappers are not essential, but it removes the clutter of handling fs:: namespace */
    string concatPath  (const string &path1, const string &path2);
    bool isAbsolutePath(const string &path);
    bool pathExists    (const string &path);
    bool pathRemove    (const string &path);
    bool isDirectory   (const string &path);

    /* Qt rewritten to std */
    string addFileExtIfNotExist(const string& fileName, const string& ext);
    string getDirectory(const string& absoluteFilePath);
    string getFileName(const string& fileName);
    string getFileNameIfExist(const string& fileName, const string& relativePath);

} // namespace HelperUtils

} //namespace corecvs


/* OS related stuff */
#ifdef is__cplusplus
extern "C" {
#endif
    void setStdTerminateHandler();					// is implemented at utils.cpp
    void setSegVHandler();							// is implemented at util.c
#ifdef is__cplusplus
} // extern "C"
#endif

#define SET_HANDLERS()          \
    setSegVHandler();           \
    setStdTerminateHandler();   \


#endif /* UTILS_H_ */
