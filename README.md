<p align="center">
  <img src="_assets/image/car.png" width="175">
</p>

# carOS

**Car Operating System**

[![Patreon](https://img.shields.io/badge/Support-Patreon-051D34?logo=patreon&logoColor=white)](https://www.patreon.com/lozoya)
[![Buy Me A Coffee](https://img.shields.io/badge/Donate-Buy%20Me%20A%20Coffee-FFDD00?logo=buymeacoffee&logoColor=white)](https://www.buymeacoffee.com/clozoya172b)
[![Ko-fi](https://img.shields.io/badge/Tip-Ko%E2%80%91fi-FF5E5B?logo=kofi&logoColor=white)](https://ko-fi.com/lozoya)
![License](https://img.shields.io/badge/license-AGPL--3.0-blue)

A lightweight operating system in C for automotive Electronic Control Units (ECUs).  
This project is focused on building a certifiable, vehicle-grade real-time kernel and supporting platform services.

---

# Introduction

This project is designed as a generic, extensible operating system that provides a stable core while exposing clear
interfaces to hardware. The operating system defines the overall structure and common services, while the user supplies
the logic that connects those interfaces to specific devices.

A few complete examples are provided to show how typical hardware can be integrated, but the design ensures that modules
can be swapped out or extended without altering the core. Hardware differences are handled entirely through the
interface layer, keeping the system consistent and portable.

The goal is to create a framework-style operating system: stable at its core, adaptable at its boundaries, and capable
of interfacing with any hardware through well-defined extension points.

---

## 1. Scope

Development begins with a single ECU domain to enable fast iteration:

- **Body Control (lights/locks/windows)**  
  Low risk, ideal for MVP (Minimum Viable Product).
    - **Lighting:** headlights, taillights, interior lights, indicators.
    - **Locks:** central locking, keyless entry, trunk release.
    - **Windows & mirrors:** power windows, mirror adjustment, defrost.
    - **Comfort features:** wipers, seat heating, HVAC fan relays.

- **Powertrain (engine/inverter)**  
  Hard real-time, higher Automotive Safety Integrity Level (ASIL).
    - **Engine control:** ignition timing, fuel injection, throttle-by-wire.
    - **Transmission / drivetrain:** gear shifting, clutch control.
    - **Hybrid/EV inverter:** motor drive, regenerative braking.
    - **Torque management:** traction control, stability interaction.

- **ADAS Gateway / Sensor Fusion**  
  High bandwidth and security heavy.
    - **Sensor fusion:** combine radar, camera, lidar, ultrasonic.
    - **Driver assistance:** adaptive cruise, lane keeping, emergency braking.
    - **Networking:** high-bandwidth Automotive Ethernet, time sync (PTP).
    - **Gateway:** firewalling, secure routing between ECUs.
    - **Security-critical paths:** intrusion detection, secure boot enforcement.

---

## 2. Architecture

Implemented entirely in C. Options under evaluation:

- **Bare-metal RTOS kernel (OSEK/VDX-style)**  
  Fixed-priority preemptive scheduler, static config, tiny footprint.
- **Time-triggered executive**  
  Cyclic schedule, no runtime allocation, ultra-predictable (ASIL-D).
- **Microkernel with MPU protection**  
  Task isolation with modest complexity.
- **AUTOSAR Classic-like stack**  
  Industry-style components (COM, Diagnostic, NVRAM, OS).

---

## 3. Kernel Feature Set

- **Scheduling:** Fixed-priority preemptive; optional rate-monotonic analysis; tickless timer.
- **Interrupts:** Bounded latency, short ISRs, defer work to tasks.
- **Synchronization:** Priority-inheritance mutexes, event flags, message queues.
- **Memory:** Static allocation only; no heap after init; optional MPU regions per task.
- **Timing:** Monotonic system clock; high-res timers for deadlines and periods.

---

## 4. Platform Services

### Communication

- CAN / CAN-FD, LIN, FlexRay, Automotive Ethernet (+ DMA).
- ISO-TP, UDS (Unified Diagnostic Services), J1939, SOME/IP.

### Diagnostics & Health

- DTC (Diagnostic Trouble Codes), OBD-II, watchdogs, brown-out detection, self-tests.

### NVRAM

- Journaling flash manager with CRC, wear leveling, and power-loss tolerance.

### Security

- Secure boot, image authentication, crypto HAL, key storage, anti-replay.

### OTA / Reprogramming

- Dual-bank firmware, authenticated updates, rollback support.

### Other

- Time sync (PTP, CAN time master).
- Power states (ignition/ACC/off, graceful shutdown).

---

## 5. Safety & Process

- **ISO 26262:** Hazard analysis, ASIL assignment, safety mechanisms, traceability.
- **Coding Standard:** MISRA C:2012 (+ Amendments); deterministic control flow, no runtime allocation.
- **Static Analysis:** PC-lint, Cppcheck, Coverity.
- **Timing Analysis:** WCET per task/ISR, measured on hardware.
- **Verification & Validation:** SIL, HIL, fault injection, robustness testing.

---

## 6. Hardware Targets

- **Preferred MCUs:** Infineon AURIX, NXP S32K/S32R, Renesas RH850, STM32 (Cortex-M7/M33).
- **Desired peripherals:** Multiple CAN/CAN-FD, Ethernet MAC with TSN, ECC RAM/Flash, MPU.

---

## 7. Deliverables (Phased)

- **Phase 0 – Board Bring-up**  
  BSP: clock tree, MPU, startup.s, linker script, SysTick/GPT, GPIO, UART.
- **Phase 1 – Kernel**  
  Task control blocks, ready queues, context switch, ISRs, mutex/PI, timers.
- **Phase 2 – Communication Drivers**  
  CAN/LIN, DMA-based UART/SPI/I2C, ISO-TP, UDS, basic DTC.
- **Phase 3 – Safety & Persistence**  
  Watchdogs, brown-out handling, CRC, NVRAM manager.
- **Phase 4 – Security & Updates**  
  Secure boot, image layout, dual-bank updater, rollback, key ladder/HSM.
- **Phase 5 – Vehicle Applications**  
  Periodic control tasks, deadline monitoring, diagnostics hooks.

---

## 8. Toolchain & CI

- **Compiler:** Vendor toolchains or GCC; warnings as errors.
- **Build System:** Make or CMake; output: binary + map + size + reports.
- **CI:** Static analysis, unit tests (Ceedling/Unity), MISRA checks, code coverage, smoke tests.
- **Tracing:** ITM/ETM/SWO or vendor trace tools; binary logs preferred over `printf`.

---

## 9. Design Guidelines

- Keep ISR work minimal; defer to tasks.
- No malloc/free after init; pre-allocate all pools.
- Validate all bus frames (length, counters, plausibility).
- Add deadline monitors per task; drop to safe state on overruns.
- Separate config (tables) from code (kernel/services).

---

## 10. First Milestone

- Board bring-up + kernel with 3 priorities and round-robin.
- CAN loopback test: periodic TX task, RX ISR → queue → parser task.
- Watchdog serviced by low-priority task; overrun injection causes reset.
- Minimal UDS “ReadDataByIdentifier” responding with build hash from NVRAM.
- Flash journal storing config blob with CRC; prove atomicity under power loss.

---

# Acronym glossary

| Acronym     | Definition                                                                                 |
|:------------|--------------------------------------------------------------------------------------------|
| ADAS        | Advanced Driver-Assistance Systems                                                         |
| ASIL        | Automotive Safety Integrity Level (ISO 26262 risk level)                                   |
| AUTOSAR     | Automotive Open System Architecture (industry standard)                                    |
| BSP         | Board Support Package                                                                      |
| CAN/CAN-FD  | (Controller Area Network / Flexible Data-Rate) in-vehicle bus                              |
| CRC         | Cyclic Redundancy Check                                                                    |
| DTC         | Diagnostic Trouble Code                                                                    |
| ECU         | Electronic Control Unit                                                                    |
| EDF         | Earliest Deadline First (scheduling)                                                       |
| EEPROM      | Electrically Erasable Programmable Read-Only Memory                                        |
| ETM/ITM/SWO | Embedded/Instrumentation Trace Macrocell / Serial Wire Output                              |
| FLASH/NVRAM | Non-Volatile RAM (e.g., Flash/EEPROM)                                                      |
| HIL/SIL     | Hardware-/Software-in-the-Loop                                                             |
| HSM         | Hardware Security Module                                                                   |
| ISO-TP      | ISO Transport Protocol (on CAN)                                                            |
| LIN         | Local Interconnect Network                                                                 |
| MC/DC       | Modified Condition/Decision Coverage                                                       |
| MCU         | Microcontroller Unit                                                                       |
| MISRA C     | Motor Industry Software Reliability Association C rules                                    |
| MPU/MMU     | Memory/Memory-Management Unit                                                              |
| OBD-II      | On-Board Diagnostics II                                                                    |
| OSEK/VDX    | Open Systems & the Corresponding Interfaces for Automotive Electronics (vehicle RTOS spec) |
| OTA         | Over-the-Air (firmware updates)                                                            |
| PTP         | Precision Time Protocol                                                                    |
| RT/RTOS     | Real-Time / Real-Time Operating System                                                     |
| SOME/IP     | Scalable service-Oriented Middleware over IP                                               |
| TSN         | Time-Sensitive Networking                                                                  |
| UDS         | Unified Diagnostic Services (ISO 14229)                                                    |
| WCET        | Worst-Case Execution Time                                                                  |

# Project Structure

```
car-os-c/
├─ app/ # Application tasks & state machines
│ ├─ app_main.c
│ ├─ app_tasks.c/h
│ ├─ app_state.c/h
│ ├─ app_power.c/h
│ └─ app_diagnostics.c/h
├─ os/ # Kernel + static configuration
│ ├─ kernel/
│ │ ├─ os_kernel.c/h # init/start, tick hook
│ │ ├─ os_sched.c/h # scheduler
│ │ ├─ os_task.c/h # task API/TCB
│ │ ├─ os_mutex.c/h # priority inheritance mutex
│ │ ├─ os_event.c/h # event flags
│ │ ├─ os_queue.c/h # message queues
│ │ ├─ os_timer.c/h # timers (tick/tickless)
│ │ └─ os_isr.c/h # ISR deferral glue
│ └─ config/
│ ├─ os_config.h # priorities, periods, stack sizes
│ ├─ board.h # board/MCU selection
│ ├─ toolchain.h # compiler attrs / diag
│ ├─ linker.ld # (placeholder for MCU)
│ └─ startup.s # (placeholder vectors/startup)
├─ platform/ # MCU-specific support
│ ├─ bsp/ # clocks, MPU, NVIC/interrupts
│ │ ├─ bsp_init.c/h
│ │ ├─ clocks.c/h
│ │ ├─ mpu.c/h
│ │ └─ interrupts.c/h
│ ├─ drivers/ # HALs
│ │ ├─ can.c/h uart.c/h timer.c/h
│ │ ├─ spi.c/h i2c.c/h eth.c/h
│ │ ├─ flash.c/h gpio.c/h watchdog.c/h
│ ├─ diag/ # diagnostics stacks
│ │ ├─ isotp.c/h uds.c/h
│ │ ├─ dtc.c/h obd.c/h
│ │ └─ health.c/h
│ ├─ nv/ # persistence
│ │ ├─ nv_storage.c/h
│ │ ├─ crc.c/h
│ │ └─ journal.c/h
│ └─ security/ # secure boot / crypto HAL
│ ├─ secure_boot.c/h
│ └─ crypto_hal.c/h
├─ network/
│ ├─ can/
│ │ ├─ can_stack.c/h # higher-layer CAN plumbing
│ │ └─ j1939.c/h # (optional)
│ └─ eth/
│ ├─ someip.c/h
│ └─ ptp.c/h # time sync
├─ tests/
│ ├─ unit/ # host unit tests (Unity/Ceedling-ready)
│ └─ hil/ # hardware-in-the-loop harness
├─ tools/
│ └─ scripts/ # codegen, static-analysis configs
├─ docs/
│ ├─ STRUCTURE.md
│ ├─ CODING.md
│ └─ SAFETY.md
├─ build/ # build artifacts
└─ Makefile # host stub: `make` builds ./build/car_os
```

---

## Support This Work

Open source engineering takes a lot of time and coffee. If you would like to directly support ongoing research, development, and maintenance of these tools, you can do so here:

[![Patreon](https://img.shields.io/badge/Support-Patreon-051D34?logo=patreon&logoColor=white)](https://www.patreon.com/lozoya)

[![Buy Me A Coffee](https://img.shields.io/badge/Donate-Buy%20Me%20A%20Coffee-FFDD00?logo=buymeacoffee&logoColor=white)](https://www.buymeacoffee.com/clozoya172b)

[![Ko-fi](https://img.shields.io/badge/Tip-Ko%E2%80%91fi-FF5E5B?logo=kofi&logoColor=white)](https://ko-fi.com/lozoya)

Your support helps keep the project healthy and moving forward.

---

## License

This project is licensed under the GNU Affero General Public License v3.0 (AGPL-3.0). Any modified version made available to users over a network must also be released under the AGPL-3.0. See the LICENSE file for full details.

![License](https://img.shields.io/badge/license-AGPL--3.0-blue)

---


