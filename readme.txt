This code was designed for newtonian mehanics final project in National
University of Colombia newtonian mechanics course for the 2020-2 period.

For compiling, you have to put in the command line the uncertainty of your
measurement instruments (half of the apreciation) for example if our executable
file is called a.out, then for compiling and not getting a segmentation fault,
we have to put-in the executable file followed of the uncertainty for high and
shadow object you used to measure the shadow, this followed of the uncertainty
for length of your pendulum, followed of the uncertainty for your period
measurements. In our case, it looks like the following, in the linux terminal:

./a.out 0.0005 0.0005 0.0005

With uncertaninty given in mks (International system of units)

The console will display some averaged quantities like average radius, average
corrected radius and average gravity, as well as the input values for you
to verificate, and the final Erath's mass.
