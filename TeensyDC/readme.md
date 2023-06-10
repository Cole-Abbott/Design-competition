Final Code for DSGN 360 Robot
=============================

The Robot needed to kick a soccer ball into a goal that was gaurded by a goalie.
Our robot used a laser to detect the goal, and a line sensor to detect the lines on the field.

The line sensor was a LED and a phototransistor inside of a 3d printed housing that was attached to the front of the robot.
It could detect the difference between the black lines and the white field, and would count how many lines it had passed 
to know how far from the ball it was. 

The laser was attached to a servo that would rotate the laser 180 degrees. The laser would detect the goal by seeing the
reflection off reflective tape that was placed on the goal using a phototransistor. The servo would rotate the laser back and forth, constantly updating the motor speeds to keep the robot on track to the goal.

Once the robot was close enough to the ball, it would kick the ball with a spring loaded kicker that was released by a servo.
Right before the kick, the robot would turn a little bit to aim around the goalie depending on where the goalie was detected. by the laser.

The robot was controlled by a Teensy 4.0 and powered by a 12v battery with a 5v regulator. It was made of laser cut acrylic and 3d printed parts.

All code can be found on GitHub at
https://github.com/Cole-Abbott/Design-competition/tree/main/TeensyDC 


![Image of Robot]()