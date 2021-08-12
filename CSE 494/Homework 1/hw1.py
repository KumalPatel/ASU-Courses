##################################################
# Homework 1, CSE 494
# Spring 2021, Dr. Heni Ben Amor
# @author Michael Drolet
# This file is used to command the Pioneer robot
# in CoppeliaSim and provide an interfaces for
# applying simple vector properties for robot
# control.
##################################################
# STUDENT NAME: Kumal Patel
# ASU ID: 1208493243
##################################################

import numpy as np
import cv2
import os
from pyrep import PyRep
import time
import math


# Simple 2D Vector class for CoppeliaSim objects
class Vector2D():
    def __init__(self, vector=[0,0]):
        self.x = vector[0]
        self.y = vector[1]

    def add(self, vec):
        return Vector2D([self.x + vec.x, self.y + vec.y])

    @staticmethod # This should be used as a static method!
    def sub(vec1, vec2):
        return Vector2D([vec1.x - vec2.x, vec1.y - vec2.y])

    def limit(self, scalar):
        if (self.x * self.x + self.y * self.y) > scalar * scalar:
            self.normalize()
            self.mult(scalar)

        return Vector2D([self.x, self.y])

    def normalize(self):
        self.x = self.x / self.magnitude()
        self.y = self.y / self.magnitude()

    def mult(self, scalar):
        self.x = self.x * scalar
        self.y = self.y * scalar

        return Vector2D([self.x, self.y])

    def magnitude(self):
        return math.sqrt((self.x * self.x) + (self.y * self.y))


