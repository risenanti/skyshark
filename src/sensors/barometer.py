#!/usr/bin/python

# System Imports
import sys
sys.path.insert(0,"./externals/Navio2/Python") # TODO: Not this.
import time

# ROS Imports
import rospy
from std_msgs.msg import Header
from sensor_msgs.msg import Temperature
from sensor_msgs.msg import FluidPressure

# Navio Imports
import navio.ms5611
import navio.util

########################################################################

# TODO: What this do?
navio.util.check_apm()

# Initialize Barometer
baro = navio.ms5611.MS5611()
baro.initialize()

def publishBarometerData():
	airPressurePub = rospy.Publisher('air_pressure', FluidPressure, queue_size=10)
	temperaturePub = rospy.Publisher('barometer_temperature', Temperature, queue_size=10)
	rospy.init_node('barometer_publisher', anonymous=True)
	
	# Set update rate, in Hz
	rate = rospy.Rate(10)

	while not rospy.is_shutdown():
		# Pressure
		baro.refreshPressure()
		time.sleep(0.1)
		baro.readPressure()
		
		# Temperature
		baro.refreshTemperature()
		time.sleep(0.1)
		baro.readTemperature()
		
		# Process the data
		baro.calculatePressureAndTemperature()
		
		# Generate Header
		header = Header()
		header.stamp = rospy.Time.now()
		
		# Generate Message (Temperature)
		temperatureMsg = Temperature()
		temperatureMsg.header = header
		temperatureMsg.temperature = baro.TEMP
		temperaturePub.publish(temperatureMsg)
		
		# Generate message and publish (Pressure)
		airPressureMsg = FluidPressure()
		airPressureMsg.header = header
		airPressureMsg.fluid_pressure = baro.PRES * 100
		airPressurePub.publish(airPressureMsg)
		
		# Sleep
		rate.sleep()

########################################################################

if __name__ == '__main__':
	try:
		publishBarometerData()
	except rospy.ROSInterruptException:
		pass
