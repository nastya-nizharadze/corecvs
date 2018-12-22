#ifndef PROCESSOR6D_H_
#define PROCESSOR6D_H_

/**
 * \file processor6D.h
 * \brief Add Comment Here
 *
 * \date Apr 2, 2011
 * \author alexander
 */


#include "core/utils/global.h"

#include "core/reflection/dynamicObject.h"

#include "core/buffers/g12Buffer.h"
#include "core/buffers/rgb24/rgb24Buffer.h"
#include "core/buffers/flow/flowBuffer.h"
#include "core/buffers/flow/sixDBuffer.h"
#include "core/stats/calculationStats.h"

namespace corecvs {

class Processor6D
{
protected:
    Processor6D() {}

public:
    enum StructureNames {
       FEATURES = 0x1
    };

    enum ResultNames {
       RESULT_FLOW = 0x01,
       RESULT_STEREO = 0x02,
       RESULT_6D = 0x04,
       RESULT_FLOAT_FLOW   = 0x08,
       RESULT_FLOAT_STEREO = 0x10,
       RESULT_FLOAT_FLOW_LIST = 0x20
    };

    enum FrameNames {
       FRAME_LEFT_ID,
       FRAME_RIGHT_ID,
       FRAME_NAME_LAST = FRAME_RIGHT_ID
    };

    virtual int beginFrame() = 0;

    /** Completly reset internal data structures. parameters are left intact **/
    virtual int reset() = 0;

    /** Implemetation may allow you to reset some internal structures at will **/
    virtual int clean(int mask) = 0;

    /**
     * You are responisble to delete the frame sometime after endFrame() is called
     * Implemetation may (and will) store additinal views (pointers) to actual image data
     * for as long as implementation need them.
     *
     * see AbstractBuffer::createViewPtr<> for details on this mechanism
     *
     * To get consistent result don't modify frame data after the call to setFrame*
     **/
    virtual int setFrameG12  (FrameNames frameType, G12Buffer   *frame) = 0;
    virtual int setFrameRGB24(FrameNames frameType, RGB24Buffer *frame) = 0;

    virtual int setDisparityBufferS16(FrameNames frameType, FlowBuffer *frame) = 0;

    /** sets statistics data. Implementation should support stats == NULL **/
    virtual int setStats(Statistics *stats) = 0;
    virtual int endFrame() = 0;


    virtual std::map<std::string, DynamicObject> getParameters() = 0;
    virtual bool setParameters(std::string name, const DynamicObject &param) = 0;


    /** Oldstyle calls **/
    virtual int setParameteri(int parameterName, int parameterValue) = 0;
    virtual int requestResultsi(int parameterName) = 0;

    /**
     * Methods below return the pointers to the internal data structures that are only valid
     * untill next beginFrame() is called. If you want them to persist - make a copy
     **/

    /* This method computes flow form current frame to previous */
    virtual FlowBuffer *getFlow() = 0;
    virtual FlowBuffer *getStereo() = 0;
    virtual CorrespondenceList *getFlowList() = 0;

    virtual int getError(std::string *errorString) = 0;

    virtual ~Processor6D() {}


};


class Processor6DFactory {
public:
   virtual Processor6D *getProcessor() = 0;
   virtual std::string getName() = 0;
   virtual ~Processor6DFactory() {}
};

class Processor6DFactoryHolder {
public:

private:
    Processor6DFactoryHolder() {}
    static std::unique_ptr<Processor6DFactoryHolder> sThis;

public:
    virtual ~Processor6DFactoryHolder();


    static Processor6DFactoryHolder* getInstance();
    static Processor6D *getProcessor(const std::string &name);
    static vector<std::string> getHints();
    static void printCaps();


    bool addFactory(Processor6DFactory * factory)
    {
        mProviders.push_back(factory);
        return true;
    }

    bool hasProvider(const std::string &name);


    vector<Processor6DFactory *> mProviders;
};

} // namespace

#endif /* PROCESSOR6D_H_ */
