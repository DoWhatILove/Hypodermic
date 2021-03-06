#pragma once

#include <stdexcept>

#include "Hypodermic/Container.h"


using namespace Hypodermic;


namespace Testing
{

    class DefaultConstructibleBase
    {
    public:
        virtual ~DefaultConstructibleBase() {}

        virtual void doSomething() = 0;
    };

    class DefaultConstructible1 : public DefaultConstructibleBase
    {
    public:
        void doSomething() override {}
    };

    class DefaultConstructible2 : public DefaultConstructibleBase
    {
    public:
        void doSomething() override {}
    };


    class ContainerDependent
    {
    public:
        explicit ContainerDependent(const std::shared_ptr< Container >& container)
            : container(container)
        {
            if (this->container == nullptr)
                throw std::runtime_error("container cannot be null");
        }

        std::shared_ptr< Container > container;
    };


    class ManualConstructible
    {
    public:
        explicit ManualConstructible(int i)
            : i(i)
        { }

        int i;
    };



    class MissingConstructorDependency
    {
    };

    class MissingConstructor
    {
    public:
        explicit MissingConstructor(const std::shared_ptr< MissingConstructorDependency >& dependency)
            : dependency(dependency)
        {
            if (this->dependency == nullptr)
                throw std::runtime_error("dependency cannot be null");
        }

        std::shared_ptr< MissingConstructorDependency > dependency;
    };



    class ProvidedDependencyBase
    {
    public:
        virtual ~ProvidedDependencyBase() {}

        virtual void doSomething() = 0;
    };

    class ProvidedDependency : public ProvidedDependencyBase
    {
    public:
        void doSomething() override {}
    };

    class RandomTypeBase
    {
    public:
        virtual ~RandomTypeBase() {}
    };

    class TypeWithOneDependency : public RandomTypeBase
    {
    public:
        explicit TypeWithOneDependency(const std::shared_ptr< ProvidedDependencyBase >& dependency)
            : dependency(dependency)
        {
            if (this->dependency == nullptr)
                throw std::runtime_error("dependency cannot be null");
        }

        std::shared_ptr< ProvidedDependencyBase > dependency;
    };


    class NestedDependency
    {
    public:
        explicit NestedDependency(int i)
            : i(i)
        {
        }

        int i;
    };

    class TopLevelConstructor
    {
    public:
        explicit TopLevelConstructor(const std::shared_ptr< NestedDependency >& dependency)
            : dependency(dependency)
        {
        }

        std::shared_ptr< NestedDependency > dependency;
    };


    class BaseType1
    {
    public:
        virtual ~BaseType1() {}
    };

    class BaseType2
    {
    public:
        virtual ~BaseType2() {}
    };

    class Type1 : public BaseType1
    {
    public:
        explicit Type1(const std::shared_ptr< BaseType2 >&)
        {
        }
    };

    class Type2 : public BaseType2
    {
    public:
        explicit Type2(const std::shared_ptr< BaseType1 >&)
        {
        }
    };


    class ILoader
    {
    public:
        virtual ~ILoader() {}

        virtual void load() = 0;
    };

    class Loader : public ILoader
    {
    public:
        void load() override {}
    };
    

    class TypeThatNeedsLoader
    {
    public:
        explicit TypeThatNeedsLoader(const std::shared_ptr< ILoader >& dependency)
            : dependency(dependency)
        {
            if (this->dependency == nullptr)
                throw std::runtime_error("dependency cannot be null");
        }

        std::shared_ptr< ILoader > dependency;
    };


    class Initializer
    {
    public:
        explicit Initializer(const std::shared_ptr< TypeThatNeedsLoader >& dependency)
            : dependency(dependency)
        {
            if (this->dependency == nullptr)
                throw std::runtime_error("dependency cannot be null");
        }

        std::shared_ptr< TypeThatNeedsLoader > dependency;
    };


    class IncompleteType;
    class CompleteType {};


    class ForwardDeclaredDependency {};

} // namespace Testing