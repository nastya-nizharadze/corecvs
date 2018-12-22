#include "core/reflection/commandLineSetter.h"

namespace corecvs {

template <>
void CommandLineSetter::visit<int, IntField>(int &field, const IntField *fieldDescriptor)
{
    field = getInt(fieldDescriptor->name.name, fieldDescriptor->defaultValue);
}

template <>
void CommandLineSetter::visit<double, DoubleField>(double &field, const DoubleField *fieldDescriptor)
{
    field = getDouble(fieldDescriptor->name.name, fieldDescriptor->defaultValue);
}

template <>
void CommandLineSetter::visit<float, FloatField>(float &field, const FloatField *fieldDescriptor)
{
    field = (float)getDouble(fieldDescriptor->name.name, fieldDescriptor->defaultValue);
}

template <>
void CommandLineSetter::visit<bool, BoolField>(bool &field, const BoolField *fieldDescriptor)
{
    field = getBool(fieldDescriptor->name.name);
}

template <>
void CommandLineSetter::visit<void *, PointerField>(void * &field,  const PointerField * /*fieldDescriptor*/)
{
    field = NULL;
}

template <>
void CommandLineSetter::visit<int, EnumField>(int &field, const EnumField *fieldDescriptor)
{
    field = getInt(fieldDescriptor->name.name, fieldDescriptor->defaultValue);
}

template <>
void CommandLineSetter::visit<std::string, StringField>(std::string &field, const StringField *fieldDescriptor)
{
    field = getString(fieldDescriptor->name.name, fieldDescriptor->defaultValue);
}

/* Old style */

template <>
void CommandLineSetter::visit<int>(int &intField, int defaultValue, const char * fieldName)
{
    intField = getInt(fieldName, defaultValue);
}

template <>
void CommandLineSetter::visit<double>(double &doubleField, double defaultValue, const char * fieldName)
{
    doubleField = getDouble(fieldName, defaultValue);
}

template <>
void CommandLineSetter::visit<bool>(bool &boolField, bool /*defaultValue*/, const char * fieldName)
{
    boolField = getBool(fieldName);
}

template <>
void CommandLineSetter::visit<std::string>(std::string &stringField, std::string defaultValue, const char * fieldName)
{
    stringField = getString(fieldName, defaultValue);
}


template<class Type>
void CommandLineSetter::visit(Type &field, Type /*defaultValue*/, const char *fieldName)
{
    /*pushChild(fieldName);*/
        field.accept(*this);
    /*popChild();*/
}

bool CommandLineSetter::hasOption(const std::string &option, unsigned *pos) const
{
    string decorated  = mArgPrefix + option;
    string decorated1 = mArgPrefix + option + mArgSeparator;


    for (unsigned i = 0; i < mArgs.size(); i++)
    {
        //SYNC_PRINT(("%d - <%s> <%s> <%s>\n", i,  decorated.c_str(), decorated1.c_str(), mArgs[i].c_str()));
        if ((mArgs[i] == decorated) ||
                (mArgs[i].compare(0, decorated1.length(), decorated1) == 0))
        {
            if (pos != 0) {
                *pos = i;
            }
            return true;
        }
    }
    return false;
}

const std::string CommandLineSetter::getOption(const std::string &option, bool *found) const
{
    string decorated = mArgPrefix + option + mArgSeparator;

    if (found != NULL) *found = false;
    for (unsigned i = 0; i < mArgs.size(); i++)
    {
        if (mArgs[i].compare(0, decorated.length(), decorated) == 0)
        {
            if (found != NULL) *found = true;
            return mArgs[i].substr(decorated.length());
        }
    }
    return "";
}

vector<std::string> CommandLineSetter::nonPrefix() const
{
    vector<string> result;

    for (unsigned i = 0; i < mArgs.size(); i++)
    {
        if (mArgs[i].compare(0, mArgPrefix.length(), mArgPrefix) != 0)
        {
            result.push_back(mArgs[i]);
        }
    }
    return result;
}

std::string CommandLineSetter::getNonPrefixParam(int id) const
{
    int num = 0;
    for (unsigned i = 0; i < mArgs.size(); i++)
    {
        if (mArgs[i].compare(0, mArgPrefix.length(), mArgPrefix) != 0)
        {
            if (num == id) {
                return (mArgs[i]);
            }
            num++;
        }
    }
    return "";
}

int CommandLineSetter::getInt(const std::string &option, int defaultInt) const
{
    const string& argument = getOption(option);

    if (argument.empty())
    {
        return defaultInt;
    }

    std::size_t pos = 0;
    int result = stoi(argument, &pos);
    if (pos != 0) {
        return result;
    } else {
        return defaultInt;
    }
}

bool CommandLineSetter::getBool(const std::string &option) const
{
    //const string& argument = getOption(option);
    return hasOption(option);
}

double CommandLineSetter::getDouble(const std::string &option, double defaultDouble) const
{
    const string& argument = getOption(option);

    if (argument.empty())
    {
        return defaultDouble;
    }

    std::size_t pos = 0;
    double result = stod(argument, &pos);
    if (pos != 0) {
        return result;
    } else {
        return defaultDouble;
    }
}

std::string CommandLineSetter::getString(const std::string &option, const std::string &defaultString) const
{
    bool found = false;
    const std::string& argument = getOption(option, &found);

    if (!found)
    {
        return std::string(defaultString);
    }

    return std::string(argument);
}

} //namespace corecvs
