## Subscription example

### Prep - create user data types using rtiddsgen

same as publication example

### Set up

#### Set up participant

same as publication example

#### Set up subscriber

The needed #includes

```c++
#include <dds/sub/ddssub.hpp>
#include <dds/domain/ddsdomain.hpp>
#include <dds/core/ddscore.hpp>
```

* Set up participant
* Create a Subscriber with each of the available constructors

```c++
    // Create the participant
    dds::domain::DomainParticipant participant(0);
    // Creating a Subscriber with default QoS and no listener
    dds::sub::Subscriber subscriber1(participant);
    // Creating a Subscriber with modified QoS
    dds::sub::qos::SubscriberQos qos;
    qos << dds::core::policy::Presentation::GroupAccessScope(true, false);
    dds::sub::Subscriber subscriber2(participant, qos);
    // Creating a Subscriber with modified QoS and a listener
    auto listener = std::make_shared<ExampleSubscriberListener>();
    dds::sub::Subscriber subscriber3(participant, qos, listener);
    // Creating a Subscriber with modified QoS, a listener, and a sample_rejected() 
    // status mask
    dds::sub::Subscriber subscriber4(
            participant,
            qos,
            listener,
            dds::core::status::StatusMask::sample_rejected());
```

#### Register user data types

Same as the publication

#### Set up topics

Same as the publication

#### Set up data readers

The needed #includes

```c++
#include <dds/sub/ddssub.hpp>
#include <dds/domain/ddsdomain.hpp>
#include <dds/core/ddscore.hpp>
#include <dds/topic/ddstopic.hpp>
#include <dds/pub/ddspub.hpp>
#include "Foo.hpp"
```

* Set up a subscriber
* Set up a Topic
* Create a DataReader of user-defined type Foo with each of the available constructors

```c++
    // Create the Participant
    dds::domain::DomainParticipant participant(0);
    // Create a Topic
    dds::topic::Topic<Foo> topic(participant, "MyTopicName");
    // When not explicitly provided to the constructor, the 
    // created DataReader's QoS is default, has a NULL listener, and a status mask
    // dds::core::status::StatusMask::all()
    // In all of the following constructors 'topic' could also be an instance 
    // of dds::topic::ContentFilteredTopic 
     
    // Creating a DataReader, creating the subscriber inline
    dds::sub::DataReader<Foo> reader1(dds::sub::Subscriber(participant), topic);
    // Create a Subscriber
    dds::sub::Subscriber subscriber(participant);
    // Create a DataReader with modified QoS
    dds::sub::qos::DataReaderQos reader_qos = 
            dds::core::QosProvider::Default().datareader_qos();
    reader_qos << dds::core::policy::History::KeepAll();
    dds::sub::DataReader<Foo> reader2(subscriber, topic, reader_qos);
    // Create a DataReader with the Qos of a topic
    reader_qos = topic.qos(); // Copy the policies in TopicQos into a DataReaderQos
    dds::sub::DataReader<Foo> reader3(subscriber, topic, reader_qos);
    // Create a DataReader with modified QoS and a listener
    std::shared_ptr<ExampleDataReaderListener> listener =
            std::make_shared<ExampleDataReaderListener>();
    dds::sub::DataReader<Foo> reader4(
            subscriber,
            topic,
            reader_qos,
            listener);
    // Create a DataReader with modified QoS, a listener, and a
    // liveliness_changed() status mask
    dds::sub::DataReader<Foo> reader5(
            subscriber,
            topic,
            reader_qos,
            listener,
            dds::core::status::StatusMask::liveliness_changed());
```

#### Set up DataReader to receive data

* Set up a DataReader
* Set up the DataReader wo handle the DDS_DATA_AVAILABLE_STATUS status, in one or both of the following two ways
  * 1)Enable DDS_DATA_AVAILABLE_STATUS for the DDSDataReaderListener associated with the data reader.
    * The processing to handle the status change is done in the DataReaderListener on_data_available() method of the attached listener.
    * Typical processing will *access the received data*.
  * 2)Enable DDS_DATA_AVAILABLE_STATUS for the DDSDtatusCondition associated with the data reader
    * The processing to *handle the status change is done when the data reader's attached status condition is triggered* and the DDS_DATA_AVAILABLE_STATUS status on the data reader is changed.
    * Typical processing will *access the received data*.

