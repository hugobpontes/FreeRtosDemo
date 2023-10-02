# FreeRtosDemo
FreeRTOS demo using my FreeRTOS STM32 f7x port

I wanted to freshen up on FreeRTOS and since I made a fork of FreeRTOS specifically for stm32f7x microcontrollers I thought a companion project might help anyone (including myself in the future) wanting to use.
This demo uses trice (https://github.com/rokath/trice/) for tracing. It won't work directly on your side, but hopefully reading documentation on that repository and seeing the examples will make it clear enough. It also uses lwrb as a submodule

All this demo is is 3 dummy tasks + trace task + dummy logger task. 
- The three tasks simulate data producers, and they are triggered periodically by waiting for event flags and semaphores, and they all write to the same log buffer (in a mutex protected way) and post a message to a logger queue informing it of what they wrote on the buffer
- The dummy logging task waits to receive a message on its inbox queue and sees how many bytes it must read from its buffer and who the data is from, then traces it but in reality it would write to to a serial port or sd card.
- The trace task is essential for the trice library to work, see documentation on (trice (https://github.com/rokath/trice/)

Feel free to ask any questions
