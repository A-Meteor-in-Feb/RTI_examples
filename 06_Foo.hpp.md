```c++
#ifndef Foo_982570024_hpp
#define Foo_982570024_hpp
#include <iosfwd>
#include "FooImpl.h"
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef RTIUSERDllExport
#define RTIUSERDllExport __declspec(dllexport)
#endif
#include "dds/domain/DomainParticipant.hpp"
#include "dds/topic/TopicTraits.hpp"
#include "dds/core/SafeEnumeration.hpp"
#include "dds/core/String.hpp"
#include "dds/core/array.hpp"
#include "dds/core/vector.hpp"
#include "dds/core/Optional.hpp"
#include "dds/core/xtypes/DynamicType.hpp"
#include "dds/core/xtypes/StructType.hpp"
#include "dds/core/xtypes/UnionType.hpp"
#include "dds/core/xtypes/EnumType.hpp"
#include "dds/core/xtypes/AliasType.hpp"
#include "rti/core/array.hpp"
#include "rti/util/StreamFlagSaver.hpp"
#include "rti/domain/PluginSupport.hpp"
#include "rti/core/LongDouble.hpp"
#include "rti/core/Pointer.hpp"
#include "rti/topic/TopicTraits.hpp"
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef RTIUSERDllExport
#define RTIUSERDllExport
#endif
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif
class NDDSUSERDllExport Foo {
  public:
    Foo();
    Foo(
        int32_t x_param,
        int32_t y_param);
    #ifdef RTI_CXX11_RVALUE_REFERENCES
    #ifndef RTI_CXX11_NO_IMPLICIT_MOVE_OPERATIONS
    Foo (Foo&&) = default;
    Foo& operator=(Foo&&) = default;
    Foo& operator=(const Foo&) = default;
    Foo(const Foo&) = default;
    #else
    Foo(Foo&& other_) OMG_NOEXCEPT;  
    Foo& operator=(Foo&&  other_) OMG_NOEXCEPT;
    #endif
    #endif 
    int32_t x() const OMG_NOEXCEPT;
    void x(int32_t value);
    int32_t y() const OMG_NOEXCEPT;
    void y(int32_t value);
    bool operator == (const Foo& other_) const;
    bool operator != (const Foo& other_) const;
    void swap(Foo& other_) OMG_NOEXCEPT;
  private:
    int32_t m_x_;
    int32_t m_y_;
};
inline void swap(Foo& a, Foo& b)  OMG_NOEXCEPT 
{
    a.swap(b);
}
NDDSUSERDllExport std::ostream& operator<<(std::ostream& o,const Foo& sample);
class NDDSUSERDllExport MyType {
  public:
    MyType();
    MyType(
        int32_t my_long_param,
        const ::dds::core::string& my_string_param,
        const Foo& my_foo_param,
        const ::dds::core::vector< int32_t>& my_sequence_param,
        const ::dds::core::array< Foo, 5L >& my_array_param,
        const ::dds::core::optional< Foo >& my_optional_param);
    #ifdef RTI_CXX11_RVALUE_REFERENCES
    #ifndef RTI_CXX11_NO_IMPLICIT_MOVE_OPERATIONS
    MyType (MyType&&) = default;
    MyType& operator=(MyType&&) = default;
    MyType& operator=(const MyType&) = default;
    MyType(const MyType&) = default;
    #else
    MyType(MyType&& other_) OMG_NOEXCEPT;  
    MyType& operator=(MyType&&  other_) OMG_NOEXCEPT;
    #endif
    #endif 
    int32_t my_long() const OMG_NOEXCEPT;
    void my_long(int32_t value);
    ::dds::core::string& my_string() OMG_NOEXCEPT; 
    const ::dds::core::string& my_string() const OMG_NOEXCEPT;
    void my_string(const ::dds::core::string& value);
    Foo& my_foo() OMG_NOEXCEPT; 
    const Foo& my_foo() const OMG_NOEXCEPT;
    void my_foo(const Foo& value);
    ::dds::core::vector< int32_t>& my_sequence() OMG_NOEXCEPT; 
    const ::dds::core::vector< int32_t>& my_sequence() const OMG_NOEXCEPT;
    void my_sequence(const ::dds::core::vector< int32_t>& value);
    ::dds::core::array< Foo, 5L >& my_array() OMG_NOEXCEPT; 
    const ::dds::core::array< Foo, 5L >& my_array() const OMG_NOEXCEPT;
    void my_array(const ::dds::core::array< Foo, 5L >& value);
    ::dds::core::optional< Foo >& my_optional() OMG_NOEXCEPT; 
    const ::dds::core::optional< Foo >& my_optional() const OMG_NOEXCEPT;
    void my_optional(const ::dds::core::optional< Foo >& value);
    bool operator == (const MyType& other_) const;
    bool operator != (const MyType& other_) const;
    void swap(MyType& other_) OMG_NOEXCEPT;
  private:
    int32_t m_my_long_;
    ::dds::core::string m_my_string_;
    Foo m_my_foo_;
    ::dds::core::vector< int32_t> m_my_sequence_;
    ::dds::core::array< Foo, 5L > m_my_array_;
    ::dds::core::optional< Foo > m_my_optional_;
};
inline void swap(MyType& a, MyType& b)  OMG_NOEXCEPT 
{
    a.swap(b);
}
NDDSUSERDllExport std::ostream& operator<<(std::ostream& o,const MyType& sample);
struct Color_def {
    enum type {
        RED, 
        GREEN, 
        BLUE
    };
    static type get_default(){ return RED;}
};
typedef ::dds::core::safe_enum< Color_def > Color;
NDDSUSERDllExport std::ostream& operator << (std::ostream& o,const Color& sample);
struct MyUnionDiscriminator_def {
    enum type {
        USE_LONG, 
        USE_STRING, 
        USE_FOO
    };
    static type get_default(){ return USE_LONG;}
};
typedef ::dds::core::safe_enum< MyUnionDiscriminator_def > MyUnionDiscriminator;
NDDSUSERDllExport std::ostream& operator << (std::ostream& o,const MyUnionDiscriminator& sample);
class NDDSUSERDllExport MyUnion {
  public:
    MyUnion();
    #ifdef RTI_CXX11_RVALUE_REFERENCES
    #ifndef RTI_CXX11_NO_IMPLICIT_MOVE_OPERATIONS
    MyUnion (MyUnion&&) = default;
    MyUnion& operator=(MyUnion&&) = default;
    MyUnion& operator=(const MyUnion&) = default;
    MyUnion(const MyUnion&) = default;
    #else
    MyUnion(MyUnion&& other_) OMG_NOEXCEPT;  
    MyUnion& operator=(MyUnion&&  other_) OMG_NOEXCEPT;
    #endif
    #endif 
    MyUnionDiscriminator& _d() ; 
    const MyUnionDiscriminator& _d() const ;
    void _d(const MyUnionDiscriminator& value);
    int32_t my_long() const ;
    void my_long(int32_t value);
    ::dds::core::string& my_string() ; 
    const ::dds::core::string& my_string() const ;
    void my_string(const ::dds::core::string& value);
    Foo& my_foo() ; 
    const Foo& my_foo() const ;
    void my_foo(const Foo& value);
    bool operator == (const MyUnion& other_) const;
    bool operator != (const MyUnion& other_) const;
    static MyUnionDiscriminator default_discriminator();  
    void swap(MyUnion& other_) OMG_NOEXCEPT;
  private:
    MyUnionDiscriminator m_d_;
    struct NDDSUSERDllExport Union_ {
        int32_t m_my_long_;
        ::dds::core::string m_my_string_;
        Foo m_my_foo_;
        Union_();
        Union_(
            int32_t my_long_param,
            const ::dds::core::string& my_string_param,
            const Foo& my_foo_param);
    };
    Union_ m_u_;
};
inline void swap(MyUnion& a, MyUnion& b)  OMG_NOEXCEPT 
{
    a.swap(b);
}
NDDSUSERDllExport std::ostream& operator<<(std::ostream& o,const MyUnion& sample);
class NDDSUSERDllExport MyOtherType {
  public:
    MyOtherType();
    MyOtherType(
        int32_t m1_param,
        double m2_param,
        const ::dds::core::string& m3_param);
    #ifdef RTI_CXX11_RVALUE_REFERENCES
    #ifndef RTI_CXX11_NO_IMPLICIT_MOVE_OPERATIONS
    MyOtherType (MyOtherType&&) = default;
    MyOtherType& operator=(MyOtherType&&) = default;
    MyOtherType& operator=(const MyOtherType&) = default;
    MyOtherType(const MyOtherType&) = default;
    #else
    MyOtherType(MyOtherType&& other_) OMG_NOEXCEPT;  
    MyOtherType& operator=(MyOtherType&&  other_) OMG_NOEXCEPT;
    #endif
    #endif 
    int32_t m1() const OMG_NOEXCEPT;
    void m1(int32_t value);
    double m2() const OMG_NOEXCEPT;
    void m2(double value);
    ::dds::core::string& m3() OMG_NOEXCEPT; 
    const ::dds::core::string& m3() const OMG_NOEXCEPT;
    void m3(const ::dds::core::string& value);
    bool operator == (const MyOtherType& other_) const;
    bool operator != (const MyOtherType& other_) const;
    void swap(MyOtherType& other_) OMG_NOEXCEPT;
  private:
    int32_t m_m1_;
    double m_m2_;
    ::dds::core::string m_m3_;
};
inline void swap(MyOtherType& a, MyOtherType& b)  OMG_NOEXCEPT 
{
    a.swap(b);
}
NDDSUSERDllExport std::ostream& operator<<(std::ostream& o,const MyOtherType& sample);
namespace dds { 
    namespace topic {
        template<>
        struct topic_type_name< Foo > {
            NDDSUSERDllExport static std::string value() {
                return "Foo";
            }
        };
        template<>
        struct is_topic_type< Foo > : public ::dds::core::true_type {};
        template<>
        struct topic_type_support< Foo > {
            NDDSUSERDllExport static void initialize_sample(Foo& sample);
            NDDSUSERDllExport static void register_type(
                ::dds::domain::DomainParticipant& participant,
                const std::string & type_name);
            NDDSUSERDllExport static std::vector<char>& to_cdr_buffer(
                std::vector<char>& buffer,
                const Foo& sample,
                ::dds::core::policy::DataRepresentationId representation
                = ::dds::core::policy::DataRepresentation::auto_id());
            NDDSUSERDllExport static void from_cdr_buffer(Foo& sample, const std::vector<char>& buffer);
            static const ::rti::topic::TypePluginKind::type type_plugin_kind = 
            ::rti::topic::TypePluginKind::NON_STL;
        };
        template<>
        struct topic_type_name< MyType > {
            NDDSUSERDllExport static std::string value() {
                return "MyType";
            }
        };
        template<>
        struct is_topic_type< MyType > : public ::dds::core::true_type {};
        template<>
        struct topic_type_support< MyType > {
            NDDSUSERDllExport static void initialize_sample(MyType& sample);
            NDDSUSERDllExport static void register_type(
                ::dds::domain::DomainParticipant& participant,
                const std::string & type_name);
            NDDSUSERDllExport static std::vector<char>& to_cdr_buffer(
                std::vector<char>& buffer,
                const MyType& sample,
                ::dds::core::policy::DataRepresentationId representation
                = ::dds::core::policy::DataRepresentation::auto_id());
            NDDSUSERDllExport static void from_cdr_buffer(MyType& sample, const std::vector<char>& buffer);
            static const ::rti::topic::TypePluginKind::type type_plugin_kind = 
            ::rti::topic::TypePluginKind::NON_STL;
        };
        template<>
        struct topic_type_name< MyUnion > {
            NDDSUSERDllExport static std::string value() {
                return "MyUnion";
            }
        };
        template<>
        struct is_topic_type< MyUnion > : public ::dds::core::true_type {};
        template<>
        struct topic_type_support< MyUnion > {
            NDDSUSERDllExport static void initialize_sample(MyUnion& sample);
            NDDSUSERDllExport static void register_type(
                ::dds::domain::DomainParticipant& participant,
                const std::string & type_name);
            NDDSUSERDllExport static std::vector<char>& to_cdr_buffer(
                std::vector<char>& buffer,
                const MyUnion& sample,
                ::dds::core::policy::DataRepresentationId representation
                = ::dds::core::policy::DataRepresentation::auto_id());
            NDDSUSERDllExport static void from_cdr_buffer(MyUnion& sample, const std::vector<char>& buffer);
            static const ::rti::topic::TypePluginKind::type type_plugin_kind = 
            ::rti::topic::TypePluginKind::NON_STL;
        };
        template<>
        struct topic_type_name< MyOtherType > {
            NDDSUSERDllExport static std::string value() {
                return "MyOtherType";
            }
        };
        template<>
        struct is_topic_type< MyOtherType > : public ::dds::core::true_type {};
        template<>
        struct topic_type_support< MyOtherType > {
            NDDSUSERDllExport static void initialize_sample(MyOtherType& sample);
            NDDSUSERDllExport static void register_type(
                ::dds::domain::DomainParticipant& participant,
                const std::string & type_name);
            NDDSUSERDllExport static std::vector<char>& to_cdr_buffer(
                std::vector<char>& buffer,
                const MyOtherType& sample,
                ::dds::core::policy::DataRepresentationId representation
                = ::dds::core::policy::DataRepresentation::auto_id());
            NDDSUSERDllExport static void from_cdr_buffer(MyOtherType& sample, const std::vector<char>& buffer);
            static const ::rti::topic::TypePluginKind::type type_plugin_kind = 
            ::rti::topic::TypePluginKind::NON_STL;
        };
    }
}
namespace rti { 
    namespace topic {
        #ifndef NDDS_STANDALONE_TYPE
        template<>
        struct dynamic_type< Foo > {
            typedef ::dds::core::xtypes::StructType type;
            NDDSUSERDllExport static const ::dds::core::xtypes::StructType& get();
        };
        #endif
        template<>
        struct impl_type< Foo > {
            typedef Foo_c type;
        };
        #ifndef NDDS_STANDALONE_TYPE
        template<>
        struct dynamic_type< MyType > {
            typedef ::dds::core::xtypes::StructType type;
            NDDSUSERDllExport static const ::dds::core::xtypes::StructType& get();
        };
        #endif
        template<>
        struct impl_type< MyType > {
            typedef MyType_c type;
        };
        #ifndef NDDS_STANDALONE_TYPE
        template<>
        struct dynamic_type< Color > {
            typedef ::dds::core::xtypes::EnumType type;
            NDDSUSERDllExport static const ::dds::core::xtypes::EnumType& get();
        };
        #endif
        #ifndef NDDS_STANDALONE_TYPE
        template<>
        struct dynamic_type< MyUnionDiscriminator > {
            typedef ::dds::core::xtypes::EnumType type;
            NDDSUSERDllExport static const ::dds::core::xtypes::EnumType& get();
        };
        #endif
        #ifndef NDDS_STANDALONE_TYPE
        template<>
        struct dynamic_type< MyUnion > {
            typedef ::dds::core::xtypes::UnionType type;
            NDDSUSERDllExport static const ::dds::core::xtypes::UnionType& get();
        };
        #endif
        template<>
        struct impl_type< MyUnion > {
            typedef MyUnion_c type;
        };
        #ifndef NDDS_STANDALONE_TYPE
        template<>
        struct dynamic_type< MyOtherType > {
            typedef ::dds::core::xtypes::StructType type;
            NDDSUSERDllExport static const ::dds::core::xtypes::StructType& get();
        };
        #endif
        template<>
        struct impl_type< MyOtherType > {
            typedef MyOtherType_c type;
        };
    }
}
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif
#endif // Foo_982570024_hpp

```

