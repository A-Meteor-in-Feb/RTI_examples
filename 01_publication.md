## Publication Example

### Pre: Create user data types using rtiddsgen

#### Usage

The code generator tool can be executed using the rtiddsgen script  located under \<RTI Connext Home>/bin or by clicking on the "Code  generator" button in the Utility tab of RTI Connext Launcher.

#### Description

rtiddsgen takes a language-independent specification of the data (in  IDL, XML, or XSD notation) and generates supporting classes and code to  distribute instances of the data over RTI Connext.

To use rtiddsgen, you must first write a description of your data types in IDL, XML, or XSD format.

#### C++ Example

The following is an example that generates the RTI Connext type myDataType:

**XML notation**

```xml
<?xml version="1.0" encoding="UTF-8"?>
<types xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" 
        xsi:noNamespaceSchemaLocation="rti_dds_topic_types.xsd">
    <struct name="myDataType">
        <member name="value" type="long"/>
    </struct>
</types>
```

Assuming the name of the IDL file is myFileName.(idl|xml|xsd), all you need to do is type:

rtiddsgen myFileName.(idl|xml|xsd)

This generates myFileName.cxx, myFileName.h, myFileNamePlugin.cxx,  myFileNamePlugin.h, myFileNameSupport.cxx and myFileNameSupport.h. By  default, rtiddsgen will not overwrite these files. You must use the  -replace argument to do that.

**XML language**

The data types can be described using XML.

RTI Connext provides DTD and XSD files that describe the XML format.

