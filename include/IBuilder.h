#ifndef IBUILDER_H_INCLUDED
#define IBUILDER_H_INCLUDED

#include <boost/shared_ptr.hpp>

class World;

class IBuilder {
public:
    virtual void build(World& world) = 0;
};
typedef boost::shared_ptr<IBuilder> BuilderPtr;


class IBuilderFactory {
public:
    virtual BuilderPtr create() = 0;
};


typedef boost::shared_ptr<IBuilderFactory> BuilderFactoryPtr;

void setBuilderFactory( BuilderFactoryPtr );
BuilderPtr getBuilder(); // factory

#endif // IBUILDER_H_INCLUDED
