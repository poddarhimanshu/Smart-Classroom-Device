## Synopsis

A device that automatically handles the power loads in a classroom based on the class timings, room temperature, incoming sunlight and if turns off the load if the
classroom is unoccupied.

### Timing based load management

Here we have demonstrated loads in the classroom in the form of the 2 light bulbs that you see in the video, lets say for demonstration purpose, the
white light that you see is fan and the yellow light that you see are the lights of the classroom here.

Now our class generally starts at 8:00 AM, and goes until 10:00AM with a short break after that. Then second session starts from 10:30 AM to 1:00PM with a 
lunch break after that and then the third session starts at 1:30PM which goes until 3:30PM.

The loads in the classroom would turn off at the end of these sessions on working days.
One question would be what if the students remain in class even during these breaks?

Well the answer is the loads will still turn off, in this case students would have to turn on the loads manually. The main objective of this device is to save energy.

Now when students come to class they turn on the loads. 
When we approach the next lunch break interval, we expect the loads to turn off automatically at 18:10:10 

Now say the third session started, and when the classes gets over the loads are again supposed to be turned off. 

### Sunlight Intensity

Now keeping in mind about the fact that there are more windows area than brick covered walls in the class, so sunlight is sometimes pretty 
sufficient and lights beside the window infact has no use. So based on the value of intensity of sunlight we turn off the lights.

### Temperature 
Now if you see Bengaluru weather, at one time you will feel like its a sunny day and in the next hour clouds cover the sky, or temperature goes down or 
it may even start raining but in this class duration of 8hours does someone bothers to turn off the fans? NO right!

Our sensor would detect the temperature of the room and soon as the temperature goes down below certain threshold it turns off the fans in the room. 
But for us it was not really possible to demonstrate by lowering the temperature, however what we really can do is increase the temperature and show you the 
readings and take decisions accordingly.

So for demonstration purpose in the video you can see we are using the hot light bulb to increase temperature of the surrounding, 
so when we brought the hot light bulb closer to our sensor so that temperature keeps increasing and when we reach a certain threshold, 
the fans(which is denoted by the white bulb here) will turn off.

### Motion Sensing
Now sometimes, we have labs or seminars or combined classes in the hall due to which we might need to leave the class during the class hours. 
And what if someone forgets to turn off the loads during that time?

Here comes our motion sensors in the picture, it will start a timer for 10minutes, if in the 10minutes it does not see any movement in the room it will turn off 
the all the loads in the room.

To demonstrate this in the video, we have set the timer to 15seconds, and if in 30s it does not find any movement the lights and fans represented by our yellow light
and white light will turn off.

## Working of the Device 

You can find the video of the working of the device here : https://www.youtube.com/watch?v=1cCko9BJsG8

## Code Files

The main code file for the project can be found here : Smart Classroom\kalpana.ino
