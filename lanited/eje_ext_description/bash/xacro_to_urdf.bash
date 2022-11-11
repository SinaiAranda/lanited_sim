#!/bin/bash


source devel/setup.bash
rosrun xacro xacro --inorder -o eje_ext.urdf src/celda/eje_ext_description/urdf/eje_ext.urdf.xacro