# Defines a class that we use to communicate with the robot
# and execute homework problems
class Vehicle():
    def __init__(self):
        # Create a remote API
        self.pyrep = PyRep()

        # Attept to open CoppeliaSim
        scene_path = os.getcwd() + "/hw1_scene.ttt"
        self.pyrep.launch(scene_path, headless=False)
        time.sleep(0.5)
        self.pyrep.start()

        # maximum speed/force parameters
        self.max_speed = 2.0
        self.max_force = 1.0

    # Returns an array of the following object:
    # [location_vector, radius_of_cylinder]
    # type(location_vector) = Vector2D
    # type(radius_of_cylinder) = float
    def getObstacles(self):
        ints,floats,strings,byte = self.pyrep.script_call(function_name_at_script_name="getObstacles@script",
                                script_handle_or_type=1,
                                ints=(),
                                floats=(),
                                strings=(),
                                bytes ="")

        obstacles = []
        for i in range(int(len(floats)/3)):
            loc = Vector2D([floats[i*3], floats[i*3 +1]])
            obstacles.append([loc, floats[i*3 +2]])

        return obstacles

    # Returns a Vector2D specifying the location of the desired target from the origin
    def getTarget(self, target):
        if target == 'WP1':
            target_type = 1
        elif target == 'WP2':
            target_type = 2
        elif target == 'WP3':
            target_type = 3
        elif target == 'Home':
            target_type = 4
        elif target == 'PM':
            target_type = 5
        elif target == 'OF1':
            target_type = 6
        elif target == 'OF2':
            target_type = 7
        elif target == 'OF3':
            target_type = 8
        else:
            print('Invalid target name! (Look at the CoppeliaSim scene graph for valid names)')
            target_type = 0

        ints,floats,strings,byte = self.pyrep.script_call(function_name_at_script_name="getTarget@script",
                                script_handle_or_type=1,
                                ints=(),
                                floats=([target_type]),
                                strings=(),
                                bytes ="")

        return Vector2D([floats[0], floats[1]])

    # Get the location (as a Vector2D) of the pioneer robot
    def getLocation(self):
        ints,floats,strings,byte = self.pyrep.script_call(function_name_at_script_name="getLocation@script",
                                script_handle_or_type=1,
                                ints=(),
                                floats=(),
                                strings=(),
                                bytes ="")

        return Vector2D([floats[0], floats[1]])

    # Shutdown PyRep
    def shutdown(self):
        self.pyrep.shutdown()

    # Get the velocity (as a Vector2D) of the pioneer robot
    def getVelocity(self):
        ints,floats,strings,byte = self.pyrep.script_call(function_name_at_script_name="getVelocity@script",
                                script_handle_or_type=1,
                                ints=(),
                                floats=(),
                                strings=(),
                                bytes ="")

        return Vector2D([floats[0], floats[1]])

    # Apply a force vector to the pioneer robot
    def applyForce(self, vec2D):
        self.pyrep.script_call("applyForce@script",
                                1,
                                ints=(),
                                floats=([vec2D.x, vec2D.y]),
                                strings=(),
                                bytes ="")
        self.pyrep.step()

    # Seek the desired target (input Vector2D)
    # Utilize the 'options' keyword at your discretion
    # (i.e, options='arrival' to stop at target)
    def seek(self, target, options='default'):
        if options == 'seek':
            location = self.getLocation()
            velocity = self.getVelocity()
            desired = Vector2D.sub(target, location)
            distance = float(desired.magnitude())
            desired.normalize()    
            desired.mult(self.max_speed)
            steer = Vector2D.sub(desired, velocity)
            steer.limit(self.max_force)
            self.applyForce(steer) 

            return distance

        elif options == 'arrival':
            location = self.getLocation()
            velocity = self.getVelocity()
            desired = Vector2D.sub(target, location)
            distance = float(desired.magnitude())
            desired.normalize()
            
            if distance < 100:
                magnitude = self.map(distance, 0, 100, 0, self.max_speed)
                desired.mult(magnitude)
            else:
                desired.mult(self.max_speed)
        
            steer = Vector2D.sub(desired, velocity)
            steer.limit(self.max_force)
            self.applyForce(steer)

            return distance

    # Arrive to the Pitchers Mound (aka Blue Disc or 'PM' target)
    # Then return back to Home ('Home')
    def executeProblem1(self):
        target = self.getTarget('PM')
        dist = self.seek(target, 'arrival')

        while int(dist) != 0: 
            target = self.getTarget('PM')
            dist = self.seek(target, 'arrival')

        target = self.getTarget('Home')
        dist = self.seek(target, 'arrival')

        while int(dist) != 0:
            target = self.getTarget('Home')
            dist = self.seek(target, 'arrival')
 

    # Round the bases! Use Path Following to navigate through the waypoints:
    # First base ('WP1'), Second base ('WP2'), Third base ('WP3'), and then Home ('Home')
    def executeProblem2(self):
        target = self.getTarget('WP1')
        dist = self.seek(target, 'seek')
        
        while int(dist) != 0:
            target = self.getTarget('WP1')
            dist = self.seek(target, 'seek')

        target = self.getTarget('WP2')
        dist = self.seek(target, 'seek')

        while int(dist) != 0:
            target = self.getTarget('WP2')
            dist = self.seek(target, 'seek')

        target = self.getTarget('WP3')
        dist = self.seek(target, 'seek')

        while int(dist) != 0:
            target = self.getTarget('WP3')
            dist = self.seek(target, 'seek')

        target = self.getTarget('Home')
        dist = self.seek(target, 'seek')

        while int(dist) != 0:
            target = self.getTarget('Home')
            dist = self.seek(target, 'seek')


    # Implement Obstacle Avoidance by traveling to
    # Left Field ('OF1'), then Center Field ('OF2'), and then Right Field ('OF3')
    # Then return back to Home plate
    def executeProblem3(self):
        obstacles = self.getObstacles()
        
        print(obstacles[0][0].x)
        print(obstacles[0][0].y)

        target = self.getTarget('OF1')
        dist = self.seek(target, 'seek')
        
        while int(dist) != 0:
            target = self.getTarget('OF1')
            dist = self.seek(target, 'seek')

        target = self.getTarget('OF2')
        dist = self.seek(target, 'seek')

        while int(dist) != 0:
            target = self.getTarget('OF2')
            dist = self.seek(target, 'seek')

        target = self.getTarget('OF3')
        dist = self.seek(target, 'seek')

        while int(dist) != 0:
            target = self.getTarget('OF3')
            dist = self.seek(target, 'seek')

        target = self.getTarget('Home')
        dist = self.seek(target, 'seek')

        while int(dist) != 0:
            target = self.getTarget('Home')
            dist = self.seek(target, 'seek')


    # Implement the Wander algorithm
    # Note the grid size is 75x75:
    # (X: -37.5 to 37.5), (Y: -37.5 to 37.5)
    def executeProblem4(self):
        # TODO: Your Code Here
        return None

    def map(self, input, inputMin, inputMax, outputMin, outputMax):
        return (input-inputMin)*(outputMax-outputMin)/(inputMax-inputMin)+outputMax

# Main entry for the code
if __name__ == "__main__":
    # Create the robot wrapper
    pioneer = Vehicle()
    pioneer.executeProblem1() # Seek and Arrival
    pioneer.executeProblem2() # Path Following
    pioneer.executeProblem3() # Obstacle Avoidance
    pioneer.executeProblem4() # Wander
    pioneer.shutdown()
