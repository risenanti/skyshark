#!/usr/bin/python

# System Imports
import sys
sys.path.insert(0,"./externals/Navio2/Python") # TODO: Not this.
import time

# ROS Imports
import rospy
from std_msgs.msg import String

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
	pub = rospy.Publisher('barometer', String, queue_size=10)
	rospy.init_node('talker', anonymous=True)
	
	# Set update rate
	rate = rospy.Rate(10) # 10hz
	
	while not rospy.is_shutdown():
		# Refresh
		baro.refreshPressure();
		baro.refreshTemperature();
		
		# Wait for update to complete
		time.sleep(0.1)
		
		# Update internal values
		baro.readPressure()
		baro.readTemperature()
		
		# Process the data
		baro.calculatePressureAndTemperature()
		
		# Publish data as string, for now.
		data = "Temperature(C): %.6f" % (baro.TEMP), "Pressure(millibar): %.6f" % (baro.PRES), "Time: %s" % rospy.get_time()
		pub.publish(str(data))
		rate.sleep()

########################################################################

if __name__ == '__main__':
	try:
		publishBarometerData()
	except rospy.ROSInterruptException:
		pass
