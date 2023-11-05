#pragma once

/*

 - 8 bit data bus
 - nRD nWR signals
 - C/nD command/data
 - nCE chip enable
 - RST reset
 - FNT font select 8x8 6x8
 - VSS-VO-VEE contrast voltage 10K pot

 func
 - after power on reset is required #10
 - the ext RAM can store text/graph/ ext CG-RAM
 - before read/write must perform status check #13
 - without status check lcd can not operate normally even with delay #14
 - first set data then command #15 (max 2 data)
 >- how does read work?
 - offset reg is external CG-RAM address
 - ade addr pointer to read/write RAM
 - there is auto inc read/write mode #26 that has to be disabled manually
 - in non auto it is possible to inc/dec/nochange the address (cmd is necessary for every byte)





 */
