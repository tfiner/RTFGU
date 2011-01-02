#include "IBuilder.h"

namespace {

    class NullBuilder : public IBuilder {
    public:
        void build(World& world) {}
    };

    class NullBuilderFactory : public IBuilderFactory {
        virtual BuilderPtr create() {
            return BuilderPtr(new NullBuilder);
        }
    };

    BuilderFactoryPtr factory = BuilderFactoryPtr(new NullBuilderFactory);
}


void setBuilderFactory( BuilderFactoryPtr newFactory ) {
    factory = newFactory;
}


BuilderPtr getBuilder() {
    return factory->create();
}
