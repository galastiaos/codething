#!/bin/bash

CENTER_X=500
CENTER_Y=1000
RADIUS=200
STEPS=36  # More steps = smoother circle
DELAY=15  # ms between segments

for ((i=0; i<$STEPS; i++)); do
    angle1=$(echo "scale=6; 2*3.1415926*$i/$STEPS" | bc -l)
    angle2=$(echo "scale=6; 2*3.1415926*($i+1)/$STEPS" | bc -l)

    x1=$(echo "$CENTER_X + $RADIUS * c($angle1)" | bc -l | awk '{printf "%d", $0}')
    y1=$(echo "$CENTER_Y + $RADIUS * s($angle1)" | bc -l | awk '{printf "%d", $0}')
    x2=$(echo "$CENTER_X + $RADIUS * c($angle2)" | bc -l | awk '{printf "%d", $0}')
    y2=$(echo "$CENTER_Y + $RADIUS * s($angle2)" | bc -l | awk '{printf "%d", $0}')

    adb shell input swipe $x1 $y1 $x2 $y2 $DELAY
done

