#!/bin/bash

CENTER_X=500
CENTER_Y=1000
RADIUS=200
STEPS=60      # More steps = smoother circle
DURATION=10   # ms for each swipe

for ((i=0; i<$STEPS; i++)); do
    theta1=$(echo "2 * 3.14159 * $i / $STEPS" | bc -l)
    theta2=$(echo "2 * 3.14159 * ($i + 1) / $STEPS" | bc -l)

    x1=$(echo "$CENTER_X + $RADIUS * c($theta1)" | bc -l | awk '{printf "%d", $0}')
    y1=$(echo "$CENTER_Y + $RADIUS * s($theta1)" | bc -l | awk '{printf "%d", $0}')
    x2=$(echo "$CENTER_X + $RADIUS * c($theta2)" | bc -l | awk '{printf "%d", $0}')
    y2=$(echo "$CENTER_Y + $RADIUS * s($theta2)" | bc -l | awk '{printf "%d", $0}')

    adb shell input swipe $x1 $y1 $x2 $y2 $DURATION
done

