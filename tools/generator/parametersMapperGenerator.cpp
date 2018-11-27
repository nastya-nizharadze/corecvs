#include <iostream>

#include "parametersMapperGenerator.h"

using std::ios;


ParametersMapperGenerator::ParametersMapperGenerator(QMap<QString, Reflection *> *reflections
                                                   , QList<QPair<QString, QString> > *mapperFields
                                                   , const QString &postfix)
    : BaseGenerator(NULL)
    , mapperPostfix(postfix)
    , mReflections(reflections)
    , mMapperFields(mapperFields)

{
}

void ParametersMapperGenerator::enterFieldContext(int i)
{
    QString name = mFieldClasses.at(i)->name.name;
    QString typeName = mFieldClasses.at(i)->typeName;

    baseName = toCamelCase(name, true);
    parametersName = baseName;
    widgetName = baseName + "ControlWidget";
    fieldName = "m" + widgetName;
    fieldType = toCamelCase(typeName, true) + "ControlWidget";
    parametersName = toCamelCase(typeName, true);

    classFileName = toCamelCase(name) + ".h";
    classWidgetFileName = toCamelCase(typeName) + "ControlWidget.h";

    signalName = toCamelCase(name) + "ParamsChanged";
    pointerName = "QSharedPointer<" + parametersName + ">";

}

void ParametersMapperGenerator::enterMapperFieldContext(int i)
{
    baseName = toCamelCase(mMapperFields->at(i).first, true);
    widgetName = baseName + "ControlWidget";

    fieldName = "m" + widgetName;
    fieldType = toCamelCase(mMapperFields->at(i).second, true) + "ControlWidget";
    parametersName = toCamelCase(mMapperFields->at(i).second, true);

    classWidgetFileName = toCamelCase(mMapperFields->at(i).second) + "ControlWidget.h";

    signalName = toCamelCase(mMapperFields->at(i).first, false) + "ParamsChanged";
    pointerName = "QSharedPointer<" + parametersName + ">";

}

bool ParametersMapperGenerator::getMapperClass(QString const &className, QList<CompositeField const *> &fields)
{
    Reflection *ref = mReflections->value(className);
    if (!ref)
        return false;

    /*skip subclass that contains other fields then composite*/
    for (int i = 0; i < ref->fieldNumber(); i++)
    {
        if (ref->fields[i]->type != BaseField::TYPE_COMPOSITE)
            return true;
    }


    for (int i = 0; i < ref->fieldNumber(); i++)
    {
        CompositeField const *compositeField = static_cast<CompositeField const *>(ref->fields[i]);

//        QString fieldName = compositeField->typeName;
//        if (Reflection *fieldRef = mReflections->value(fieldName))
//        {
//            // TODO: handle recursively
//        }
        fields.append(compositeField);
    }

    return true;
}

void ParametersMapperGenerator::generateMapper()
{
    foreach (StringPair field, *mMapperFields)
    {
        QList<CompositeField const *> fields;
        if (!getMapperClass(field.second, fields))
            continue;

        mFieldClasses += fields;

        mCompositeClasses.insert(field.first, fields);
    }

    generateHeader();
    generateSource();
}

void ParametersMapperGenerator::generateHeader()
{
    QString result;

    QString fileName    = "parametersMapper"+mapperPostfix+".h";
    QString guardDefine = "PARAMETERS_MAPPER_"+mapperPostfix.toUpper()+"_H_";
    QString mapperName  = "ParametersMapper"+mapperPostfix;

    out.close();
    out.open(QString(getGenerateDir() + QDir::separator() + fileName).toLatin1(), ios::out);

    result +=
    "#ifndef "+guardDefine+"\n"
    "#define "+guardDefine+"\n"
    "/**\n"
    " * \\file "+fileName+"\n"
    " * \\attention This file is automatically generated and should not be in general modified manually\n"
    " *\n"
    " * \\date MMM DD, 20YY\n"
    " * \\author autoGenerator\n"
    " */\n"
    "\n"
    "#include <iostream>\n"
    "#include <QtCore/QSharedPointer>\n"
    "\n"
    "#include \"core/reflection/reflection.h\"\n"
    "#include \"core/reflection/defaultSetter.h\"\n"
    "\n";


    for (int i = 0; i < mFieldClasses.size(); i++)
    {
        enterFieldContext(i);

    result +=
    "#include \""+classWidgetFileName+"\"\n";
    }

    for (int i = 0; i < mMapperFields->size(); i++)
    {
        enterMapperFieldContext(i);

    result+=
    "#include \""+classWidgetFileName+"\"\n";
    }

    result +=
    "\n"
    "class "+mapperName+" : public QObject\n"
    "{\n"
    "    Q_OBJECT"
    "\n"
    "public:\n"
    "    "+mapperName+"();\n"
    "\n";

    for (int i = 0; i < mFieldClasses.size(); i++)
    {
        enterFieldContext(i);

    result+=
    "    void set"+widgetName+"("+fieldType+" *widget);\n";
    }

    for (int i = 0; i < mMapperFields->size(); i++)
    {
        enterMapperFieldContext(i);

    result+=
    "    void set"+widgetName+"("+fieldType+" *widget);\n";
    }

    result+=
    "\n"
    "public slots:\n"
    "    void paramsChanged();\n"
    "\n"
    "signals:\n";

    for (int i = 0; i < mMapperFields->size(); i++)
    {
        enterMapperFieldContext(i);

    result+=
    "    void "+signalName+"("+pointerName+" params);\n";
    }

    result+=
    "\n"
    "private:\n";

    for (int i = 0; i < mFieldClasses.size(); i++)
    {
        enterFieldContext(i);

    result+=
    "    "+fieldType+" *"+fieldName+";\n";
    }

    for (int i = 0; i < mMapperFields->size(); i++)
    {
        enterMapperFieldContext(i);

    result+=
    "    "+fieldType+" *"+fieldName+";\n";
    }

    result+=
    "};\n"
    "#endif //"+guardDefine+"\n";

    out << result.toLatin1().constData();
}

