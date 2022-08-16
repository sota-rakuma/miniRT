#!/bin/bash

test() {
    input="$1"
    len=$(( $(tput cols) - $(echo $input | wc -c) - 7 ))

    echo -n case "[$input]"
    for i in $(seq 1 $len)
    do
        echo -n "-"
    done
    echo
    ./miniRT rtfiles/$input
    echo
}

test all_objects.rt
test cylinder.rt
test cylinder_multiple.rt
test diffuse_sphere.rt
test glitch1.rt
test glitch2.rt
test glitch3.rt
test inner_cylinder.rt
test inner_sphere.rt
test light_v_plane.rt
test mix.rt
test plane.rt
test plane_multiple.rt
test plane_reverse.rt
test specular_sphere.rt
test sphere.rt
test sphere_multiple.rt
test triangle.rt
test testrt/fov180_inner_cylinder_horizontal.rt
test testrt/fov180_inner_cylinder_vertical.rt
test testrt/sphere.rt
test testrt/sphere_0_0_0.rt
test testrt/sphere_0_0_10.rt
test testrt/sphere_0_10_0.rt
test testrt/sphere_0_10_10.rt
test testrt/sphere_10_0_0.rt
test testrt/sphere_10_0_10.rt
test testrt/sphere_10_10_0.rt

 test invalid_rtfiles/empty.rt
 test invalid_rtfiles/excess_comma.rt
 test invalid_rtfiles/excess_scalar.rt
 test invalid_rtfiles/excess_string.rt
 test invalid_rtfiles/excess_vector.rt
 test invalid_rtfiles/invalid_colors_ambient.rt
 test invalid_rtfiles/invalid_colors_cylinder.rt
 test invalid_rtfiles/invalid_colors_light.rt
 test invalid_rtfiles/invalid_colors_plane.rt
 test invalid_rtfiles/invalid_colors_sphere.rt
 test invalid_rtfiles/invalid_fov_camera.rt
 test invalid_rtfiles/invalid_normalized_camera.rt
 test invalid_rtfiles/invalid_normalized_cylinder.rt
 test invalid_rtfiles/invalid_normalized_plane.rt
 test invalid_rtfiles/invalid_ratio_ambient.rt
 test invalid_rtfiles/invalid_ratio_light.rt
 test invalid_rtfiles/multiple_ambient.rt
 test invalid_rtfiles/multiple_camera.rt
 test invalid_rtfiles/multiple_light.rt
 test invalid_rtfiles/no_ambient.rt
 test invalid_rtfiles/no_camera.rt
 test invalid_rtfiles/no_light.rt
 test invalid_rtfiles/unexpected_id.rt
 test invalid_rtfiles/vector_additional_component.rt
 test invalid_rtfiles/vector_blank_component.rt
 test invalid_rtfiles/vector_commas.rt
 test invalid_rtfiles/vector_spaceless.rt
