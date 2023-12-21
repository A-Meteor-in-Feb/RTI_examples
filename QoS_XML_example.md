
<!--
RTI Data Distribution Service Deployment
-->
<dds xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
     xsi:noNamespaceSchemaLocation="http://community.rti.com/schema/6.1.2/rti_dds_profiles.xsd">
         
    <!-- Qos Library -->
    <!-- The place for QoS definition: just a placeholder, QoS library and profile are empty -->
    <qos_library name="qosLibrary">
        <qos_profile name="DefaultProfile">
        </qos_profile>
    </qos_library>

    
    <!-- types -->
    <types>
        <const name="MAX_NAME_LEN" type="long" value="64"/>
        <const name="MAX_MSG_LEN"  type="long" value="128"/>

        <!-- The data associated with Topic-HelloWorld consists of 2 strings and 1 long -->
        <struct name="HelloWorld">
            <member name="sender"  type="string"  stringMaxLength="MAX_NAME_LEN"  key="true"/>
            <member name="message" type="string"  stringMaxLength="MAX_MSG_LEN"/>
            <member name="count"   type="long"/>
        </struct>
    </types>

    
    <!-- Domain Library -->
    <!-- The domain section is used to define the system's Topics and the corresponding data types associated with each Topic.
         To define a Topic, the associated data type must be registered with the domain, giving it a registered type name.
         The registered type name is used to refer to that data type within the domain at the time the Topic is defined.--> 
    <domain_library name="MyDomainLibrary" >

        <!-- This configuration file registers the previously defined HelloWorld type under the name HelloWorldType.
             Then it defined a Topic named HelloWorldTopic, whcih is associated with the registered type,
             referring to it by its registered name, HelloWorldType.-->
        <!-- One library can have multiple domains. One domain can have multiple types & topics-->
        <domain name="HelloWorldDomain" domain_id="0">

            <register_type name="HelloWorldType" type_ref="HelloWorld" />
            
            <topic name="HelloWorldTopic" register_type_ref="HelloWorldType">
                <topic_qos name="HelloWorld_qos" base_name="qosLibrary::DefaultProfile"/>
            </topic>
        
        </domain>
    </domain_library>

    
    <!-- Participant library -->
    <domain_participant_library name="MyParticipantLibrary">

        <domain_participant name="PublicationParticipant" domain_ref="MyDomainLibrary::HelloWorldDomain">
            
            <publisher name="MyPublisher">
                <data_writer name="HelloWorldWriter" topic_ref="HelloWorldTopic"/>
            </publisher>
        
        </domain_participant>
        
        <domain_participant name="SubscriptionParticipant" domain_ref="MyDomainLibrary::HelloWorldDomain">
            
            <subscriber name="MySubscriber">
                <data_reader name="HelloWorldReader" topic_ref="HelloWorldTopic">
                    <datareader_qos name="HelloWorld_reader_qos"  base_name="qosLibrary::DefaultProfile"/>
                    <!-- To use a content filter, '&gt;' means greater than it, '&lt;' means less than it
                    <content_filter name="HelloWorldTopic" kind = "builtin.sql">
                        <expression>count &gt; 2</expression>
                    </content_filter>
                     -->                                    
                </data_reader>
            </subscriber>
        
        </domain_participant>
    </domain_participant_library>

</dds>