##### 1. Enable DDS_DATA_AVAILABLE_STATUS for the DDSDataReaderListener associated with the data reader.

**Changing the listener and enabling/disabling statues associated with it**:

The listener for an entity can be specified at the entity creation time. By default the listener is *enabled* for all the statuses supported by the entity.

Once an entity has been created, its listener and/or the statuses for which it is enabled can be manipulated as follows.

The following examples use a DomainParticipant but the same examples  can be applied to all other entities (Subscribers, Publishers,  DataReaders, DataWriters, and Topics).

* user defines entity listener methods

  ```c++
  class ExampleDomainParticipantListener : public dds::domain::NoOpDomainParticipantListener
  {
  public:
      ExampleDomainParticipantListener() {}
  public:
      void on_liveliness_lost(
         dds::pub::AnyDataWriter&,
         const::dds::core::status::LivelinessLostStatus&)
      {
          std::cout << "on_liveliness_lost" << std::endl;
      }
      void on_liveliness_changed(
         dds::sub::AnyDataReader&,
         const dds::core::status::LivelinessChangedStatus&)
      {
          std::cout << "on_liveliness_changed" << std::endl;
      }
      void on_inconsistent_topic(
         dds::topic::AnyTopic&,
         const dds::core::status::InconsistentTopicStatus&)
      {
          std::cout << "on_inconsistent_topic" << std::endl;
      }
      void on_data_on_readers(
         dds::sub::Subscriber&)
      {
          std::cout << "on_data_on_readers" << std::endl;
      }
      void on_offered_deadline_missed(
         dds::pub::AnyDataWriter&,
         const::dds::core::status::OfferedDeadlineMissedStatus&)
      {
          std::cout << "on_offered_deadline_missed" << std::endl;
      }
      void on_offered_incompatible_qos(
         dds::pub::AnyDataWriter&,
         const::dds::core::status::OfferedIncompatibleQosStatus&)
      {
          std::cout << "on_offered_incompatible_qos" << std::endl;
      }
      void on_publication_matched(
         dds::pub::AnyDataWriter&,
         const::dds::core::status::PublicationMatchedStatus&)
      {
          std::cout << "on_publication_matched" << std::endl;
      }
      void on_requested_deadline_missed(
         dds::sub::AnyDataReader&,
         const dds::core::status::RequestedDeadlineMissedStatus&)
      {
          std::cout << "on_requested_deadline_missed" << std::endl;
      }
      void on_requested_incompatible_qos(
         dds::sub::AnyDataReader&,
         const dds::core::status::RequestedIncompatibleQosStatus&)
      {
          std::cout << "on_requested_incompatible_qos" << std::endl;
      }
      void on_sample_lost(
         dds::sub::AnyDataReader&,
         const dds::core::status::SampleLostStatus&)
      {
          std::cout << "on_sample_lost" << std::endl;
      }
      void on_sample_rejected(
         dds::sub::AnyDataReader&,
         const dds::core::status::SampleRejectedStatus&)
      {
          std::cout << "on_sample_rejected" << std::endl;
      }
      void on_subscription_matched(
         dds::sub::AnyDataReader&,
         const dds::core::status::SubscriptionMatchedStatus&)
      {
          std::cout << "on_subscription_matched" << std::endl;
      }
      void on_data_available(
         dds::sub::AnyDataReader&)
      {
          std::cout << "on_data_available" << std::endl;
      }
  };
  ```

* Get an entity's listener

  ```c++
      ExampleDomainParticipantListener *listener = new ExampleDomainParticipantListener;
      dds::domain::DomainParticipant participant(
         0, dds::domain::qos::DomainParticipantQos(), listener);
      dds::domain::DomainParticipantListener *retrieved_listener = participant.listener();
  ```

* Enable statues for the listener

  ```c++
      // The default constructor creates an empty StatusMask
      dds::core::status::StatusMask enabled_status_list; 
      // ...
      // Add more statuses to the enabled_status_list
      enabled_status_list |= dds::core::status::StatusMask::liveliness_changed() |
          dds::core::status::StatusMask::offered_incompatible_qos();
  ```

* Disable a status for the listener

  ```c++
      enabled_status_list &= ~dds::core::status::StatusMask::offered_incompatible_qos();
  ```

