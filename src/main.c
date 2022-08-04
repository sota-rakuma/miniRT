#include "minirt.h"

int key_event(int key_code, void *param) {
    printf("key_code: %d\n", key_code);
    if (key_code == 65307)
        exit(0);
    return (0);
}

t_shape *compute_intersected_shape(t_world *world, t_vec3d to_screen) {
    t_vec3d camera_to_screen;
    t_shape *now_shape;
    t_shape *intersected_shape;
    double minimum_t;
    double t;

    camera_to_screen = vec3d_camera_to_screen(world->camera, to_screen);
    intersected_shape = NULL;
    minimum_t = -1;
    now_shape = world->shape_list;
    while (now_shape) {
        t = shape_get_intersection(camera_to_screen,
                                   vec3d_camera(world->camera), now_shape);
        if (t >= 1.0 && (intersected_shape == NULL || minimum_t > t)) {
            intersected_shape = now_shape;
            minimum_t = t;
        }
        now_shape = now_shape->next;
    }
    return intersected_shape;
}

t_color compute_ambient_light(t_world *world, t_shape *shape, t_light *light) {
    t_color ia = color_mult_num(light->color, light->intensity / 255.0);
    t_color radience_amb = color_mult_color(ia, shape->ka);
    return radience_amb;
}

t_vec3d compute_intersected_pos(t_camera *camera, t_vec3d to_screen,
                                t_shape *shape) {
    t_vec3d o_to_screen = vec3d_camera_to_screen(camera, to_screen);
    double t = shape_get_intersection(o_to_screen, camera->pos, shape);
    t_vec3d pos = vec3d_add(camera->pos, vec3d_mult(o_to_screen, t));
    return pos;
}

bool compute_is_shadow(t_world *world, t_shape *shape, t_light *light,
                       t_vec3d intersected_pos) {
    t_shape *now_shape = world->shape_list;
    t_vec3d int_to_light_dir = vec3d_sub(light->pos, intersected_pos);
    while (now_shape) {
        double t = shape_get_intersection(
            int_to_light_dir,
            vec3d_add(intersected_pos,
                      vec3d_mult(int_to_light_dir,
                                 0.000000001 / vec3d_length(int_to_light_dir))),
            now_shape);
        if (0.0 < t && t < 1.0)
            return true;
        now_shape = now_shape->next;
    }
    return false;
}

// t_color compute_specular(t_shape *shape, t_light *light) {

// }

// t_color compute_diffuse(t_shape *shape, t_light *light) {

// }

t_color compute_light(t_world *world, t_vec3d to_screen, t_shape *shape,
                      t_light *light) {
    t_color intensity = (t_color){0.0, 0.0, 0.0};

    // 交差位置: 球面上の点 P = O + tD
    t_vec3d intersected_pos =
        compute_intersected_pos(world->camera, to_screen, shape);
    t_vec3d o_to_screen = vec3d_camera_to_screen(world->camera, to_screen);
    // 付影処理
    if (compute_is_shadow(world, shape, light, intersected_pos)) {
        light = light->next;
        return (t_color){0.0, 0.0, 0.0};
    }
    t_vec3d pos_to_light_dir =
        vec3d_unit(vec3d_sub(light->pos, intersected_pos));
    t_vec3d normal = shape_normal_vec(shape, intersected_pos);
    // 視線ベクトルの逆単位ベクトルと法線ベクトルのなす角が90度以上なら逆に向ける
    // 視線ベクトルの逆単位ベクトル
    t_vec3d v = vec3d_unit(vec3d_mult(o_to_screen, -1.0));
    if (vec3d_dot(v, normal) <= 0.0) {
        normal = vec3d_mult(normal, -1.0);
    }
    t_color ii = color_mult_num(light->color, light->intensity / 255.0);
    // 拡散反射光 ----------------------------------------
    // vec3d_dot(入射ベクトル, 法線ベクトル) =
    // |入射ベクトル||法線ベクトル|cosA
    //  = 1 * 1 * cosA = cosA
    double cosA = double_max(0.0, vec3d_dot(pos_to_light_dir, normal));
    t_color radience_dif =
        color_mult_num(color_mult_color(shape->kd, ii), cosA);
    intensity = color_add_color(intensity, radience_dif);
    // 鏡面反射光 ----------------------------------------
    t_color radience_spe = (t_color){0.0, 0.0, 0.0};
    if (cosA > 0) {
        //正反射ベクトル
        t_vec3d r = vec3d_sub(vec3d_mult(normal, 2 * (cosA)), pos_to_light_dir);
        radience_spe = color_mult_num(
            color_mult_color(shape->ks, ii),
            pow(double_max(vec3d_dot(v, r), 0.0), shape->shininess));
    }
    intensity = color_add_color(intensity, radience_spe);
    return intensity;
}

t_color compute_brightness(t_world *world, t_vec3d to_screen, t_shape *shape) {
    t_color intensity = (t_color){0.0, 0.0, 0.0};
    t_color add_intensity;

    if (shape == NULL)
        return (t_color){0.0, 0.0, 0.0};
    t_light *now_light = world->light_list;
    while (now_light) {
        // 環境光
        if (now_light->kind == AMBIENT_LIGHT)
            add_intensity = compute_ambient_light(world, shape, now_light);
        // 点光源
        if (now_light->kind == LIGHT)
            add_intensity = compute_light(world, to_screen, shape, now_light);
        intensity = color_add_color(intensity, add_intensity);
        now_light = now_light->next;
    }
    return intensity;
}

t_color compute_color_of_pixel(t_world *world, t_vec3d to_screen) {
    t_vec3d o_to_screen = vec3d_camera_to_screen(world->camera, to_screen);
    t_shape *intersected_shape = compute_intersected_shape(world, to_screen);
    double minimum_t = shape_get_intersection(
        o_to_screen, vec3d_camera(world->camera), intersected_shape);
    if (intersected_shape == NULL)
        return world->bg;
    // 鏡か？
    // if (intersected_shape->is_mirror) {
    //     t_vec3d pos =
    //         vec3d_add(world->camera->pos, vec3d_mult(o_to_screen, minimum_t));
    //     t_color color = compute_mirror(world, intersected_shape, o_to_screen,
    //                                    minimum_t, 0, pos);
    //     return color;
    // }
    // 光の強度
    t_color intensity = compute_brightness(world, to_screen, intersected_shape);
    intensity = color_normalize(intensity);
    t_color screen_color = color_mult_num(intensity, 255.0);
    return screen_color;
}

int main(int argc, char *argv[]) {
    void *mlx = mlx_init();
    if (mlx == NULL) {
        printf("initialized mlx error\n");
        exit(0);
    }
    t_screen *screen = screen_init("miniRT");

    // ファイルをパース
    t_world *world = world_init(argv[1]);
    camera_set(world->camera);
    t_camera *camera = world->camera;

    long y;
    long x;
    y = 0;
    while (y < HEIGHT) {
        t_vec3d screen_p_yaxis = vec3d_add(
            camera->screen_start_pos,
            vec3d_mult(camera->screen_vertical_normal, camera->dy * (double)y));
        x = 0;
        while (x < WIDTH) {
            t_vec3d to_screen = vec3d_add(
                screen_p_yaxis, vec3d_mult(camera->screen_horizon_normal,
                                           camera->dx * (double)x));
            t_color color = compute_color_of_pixel(world, to_screen);
            img_pixel_put(screen->_img, x, y, convert_color(color));
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(screen->_mlx, screen->_win, screen->_img->_img, 0,
                            0);
    mlx_key_hook(screen->_win, key_event, NULL);
    mlx_loop(screen->_mlx);
    return (0);
}
