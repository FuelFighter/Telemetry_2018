# Telemetry_2018
Here is the solution for the universal module that is passing can-data to the telemetry system. 

This very same UM might later be configured to also obtain and pass data from the strain sensors. SPI or I2C should be suitable for this. 

Note: The universal module drivers should be put in a seperate folder for increased smoothness. However, this can't be done right now as the "official" uart.c has incorrectly defined pins. 