The DTD definition of the XML elements can be found in [rti_dds_topic_types.dtd](https://community.rti.com/static/documentation/connext-dds/6.1.2/resource/app/app_support/rtiddsgen/schema/rti_dds_topic_types.dtd) under <NDDSHOME>/resource/app/app_support/rtiddsgen/schema.

The XSD definition of the XML elements can be found in [rti_dds_topic_types.xsd](https://community.rti.com/static/documentation/connext-dds/6.1.2/resource/app/app_support/rtiddsgen/schema/rti_dds_topic_types.xsd) under <NDDSHOME>/resource/app/app_support/rtiddsgen/schema.

The XML validation performed by rtiddsgen always uses the DTD  definition. If the <!DOCTYPE> tag is not present in the XML file,  rtiddsgen will look for the DTD document under  <NDDSHOME>/resource/app/app_support/rtiddsgen/schema. Otherwise,  it will use the location specified in <!DOCTYPE>.

#### Using Generated Types Without RTI Connext (Standalone)

You can use the generated type-specific source and header files  without linking the RTI Connext libraries or even including the RTI  Connext header files. That is, the generated files for your data types  can be used standalone.

The directory  <NDDSHOME>resource/app/app_support/rtiddsgen/standalone/include  contains the helper files required to work in standalone mode: 

- include: header and templates files for C/C++. 
- src: source files for C/C++. 
- class: Java jar file.

**Using Standalone Types in C++**

The generated files that can be used standalone are: 

- <idl file name>.cxx : Types source file 
- <idl file name>.h : Types header file

You *cannot* use the type plugin (<idl file>Plugin.cxx  <idl file>Plugin.h) or the type support (<idl  file>Support.cxx <idl file>Support.h) code standalone.

To use the generated types in a standalone manner: 

- Include the directory  <NDDSHOME>resource/app/app_support/rtiddsgen/standalone/include in the list of directories to be searched for header files. 
- Add the source files ndds_standalone_type.cxx and <idl file name>.cxx to your project. 
- Include the file <idl file name>.h in the source files that will use the generated types in a standalone way. 
- Compile the project using the two following preprocessor definitions: 
  - NDDS_STANDALONE_TYPE 
  - The definition for your platform: RTI_VXWORKS, RTI_QNX, RTI_WIN32, RTI_INTY, RTI_LYNX or RTI_UNIX 

### Set up

#### Set up participant

The needed #includes:

```c++
#include <dds/domain/ddsdomain.hpp>
```

How to create DomainParticipants with each of the available constructors

```c++
    
    // Creating a DomainParticipants on domain 0, with default Qos, and no
    // listener
    dds::domain::DomainParticipant participant1(0) ;
    // Creating a DomainParticipants with a non-default QoS values
    dds::domain::qos::DomainParticipantQos qos;
     // Set the initial peers. 
     // The peers stored in initial_peers are merely potential peers--there is 
     // no requirement that the peer DomainParticipants are actually up and
     // running or even will eventually exist. The Connext discovery process 
     // will try to contact all potential peer participants in the list 
     // periodically using unicast transports. 
     const char * initial_peers_array[] = {
       "host1",
       "10.10.30.192",
       "1@localhost",        
       "2@host2",
       "my://", /* all unicast addrs on transport plugins with alias "my" */
       "2@shmem://", /* shared memory */
       "FF00:ABCD::0",
       "1@FF00:0:1234::0",
       "225.1.2.3",
       "3@225.1.0.55",
       "FAA0::0#0/0/R"};
    const dds::core::StringSeq initial_peers_list(initial_peers_array, initial_peers_array+11);
    // Add the initial peers list to the DiscoveryQosPolicy while modifying
    // the participant's qos inline
    qos << rti::core::policy::Discovery().initial_peers(initial_peers_list);
    // Creating a DomainParticipants on domain 1 with modified QoS
    dds::domain::DomainParticipant participant2(1, qos);
    // Creating a DomainParticipants on domain 2, with modified QoS, and a
    // listener
    auto listener = std::make_shared<ExampleParticipantListener>();
    dds::domain::DomainParticipant participant3(2, qos, listener);
    // Creating a DomainParticipants on domain 3, with modified QoS, a listener
    // and a data_available() status mask
    dds::domain::DomainParticipant participant4(
            3,
            qos,
            listener,
            dds::core::status::StatusMask::data_available());
```

Setting the DomainParticipantFactoryQoS so that participants are created disabled(optional)

```c++
    dds::domain::qos::DomainParticipantFactoryQos qos;
    qos << dds::core::policy::EntityFactory::ManuallyEnable();
    dds::domain::DomainParticipant::participant_factory_qos(qos);
```

#### set up publisher

The needed #includes

```c++
#include <dds/pub/ddspub.hpp>
#include <dds/domain/ddsdomain.hpp>
#include <dds/core/ddscore.hpp>
```

* Set up participant
* Create a Publisher with each of the available constructors

```c++
    // Create the participant
    dds::domain::DomainParticipant participant(0);
    // When not explicitly provided to the constructor, the 
    // created publisher's QoS is default, has a NULL listener, and a status mask
    // dds::core::status::StatusMask::all()
    // Creating a publisher
    dds::pub::Publisher publisher1(participant);
    // Creating a publisher with modified QoS
    dds::pub::qos::PublisherQos qos;
    qos << rti::core::policy::EntityName("PublisherName");
    dds::pub::Publisher publisher2(participant, qos);
    // Creating a publisher with modified QoS and a listener
    auto listener = std::make_shared<ExamplePublisherListener>();
    dds::pub::Publisher publisher3(participant, qos, listener);
    // Creating a publisher with modified QoS, a listener, and a
    // sample_rejected() status mask
    dds::pub::Publisher publisher4(
            participant,
            qos,
            listener,
            dds::core::status::StatusMask::offered_deadline_missed());
```

#### Register user data type(s)

Types are implicitly registered during Topic construction, see Setting up a Topic

#### Set up topics

The needed #includes:

```c++
#include <dds/domain/ddsdomain.hpp>
#include <dds/core/ddscore.hpp>
#include <dds/topic/ddstopic.hpp>
#include "Foo.hpp"
```

* Set up a DomainParticipant
* Create a Topic with each of the available constructors

```c++
    // Create the participant
    dds::domain::DomainParticipant participant(0);
    // Creating a topic with user-defined type Foo and topic name MyTopic1,
    // with default Qos and no listener
    dds::topic::Topic<Foo> topic1(participant, "MyTopic1");
    // Creating a topic with user-defined type Foo, topic name MyTopic1, 
    // type name MyTypeName
    dds::topic::Topic<Foo> topic2(participant, "MyTopic2", "MyTypeName2");
    // Creating a topic with user-defined type Foo, topic name MyTopic3, and
    // modified QoS
    dds::topic::qos::TopicQos qos;
    qos << dds::core::policy::Durability::TransientLocal();
    dds::topic::Topic<Foo> topic3(participant, "MyTopic3", qos);
    // Creating a topic with user-defined type Foo, topic name MyTopic4, type 
    // name MyTypeName4 and modified QoS
    dds::topic::Topic<Foo> topic4(participant, "MyTopic4", "MyTypeName4", qos);
    // Creating a topic with user-defined type Foo, topic name MyTopic5, 
    // modified QoS, and a listener
    auto listener = std::make_shared<ExampleTopicListener>();
    dds::topic::Topic<Foo> topic5(participant, "MyTopic5", qos, listener);
    // Creating a topic with user-defined type Foo, topic name MyTopic6, type
    // name MyTypeName6, modified QoS, and a listener
    dds::topic::Topic<Foo> topic6(
       participant, "MyTopic6", "MyTypeName6", qos, listener);
    // Creating a topic with user-defined type Foo, topic name MyTopic7, 
    // modified QoS, a non-NULL listener, and a inconsistent_topic status mask
    dds::topic::Topic<Foo> topic7(
       participant, "MyTopic7", qos, listener, 
       dds::core::status::StatusMask::inconsistent_topic());
    // Creating a topic with user-defined type Foo, topic name MyTopic8, type
    // name MyTypeName8, modified QoS, a listener, and
    // a inconsistent_topic status mask
    dds::topic::Topic<Foo> topic8(
       participant, "MyTopic8", "MyTypeName8", qos, listener, 
       dds::core::status::StatusMask::inconsistent_topic());

```

#### Set up data writer(s)

The needed #includes:

```c++
#include <dds/pub/ddspub.hpp>
#include <dds/domain/ddsdomain.hpp>
#include <dds/core/ddscore.hpp>
#include <dds/topic/ddstopic.hpp>
#include <dds/sub/ddssub.hpp>
#include "Foo.hpp"
```

* Set up a Publisher
* Set up a Topic
* Create a DataWriter of user-defined type Foo with each of the available constructors

```c++
    // Create the Participant
    dds::domain::DomainParticipant participant(0);
    // Create a Topic
    dds::topic::Topic<Foo> topic(participant, "MyTopicName");
    // When not explicitly provided to the constructor, the 
    // created DataWriter's QoS is default, has a NULL listener, and a status mask
    // dds::core::status::StatusMask::all()
    // Creating a DataWriter, creating the subscriber inline
    dds::pub::DataWriter<Foo> writer1(dds::pub::Publisher(participant), topic);
    // Create a Publisher
    dds::pub::Publisher publisher(participant);
    // Create a DataWriter with modified QoS
    dds::pub::qos::DataWriterQos writer_qos = 
            dds::core::QosProvider::Default().datawriter_qos();
    writer_qos << dds::core::policy::Liveliness::ManualByParticipant();
    dds::pub::DataWriter<Foo> writer2(publisher, topic, writer_qos);
    // Create a DataWriter with the Qos of a topic
    writer_qos = topic.qos(); // Copy the policies in TopicQos into a DataWriterQos
    dds::pub::DataWriter<Foo> writer3(publisher, topic, writer_qos);
    // Create a DataWriter with modified QoS and a listener
    auto listener = std::make_shared<ExampleDataWriterListener<Foo>>();
    dds::pub::DataWriter<Foo> writer4(
       publisher, 
       topic, 
       writer_qos, 
       listener);
    // Create a DataWriter with modified QoS, a listener, and a liveliness_lost() 
    // status mask
    dds::pub::DataWriter<Foo> writer5(
       publisher, 
       topic, 
       writer_qos, 
       listener, 
       dds::core::status::StatusMask::liveliness_lost());
```

### Adjust the desired quality of service (QoS)

The needed #include

```c++
#include <dds/domain/ddsdomain.hpp>
```

The QoS for an entity can be specified at entity creation time. Once an  entity has been created, its QoS can be manipulated as the following  examples illustrate. A DataWriter is used in these examples, but the  same can be applied to any reference-type, such as DomainParticipants, Subscribers, Publishers, DataReaders, and Topics.

* See [QosProvider](https://community.rti.com/static/documentation/connext-dds/6.1.2/doc/api/connext_dds/api_cpp2/group__DDSQosProviderExampleModule.html) for examples on how to manage user-defined QoS profiles. 

* See [Qos Use Cases](https://community.rti.com/static/documentation/connext-dds/6.1.2/doc/api/connext_dds/api_cpp2/group__DDSQosExampleModule.html) for examples on how to work with the Qos policy classes. 

* Get an entity's QoS settings

  ```c++
      dds::pub::DataWriter<Foo> writer(dds::pub::Publisher(participant), a_topic); 
      // Get the DataWriter's QoS 
      dds::pub::qos::DataWriterQos writer_qos = writer.qos();
  ```

* Change the desired QoS policy fields

  ```c++
      // Change the History QoS for the DataWriter using the History QoS's 
      // KeepAll named constructor
      writer_qos << dds::core::policy::History::KeepAll();
  ```

* Set the QoS

  ```c++
      // Set the modified QoS for the DataWriter
      writer.qos(writer_qos);
  ```

### Send data

* Set up a DataWriter

* Register an instance

* Write instances of type Foo

  ```c++
      Foo data;
      dds::core::InstanceHandle handle = 
          dds::core::InstanceHandle::nil();
      dds::core::Time timestamp(123);
      // Write a sample 
      writer.write(data);
      // You can also write a sample with a timestamp that will be used as the 
      // source timestamp for this sample
      writer.write(data, timestamp);
      // You can also write a sample with an InstanceHandle
      writer.write(data, handle);
      // The above call to write is equivalent to the following
      writer.write(dds::topic::TopicInstance<Foo>(handle, data));
      // Or a combination of handle and timestamp
      writer.write(data, handle, timestamp);
      // The above call to write is equivalent to the following
      writer.write(dds::topic::TopicInstance<Foo>(handle, data), timestamp);
      // Create a vector of three default-constructed samples
      std::vector<Foo> samples(3, Foo());
      // You can also write samples that are stored in a container by 
      // passing in an iterator range to write()
      writer.write(samples.begin(), samples.end());
      // You can add a timestamp to the above call to write
      writer.write(samples.begin(), samples.end(), timestamp);
      // Create a vector of three instance handles
      std::vector<dds::core::InstanceHandle> handles(
         3, dds::core::InstanceHandle::nil());
      // Write 3 samples along with their handles
      writer.write(samples.begin(), samples.end(), 
                   handles.begin(), handles.end());
      // You can add a timestamp to the above call to write
      writer.write(samples.begin(), samples.end(), 
                   handles.begin(), handles.end(), 
                   timestamp);
      // You can also use operator << to write samples
      writer << Foo(1, 2)
             << std::make_pair(Foo(3, 4), timestamp) // add a timestamp
             << std::make_pair(Foo(5, 6), handle); // add an instance handle
  ```

### Tear down

The following examples use a DomainParticipant to show the various  patterns which exist to tear down an entity, but the same examples can  also be applied when shutting down Subscribers, Publishers, DataReaders, DataWriters, and Topics

* Let all references to a given entity go out-of-scope and let the destructor take care of entity clean up

  ```c++
  {
      {
          // Create a participant on domain 0
          dds::domain::DomainParticipant participant(0);
          
          // ...
      } // participant destroyed here
      // found_participant will equal dds::core::null because the participant's
      // destructor was called when the only reference to it went out of scope
      dds::domain::DomainParticipant found_participant = dds::domain::find(0);
  }
  ```

* Explicitly call close() on one of the existing references to an Entity

  ```c++
      // Create a participant on domain 0
      dds::domain::DomainParticipant participant(0);
      // All Entities are Reference types, meaning that the assignment operator
      // will not make a copy of the participant, but instead will just create 
      // another reference to the previously created participant 
      dds::domain::DomainParticipant same_participant = participant;
      // Call close() on same_participant to explicitly destroy the participant.
      // Both references (participant and same_participant) are now invalid.
      same_participant.close();
      try {
          // Any attempt to use the closed participant, will cause a 
          // dds::core::AlreadyClosedError exception
          participant.enable();
      }
      catch (dds::core::AlreadyClosedError& ex) {
          std::cout << "Expected AlreadyClosedError: " << ex.what() << std::endl;
      }
  ```

* Assigning dds::core::null to a variable has the same effect as if the reference went out of scope. Assigning dds::core::null to the last reference destroys the underlying object.

  ```c++
      // Create a reference to a null participant
      dds::domain::DomainParticipant participant1(dds::core::null);
      // Now create a participant on domain 0
      dds::domain::DomainParticipant participant2(0);
      // Assign participant1 to this valid participant
      participant1 = participant2;
      // Assign dds::core:null to participant2. The participant will not be 
      // destroyed because participant1 is still a valid reference
      participant2 = dds::core::null;
      // We can still use the participant because participant1 is still a 
      // valid reference
      dds::domain::qos::DomainParticipantQos qos = 
          participant1.default_participant_qos();
      // Assigning dds::core::null to the only remaining reference to the 
      // participant will now cause its destructor to be called
      participant1 = dds::core::null;
      // found_participant will equal dds::core::null because the previous
      // assignment to dds::core::null caused the participant to be destroyed
      dds::domain::DomainParticipant found_participant = dds::domain::find(0);
  ```

* Retaining and then destroying an Entity

  ```c++
  void howto_teardown_retain()
  {
      // To prevent participant destruction when all references go out of scope 
      // you can call retain().
      const uint32_t domain_id_0 = 0;
      const uint32_t domain_id_1 = 1;
      create_and_retain_participant(domain_id_0, false);
      create_and_retain_participant(domain_id_1, true);
      // We did not retain the participant with domain_id_0, so the following 
      // will result in participant0 == dds::core::null
      dds::domain::DomainParticipant participant0 = dds::domain::find(domain_id_0);
      // We can recover the participant with domain_id_1 using find() because we 
      // retained it. participant1 will be a valid reference to 
      // the participant that was created on domain 1
      dds::domain::DomainParticipant participant1 = dds::domain::find(domain_id_1);
      // Because we called retain on the participant, the only way to destroy
      // the participant is to explicitly call close() on a reference to the
      // participant. Any attempt to use the participant after calling 
      // close will cause a dds::core::AlreadyClosedError exception to be thrown
      // Destroy the participant
      participant1.close();
      try {
          // This call will cause a dds::core::AlreadyClosedError exception
          participant1.enable();
      }
      catch (dds::core::AlreadyClosedError& ex) {
          std::cout << "Expected AlreadyClosedError: " << ex.what() << std::endl;
      }
       
  }
  void create_and_retain_participant(const uint32_t domain_id, bool retain)
  {
      // Create and retain a participant. If retained, the participant will not 
      // be destroyed when it goes out of scope and can be retrieved again
      dds::domain::DomainParticipant participant(domain_id);
      if (retain) {
          participant.retain();
      }
  }
  ```

  