void ParametersMapperGenerator::generateSource()
{
    QString result;


    QString fileName    = "parametersMapper"+mapperPostfix+".cpp";
    QString headerName  = "parametersMapper"+mapperPostfix+".h";;
    QString mapperName  = "ParametersMapper"+mapperPostfix;

    out.close();
    out.open(QString(getGenerateDir() + QDir::separator() + fileName).toLatin1(), ios::out);

    result +=
    "/**\n"
    " * \\file "+fileName+"\n"
    " * \\attention This file is automatically generated and should not be in general modifed manually\n"
    " *\n"
    " * \\date MMM DD, 20YY\n"
    " * \\author autoGenerator\n"
    " */\n"
    "\n"
    "#include \""+headerName+"\"\n"
    "\n"
    ""+mapperName+"::"+mapperName+"() :\n";
    int count = 0;
    for (int i = 0; i < mFieldClasses.size(); i++, count++)
    {
        enterFieldContext(i);
        QString separator = (count == 0 ? " " :  ",");

    result+=
    "  "+separator+" "+fieldName+"(NULL)\n";
    }

    for (int i = 0; i < mMapperFields->size(); i++, count++)
    {
       enterMapperFieldContext(i);
       QString separator = (count == 0 ? " " :  ",");

    result+=
    "  "+separator+" "+fieldName+"(NULL)\n";
    }

    result +=
    "{\n";

    for (int i = 0; i < mFieldClasses.size(); i++)
    {
        enterFieldContext(i);

    result+=
    "    qRegisterMetaType<"+pointerName+" >(\""+pointerName+"\");\n";
    }

    for (int i = 0; i < mMapperFields->size(); i++)
    {
        enterMapperFieldContext(i);

    result+=
    "    qRegisterMetaType<"+pointerName+" >(\""+pointerName+"\");\n";
    }

    result+=
    "}\n"
    "\n";

    for (int i = 0; i < mFieldClasses.size(); i++)
    {
        enterFieldContext(i);

    result+=
    "void "+mapperName+"::set"+widgetName+"("+fieldType+" *widget)\n"
    "{\n"
    "    "+fieldName+" = widget;\n"
    "    QObject::connect("+fieldName+", SIGNAL(paramsChanged()), this, SLOT(paramsChanged()));\n"
    "}\n"
    "\n";
    }

    for (int i = 0; i < mMapperFields->size(); i++)
    {
        enterMapperFieldContext(i);

    result+=
    "void "+mapperName+"::set"+widgetName+"("+fieldType+" *widget)\n"
    "{\n"
    "    "+fieldName+" = widget;\n"
    "    QObject::connect("+fieldName+", SIGNAL(paramsChanged()), this, SLOT(paramsChanged()));\n"
    "}\n"
    "\n";
    }

    result+=
    "void "+mapperName+"::paramsChanged()\n"
    "{\n";

    if (mFieldClasses.size() != 0) {
    result+=
    "    if(\n";

    for (int i = 0; i < mFieldClasses.size(); i++)
    {
       enterFieldContext(i);
       QString separator = (i == 0 ? " " :  "||");
    result+=
    "      "+separator+" ("+fieldName+" == NULL)\n";
    }

    result+=
    "    )\n"
    "    {\n"
    "          std::cout << \"One of the fields for "+mapperName+" \\n\"\n"
    "               \"is still NULL but the mapper is already in use. This will cause crash.\\n\"\n"
    "               \"You should modify your <HostWidget>::createCalculator() function\" << std::endl;\n"
    "    }\n"
    "\n";
    }

    count = 0;
    for (int i = 0; i < mMapperFields->size(); i++)
    {
        enterMapperFieldContext(i);

        int countInternal = 0;

        QList<CompositeField const *> fields = mCompositeClasses.value(mMapperFields->at(i).first);
        if (fields.size() > 0)
        {
            for (int j = 0; j < fields.size(); j++)
            {
                fieldName = "m" + toCamelCase(fields.at(j)->name.name, true) + "ControlWidget";
                parametersName = toCamelCase(fields.at(j)->typeName, true);
    result+=
    "    "+parametersName+" *param"+QString::number(count+countInternal)+" = "+fieldName+"->createParameters();\n";
                countInternal++;
            }

    result+=
    "\n";

    result+=
    "    emit "+signalName+"("+pointerName+"(new "+baseName+"(";

            for (int j = 0; j < fields.size(); j++)
            {
    result +=
    "\n"
    "            *param"+QString::number(count+j)+",";
            }
            result.chop(1);

    result+=
    ")));\n\n";

            for (int j = 0; j < fields.size(); j++)
            {
    result +=
    "    delete param"+QString::number(count+j)+";\n";

            }
        }
        else
        {
    result+=
    "    if ("+fieldName+" == NULL)\n"
    "    {\n"
    "          std::cout << \"One of the fields for "+mapperName+" \\n\"\n"
    "               \"is still NULL but the mapper is already in use. This will cause crash.\\n\"\n"
    "               \"You should modify your <HostWidget>::createCalculator() function\" << std::endl;\n"
    "    }\n"
    "    emit "+signalName+"("+pointerName+"("+fieldName+"->createParameters("
    ")));\n\n";
        }

    result+=
    "\n";

        count += countInternal;
    }


    result+=
    "}\n"
    "\n";

    out << result.toLatin1().constData();
}
