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