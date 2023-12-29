
#include <iostream>

#include <dds/pub/ddspub.hpp>
#include <rti/util/util.hpp>      // for sleep()
#include <rti/config/Logger.hpp>  // for logging
// alternatively, to include all the standard APIs:
//  <dds/dds.hpp>
// or to include both the standard APIs and extensions:
//  <rti/rti.hpp>

#include "application.hpp"  // for command line parsing and ctrl-c
#include "version01.hpp"

void run_publisher_application(unsigned int domain_id, unsigned int sample_count){

    // Start communicating in a domain, usually one participant per application
    dds::domain::DomainParticipant participant_pub(domain_id);

    // Create the topics with a name and a datatype
    dds::topic::Topic<tele2vehicle::control_data> t2v_control_topic(participant_pub, "tele2vehicle_control_data");

    dds::topic::Topic<vehicle2tele::status_data> v2t_status_topic(participant_pub, "vehicle2tele_status_data");
    dds::topic::Topic<vehicle2tele::GPSlocation_data> v2t_GPS_topic(participant_pub, "vehicle2tele_GPSLocation_data");
    dds::topic::Topic<vehicle2tele::IMU_data> v2t_IMU_topic(participant_pub, "vehicle2tele_IMU_data");
    dds::topic::Topic<vehicle2tele::other_properties_data> v2t_op_topic(participant_pub, "vehicle2tele_other_properties_data");

    // Create a Publisher
    dds::pub::Publisher tele_publisher(participant_pub);
    dds::pub::Publisher vehicle_publisher(participant_pub);

    // Create a DataWriter with default QoS
    dds::pub::DataWriter<tele2vehicle::control_data> control_writer(tele_publisher, t2v_control_topic);

    dds::pub::DataWriter<vehicle2tele::status_data> status_writer(vehicle_publisher, v2t_status_topic);
    dds::pub::DataWriter<vehicle2tele::GPSlocation_data> GPS_writer(vehicle_publisher, v2t_GPS_topic);
    //dds::pub::DataWriter<vehicle2tele::IMU_data> IMU_writer(vehicle_publisher, v2t_IMU_topic);
    dds::pub::DataWriter<vehicle2tele::other_properties_data> op_writer(vehicle_publisher, v2t_op_topic);

    tele2vehicle::control_data control_data;
    
    vehicle2tele::status_data status_data;
    vehicle2tele::GPSlocation_data GPSlocation_data;
    //vehicle2tele::IMU_data IMU_data;
    vehicle2tele::other_properties_data op_data;
    
    // Main loop, write data
    for (unsigned int samples_written = 0; !application::shutdown_requested && samples_written < sample_count; samples_written++) {
        // Modify the data to be written here
        control_data.steering(static_cast<float>(samples_written));
        control_data.gear(static_cast<int32_t>(samples_written));
        control_data.acceleration(static_cast<float>(samples_written));
        control_data.brake(static_cast<float>(samples_written));
        control_data.additional_button1(static_cast<int32_t>(samples_written));
        
        std::cout << "Writing tele2vehicle::control_data, count " << samples_written << std::endl;
        control_writer.write(control_data);

        status_data.online(static_cast<bool>(samples_written));
        status_data.connected(static_cast<bool>(samples_written));

        std::cout << "Writing vehicle2tele::status_data, count " << samples_written << std::endl;
        status_writer.write(status_data);

        GPSlocation_data.latitude(static_cast<double>(samples_written));
        GPSlocation_data.longitude(static_cast<double>(samples_written));
        GPSlocation_data.altitude(static_cast<double>(samples_written));

        std::cout << "Writing vehicle2tele::GPSLocation_data, count " << samples_written << std::endl;
        GPS_writer.write(GPSlocation_data);

        /* This is a problem wating to be handled ... ... ... ... ... ... ... ... ...
        IMU_data.quaternion(static_cast<double>(samples_written));
        IMU_data.angular_velocity(static_cast<double>(samples_written));
        IMU_data.linear_acceleration(static_cast<double>(samples_written));

        std::cout << "Writing vehicle2tele::IMU_data, count " << samples_written << std::endl;
        IMU_writer.write(IMU_data);
        */

        op_data.steering_position(static_cast<double>(samples_written));
        op_data.speed(static_cast<double>(samples_written));
        op_data.indicators(static_cast<int32_t>(samples_written));
        op_data.gear(static_cast<int32_t>(samples_written));

        std::cout << "Writing vehicle2tele::other_properties_data, count " << samples_written << std::endl;
        op_writer.write(op_data);

        // Send once every second
        rti::util::sleep(dds::core::Duration(1));
    }
}

int main(int argc, char *argv[]){

    using namespace application;

    // Parse arguments and handle control-C
    auto arguments = parse_arguments(argc, argv);
    if (arguments.parse_result == ParseReturn::exit) {
        return EXIT_SUCCESS;
    } else if (arguments.parse_result == ParseReturn::failure) {
        return EXIT_FAILURE;
    }
    setup_signal_handlers();

    // Sets Connext verbosity to help debugging
    rti::config::Logger::instance().verbosity(arguments.verbosity);

    try {
        run_publisher_application(arguments.domain_id, arguments.sample_count);
    } catch (const std::exception& ex) {
        // This will catch DDS exceptions
        std::cerr << "Exception in run_publisher_application(): " << ex.what()
        << std::endl;
        return EXIT_FAILURE;
    }

    // Releases the memory used by the participant factory.  Optional at
    // application exit
    dds::domain::DomainParticipant::finalize_participant_factory();

    return EXIT_SUCCESS;
}