* Set an entity's listener and only enable the listener for the statuses specified by the enabled_status_list.

  ```c++
      participant.listener(listener, enabled_status_list);
  ```

##### 2. Enable DDS_DATA_AVAILABLE_STATUS for the DDSDtatusCondition associated with the data reader

**Enabling/Disabling statuses associated with a status condition**

Upon entity creation, by default, all the statuses are *enabled* for the DDS_StatusCondition associated with the entity.

Once an entity has been created, the list of statuses for which the  DDS_StatusCondition is triggered can be manipulated as follows.

* Given an entity and the associated status_condition

  ```c++
      ExampleDomainParticipantListener *listener = new ExampleDomainParticipantListener;
      dds::domain::DomainParticipant participant(
         0, dds::domain::qos::DomainParticipantQos(), listener);
      dds::core::cond::StatusCondition status_condition(participant);
  ```

* Get the list of statuses enabled for the status_condition

  ```c++
      dds::core::status::StatusMask enabled_status_list = status_condition.enabled_statuses();
  ```

* Check is a given status is enabled for the status_condition

  ```c++
      // StatusMask inherits from std::bitset. You can use std::bitset's any() 
      // method to check if a given status is enabled
      if ((enabled_status_list & dds::core::status::StatusMask::data_on_readers()).any()) {
          // Do something to handle the on_data_on_readers status...
      }
  ```

* Enable statuses for the status_condition

  ```c++
      status_condition.enabled_statuses(
         dds::core::status::StatusMask::inconsistent_topic() | 
         dds::core::status::StatusMask::sample_rejected());
  ```

* Disable statuses for the status_condition

  ```c++
      status_condition.enabled_statuses(
         ~dds::core::status::StatusMask::inconsistent_topic());
  ```

##### 2.2 Waiting for the Condition(s) to trigger

You have two ways to wait for the conditions to trigger: wait or dispatch

* Wait example

  ```c++
      // Wait for at most 20 seconds until one or more conditions are active and
      // then return them.
      // In case of timeout, active_conditions will be empty.
      dds::core::cond::WaitSet::ConditionSeq active_conditions =
          waitset.wait(dds::core::Duration::from_secs(20));
      for (uint32_t i = 0; i < active_conditions.size(); i++) {
          if (active_conditions[i] == guard_cond) {
              std::cout << "guard_cond was triggered\n";
          } else if (active_conditions[i] == status_cond) {
              std::cout << "status_cond was triggered\n";
          } // ...
      }
  ```

* Dispatch example

  ```c++
      using dds::core::cond::Condition;
      using dds::sub::cond::ReadCondition;
      // create a WaitSet
      dds::core::cond::WaitSet waitset;
      // Create a ReadCondition for reader1 with a functor handler
      ReadCondition read_cond1(reader1, dds::sub::status::DataState::any(), []() {
          std::cout << "read_cond1 was triggered\n";
      });
      ReadCondition read_cond2(
              reader2,
              dds::sub::status::DataState::any(),
              [](Condition c) {  // The handler can optionally
                                 // receive the condition
                  auto rc = dds::core::polymorphic_cast<ReadCondition>(c);
                  auto reader = rc.data_reader();  // reader == reader2
                  std::cout << "read_cond2 was triggered (topic is "
                            << reader.topic_name() << ")" << std::endl;
              });
      // Attach conditions
      waitset += read_cond1;
      waitset += read_cond2;
      // Wait at most 20 seconds until one or more conditions are active and
      // then call the handler of the active conditions. You can repeat this in
      // a loop.
      waitset.dispatch(dds::core::Duration::from_secs(20));
  ```

##### 3. Accessing Received Data

##### 3.1 Reading data samples

You can read data samples from a DataReader by receiving a loan,  inspecting the samples and then returning the loan, or you can directly  copy them.

