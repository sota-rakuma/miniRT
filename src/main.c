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

    // 視点の位置を決める
    t_camera *camera = world->camera;

    // 背景
    t_color bg = world->bg;

    // スクリーン上の点
    t_vec3d to_screen;

    // 交差判定をする関数ポインタの配列
    // double (*shape_get_intersection[])() = {with_sphere, with_plane,
    // with_cylinder};

    // forで回す
    long y;
    long x;

    y = 0;
    while (y < HEIGHT) {
        t_vec3d screen_p_yaxis = vec3d_add(
            camera->screen_start_pos,
            vec3d_mult(camera->screen_vertical_normal, camera->dy * (double)y));
        x = 0;
        while (x < WIDTH) {
            to_screen = vec3d_add(screen_p_yaxis,
                                  vec3d_mult(camera->screen_horizon_normal,
                                             camera->dx * (double)x));
            // カメラから一番近いshapeを取得する--------------------------
            // 視線ベクトル
            t_vec3d o_to_screen =
                vec3d_camera_to_screen(world->camera, to_screen);
            t_shape *intersected_shape =
                compute_intersected_shape(world, to_screen);
            double minimum_t = shape_get_intersection(
                o_to_screen, vec3d_camera(world->camera), intersected_shape);

            // // 鏡か？
            // if (intersected_shape && intersected_shape->is_mirror)
            // {
            //     // printf("mirror\n");
            //     t_vec3d pos = vec3d_add(world->camera->pos,
            //     vec3d_mult(o_to_screen, minimum_t)); t_color color =
            //     compute_mirror(world, intersected_shape, o_to_screen,
            //     minimum_t, 0, pos);
            //     // printf("color{%.4f, %.4f, %.4f}\n", color.r, color.g,
            //     color.b); img_pixel_put(screen->_img, x, y,
            //     convert_color(color)); x++; continue;
            // }

            // 光の強度
            t_color intensity = (t_color){0.0, 0.0, 0.0};

            if (intersected_shape) {
                t_light *now_light = world->light_list;
                while (now_light) {
                    // 環境光
                    if (now_light->kind == AMBIENT_LIGHT)
                        intensity = color_add_color(
                            intensity,
                            compute_ambient_light(world, intersected_shape,
                                                  now_light));
                    // 点光源
                    if (now_light->kind == LIGHT) {
                        // 交差位置: 球面上の点 P = O + tD
                        t_vec3d int_pos = vec3d_add(
                            camera->pos, vec3d_mult(o_to_screen, minimum_t));

                        // 付影処理
                        if (compute_is_shadow(world, intersected_shape,
                                              now_light, int_pos)) {
                            now_light = now_light->next;
                            continue;
                        }

                        // 入射ベクトル: 点光源 - 交差位置
                        //  -> 単位ベクトル
                        t_vec3d light_dir = vec3d_sub(now_light->pos, int_pos);
                        light_dir = vec3d_mult(light_dir,
                                               1.0 / vec3d_length(light_dir));

                        t_vec3d normal;
                        // 法線ベクトル[球]     : 交差位置(球面上の点) - 球中心
                        // 法線ベクトル[平面]   : t_shapeの要素
                        //  -> 単位ベクトル
                        if (intersected_shape->kind == SPHERE)
                            normal =
                                vec3d_sub(int_pos, intersected_shape->center);
                        else if (intersected_shape->kind == PLANE)
                            normal = intersected_shape->oriental_normal;
                        else if (intersected_shape->kind == CYLINDER) {
                            normal = vec3d_cross(
                                vec3d_sub(int_pos, intersected_shape->center),
                                intersected_shape->oriental_normal);
                            normal = vec3d_cross(
                                intersected_shape->oriental_normal, normal);
                        }
                        // 視線ベクトルの逆単位ベクトルと法線ベクトルのなす角が90度以上なら逆に向ける
                        // 視線ベクトルの逆単位ベクトル
                        t_vec3d v =
                            vec3d_mult(o_to_screen,
                                       -1.0 * 1.0 / vec3d_length(o_to_screen));
                        if (vec3d_dot(v, normal) <= 0.0) {
                            normal = vec3d_mult(normal, -1.0);
                        }
                        normal = vec3d_mult(normal, 1.0 / vec3d_length(normal));

                        t_color ii = color_mult_num(
                            now_light->color, now_light->intensity / 255.0);

                        // 拡散反射光 ----------------------------------------
                        // vec3d_dot(入射ベクトル, 法線ベクトル) =
                        // |入射ベクトル||法線ベクトル|cosA
                        //  = 1 * 1 * cosA = cosA
                        double cosA = vec3d_dot(light_dir, normal);
                        cosA = cosA >= 0 ? cosA : 0.0;
                        t_color radience_dif = color_mult_num(
                            color_mult_color(intersected_shape->kd, ii), cosA);
                        intensity = color_add_color(intensity, radience_dif);

                        // 鏡面反射光 ----------------------------------------
                        t_color radience_spe = (t_color){0.0, 0.0, 0.0};
                        if (cosA > 0) {
                            //正反射ベクトル
                            t_vec3d r = vec3d_sub(
                                vec3d_mult(normal, 2 * (cosA)), light_dir);
                            // 視線ベクトルの逆単位ベクトル
                            // t_vec3d v = vec3d_mult(
                            //    o_to_screen, -1.0 * 1.0 /
                            //    vec3d_length(o_to_screen));
                            // 視線ベクトルの逆単位ベクトルと正反射ベクトルの内積
                            double v_dot_r = vec3d_dot(v, r);
                            v_dot_r = v_dot_r >= 0 ? v_dot_r : 0.0;
                            radience_spe = color_mult_num(
                                color_mult_color(intersected_shape->ks, ii),
                                pow(v_dot_r, intersected_shape->shininess));
                        }
                        intensity = color_add_color(intensity, radience_spe);
                    }
                    now_light = now_light->next;
                }
            }

            // [0, 1]に収める
            intensity = color_normalize(intensity);

            t_color screen_color;
            if (intersected_shape) {
                screen_color = color_mult_num(intensity, 255.0);
            } else {
                screen_color = bg;
            }
            img_pixel_put(screen->_img, x, y, convert_color(screen_color));
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
