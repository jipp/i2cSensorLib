numberLed = 16;
circleRadius = 30;
ledHeight = 1;
ledLength = 6;
ringHeight = 2;

displayLength = 15;
displayWidth = 27;
displayHeight = 2;
displayPCBLength = 28;
displayPCBWidth = 28;
displayPCBHeight = 1;

$fn = 90;

module ring()
{
    translate([0, 0, ledHeight]) difference()
    {
        cylinder(h = ringHeight, r = circleRadius+ledLength/2+2);
        cylinder(h = ringHeight, r = circleRadius-ledLength/2-2);
    }

    for (i = [0:360/numberLed:360]) 
        rotate([0, 0, i]) translate([0, circleRadius, ledHeight/2]) cube([ledLength, ledLength, ledHeight], true);
}

module display()
{
    union()
    {
        translate([0, 0, displayHeight/2]) cube([displayWidth, displayLength, displayHeight], true);
        translate([0, -2, displayHeight/2+displayPCBHeight/2]) cube([displayPCBWidth, displayPCBLength, displayPCBHeight], true);
    }
}

module displayHolder()
{
    difference()
    {
        translate([0, -2, displayHeight/2+displayPCBHeight/2]) cube([displayPCBWidth+1, displayPCBLength+1, displayPCBHeight*3], true);
        translate([0, -2, displayHeight/2+displayPCBHeight/2]) cube([displayPCBWidth, displayPCBLength, displayPCBHeight*3], true);
    }
}

height = 1;

difference()
{
    translate([0, 0, height/2]) cube([80, 80, height], true);
    ring();
    display();
}

displayHolder();
