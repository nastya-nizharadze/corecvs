#include "core/reflection/dynamicObject.h"

namespace corecvs {

bool DynamicObjectWrapper::simulateConstructor()
{
    if (reflection == NULL || rawObject == NULL)
        return false;

    for (int count = 0; count < reflection->fieldNumber(); count++)
    {
        const BaseField *field = reflection->fields[count];
        switch (field->type) {
        case BaseField::TYPE_BOOL:
        {
            const BoolField *tfield = static_cast<const BoolField *>(field);
            *getField<bool>(count) = tfield->defaultValue;
            break;
        }
        case BaseField::TYPE_INT:
        {
            const IntField *tfield = static_cast<const IntField *>(field);
            *getField<int>(count) = tfield->defaultValue;
            break;
        }
        case BaseField::TYPE_DOUBLE:
        {
            const DoubleField *tfield = static_cast<const DoubleField *>(field);
            *getField<double>(count) = tfield->defaultValue;
            break;
        }
        case BaseField::TYPE_STRING:
        {
            const StringField *tfield = static_cast<const StringField *>(field);
            std::string *target = getField<std::string>(count);
            target = new (target) std::string(tfield->defaultValue);
            break;
        }
        case BaseField::TYPE_WSTRING:
        {
            const WStringField *tfield = static_cast<const WStringField *>(field);
            std::wstring *target = getField<std::wstring>(count);
            target = new (target) std::wstring(tfield->defaultValue);;
            break;
        }
        case (BaseField::FieldType)(BaseField::TYPE_VECTOR_BIT | BaseField::TYPE_DOUBLE) :
        {
            const DoubleVectorField *tfield = static_cast<const DoubleVectorField *>(field);
            *getField<vector<double> >(count) = tfield->defaultValue;
            break;
        }
        case BaseField::TYPE_COMPOSITE:
        {
            const CompositeField *tfield = static_cast<const CompositeField *>(field);
            if (tfield->reflection == NULL)
            {
                SYNC_PRINT(("DynamicObject::simulateConstructor(%s): composite field (%d : %s) has empty reflection",
                            reflection->name.name, count, tfield->name.name
                            ));
                break;
            }
            DynamicObjectWrapper obj(tfield->reflection, getField<void *>(count));
            obj.simulateConstructor();
            break;
        }

        default:
            break;
        }
    }

    return true;
}

DynamicObject::~DynamicObject()
{
    if (reflection != NULL && rawObject != NULL)
    {
        for (int count = 0; count < reflection->fieldNumber(); count++)
        {
            const BaseField *field = reflection->fields[count];
            switch (field->type) {
                case BaseField::TYPE_STRING:
                {
                    std::string *target = getField<std::string>(count);
                    target->~basic_string();
                    break;
                }
                case BaseField::TYPE_WSTRING:
                {
                    std::wstring *target = getField<std::wstring>(count);
                    target->~basic_string();
                    break;
                }
                default:
                    break;
            }

        }
    }


    free(rawObject);
}

} // namespace corecvs

