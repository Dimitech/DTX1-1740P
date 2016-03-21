target remote localhost:2331
monitor speed 1000
monitor flash device = AT91SAM4S8B
monitor flash breakpoints = 1
monitor flash download = 1
monitor endian little
load out/DTX_1740P.elf
monitor reset 0
monitor sleep 10
break main
define rr
	monitor reset 2
end