* To iterate through loaned data samples in your application you will use a LoanedSamples container. The following code shows different ways to use this container

  ```c++
      // Take all the samples in the reader queue (if you don't want to remove
      // them from the queue and read them later again, use reader.read() instead)
      dds::sub::LoanedSamples<Foo> samples = reader.take();
      // LoanedSamples<Foo> is a container of LoanedSample<Foo> elements, which
      // contain the actual data (Foo) and the SampleInfo
      for (dds::sub::LoanedSamples<Foo>::iterator sample_it = samples.begin();
           sample_it != samples.end();
           ++sample_it) {
          if (sample_it->info().valid()) {
              std::cout << "Received: " << sample_it->data() << std::endl;
          }
      }
      // The previous code is simpler with a range-based for-loop (C++11)
      for (const auto& sample : samples) {
          if (sample.info().valid()) {
              std::cout << "Received: " << sample.data() << std::endl;
          }
      }
      // If you don't need to access the SampleInfo in invalid-data samples,
      // use valid_data() to simplify the for loop
      auto valid_samples = rti::sub::valid_data(reader.take());
      for (const auto& sample : valid_samples) {
          // No need to check sample.info().valid()
          std::cout << "Received: " << sample.data() << std::endl;
      }
      // You can also access samples using the subscript operator
      if (samples.length() >= 2) {
          if (samples[1].info().valid()) {
              std::cout << "Second sample is " << samples[1].data() << std::endl;
          } else {
              std::cout << "Second sample is invalid\n";
          }
      }
      // You can copy the samples using std::copy:
      std::vector<rti::sub::LoanedSample<Foo> > samples_copy;
      std::copy(samples.begin(), samples.end(), std::back_inserter(samples_copy));
      // You can also access the data directly. A sample can be implicitly
      // converted into a reference to its data type as long as it contains
      // valid data.
      //
      // The iterator returned by this other overload of valid_data provides
      // another way to skip invalid-data samples
      //
      std::vector<Foo> data_copy;
      std::copy(
          rti::sub::valid_data(samples.begin()),
          rti::sub::valid_data(samples.end()),
          std::back_inserter(data_copy));
      // Attempting to access invalid data will result in an exception.
      try {
          // The following will throw if !samples[0].info().valid()
          Foo data = samples[0].data();
          std::cout << data << std::endl;
          // The following will throw if any sample contains invalid data
          std::copy(samples.begin(), samples.end(), std::back_inserter(data_copy));
      } catch (const dds::core::PreconditionNotMetError& ex) {
          std::cerr << "Attempted to access sample containing invalid data: "
                    << ex.what() << std::endl;
      }
      // You can also apply other iterator-based algorithms,
      // like this example that prints just one field of the data type
      // (assuming that Foo contains an integer field called 'x')
      std::transform(
          rti::sub::valid_data(samples.begin()),
          rti::sub::valid_data(samples.end()),
          std::ostream_iterator<int>(std::cout, ", "),
          [](const Foo& data) { return data.x(); });
      // Once a LoanedSamples object goes out of scope its destructor
      // automatically returns the loan to the middleware. If you need to
      // explicitly return it, call return_loan()
      //
      // samples.return_loan()
  ```

* Although the LoanedSamples is the most generic way to access data in a  DataReader, for convinience other overloaded versions of read/take allow to directly copy the data

  ```c++
      // The first version of read/take receives a back-insert iterator
      std::vector<dds::sub::Sample<Foo> > my_vector1;
      reader.take(std::back_inserter(my_vector1));
      // The second version receives a forward iterator and the maximum size
      std::vector<dds::sub::Sample<Foo> > my_vector2(10);
      reader.take(my_vector2.begin(), 10);
  ```

##### 3.2 Selecting what samples to read

