#ifndef RAPIDJSONWRITER_H
#define RAPIDJSONWRITER_H

#include "reflection.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"


using corecvs::IntField;
using corecvs::UInt64Field;
using corecvs::DoubleField;
using corecvs::FloatField;
using corecvs::BoolField;
using corecvs::StringField;
using corecvs::PointerField;
using corecvs::EnumField;
using corecvs::DoubleVectorField;

class RapidJSONWriter
{
public:
    bool isSaver () { return true ;}
    bool isLoader() { return false;}


public:



    /**
     *  Create a setter object that will store data to a given XML
     **/
    RapidJSONWriter(rapidjson::Value &document)
    {
        mNodePath.push_back(&document);
    }

    virtual ~RapidJSONWriter();

    template <class inputType>
    void visit(inputType &field, const char *fieldName)
    {
        pushChild(fieldName);
            field.accept(*this);
        popChild(fieldName);
    }

    template <typename Type, typename std::enable_if<
                  !(std::is_enum<Type>::value ||
                  (std::is_arithmetic<Type>::value && !(std::is_same<bool, Type>::value || std::is_same<uint64_t, Type>::value))), int>::type foo = 0>
    void visit(Type &field, Type /*defaultValue*/, const char *fieldName)
    {
        visit(field, fieldName);
    }

    template <typename inputType, typename reflectionType>
    void visit(inputType &field, const reflectionType * fieldDescriptor)
    {
        visit(field, fieldDescriptor->getSimpleName());
    }

    /*
     * Generic Array support
     */
#if 0
    template <typename inputType>
    void visit(std::vector<inputType> &fields, const char * arrayName)
    {
        rapidjson::Value array(rapidjson::kArrayType);
        for (size_t i = 0; i < fields.size(); i++)
        {
            mNodePath.push_back(QJsonObject());
            fields[i].accept(*this);
            array.append(mNodePath.back());
            mNodePath.pop_back();
        }

        mNodePath.back().insert(arrayName, array);
    }

    template <typename innerType>
    void visit(std::vector<std::vector<innerType>> &fields, const char *arrayName)
    {
        rapidjson::Value  arrayOuter(rapidjson::kArrayType);
        for (size_t i = 0; i < fields.size(); ++i)
        {
            rapidjson::Value arrayInner(rapidjson::kArrayType);
            visit(fields[i], arrayInner);
            arrayOuter.append(arrayInner);
        }

        mNodePath.back().insert(arrayName, arrayOuter);
    }

    template <typename innerType>
    void visit(std::vector<std::vector<innerType>> &fields, QJsonArray &array)
    {
        for (size_t i = 0; i < fields.size(); ++i)
        {
            QJsonArray arrayInner;
            visit(fields[i], arrayInner);
            array.append(arrayInner);
        }
    }


    void visit(std::vector<std::string> &fields, QJsonArray &array)
    {
        for (size_t i = 0; i < fields.size(); ++i)
        {
           array.append(QString::fromStdString(fields[i]));
        }
    }


    // XXX: Here we hope that either stack is unwinded automatically or it is not too big
    template <typename innerType, typename std::enable_if<!std::is_arithmetic<innerType>::value,int>::type foo = 0>
    void visit(std::vector<innerType> &fields, QJsonArray &array)
    {
        for (size_t i = 0; i < fields.size(); ++i)
        {
            mNodePath.push_back(QJsonObject());
            fields[i].accept(*this);
            array.append(mNodePath.back());
            mNodePath.pop_back();
        }
    }


    template <typename innerType, typename std::enable_if<std::is_arithmetic<innerType>::value,int>::type foo=0>
    void visit(std::vector<innerType> &fields, QJsonArray &array)
    {
        for (size_t i = 0; i < fields.size(); ++i)
        {
            array.append((QJsonValue)(double)fields[i]);
        }
    }
    #endif

    template <typename inputType, typename reflectionType>
    void visit(std::vector<inputType> &fields, const reflectionType * /*fieldDescriptor*/)
    {
        for (size_t i = 0; i < fields.size(); i++)
        {
            fields[i].accept(*this);
        }
    }

    template <typename type, typename std::enable_if<std::is_arithmetic<type>::value && !std::is_same<bool, type>::value && !std::is_same<uint64_t, type>::value, int>::type foo = 0>
    void visit(type &field, type, const char *fieldName)
    {
        double extended = static_cast<double>(field);
        (*mNodePath.back()).AddMember(fieldName, extended, mDocument.GetAllocator());
    }

    template <typename type, typename std::enable_if<std::is_enum<type>::value, int>::type foo = 0>
    void visit(type &field, type defaultValue, const char *fieldName)
    {
        using U = typename std::underlying_type<type>::type;
        U u = static_cast<U>(field);
        visit(u, static_cast<U>(defaultValue), fieldName);
        field = static_cast<type>(u);
    }

    void pushChild(const char *childName)
    {
        CORE_UNUSED(childName);
        mNodePath.push_back(QJsonObject());
    }

    void popChild(const char *childName)
    {
        rapidjson::Value * mainNode = mNodePath.back();
        mNodePath.pop_back();
        mNodePath.back().AddMember(childName, *mainNode, mDocument.GetAllocator());
    }

private:
    rapidjson::Document mDocument;
    std::vector<rapidjson::Value *> mNodePath;
    std::string                     mFileName;
    std::string                     mChildName;
};

template <>
void RapidJSONWriter::visit<uint64_t>(uint64_t &intField, uint64_t defaultValue, const char *fieldName);

template <>
void RapidJSONWriter::visit<bool>(bool &boolField, bool defaultValue, const char *fieldName);

template <>
void RapidJSONWriter::visit<std::string>(std::string &stringField, std::string defaultValue, const char *fieldName);


/* New style visitor */

template <>
void RapidJSONWriter::visit<unsigned char, IntField>(unsigned char &field, const IntField *fieldDescriptor);

template <>
void RapidJSONWriter::visit<int, IntField>(int &field, const IntField *fieldDescriptor);

template <>
void RapidJSONWriter::visit<uint64_t, UInt64Field>(uint64_t &field, const UInt64Field *fieldDescriptor);

template <>
void RapidJSONWriter::visit<double, DoubleField>(double &field, const DoubleField *fieldDescriptor);

template <>
void RapidJSONWriter::visit<float, FloatField>(float &field, const FloatField *fieldDescriptor);

template <>
void RapidJSONWriter::visit<bool, BoolField>(bool &field, const BoolField *fieldDescriptor);

template <>
void RapidJSONWriter::visit<std::string, StringField>(std::string &field, const StringField *fieldDescriptor);

template <>
void RapidJSONWriter::visit<void *, PointerField>(void * &field, const PointerField *fieldDescriptor);

template <>
void RapidJSONWriter::visit<int, EnumField>(int &field, const EnumField *fieldDescriptor);

/* Arrays */
template <>
void RapidJSONWriter::visit<double, DoubleVectorField>(std::vector<double> &field, const DoubleVectorField *fieldDescriptor);


#endif // RAPIDJSONWRITER_H
