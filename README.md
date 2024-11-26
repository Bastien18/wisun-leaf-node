# wisun-leaf-node

The Wi-SUN nanostack provides the necessary code for routers node. However there's no code to program a leaf node on MBED-OS yet. In the nanostack source files there's "placeholder" for the leaf node part but nothing is implemented.

The goal now is to complete those "placeholder" with the corresponding code and implement the correct behaviour of a leaf node.

## Work done so far

### Bootstraping

The bootstraping part for leaf node in the nanostack is handled by functions defined in the [ws_bootstrap_6ln.c](./mbed-os/connectivity/nanostack/sal-stack-nanostack/source/6LoWPAN/ws/ws_bootstrap_6ln.c). Most of the functions needed aren't implemented yet. All the necessary code had been, first, copied from the [ws_bootstrap_6lr.c](./mbed-os/connectivity/nanostack/sal-stack-nanostack/source/6LoWPAN/ws/ws_bootstrap_6lr.c). Here is the list of added functions:

- ws_bootstrap_6ln_start_discovery
- ws_bootstrap_6ln_network_discovery_configure
- ws_bootstrap_6ln_start_discovery
- ws_bootstrap_6ln_start_configuration_learn
- ws_bootstrap_6ln_rpl_callback
- ws_bootstrap_6ln_rpl_prefix_callback
- ws_bootstrap_6ln_rpl_new_parent_callback
- ws_bootstrap_6ln_rpl_parent_dis_callback
- ws_bootstrap_6ln_rpl_scan_start
- ws_bootstrap_6ln_ip_stack_addr_clear
- ws_bootstrap_6ln_fhss_configure
- ws_bootstrap_6ln_ip_stack_addr_clear
- ws_bootstrap_6ln_set_fhss_hop
- ws_bootstrap_6ln_rank_get
- ws_bootstrap_6ln_get_rpl_instance
- ws_bootstrap_6ln_min_rank_inc_get
- ws_bootstrap_6ln_parent_confirm
- ws_bootstrap_6ln_address_update
- ws_bootstrap_6ln_address_registration_update
- ws_bootstrap_6ln_rpl_candidate_soft_filtering
- ws_bootstrap_6ln_asynch_ind
- ws_bootstrap_6ln_pan_advertisement_analyse
- ws_bootstrap_6ln_pan_information_store
- ws_bootstrap_6ln_pan_advertisement_analyse_active
- ws_bootstrap_6ln_pan_advertisement_solicit_analyse
- ws_bootstrap_6ln_pan_config_analyse
- ws_bootstrap_6ln_pan_config_lfn_analyze
- ws_bootstrap_6ln_pan_config_solicit_analyse
- ws_bootstrap_6ln_network_scan_process
- ws_bootstrap_6ln_configure_process
- ws_bootstrap_6ln_network_configuration_learn
- ws_bootstrap_6ln_rpl_wait_process
- ws_bootstrap_6ln_primary_parent_update
- ws_bootstrap_6ln_secondary_parent_update

Features already strip down from copied router functions are:

Enable of dhcp relay:

```
tr_debug("Enable DHCPv6 relay");

dhcp_relay_agent_enable(cur->id, dodag_info.dodag_id);
```

Sending DIS msg when no DIO heard:

```
else if (!rpl_control_have_dodag(cur->rpl_domain))

{

// RPL not ready send DIS message if possible

if (cur->bootsrap_mode == ARM_NWK_BOOTSRAP_MODE_6LoWPAN_ROUTER)

{

// TODO Multicast DIS should be sent only if no DIO heard for some time

rpl_control_transmit_dis(cur->rpl_domain, cur, 0, 0, NULL, 0, ADDR_LINK_LOCAL_ALL_RPL_NODES);

}

// set timer for next DIS

cur->bootsrap_state_machine_cnt = randLIB_get_random_in_range(WS_RPL_DIS_TIMEOUT / 2, WS_RPL_DIS_TIMEOUT);

}
```

Those features have been removed from the functions in [ws_bootstrap_6ln.c](./mbed-os/connectivity/nanostack/sal-stack-nanostack/source/6LoWPAN/ws/ws_bootstrap_6ln.c) file.

In order to use the nanostack correctly the macro ```"mbed-mesh-api.wisun-device-type" : "MESH_DEVICE_TYPE_WISUN_LEAF_NODE"``` must be defined in the [mbed_app.json](./mbed_app.json) file.

Now the device is able to pass bootstrap sequence and connect itself to the mesh network.

### Making device deep sleep

The purpose of a leaf node is to be very low power consuming. Deep sleep mode ensure a current consumption of a few uA on the platform.

Previous tests with deepsleep have been performed on the stm32f769i discovery kit platform. A function, ```sleep_manager_can_deep_sleep```, tells us if the device can actualy deepsleep by checking if no standard us timer are currently in use.

To be sure that the device is actually in deepsleep mode, we started using the EFR32FG25 radio board. It's possible to track actual current consumption of the board with the simplicity studio software.

In order to track global current consumption, user must switch R210 resistor to R211 resistor placeholder.

The main issue now is located during the init phase of the mesh. During this phase a standard us timer is used in [arm_hal_timer.cpp](./mbed-os/connectivity/nanostack/nanostack-hal-mbed-cmsis-rtos/arm_hal_timer.cpp). To let the device deepsleep the goal is to replace this us timer with a low power timer.

## Next step

Making the device sleep when is waiting during the init phase.

Making the device sleep when is connected to the mesh and is not receiving message from router nodes.

Sending periodically DAO message to the border router to avoid being kicked out the mesh network.