The functions [read()](https://community.rti.com/static/documentation/connext-dds/6.1.2/doc/api/connext_dds/api_cpp2/classdds_1_1sub_1_1DataReader.html#a98dec1c877cf53e47890cf44b0021274) and [take()](https://community.rti.com/static/documentation/connext-dds/6.1.2/doc/api/connext_dds/api_cpp2/classdds_1_1sub_1_1DataReader.html#a1d38fa7050790fd33745d6e45dc1b55c) select all samples in the DataReader queue. The function select()  allows specifying different criteria about the data to read. A  equivalent API, using the streaming >> operator is available too.

* select() example

  ```c++
      // To select what samples you want to read (or take) from a DataReader
      // queue, you can use a Selector. When you don't specify a parameter in the
      // Selector, the default applies.
      dds::sub::LoanedSamples<Foo> samples =
          // Call select() to create a Selector and then specify its parameters
          reader.select()
              // Specifies the maximum number of samples to read/take
              // in this function call. Default: set by Qos.
              .max_samples(20)
              // Specifies the sample, view and instance states - default: all.
              .state(dds::sub::status::DataState::new_instance())
              // Specifies a query on the data sample - default: all
              .content(dds::sub::Query(reader, "x > 10"))
              // Specifies what instance to read - default: all instances
              .instance(my_instance_handle)
              // And finally call read() or take()
              .take();
      // You can also specify state and content by using a Condition. Reusing
      // a Condition for multiple reads is more efficient than specifying the
      // content() every time.
      dds::sub::cond::QueryCondition query_condition(
          dds::sub::Query(reader, "x > 10"),
          dds::sub::status::DataState(
              dds::sub::status::SampleState::not_read(),
              dds::sub::status::ViewState::new_view(),
              dds::sub::status::InstanceState::alive()));
      samples = reader.select()
          .condition(query_condition)
          .take();
      // And you can read instance by instance using next_instance().
      //
      // To read the first instance, use InstanceHandle::nil()
      dds::core::InstanceHandle previous_handle = dds::core::InstanceHandle::nil();
      do {
          samples = reader.select()
              .next_instance(previous_handle)
              .take();
          if (samples.length() > 0) {
              // do something with samples ...
              // Update previous_handle to read the instance following this one
              previous_handle = samples[0].info().instance_handle();
          }
      } while (samples.length() > 0);
      // select() returns an object you can reuse
      dds::sub::DataReader<Foo>::Selector selector = reader.select().max_samples(20);
      samples = selector.read();
      // ...
      selector.state(dds::sub::status::DataState::new_instance());
      samples = selector.take();
  
  ```

* Streaming example

  ```c++
      using namespace dds::sub;
      // The overloaded shift operator defines a domain-specific language to
      // specify what samples to read. The following code has the same effect as
      // the first select() example from the previous code snippet
      LoanedSamples<Foo> samples;
      reader >> take // first indicate if you want to read or take;
             >> max_samples(20) // then specify the parameters you want...
             >> state(status::DataState::new_instance())
             >> content(Query(reader, "x > 10"))
             >> instance(my_instance_handle)
             >> samples; // and finally, the destination LoanedSamples container.
  ```

##### 3.3 Reading samples using coherent access

If a Subscriber's PresentationQosPolicy access_scope is GROUP and  ordered_access is true, the application can access the samples in order  across DataWriters of the same group (Publisher with access_scope  GROUP). The queue is ordered/sorted per topic across all instances  belonging to DataWriters (or DataReaders) within the same Publisher (or  Subscriber).

* Read samples using CoherentAccess

  ```c++
  void howto_read_coherently()
  {
      dds::domain::DomainParticipant participant(0);
      dds::topic::Topic<Foo> topic1(participant, "Topic1");
      dds::topic::Topic<Foo> topic2(participant, "Topic2");
      // Create a Subscriber with group presentation. The Publisher must also
      // have group presentation set in its QoS
      dds::sub::qos::SubscriberQos subscriber_qos;
      subscriber_qos << dds::core::policy::Presentation::GroupAccessScope(false, true);
      dds::sub::Subscriber subscriber(participant, subscriber_qos);
      dds::sub::DataReader<Foo> reader1(subscriber, topic1);
      dds::sub::DataReader<Foo> reader2(subscriber, topic2);
      // Assuming that a writer of "Topic1" wrote before the writer of "Topic2"
      // reader2 will only be able to access it's samples after reader1 takes 
      // its sample as long as CoherentAccess to the samples has been started
      int sample_count = read_coherently(subscriber, reader2);
      std::cout << sample_count << std::endl; // will be 0
      // The CoherentAccess destructor called when read_coherently exited 
      // will end coherent access to the samples. 
      // You can also explicitly call coherent_access.end() to end coherent access
      // reader2 can now access its sample 
      // ordered_samples.size() will = 1 
      dds::sub::LoanedSamples<Foo> ordered_samples = reader2.take();
  }
  template <typename T>
  int read_coherently(dds::sub::Subscriber& subscriber, dds::sub::DataReader<T>& reader)
  {
      dds::sub::CoherentAccess coherent_access(subscriber);
      dds::sub::LoanedSamples<T> ordered_samples = reader.take();
      return ordered_samples.length();
  }
  ```

### Adjust the desired quality of service (QoS)

same as publication

### Receive data

Read all samples or select which samples to read from the DataReader queue

see 3.1 & 3.2

### Tear down

tear down all entities

same as publica
