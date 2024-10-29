/**
 * @file main.cpp
 * @author Yann Charbon <yann.charbon@heig-vd.ch>, <yann.charbon@ik.me>
 * @brief System entry point.
 * @version 1.0
 * @date 2022-10-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "mbed.h"
#include "Thread.h"
#include "NanostackInterface.h"
#include "EthernetInterface.h"
#include "mbed-trace/mbed_trace.h"

#include "PinNames.h"

#define TRACE_GROUP "APP"

#ifdef EFR32_BETECH
DigitalOut oscillator39MhzEnable(OSC_CC_EN);
#endif


void trace_printer(const char* str) {
    printf("%s\n", str);
}

static Mutex SerialOutMutex;

void serial_out_mutex_wait()
{
    SerialOutMutex.lock();
}

void serial_out_mutex_release()
{
    SerialOutMutex.unlock();
}

MeshInterface *mesh ;

#ifdef EFR32_CUSTOM_BOARD
DigitalOut enableVCOM(ENABLE_VCOM);
#endif


int main()
{
#ifdef EFR32_CUSTOM_BOARD
    enableVCOM.write(1);
#endif

#ifdef EFR32_BETECH
    oscillator39MhzEnable = 0;
#endif
    bool can_deep = sleep_manager_can_deep_sleep();
    printf("Deep sleep allowed: %i\r\n", can_deep);

    mbed_trace_init();
    mbed_trace_print_function_set(trace_printer);
    mbed_trace_mutex_wait_function_set( serial_out_mutex_wait );
    mbed_trace_mutex_release_function_set( serial_out_mutex_release );

    /* *** Head over to user application *** */
    mesh = MeshInterface::get_default_instance();
    if (!mesh) {
        printf("Error! MeshInterface not found!\n");
        return -1;
    }

    printf("Connecting to the mesh...\n");
    int error = mesh->connect();
    if (error) {
        printf("Connection failed! %d\n", error);
        return error;
    }

    SocketAddress sockAddr;
    while (NSAPI_ERROR_OK != mesh->get_ip_address(&sockAddr))
        ThisThread::sleep_for(500ms);

    printf("Connected. IP = %s\n", sockAddr.get_ip_address());

    //mts_framework_send_user_event(MTS_WISUN_STATE_CONNECTED, (void*)sockAddr.get_ip_address(), strlen(sockAddr.get_ip_address()) + 1);

    while (1) {
        ThisThread::sleep_for(40s);
    }
}
