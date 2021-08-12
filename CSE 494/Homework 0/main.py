# Take care of some of the imports we need
import numpy as np
import cv2
import os
from pyrep import PyRep
from pyrep.objects.vision_sensor import VisionSensor

# Defines a class that we use to communicate with the robot. 
class YouBot():
    def __init__(self):
        # Create a remote API
        self.pyrep = PyRep()

        # Attept to open CoppeliaSim 
        scene_path = os.getcwd() + "/robot.ttt"
        self.pyrep.launch(scene_path, headless=False)

    def _getCameraImage(self):
        # TODO: Add camera code
        rgb_obs = self.camera.capture_rgb()
        rgb_obs = (np.asarray(rgb_obs) * 255).astype(dtype=np.uint8)
        rgb_obs = np.flip(rgb_obs , (2))
        return  rgb_obs

    def _setTargetVelocity(self, vel_fwbw=0.0, vel_lr=0.0, vel_rot=0.0):
        # TODO: Add RPC call
        _, _, _, _ = self.pyrep.script_call(
            function_name_at_script_name="setTargetVelocity@script",
            script_handle_or_type =1,
            ints =[], floats =[vel_fwbw , vel_lr , vel_rot], strings =[], bytes=""
        )

    def _setRobotArmTargetJoint(self, joint_angles):
        # TODO: Add RPC call: Make sure to provide the angles in radiant 
        _, _, _, _= self.pyrep.script_call(
            function_name_at_script_name="setRobotArmTargetJoint@script",
            script_handle_or_type =1,
            ints =[], floats =joint_angles, strings =[], bytes=""
        )
    
    def _actuateGripper(self, g_open):
        # TODO: Add RPC call
        _, _, _, _ = self.pyrep.script_call(
            function_name_at_script_name="actuateGripper@script",
            script_handle_or_type =1,
            ints =g_open, floats =[], strings =[], bytes=""
        )

    def shutdown(self):
        self.pyrep.shutdown()
   
    def runSimulator(self):
        # Start the simulation
        self.pyrep.start()
        
        # Define our vision sensor
        self.camera = VisionSensor("kinect_rgb")        

        # Track if we are done with our simulation
        done        = False
        
        # Global simulation step
        step        = 0 

        # Simulate for one timestep (50ms) until we are done
        while not done:
            # Advance the simulation step counter by one
            step       += 1
            # Actually advance the simulation by one step
            self.pyrep.step()            
            # Grab the image from our camera sensor
            image = self._getCameraImage()

            # Allow the simulator to run for a few steps to stabilize physics before doing our actual code
            # This is useful to let objects settle and initialize the camera steam from our vision sensor.
            if step <= 5:
                continue

            # TODO: Add the code for your assignment here
            self._setTargetVelocity(2.0,2.0,2.0)
            self._setRobotArmTargetJoint([0.1,0.2,0.3,0.4,0.5])
            self._actuateGripper([0])

            # For now, we will run the simulation for 5 seconds and then quit 
            # (The simulation runs with 20 steps per second by default)
            if step > 20*5:
                done = True

         
        self.pyrep.stop()

# Main entry for the code
if __name__ == "__main__":
    # Create the robot wrapper
    robot = YouBot()
    # Run the simulation until it is done
    robot.runSimulator()
    # Shutdown the simulator (Close CoppeliaSim)
    robot.shutdown()
